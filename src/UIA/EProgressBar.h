#ifndef EPROGRESSBAR_H
#define EPROGRESSBAR_H

#include "Element.h"


class EProgressBar : public Element
{
public:
  EProgressBar(IUIAutomationElement* element);
  inline QString getType() const;
  XUL::Item* exportXUL(int diffLeft, int diffTop) const;
};

#endif // EPROGRESSBAR_H
