#ifndef CLIENT_H
#define CLIENT_H

#include "includes.h"
#include "Element.h"
#include "LogType.h"
#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QString>
#include <QtCore/QFuture>
#include <QtCore/QFutureWatcher>


class Client : public QObject
{
  Q_OBJECT

public:
  Client();
  ~Client();

  void init();
  Element* getRootElement();
  Element* getTopMenuElement(Element* window);
  QList<Element*> getImmediateChildren(Element* parent, bool deleteParent = false);
  void loadTopLevelWindows();

signals:
  void eventHappened(const QString&, Log::Type = Log::NORMAL);
  void topLevelWindowsLoaded(const QList<Element*>&);

private slots:
  void getTopLevelWindows();

private:
  IUIAutomation* UIA;
  QFuture< QList<Element*> > future;
  QFutureWatcher< QList<Element*> > watcher;
};

#endif // CLIENT_H
