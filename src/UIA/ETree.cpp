#include "ETree.h"


ETree::ETree(IUIAutomationElement* element)
  : Element(element)
{
}

QString ETree::getType() const
{
  return "tree";
}
