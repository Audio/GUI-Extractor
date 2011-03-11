#ifndef CLIENT_H
#define CLIENT_H

#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QString>
#include "includes.h"
#include "Element.h"


class Client : public QObject
{
  Q_OBJECT

public:
  explicit Client();
  ~Client();

  void initialize();
  QList<Element*> topLevelWindows();

signals:
  void error(const QString& message);

private:
  IUIAutomation* UIA;
};

#endif // CLIENT_H
