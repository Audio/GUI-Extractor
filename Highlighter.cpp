#include "Highlighter.h"
#include <QtGui/QBrush>
#include <QtGui/QPainter>


Highlighter* Highlighter::instance = NULL;

void Highlighter::highlight(const Element* element)
{
  const ElementArea* area = element->getArea();

  if (!area)
    return;

  if (instance) {
    instance->setArea(area);
  } else {
    instance = new Highlighter(element);
    instance->show();
  }
}

void Highlighter::hideActive()
{
  destroyActiveInstance();
}

Highlighter::Highlighter(const Element* element)
  : QWidget()
{
  setWindowTitle("Highlighter");
  setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
  setWindowOpacity(0.5);

  setArea( element->getArea() );
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
  painter.setBrush( QBrush( QColor(51, 102, 204, 255), Qt::SolidPattern ));
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
