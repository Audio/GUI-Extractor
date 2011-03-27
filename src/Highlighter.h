#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include "UIA/ElementArea.h"
#include <QtGui/QWidget>


class Highlighter : public QWidget
{
public:
  static void highlight(const ElementArea* area);
  static void hideActive();

private:
  Highlighter(const ElementArea* area);
  void setArea(const ElementArea* area);

  static void destroyActiveInstance();

protected:
  void paintEvent(QPaintEvent*);
  QSize sizeHint () const;

private:
  static Highlighter* instance;
  int width;
  int height;
};

#endif // HIGHLIGHTER_H
