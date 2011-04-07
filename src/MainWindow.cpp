#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "UIA/Client.h"
#include "Highlighter.h"
#include "XUL/Exporter.h"
#include <QtCore/QtDebug>
#include <QtCore/QTime>
#include <QtGui/QColorDialog>
#include <QtGui/QFileDialog>
#include <QtGui/QMessageBox>


MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent), ui(new Ui::MainWindow), analyzedWindow(NULL)
{
  ui->setupUi(this);
  ui->elementTree->setColumnWidth(0, 250);
  setupUiConnections();

  setWindowFlags(Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);

  client = new Client();
  connect(client, SIGNAL( eventHappened(const QString&, Log::Type) ), SLOT( logMessage(const QString&, Log::Type) ));
  client->init();
}

void MainWindow::setupUiConnections()
{
  connect(ui->actionQuit, SIGNAL( triggered() ), qApp, SLOT( quit() ));

  connect(ui->buttonReload, SIGNAL( pressed() ), SLOT( loadTopLevelWindows() ));
  connect(ui->actionReloadWindowList, SIGNAL( triggered() ), SLOT( loadTopLevelWindows() ));

  connect(ui->buttonAnalyze, SIGNAL( pressed() ), SLOT( analyzeSelectedWindow() ));
  connect(ui->actionSelectedWindow, SIGNAL( triggered() ), SLOT( analyzeSelectedWindow() ));

  connect(ui->actionExportXUL, SIGNAL( triggered() ), SLOT( exportXUL() ));

  connect(ui->topWindows, SIGNAL( itemSelectionChanged() ), SLOT( highlightSelectedWindow() ));
  connect(ui->elementTree, SIGNAL( itemSelectionChanged() ), SLOT( highlightSelectedElement() ));

  connect(ui->actionEnableHighlighting, SIGNAL( toggled(bool) ), SLOT( highlightingEnabledChanged(bool) ));
  connect(ui->actionSelectHighlightingColor, SIGNAL( triggered() ), SLOT( setHighlightingColor() ));
}

MainWindow::~MainWindow()
{
  disconnect(client, 0, 0, 0);
  delete ui;
  delete client;
}

void MainWindow::logMessage(const QString& message, Log::Type logType)
{
  QString time = "[" + QTime::currentTime().toString("HH:mm:ss") + "] ";
  qDebug() << time + message;

  QString color = colorBaseOnLogType(logType);
  QString formattedMessage = time + "<span style=\"color:" + color + "\">" + message + "</span>";
  ui->logArea->append(formattedMessage);
}

void MainWindow::closeEvent(QCloseEvent* event)
{
  Highlighter::hideActive();
  event->accept();
}

bool MainWindow::isThisApplication(Element* element)
{
  UIA_HWND elementId;
  element->getUIAElement()->get_CurrentNativeWindowHandle(&elementId);
  return winId() == elementId;
}

Element* MainWindow::getSelectedTopLevelWindow() const
{
  QList<QTreeWidgetItem*> selected = ui->topWindows->selectedItems();
  return ( selected.size() ) ? ((TopWindowsItem*) selected.first())->getElement()
                             : NULL;
}

Element* MainWindow::getSelectedElement() const
{
  QList<QTreeWidgetItem*> selected = ui->elementTree->selectedItems();
  return ( selected.size() ) ? ((ElementTreeItem*) selected.first())->getElement()
                             : NULL;
}

void MainWindow::analyzeSelectedWindow()
{
  Element* element = getSelectedTopLevelWindow();
  if (!element)
    return logMessage( tr("No window has been selected for analysis"), Log::WARNING);

  logMessage( tr("Analyzing: ") + element->getName() );
  ui->elementTree->clear();

  QList<Element*> children = client->getImmediateChildren(element);
  foreach(Element* child, children)
    addToTreeIncludingChildren(child);

  analyzedWindow = element;
}

void MainWindow::addToTreeIncludingChildren(Element* element, ElementTreeItem* parent)
{
  ElementTreeItem* item = (parent) ? new ElementTreeItem(parent, element)
                                   : new ElementTreeItem(ui->elementTree, element);

  QList<Element*> children = client->getImmediateChildren(element);
  foreach(Element* child, children)
    addToTreeIncludingChildren(child, item);
}

void MainWindow::highlightSelectedWindow()
{
  highlightIfEnabled( getSelectedTopLevelWindow() );
}

void MainWindow::highlightSelectedElement()
{
  highlightIfEnabled( getSelectedElement() );
}

void MainWindow::highlightIfEnabled(Element* element)
{
  if ( highlightingEnabled() && element ) {
    bool valid;
    ElementArea area = element->getArea(valid);
    if (valid) {
      Highlighter::highlight(area);
      activateWindow();
    }
  }
}

void MainWindow::loadTopLevelWindows()
{
  ui->topWindows->clear();
  QList<Element*> windows = client->topLevelWindows();
  foreach(Element* window, windows) {
    if ( !isThisApplication(window) )
      new TopWindowsItem(ui->topWindows, window);
  }
}

bool MainWindow::highlightingEnabled() const
{
  return ui->actionEnableHighlighting->isChecked();
}

void MainWindow::highlightingEnabledChanged(bool enabled)
{
  if (!enabled)
    Highlighter::hideActive();
  else if ( ui->topWindows->hasFocus() )
    highlightSelectedWindow();
  else if( ui->elementTree->hasFocus() )
    highlightSelectedElement();
}

void MainWindow::setHighlightingColor()
{
  QColor current = Highlighter::getColor();
  QColor color = QColorDialog::getColor(current, this);
  if ( color.isValid() )
    Highlighter::setColor(color);
}

void MainWindow::exportXUL()
{
  if (!analyzedWindow)
    return logMessage( tr("Nothing to export: an analysis must be done before exporting anything."), Log::WARNING);

  if ( analyzedWindow->isOffScreen() ) {
    logMessage( tr("Warning: exporting hidden window can lead to unpredicteable results."), Log::WARNING);
    QString warn = tr("Selected windows is hidden. This can lead to unpredicteable results. Do you really want to run analysis for that window?");
    int button = QMessageBox::warning(this, tr("Hidden application"), warn, tr("Continue"), tr("Abort"), QString(), 1);
    if (button != 0)
      return;
  }

  QString filename = QFileDialog::getSaveFileName(this, tr("Export in XUL format"), QString(), tr("XUL files (*.xul)") );
  if ( filename.isEmpty() )
    return;

  XUL::Exporter ex(analyzedWindow, ui->elementTree);
  connect(&ex, SIGNAL( eventHappened(const QString&, Log::Type)), SLOT( logMessage(const QString&, Log::Type) ));
  ex.save(filename);
  disconnect(&ex, 0, 0, 0);
}

QString MainWindow::colorBaseOnLogType(Log::Type logType) const
{
  switch (logType) {
    case Log::WARNING: return "red";
    default: return "black";
  }
}
