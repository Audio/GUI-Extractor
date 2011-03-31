#ifndef EXPORTER_H
#define EXPORTER_H

#include "ElementTreeItem.h"
#include <QtCore/QList>
#include <QtCore/QString>
#include <QtGui/QTreeWidget>


namespace XUL {

  class Exporter
  {
  public:
    Exporter(const Element* window, const QTreeWidget* elementTree);

    void save(const QString& filename);

  private:
    void saveToFile(const QString& filename);

    void elementDataToXml(const ElementTreeItem* element, int indent);
    QString getStartTag(const XUL::Item* item, int indent, bool close = false) const;
    QString getIndentText(int indent) const;

    QString getWindowBeginTag() const;
    inline QString getWindowEndTag() const;

    inline QString getHeaderVersion() const;
    inline QString getHeaderStylesheet() const;

    const Element* window;
    const QTreeWidget* tree;
    QList<QString> xml;
  };

}

#endif // EXPORTER_H
