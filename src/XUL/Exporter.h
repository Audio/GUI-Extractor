#ifndef EXPORTER_H
#define EXPORTER_H

#include "ElementTreeItem.h"
#include "LogType.h"
#include "UIA/Client.h"
#include "XUL/MenuExporter.h"
#include <QtCore/QList>
#include <QtCore/QString>
#include <QtGui/QTreeWidget>


namespace XUL {

  class Exporter : public QObject
  {
    Q_OBJECT

  public:
    Exporter(Element* window, const QTreeWidget* elementTree, Client* client);

    void save(const QString& filename);

  signals:
    void eventHappened(const QString&, Log::Type = Log::NORMAL);
    void finished();

  private slots:
    void saveToFile();
    void saveStylesFile();
    void setRelativeWindowPositon();

    bool analyzeMenubarIfExists();
    EMenuBar* findMenuBar();
    void exportMenu(EMenuItem* menuItem, QList<Element*> items = QList<Element*>() );
    void completeMenuAnalysis();

    void analyzeContentAndCompleteSave();

    void elementDataToXml(const ElementTreeItem* element, int indent);
    QString getStartTag(const XUL::Item* item, int indent, bool close = false) const;
    QString getIndentText(int indent) const;

    void insertDocumentStartTags();
    void insertDocumentEndTags();

    inline bool isEmptyElementAndHasNoChildren(const QString& elementName, int childrenCount) const;

  private:
    Element* window;
    Client* client;
    MenuExporter* menuExp;
    int windowPositionLeft;
    int windowPositionTop;

    const QTreeWidget* tree;
    QList<QString> xml;
    QString filename;
  };

}

#endif // EXPORTER_H
