#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "UIA/Element.h"
#include "XUL/Exporter.h"
#include "ElementTreeItem.h"
#include "TopWindowsItem.h"
#include "LogType.h"
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
  void logMessage(const QString& message, Log::Type logType = Log::NORMAL);

protected slots:
  void closeEvent(QCloseEvent* event);

private slots:
  void setupUiConnections();
  bool isThisApplication(Element* element);

  void enableDisableAnalysis();
  Element* getSelectedTopLevelWindow() const;
  Element* getSelectedElement() const;
  void analyzeSelectedWindow();
  void addToTreeIncludingChildren(Element* element, ElementTreeItem* parent = 0);

  void highlightSelectedWindow();
  void highlightSelectedElement();
  void highlightIfEnabled(Element* element);

  void loadTopLevelWindows();

  bool highlightingEnabled() const;
  void highlightingEnabledChanged(bool enabled);
  void setHighlightingColor();

  void exportXUL();
  void exportXULComplete();

  QString colorBaseOnLogType(Log::Type logType) const;

private:
  Ui::MainWindow* ui;
  Client* client;
  Element* analyzedWindow;
  XUL::Exporter* xulExp;
};

#endif // MAINWINDOW_H
