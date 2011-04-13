#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "UIA/Client.h"
#include "Highlighter.h"
#include "AboutDialog.h"
#include <QtCore/QtDebug>
#include <QtCore/QTime>
#include <QtGui/QColorDialog>
#include <QtGui/QFileDialog>
#include <QtGui/QMessageBox>


MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent), ui(new Ui::MainWindow), analyzedWindow(NULL), xulExp(NULL)
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
  connect(ui->topWindows, SIGNAL( itemSelectionChanged() ), SLOT( enableDisableAnalysis() ));
  connect(ui->elementTree, SIGNAL( itemSelectionChanged() ), SLOT( highlightSelectedElement() ));

  connect(ui->actionEnableHighlighting, SIGNAL( toggled(bool) ), SLOT( highlightingEnabledChanged(bool) ));
  connect(ui->actionSelectHighlightingColor, SIGNAL( triggered() ), SLOT( setHighlightingColor() ));

  connect(ui->actionAbout, SIGNAL( triggered() ), SLOT( displayAboutDialog() ));
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

void MainWindow::enableDisableAnalysis()
{
  bool selected = getSelectedTopLevelWindow() != NULL;
  ui->actionSelectedWindow->setEnabled(selected);
  ui->buttonAnalyze->setEnabled(selected);
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
  logMessage( tr("Analyzing: ") + element->getName() );
  ui->elementTree->clear();

  QList<Element*> children = client->getImmediateChildren(element);
  foreach(Element* child, children)
    addToTreeIncludingChildren(child);

  analyzedWindow = element;
  ui->actionExportXUL->setEnabled(true);
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
  ui->actionSelectedWindow->setEnabled(true);
  ui->buttonAnalyze->setEnabled(true);
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
  ui->elementTree->clear();
  ui->actionExportXUL->setEnabled(false);
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
  if ( analyzedWindow->isOffScreen() ) {
    logMessage( tr("Warning: exporting hidden window can lead to unpredicteable results."), Log::WARNING);
    QString warn = tr("Selected windows is hidden. This can lead to unpredicteable results. Do you really want to run analysis for that window?");
    int button = QMessageBox::warning(this, tr("Hidden application"), warn, tr("Continue"), tr("Abort"), QString(), 1);
    if (button != 0)
      return;
  }

  if (xulExp)
    return logMessage( tr("XUL export: already exporting!"), Log::WARNING);

  QString filename = QFileDialog::getSaveFileName(this, tr("Export in XUL format"), QString(), tr("XUL files (*.xul)") );
  if ( filename.isEmpty() )
    return;

  xulExp = new XUL::Exporter(analyzedWindow, ui->elementTree, client);
  connect(xulExp, SIGNAL( eventHappened(const QString&, Log::Type)), SLOT( logMessage(const QString&, Log::Type) ));
  xulExp->save(filename);
}

void MainWindow::exportXULComplete()
{
  disconnect(xulExp, 0, 0, 0);
  delete xulExp;
  xulExp = NULL;
}

QString MainWindow::colorBaseOnLogType(Log::Type logType) const
{
  switch (logType) {
    case Log::WARNING: return "red";
    default: return "black";
  }
}

void MainWindow::displayAboutDialog()
{
  AboutDialog* d = new AboutDialog(this);
  d->setModal(true);
  d->setFixedSize(400, 200);
  d->show();
}
