#ifndef ELEMENTAREA_H
#define ELEMENTAREA_H

#include "includes.h"


struct ElementArea
{
public:
  ElementArea(const RECT& boundingRectangle);

  inline int getLeft()   const { return left; };
  inline int getTop()    const { return top; };
  inline int getWidth()  const { return width; };
  inline int getHeight() const { return height; };

private:
  int left;
  int top;
  int width;
  int height;
};

#endif // ELEMENTAREA_H
