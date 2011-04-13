#ifndef EMENUITEM_H
#define EMENUITEM_H

#include "Element.h"


class EMenuItem : public Element
{
public:
  EMenuItem(IUIAutomationElement* element);
  inline QString getType() const;
  XUL::Item* exportXUL(int, int) const;

  bool supportExpandCollapse();
  void expandMenu();
  void collapseMenu();

private:
  void expandOrCollapseMenu(bool expand);
};

#endif // EMENUITEM_H
