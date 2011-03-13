#include "Highlighter.h"
#include <QtGui/QBrush>
#include <QtGui/QPainter>


Highlighter* Highlighter::instance = NULL;

void Highlighter::highlight(const Element* element)
{
  destroyActiveInstance();
  instance = new Highlighter(element);
  instance->show();
}

void Highlighter::hideActive()
{
  destroyActiveInstance();
}

Highlighter::Highlighter(const Element* element)
  : QWidget()
{
  const ElementArea* area = element->getArea();
  this->width = area->getWidth();
  this->height = area->getHeight();

  move( area->getLeft(), area->getTop() );

  setWindowTitle("Highlighter");
  setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
  setWindowOpacity(0.5);
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
    if ( instance->isVisible() )
      instance->close();

    delete instance;
    instance = NULL;
  }
}
