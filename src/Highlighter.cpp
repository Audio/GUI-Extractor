#include "Highlighter.h"
#include <QtGui/QBrush>
#include <QtGui/QPainter>


Highlighter* Highlighter::instance = NULL;
QColor Highlighter::color = QColor(51, 102, 204);

void Highlighter::highlight(const ElementArea* area)
{
  if (instance) {
    instance->setArea(area);
  } else {
    instance = new Highlighter(area);
    instance->show();
  }
}

void Highlighter::hideActive()
{
  destroyActiveInstance();
}

QColor Highlighter::getColor()
{
  return color;
}

void Highlighter::setColor(const QColor& newColor)
{
  color = newColor;
}

Highlighter::Highlighter(const ElementArea* area)
  : QWidget()
{
  setWindowTitle("Highlighter");
  setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
  setWindowOpacity(0.5);

  setArea(area);
}

void Highlighter::setArea(const ElementArea* area)
{
  this->width = area->getWidth();
  this->height = area->getHeight();

  move( area->getLeft(), area->getTop() );
  resize(width, height);
}

void Highlighter::paintEvent(QPaintEvent*)
{
  QPainter painter(this);
  painter.setBrush( QBrush(color, Qt::SolidPattern ));
  painter.drawRect(0, 0, width, height);
}

QSize Highlighter::sizeHint() const
{
  return QSize(width, height);
}

void Highlighter::destroyActiveInstance()
{
  if (instance) {
    instance->close();
    delete instance;
    instance = NULL;
  }
}
