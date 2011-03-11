#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "TopWindowsItem.h"
#include "UIA/Client.h"
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
  client->initialize();
}

MainWindow::~MainWindow()
{
  delete client;
  delete ui;
}

void MainWindow::logMessage(const QString& message)
{
  qDebug() << message;
  ui->logArea->appendPlainText(message);
}

void MainWindow::analyzeSelectedWindow()
{
  QList<QListWidgetItem*> selected = ui->topWindows->selectedItems();
  if ( selected.size() != 1 )
    return;

  TopWindowsItem* window = (TopWindowsItem*) selected.first();
  QString title = window->getElement()->getName();
  logMessage("To analyze: " + title);
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
