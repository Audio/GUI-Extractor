#ifndef MENUEXPORTER_H
#define MENUEXPORTER_H

#include "LogType.h"
#include "UIA/Client.h"
#include "UIA/EMenuBar.h"
#include "UIA/EMenuItem.h"
#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QString>
#include <QtCore/QTimer>


class MenuExporter : public QObject
{
  Q_OBJECT

public:
  MenuExporter(EMenuBar* menubar, Element* window, Client* client, QObject* parent);

signals:
  void menuLoaded(EMenuItem* menuItem, QList<Element*>);
  void menuNotLoaded(EMenuItem* menuItem);
  void allMenusLoaded();
  void eventHappened(const QString&, Log::Type = Log::NORMAL);

private slots:
  void prepareToLoadNextMenu();
  void tryAnalyzeMenu();

private:
  Element* window;
  Client* client;
  QList<EMenuItem*> items;
  EMenuItem* currentItem;
  QTimer* timer;
  int failAttempts;
  const int TIMEOUT;
};

#endif // MENUEXPORTER_H
