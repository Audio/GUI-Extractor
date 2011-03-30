#include "Exporter.h"
#include <QtCore/QFile>
#include <QDebug>


using namespace XUL;

Exporter::Exporter(const Element* window, const QTreeWidget* elementTree)
  : window(window), tree(elementTree)
{
}

void Exporter::save(const QString& filename)
{
  xml.append( getHeaderVersion() );
  xml.append( getHeaderStylesheet() );
  xml.append( QString() );

  // TODO begin of window element
  xml.append("<window>");

  int topLevels = tree->topLevelItemCount();
  for (int i = 0; i < topLevels; ++i) {
    ElementTreeItem* topItem = (ElementTreeItem*) tree->topLevelItem(i);
    elementDataToXml(topItem, 1);
  }

  // TODO end of window element
  xml.append("</window>");

  saveToFile(filename);
}

void Exporter::saveToFile(const QString& filename)
{
  QFile file(filename);
  if ( !file.open(QIODevice::WriteOnly | QIODevice::Text) ) {
    qDebug().nospace() << "Export: cannot write to the selected file!" << filename;
    return;
  }

  QTextStream out(&file);
  QListIterator<QString> it(xml);
  while ( it.hasNext() )
    out << it.next() << "\r\n";

  file.close();
}

void Exporter::elementDataToXml(const ElementTreeItem* treeItem, int indent)
{
  XUL::Item* item = treeItem->getElement()->exportXUL();
  xml.append( getStartTag(item, indent) );

  int children = treeItem->childCount();
  for (int i = 0; i < children; ++i)
    elementDataToXml( (ElementTreeItem*) treeItem->child(i), ++indent );

  xml.append("</" + item->getName() + ">");
}

QString Exporter::getStartTag(const XUL::Item* item, int indent) const
{
  QString tag = getIndentText(indent);
  tag +="<" + item->getName();

  const QMap<QString, QString> attributes = item->getAttributes();

  QMapIterator<QString, QString> it(attributes);
  while ( it.hasNext() ) {
    it.next();
    tag += " " + it.key() + "=\"" + it.value() + "\"";
  }

  return tag += ">";
}

QString Exporter::getIndentText(int indent) const
{
  QString whitespaces;
  return whitespaces.fill(' ', indent);
}

QString Exporter::getHeaderVersion() const
{
  return "<?xml version=\"1.0\"?>";
}

QString Exporter::getHeaderStylesheet() const
{
  return "<?xml-stylesheet href=\"chrome://global/skin/\" type=\"text/css\"?>";
}
