#ifndef CLIENT_H
#define CLIENT_H

#include "includes.h"
#include "Element.h"
#include "LogType.h"
#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QString>


class Client : public QObject
{
  Q_OBJECT

public:
  Client();
  ~Client();

  void init();
  Element* getRootElement();
  QList<Element*> getImmediateChildren(Element* parent);
  QList<Element*> topLevelWindows();

signals:
  void eventHappened(const QString&, Log::Type = Log::NORMAL);

private:
  IUIAutomation* UIA;
};

#endif // CLIENT_H
