#ifndef CLIENT_H
#define CLIENT_H

#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QString>
#include "includes.h"


class Client : public QObject
{
  Q_OBJECT

public:
  explicit Client();
  ~Client();

  void initialize();
  QList<IUIAutomationElement*> topLevelWindows();
  QString getElementName(IUIAutomationElement* element);

signals:
  void error(const QString& message);

private:
  QString bstrToQString(const BSTR& bstr);

  IUIAutomation* uia;
};

#endif // CLIENT_H
