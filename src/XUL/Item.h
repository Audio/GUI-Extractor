#ifndef ITEM_H
#define ITEM_H

#include <QtCore/QString>
#include <QtCore/QMap>


namespace XUL {

  class Item
  {
  public:
    Item(const QString& name);

    QString getName() const { return name; }
    void setAttribute(const QString& key, const QString& value);
    const QMap<QString, QString>& getAttributes() const { return attributes; }

  private:
    QString name;
    QMap<QString, QString> attributes;
  };

  const int NO_EXPORT = 0;

}

#endif // ITEM_H
