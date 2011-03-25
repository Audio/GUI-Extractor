#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "UIA/Element.h"
#include "ElementTreeItem.h"
#include "TopWindowsItem.h"
#include <QtGui/QCloseEvent>
#include <QtGui/QMainWindow>


namespace Ui {
  class MainWindow;
}

class Client;

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget* parent = 0);
  ~MainWindow();

public slots:
  void logMessage(const QString& message);

protected slots:
  void closeEvent(QCloseEvent* event);

private slots:
  Element* getSelectedTopLevelWindow() const;
  void analyzeSelectedWindow();
  void addToTreeIncludingChildren(Element* element, ElementTreeItem* parent = 0);

  void highlightSelectedWindow();
  void highlightSelectedElement();
  void createHighlightWindow(Element* element);

  void loadTopLevelWindows();

  bool highlightWindows() const;
  bool highlightElements() const;

private:
  Ui::MainWindow* ui;
  Client* client;
};

#endif // MAINWINDOW_H
