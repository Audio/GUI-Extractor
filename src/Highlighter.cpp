#include "Highlighter.h"
#include <QtGui/QBrush>
#include <QtGui/QHBoxLayout>
#include <QtGui/QPainter>


Highlighter* Highlighter::instance = NULL;
QColor Highlighter::color = QColor(51, 102, 204);

void Highlighter::highlight(const ElementArea& area)
{
  if (instance)
    instance->setArea(area);
  else
    instance = new Highlighter(area);

  instance->show();
  instance->showCloseButtonIfNeeded();
}

void Highlighter::hideActive()
{
  destroyActiveInstance();
}

bool Highlighter::isCurrentlyVisible()
{
  return instance && instance->isVisible();
}

QColor Highlighter::getColor()
{
  return color;
}

void Highlighter::setColor(const QColor& newColor)
{
  color = newColor;
  if ( isCurrentlyVisible() ) {
    instance->close();
    instance->show();
  }
}

Highlighter::Highlighter(const ElementArea& area)
  : QWidget()
{
  setWindowTitle("Highlighter");
  setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
  setWindowOpacity(0.5);

  setArea(area);
  createCloseButton();
}

Highlighter::~Highlighter()
{
  disconnect(closeButton, 0, 0, 0);
  delete closeButton;
}

void Highlighter::setArea(const ElementArea& area)
{
  this->width = area.getWidth();
  this->height = area.getHeight();

  move( area.getLeft(), area.getTop() );
  resize(width, height);
}

void Highlighter::createCloseButton()
{
  closeButton = new QPushButton( QIcon(":/icons/close.png"), QString(), this );
  closeButton->setIconSize( QSize(16, 16) );
  closeButton->setMaximumSize(16, 16);
  closeButton->setToolTip( tr("Close highlighter") );

  connect(closeButton, SIGNAL( clicked() ), SLOT( close() ));

  QHBoxLayout* lay = new QHBoxLayout(this);
  lay->addWidget(closeButton);
  setLayout(lay);
}

void Highlighter::showCloseButtonIfNeeded()
{
  closeButton->setVisible(width > 200 && height > 100);
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
