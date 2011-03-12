#ifndef ELEMENTAREA_H
#define ELEMENTAREA_H

#include "includes.h"
#include <QtGui/QWidget>


class ElementArea : public QWidget
{
public:
  ElementArea(const RECT& boundingRectangle);

protected:
  void paintEvent(QPaintEvent*);
  QSize sizeHint () const;

private:
  int left;
  int top;
  int width;
  int height;
};

#endif // ELEMENTAREA_H
