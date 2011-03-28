#ifndef EXPORTER_H
#define EXPORTER_H

#include "UIA/Element.h"
#include <QtCore/QString>
#include <QtGui/QTreeWidget>


namespace XUL {

  class Exporter
  {
  public:
    Exporter(const Element* window, const QTreeWidget* elementTree);

    void save(const QString& filename);

  private:
    const Element* window;
    const QTreeWidget* tree;
  };

}

#endif // EXPORTER_H
