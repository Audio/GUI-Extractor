#include "Exporter.h"
#include "ElementTreeItem.h"
#include <QDebug>


using namespace XUL;

Exporter::Exporter(const Element* window, const QTreeWidget* elementTree)
  : window(window), tree(elementTree)
{
}

void Exporter::save(const QString& filename)
{
  qDebug() << "== EXPORT BEGIN ==";

  // TODO include XUL HEADER

  int topLevels = tree->topLevelItemCount();
  for (int i = 0; i < topLevels; ++i) {
    ElementTreeItem* topItem = (ElementTreeItem*) tree->topLevelItem(i);
    XUL::Item* item = topItem->getElement()->exportXUL();

    QString tag = "<" + item->getName();

    const QMap<QString, QString> attributes = item->getAttributes();

    QMapIterator<QString, QString> it(attributes);
    while ( it.hasNext() ) {
        it.next();
        tag += " " + it.key() + "=\"" + it.value() + "\"";
    }

    tag += "></" + item->getName() + ">";
    qDebug().nospace() << tag;
  }

  // TODO include XUL footer

  qDebug() << "== EXPORT END ==";
}
