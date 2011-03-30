#ifndef EPROGRESSBAR_H
#define EPROGRESSBAR_H

#include "Element.h"


class EProgressBar : public Element
{
public:
  EProgressBar(IUIAutomationElement* element);
  inline QString getType() const;
};

#endif // EPROGRESSBAR_H
