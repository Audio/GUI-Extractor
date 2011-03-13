#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include "UIA/Element.h"
#include <QtGui/QWidget>


class Highlighter : public QWidget
{
public:
  static void highlight(const Element* element);
  static void hideActive();

private:
  Highlighter(const Element* element);

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
