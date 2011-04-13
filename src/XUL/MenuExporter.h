#ifndef MENUEXPORTER_H
#define MENUEXPORTER_H

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
};

#endif // MENUEXPORTER_H
