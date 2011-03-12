#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "UIA/Client.h"
#include "TopWindowsItem.h"
#include <QtCore/QtDebug>


MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent), ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  setWindowFlags(Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);

  connect(ui->actionQuit, SIGNAL( triggered() ), qApp, SLOT( quit() ));
  connect(ui->buttonReload, SIGNAL( pressed() ), SLOT( loadTopLevelWindows() ));
  connect(ui->buttonAnalyze, SIGNAL( pressed() ), SLOT( analyzeSelectedWindow() ));
  connect(ui->buttonHighlight, SIGNAL( pressed() ), SLOT( highlightSelectedWindow() ));

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
  Element* element = getSelectedTopLevelWindow();
  if (!element)
    return logMessage("No window has been selected to be highlighted");

  element->highlight();
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
