#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include "UIA/ElementArea.h"
#include <QtGui/QWidget>
#include <QtGui/QColor>
#include <QtGui/QPushButton>



class Highlighter : public QWidget
{
public:
  static void highlight(const ElementArea& area);
  static void hideActive();
  static QColor getColor();
  static void setColor(const QColor& newColor);

private:
  Highlighter(const ElementArea& area);
  ~Highlighter();
  void setArea(const ElementArea& area);
  void showCloseButtonIfNeeded();

  static void destroyActiveInstance();

protected:
  void paintEvent(QPaintEvent*);
  QSize sizeHint () const;

private:
  static Highlighter* instance;
  static QColor color;
  QPushButton* closeButton;
  int width;
  int height;
};

#endif // HIGHLIGHTER_H
