#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "UIA/Client.h"
#include "Highlighter.h"
#include <QtCore/QtDebug>
#include <QtGui/QColorDialog>


MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent), ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  ui->elementTree->setColumnWidth(0, 250);
  setupUiConnections();

  setWindowFlags(Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);

  client = new Client();
  connect(client, SIGNAL( error(const QString&) ), SLOT( logMessage(const QString&) ));
}

void MainWindow::setupUiConnections()
{
  connect(ui->actionQuit, SIGNAL( triggered() ), qApp, SLOT( quit() ));

  connect(ui->buttonReload, SIGNAL( pressed() ), SLOT( loadTopLevelWindows() ));
  connect(ui->actionReloadWindowList, SIGNAL( triggered() ), SLOT( loadTopLevelWindows() ));

  connect(ui->buttonAnalyze, SIGNAL( pressed() ), SLOT( analyzeSelectedWindow() ));
  connect(ui->actionSelectedWindow, SIGNAL( triggered() ), SLOT( analyzeSelectedWindow() ));

  connect(ui->topWindows, SIGNAL( itemSelectionChanged() ), SLOT( highlightSelectedWindow() ));
  connect(ui->elementTree, SIGNAL( itemSelectionChanged() ), SLOT( highlightSelectedElement() ));

  connect(ui->actionSelectHighlightingColor, SIGNAL( triggered() ), SLOT( setHighlightingColor() ));
}

MainWindow::~MainWindow()
{
  disconnect(client, 0, 0, 0);
  delete ui;
  delete client;
}

void MainWindow::logMessage(const QString& message)
{
  qDebug() << message;
  ui->logArea->appendPlainText(message);
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
    return logMessage("No window has been selected for analysis");

  logMessage("Analyzing: " + element->getName() );
  ui->elementTree->clear();

  QList<Element*> children = client->getImmediateChildren(element);
  foreach(Element* child, children)
    addToTreeIncludingChildren(child);
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
    const ElementArea* area = element->getArea();
    if (area) {
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

void MainWindow::setHighlightingColor()
{
  QColor current = Highlighter::getColor();
  QColor color = QColorDialog::getColor(current, this);
  if ( color.isValid() )
    Highlighter::setColor(color);
}
