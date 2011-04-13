#include "Exporter.h"
#include "UIA/EMenuItem.h"
#include <QtCore/QFile>
#include <QtCore/QFileInfo>
#include <QtCore/QTextStream>


using namespace XUL;

Exporter::Exporter(Element* window, const QTreeWidget* elementTree, Client* client)
  : QObject(), window(window), client(client), tree(elementTree)
{
}

void Exporter::save(const QString& filename)
{
  this->filename = filename;
  emit eventHappened( tr("XUL export is running, please wait...") );

  setRelativeWindowPositon();
  insertDocumentStartTags();

  bool menubarExists = analyzeMenubarIfExists();
  if (!menubarExists)
    analyzeContentAndCompleteSave();
}

void Exporter::saveToFile()
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

void Exporter::saveStylesFile()
{
  QFileInfo fi(filename);
  QString destination = fi.absolutePath() + "/gui_ex.css";
  bool ok = QFile::copy(":/styles/gui_ex.css", destination);

  if (!ok && !QFile::exists(destination) )
    emit eventHappened( tr("XUL export: cannot save the styles file"), Log::WARNING );
}

void Exporter::setRelativeWindowPositon()
{
  bool valid;
  ElementArea a = window->getArea(valid);
  windowPositionLeft = valid ? a.getLeft() : 0;
  windowPositionTop = valid ? a.getTop() : 0;
}

bool Exporter::analyzeMenubarIfExists()
{
  EMenuBar* menubar = findMenuBar();

  if (!menubar) {
    return false;
  } else {
    xml.append( getIndentText(1) + "<menubar>" );

    menuExp = new MenuExporter(menubar, window, client, this);
    connect(menuExp, SIGNAL( menuLoaded(EMenuItem*, QList<Element*>) ), SLOT( exportMenu(EMenuItem*, QList<Element*>) ));
    connect(menuExp, SIGNAL( menuNotLoaded(EMenuItem*) ), SLOT( exportMenu(EMenuItem*) ));
    connect(menuExp, SIGNAL( allMenusLoaded() ), SLOT( completeMenuAnalysis() ));
    return true;
  }
}

EMenuBar* Exporter::findMenuBar()
{
  int topLevels = tree->topLevelItemCount();
  for (int i = 0; i < topLevels; ++i) {
    ElementTreeItem* topItem = (ElementTreeItem*) tree->topLevelItem(i);
    if ( topItem->getElement()->getType() == "menubar" )
      return (EMenuBar*) topItem->getElement();
  }

  return NULL;
}

void Exporter::exportMenu(EMenuItem* menuItem, QList<Element*> items)
{
  const QString label = menuItem->getCachedName();
  xml.append( getIndentText(2) + "<menu label=\"" + label + "\">" );
  xml.append( getIndentText(3) + "<menupopup>" );

  foreach (Element* item, items) {
    XUL::Item* xi = item->exportXUL(0, 0);
    xml.append( getStartTag(xi, 4, true) );
    delete xi;
  }

  xml.append( getIndentText(3) + "</menupopup>" );
  xml.append( getIndentText(2) + "</menu>" );
}

void Exporter::completeMenuAnalysis()
{
  xml.append( getIndentText(1) + "</menubar>" );
  analyzeContentAndCompleteSave();
}

void Exporter::analyzeContentAndCompleteSave()
{
  QString stackStart = getIndentText(1) + "<stack>";
  xml.append(stackStart);

  int topLevels = tree->topLevelItemCount();
  for (int i = 0; i < topLevels; ++i) {
    ElementTreeItem* topItem = (ElementTreeItem*) tree->topLevelItem(i);
    if ( topItem->getElement()->getType() != "menubar" )
      elementDataToXml(topItem, 2);
  }

  QString stackEnd = getIndentText(1) + "</stack>";
  xml.append(stackEnd);

  insertDocumentEndTags();
  saveToFile();
  saveStylesFile();
  emit finished();
}

void Exporter::elementDataToXml(const ElementTreeItem* treeItem, int indent)
{
  XUL::Item* item = treeItem->getElement()->exportXUL(windowPositionLeft, windowPositionTop);
  if (item == XUL::NO_EXPORT ||  isEmptyElementAndHasNoChildren( item->getName(), treeItem->childCount() )) {
    delete item;
    return;
  }

  const int CHILDREN_COUNT = treeItem->childCount();
  const bool EXPORT_CHILDREN = treeItem->getElement()->ignoreChildren() == false && CHILDREN_COUNT > 0;
  xml.append( getStartTag(item, indent, !EXPORT_CHILDREN) );

  if (EXPORT_CHILDREN) {
    for (int i = 0; i < CHILDREN_COUNT; ++i)
      elementDataToXml( (ElementTreeItem*) treeItem->child(i), indent + 1 );

    xml.append( getIndentText(indent) + "</" + item->getName() + ">" );
  }

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
}

void Exporter::insertDocumentEndTags()
{
  xml.append("</window>");
}

bool Exporter::isEmptyElementAndHasNoChildren(const QString& elementName, int childrenCount) const
{
  return elementName == "stack" && childrenCount == 0;
}
