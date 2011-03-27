#include "ElementFactory.h"
#include "EButton.h"
#include "ECheckBox.h"
#include "EComboBox.h"
#include "EEdit.h"
#include "EMenuBar.h"
#include "EMenuItem.h"
#include "EProgressBar.h"
#include "ERadio.h"
#include "EScrollBar.h"
#include "ESlider.h"
#include "EUnknown.h"


Element* ElementFactory::getElement(IUIAutomationElement* element)
{
  CONTROLTYPEID type;
  HRESULT hr = element->get_CurrentControlType(&type);
  if ( !SUCCEEDED(hr) )
    return new EUnknown(element);

  switch (type) {
    case UIA_ButtonControlTypeId      : return new EButton(element);
    case UIA_CheckBoxControlTypeId    : return new ECheckBox(element);
    case UIA_ComboBoxControlTypeId    : return new EComboBox(element);
    case UIA_EditControlTypeId        : return new EEdit(element);
    case UIA_MenuBarControlTypeId     : return new EMenuBar(element);
    case UIA_MenuItemControlTypeId    : return new EMenuItem(element);
    case UIA_ProgressBarControlTypeId : return new EProgressBar(element);
    case UIA_RadioButtonControlTypeId : return new ERadio(element);
    case UIA_ScrollBarControlTypeId   : return new EScrollBar(element);
    case UIA_SliderControlTypeId      : return new ESlider(element);
    default : return new EUnknown(element);
  }
}
