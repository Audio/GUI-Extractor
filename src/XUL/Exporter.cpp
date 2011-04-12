#include "Exporter.h"
#include <QtCore/QFile>
#include <QtCore/QFileInfo>
#include <QtCore/QTextStream>


using namespace XUL;

Exporter::Exporter(const Element* window, const QTreeWidget* elementTree)
  : QObject(), window(window), tree(elementTree)
{
}

void Exporter::save(const QString& filename)
{
  emit eventHappened( tr("XUL export is running, please wait...") );

  setRelativeWindowPositon();
  insertDocumentStartTags();

  int topLevels = tree->topLevelItemCount();
  for (int i = 0; i < topLevels; ++i) {
    ElementTreeItem* topItem = (ElementTreeItem*) tree->topLevelItem(i);
    elementDataToXml(topItem, 2);
  }

  insertDocumentEndTags();
  saveToFile(filename);
  saveStylesFile(filename);
}

void Exporter::saveToFile(const QString& filename)
{
  QFile file(filename);
  if ( !file.open(QIODevice::WriteOnly | QIODevice::Text) ) {
    emit eventHappened( tr("XUL export: cannot write to the selected file ") + filename, Log::WARNING);
    return;
  }

  QTextStream out(&file);
  QListIterator<QString> it(xml);
  while ( it.hasNext() )
    out << it.next() << "\n";

  file.close();
  emit eventHappened( tr("XUL export completed!") );
}

void Exporter::saveStylesFile(const QString& originalFilename)
{
  QFileInfo fi(originalFilename);
  QString destination = fi.absolutePath() + "/gui_ex.css";
  bool ok = QFile::copy(":/styles/gui_ex.css", destination);

  if (!ok)
    emit eventHappened( tr("XUL export: cannot save the styles file"), Log::WARNING );
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
  if (item == XUL::NO_EXPORT)
    return;

  int children = treeItem->childCount();

  if ( isEmptyElementAndHasNoChildren( item->getName(), children) )
    return;

  xml.append( getStartTag(item, indent, children == 0) );

  for (int i = 0; i < children; ++i)
    elementDataToXml( (ElementTreeItem*) treeItem->child(i), indent + 1 );

  if (children > 0)
    xml.append( getIndentText(indent) + "</" + item->getName() + ">" );

  delete item;
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

void Exporter::insertDocumentStartTags()
{
  xml.append("<?xml version=\"1.0\" encoding=\"windows-1250\"?>");
  xml.append("<?xml-stylesheet href=\"gui_ex.css\" type=\"text/css\"?>");
  xml.append( QString() );

  XUL::Item w("window");
  w.setAttribute("xmlns", "http://www.mozilla.org/keymaster/gatekeeper/there.is.only.xul");
  w.setAttribute("title", window->getCachedName() );
  xml.append( getStartTag(&w, 0) );

  QString stackStart = getIndentText(1) + "<stack>";
  xml.append(stackStart);
}

void Exporter::insertDocumentEndTags()
{
  QString stackEnd = getIndentText(1) + "</stack>";
  xml.append(stackEnd);
  xml.append("</window>");
}

bool Exporter::isEmptyElementAndHasNoChildren(const QString& elementName, int childrenCount) const
{
  return false;
  // return elementName == "stack" && childrenCount == 0;
}
