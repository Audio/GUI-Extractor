#include "EMenuItem.h"


EMenuItem::EMenuItem(IUIAutomationElement* element)
  : Element(element)
{
}

QString EMenuItem::getType() const
{
  return "menu item";
}

XUL::Item* EMenuItem::exportXUL(int, int) const
{
  XUL::Item* item = new XUL::Item("menuitem");
  item->setAttribute("label", getCachedName() );
  return item;
}

bool EMenuItem::supportExpandCollapse()
{
  IUnknown* patternObject;
  HRESULT hr = UIAElement->GetCurrentPattern(UIA_ExpandCollapsePatternId, &patternObject);
  if (patternObject)
    patternObject->Release();
  return SUCCEEDED(hr);
}

void EMenuItem::expandMenu()
{
  expandOrCollapseMenu(true);
}

void EMenuItem::collapseMenu()
{
  expandOrCollapseMenu(false);
}

void EMenuItem::expandOrCollapseMenu(bool expand)
{
  IUnknown* unk;
  UIAElement->GetCurrentPattern(UIA_ExpandCollapsePatternId, &unk);
  IExpandCollapseProvider* icp = (IExpandCollapseProvider*) unk;

  if (expand)
    icp->Expand();
  else
    icp->Collapse();

  icp->Release();
}
