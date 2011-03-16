#include "ElementFactory.h"
#include "EButton.h"
#include "EUnknown.h"


Element* ElementFactory::getElement(IUIAutomationElement* element)
{
  CONTROLTYPEID type;
  HRESULT hr = element->get_CurrentControlType(&type);
  if ( !SUCCEEDED(hr) )
    return new EUnknown(element);

  switch (type) {
    case UIA_ButtonControlTypeId      : return new EButton(element);
    // case UIA_CheckBoxControlTypeId    : return new Element(element);
    // case UIA_RadioButtonControlTypeId : return new Element(element);
    default : return new EUnknown(element);
  }
}
