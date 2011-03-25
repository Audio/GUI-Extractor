#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "UIA/Client.h"
#include "Highlighter.h"
#include <QtCore/QtDebug>


MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent), ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  ui->elementTree->setColumnWidth(0, 300);

  setWindowFlags(Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);

  connect(ui->actionQuit, SIGNAL( triggered() ), qApp, SLOT( quit() ));
  connect(ui->buttonReload, SIGNAL( pressed() ), SLOT( loadTopLevelWindows() ));
  connect(ui->buttonAnalyze, SIGNAL( pressed() ), SLOT( analyzeSelectedWindow() ));
  connect(ui->topWindows, SIGNAL( itemSelectionChanged() ), SLOT( highlightSelectedWindow() ));
  connect(ui->elementTree, SIGNAL( itemSelectionChanged() ), SLOT( highlightSelectedElement() ));

  client = new Client();
  connect(client, SIGNAL( error(const QString&) ), SLOT( logMessage(const QString&) ));
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

Element* MainWindow::getSelectedTopLevelWindow() const
{
  QList<QListWidgetItem*> selected = ui->topWindows->selectedItems();
  return ( selected.size() ) ? ((TopWindowsItem*) selected.first())->getElement()
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
  if ( highlightWindows() ) {
    QList<QListWidgetItem*> items = ui->topWindows->selectedItems();
    if ( items.size() ) {
      TopWindowsItem* item = (TopWindowsItem*) items.first();
      createHighlightWindow( item->getElement() );
    }
  }
}

void MainWindow::highlightSelectedElement()
{
  if ( highlightElements() ) {
    QList<QTreeWidgetItem*> items = ui->elementTree->selectedItems();
    if ( items.size() ) {
      ElementTreeItem* item = (ElementTreeItem*) items.first();
      createHighlightWindow( item->getElement() );
    }
  }
}

void MainWindow::createHighlightWindow(Element* element)
{
  const ElementArea* area = element->getArea();
  if (area) {
    Highlighter::highlight(area);
    activateWindow();
  }
}

void MainWindow::loadTopLevelWindows()
{
  ui->topWindows->clear();
  QList<Element*> windows = client->topLevelWindows();
  foreach(Element* window, windows) {
    TopWindowsItem* item = new TopWindowsItem(ui->topWindows, window);
    ui->topWindows->addItem(item);
  }
}

bool MainWindow::highlightWindows() const
{
  return ui->highlightWindows->isChecked();
}

bool MainWindow::highlightElements() const
{
  return ui->highlightElements->isChecked();
}
