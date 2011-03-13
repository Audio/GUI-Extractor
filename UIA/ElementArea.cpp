#include "ElementArea.h"


ElementArea::ElementArea(const RECT& boundingRectangle)
{
  this->left = boundingRectangle.left;
  this->top = boundingRectangle.top;
  this->width = boundingRectangle.right - boundingRectangle.left;
  this->height = boundingRectangle.bottom - boundingRectangle.top;
}
