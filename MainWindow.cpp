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

void MainWindow::analyzeSelectedWindow()
{
  QList<QListWidgetItem*> selected = ui->topWindows->selectedItems();
  if ( !selected.size() ) {
    logMessage("No window has been selected for analysis");
    return;
  }

  ui->elementTree->clear();

  Element* element = ((TopWindowsItem*) selected.first())->getElement();
  logMessage("Analyzing: " + element->getName() );

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

void MainWindow::loadTopLevelWindows()
{
  ui->topWindows->clear();
  QList<Element*> windows = client->topLevelWindows();
  foreach(Element* window, windows) {
    TopWindowsItem* item = new TopWindowsItem(ui->topWindows, window);
    ui->topWindows->addItem(item);
  }
}
