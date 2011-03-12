#include "ElementArea.h"
#include <QtCore/QDebug>
#include <QtGui/QBrush>
#include <QtGui/QPainter>


ElementArea::ElementArea(const RECT& boundingRectangle)
{
  this->left = boundingRectangle.left;
  this->top = boundingRectangle.top;
  this->width = boundingRectangle.right - boundingRectangle.left;
  this->height = boundingRectangle.bottom - boundingRectangle.top;

  move(left, top);

  setWindowTitle("Highlighter");
  setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
  setWindowOpacity(0.5);
}

void ElementArea::paintEvent(QPaintEvent*)
{
  qDebug() << "Displaying highlighter with these attributes:";
  qDebug() << "Left: " << left << ", top: " << top;
  qDebug() << "Width: " << width << ", height: " << height;

  QPainter painter(this);
  painter.setBrush( QBrush( QColor(51, 102, 204, 255), Qt::SolidPattern ));
  painter.drawRect(0, 0, width, height);
}

QSize ElementArea::sizeHint() const
{
  return QSize(width, height);
}
