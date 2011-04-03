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
  setRelativeWindowPositon();

  xml.append( getHeaderVersion() );
  xml.append( getHeaderStylesheet() );
  xml.append( QString() );

  xml.append( getWindowBeginTag() );

  int topLevels = tree->topLevelItemCount();
  for (int i = 0; i < topLevels; ++i) {
    ElementTreeItem* topItem = (ElementTreeItem*) tree->topLevelItem(i);
    elementDataToXml(topItem, 1);
  }

  xml.append( getWindowEndTag() );

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
    out << it.next() << "\n";

  file.close();
}

void Exporter::setRelativeWindowPositon()
{
  bool valid;
  ElementArea a = window->getArea(valid);
  windowPositionLeft = valid ? a.getLeft() : 0;
  windowPositionTop = valid ? a.getTop() : 0;
}

void Exporter::elementDataToXml(const ElementTreeItem* treeItem, int indent)
{
  XUL::Item* item = treeItem->getElement()->exportXUL(windowPositionLeft, windowPositionTop);
  int children = treeItem->childCount();

  xml.append( getStartTag(item, indent, children == 0) );

  for (int i = 0; i < children; ++i)
    elementDataToXml( (ElementTreeItem*) treeItem->child(i), indent + 1 );

  if (children > 0)
    xml.append( getIndentText(indent) + "</" + item->getName() + ">" );
}

QString Exporter::getStartTag(const XUL::Item* item, int indent, bool close) const
{
  QString tag = getIndentText(indent);
  tag +="<" + item->getName();

  const QMap<QString, QString> attributes = item->getAttributes();

  QMapIterator<QString, QString> it(attributes);
  while ( it.hasNext() ) {
    it.next();
    tag += " " + it.key() + "=\"" + it.value() + "\"";
  }

  tag += (close) ? " />" : ">";
  return tag;
}

QString Exporter::getIndentText(int indent) const
{
  QString whitespaces;
  return whitespaces.fill(' ', indent * 2);
}

QString Exporter::getWindowBeginTag() const
{
  XUL::Item w("window");
  w.setAttribute("xmlns", "http://www.mozilla.org/keymaster/gatekeeper/there.is.only.xul");
  w.setAttribute("title", window->getCachedName() );
  return getStartTag(&w, 0);
}

QString Exporter::getWindowEndTag() const
{
  return "</window>";
}

QString Exporter::getHeaderVersion() const
{
  return "<?xml version=\"1.0\"?>";
}

QString Exporter::getHeaderStylesheet() const
{
  return "<?xml-stylesheet href=\"chrome://global/skin/\" type=\"text/css\"?>";
}
