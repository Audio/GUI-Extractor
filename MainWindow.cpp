#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "UIA/Client.h"
#include "Highlighter.h"
#include <QtCore/QtDebug>


MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent), ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  ui->topWindows->setMouseTracking(true);
  ui->elementTree->setMouseTracking(true);
  ui->elementTree->setColumnWidth(0, 300);

  setWindowFlags(Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);

  connect(ui->actionQuit, SIGNAL( triggered() ), qApp, SLOT( quit() ));
  connect(ui->buttonReload, SIGNAL( pressed() ), SLOT( loadTopLevelWindows() ));
  connect(ui->buttonAnalyze, SIGNAL( pressed() ), SLOT( analyzeSelectedWindow() ));
  connect(ui->topWindows, SIGNAL( itemEntered(QListWidgetItem*) ), SLOT( highlightSelectedWindow(QListWidgetItem*) ));
  connect(ui->elementTree, SIGNAL( itemEntered(QTreeWidgetItem*, int) ), SLOT( highlightSelectedElement(QTreeWidgetItem*) ));

  client = new Client();
  connect(client, SIGNAL( error(const QString&) ), SLOT( logMessage(const QString&) ));
}

MainWindow::~MainWindow()
{
  Highlighter::hideActive();
  disconnect(client, 0, 0, 0);

  delete ui;
  delete client;
}

void MainWindow::logMessage(const QString& message)
{
  qDebug() << message;
  ui->logArea->appendPlainText(message);
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

void MainWindow::highlightSelectedWindow(QListWidgetItem* item)
{
  if ( highlightWindows() ) {
    Element* element = ((TopWindowsItem*) item)->getElement();
    Highlighter::highlight(element);
  }
}

void MainWindow::highlightSelectedElement(QTreeWidgetItem* item)
{
  if ( highlightElements() ) {
    Element* element = ((ElementTreeItem*) item)->getElement();
    Highlighter::highlight(element);
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
