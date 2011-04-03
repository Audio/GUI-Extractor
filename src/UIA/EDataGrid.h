#ifndef EDATAGRID_H
#define EDATAGRID_H

#include "Element.h"


class EDataGrid : public Element
{
public:
  EDataGrid(IUIAutomationElement* element);
  inline QString getType() const;
};

#endif // EDATAGRID_H
