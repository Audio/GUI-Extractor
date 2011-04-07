#ifndef EXPORTER_H
#define EXPORTER_H

#include "ElementTreeItem.h"
#include "LogType.h"
#include <QtCore/QList>
#include <QtCore/QString>
#include <QtGui/QTreeWidget>


namespace XUL {

  class Exporter : public QObject
  {
    Q_OBJECT

  public:
    Exporter(const Element* window, const QTreeWidget* elementTree);

    void save(const QString& filename);

  signals:
    void eventHappened(const QString&, Log::Type = Log::NORMAL);

  private:
    void saveToFile(const QString& filename);
    void setRelativeWindowPositon();

    void elementDataToXml(const ElementTreeItem* element, int indent);
    QString getStartTag(const XUL::Item* item, int indent, bool close = false) const;
    QString getIndentText(int indent) const;

    void insertDocumentStartTags();
    void insertDocumentEndTags();

    inline bool isEmptyElementAndHasNoChildren(const QString& elementName, int childrenCount) const;

    const Element* window;
    int windowPositionLeft;
    int windowPositionTop;

    const QTreeWidget* tree;
    QList<QString> xml;
  };

}

#endif // EXPORTER_H
