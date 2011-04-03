#include "ElementFactory.h"
#include "EButton.h"
#include "ECalendar.h"
#include "ECheckBox.h"
#include "EComboBox.h"
#include "EDataGrid.h"
#include "EDataItem.h"
#include "EDocument.h"
#include "EEdit.h"
#include "EGroup.h"
#include "EHeader.h"
#include "EHeaderItem.h"
#include "EHyperlink.h"
#include "EImage.h"
#include "EList.h"
#include "EListItem.h"
#include "EMenuBar.h"
#include "EMenu.h"
#include "EMenuItem.h"
#include "EPane.h"
#include "EProgressBar.h"
#include "ERadio.h"
#include "EScrollBar.h"
#include "ESeparator.h"
#include "ESlider.h"
#include "ESpinner.h"
#include "ESplitButton.h"
#include "EStatusBar.h"
#include "ETab.h"
#include "ETabItem.h"
#include "ETable.h"
#include "EText.h"
#include "EThumb.h"
#include "ETitleBar.h"
#include "EToolBar.h"
#include "EToolTip.h"
#include "ETree.h"
#include "ETreeItem.h"
#include "EWindow.h"
#include "EUnknown.h"


Element* ElementFactory::getElement(IUIAutomationElement* element)
{
  CONTROLTYPEID type;
  HRESULT hr = element->get_CurrentControlType(&type);
  if ( !SUCCEEDED(hr) )
    return new EUnknown(element);

  switch (type) {
    case UIA_ButtonControlTypeId      : return new EButton(element);
    case UIA_CalendarControlTypeId    : return new ECalendar(element);
    case UIA_CheckBoxControlTypeId    : return new ECheckBox(element);
    case UIA_ComboBoxControlTypeId    : return new EComboBox(element);
    case UIA_DataGridControlTypeId    : return new EDataGrid(element);

    case UIA_DataItemControlTypeId    : return new EDataItem(element);
    case UIA_DocumentControlTypeId    : return new EDocument(element);
    case UIA_EditControlTypeId        : return new EEdit(element);
    case UIA_GroupControlTypeId       : return new EGroup(element);
    case UIA_HeaderControlTypeId      : return new EHeader(element);

    case UIA_HeaderItemControlTypeId  : return new EHeaderItem(element);
    case UIA_HyperlinkControlTypeId   : return new EHyperlink(element);
    case UIA_ImageControlTypeId       : return new EImage(element);
    case UIA_ListControlTypeId        : return new EList(element);
    case UIA_ListItemControlTypeId    : return new EListItem(element);

    case UIA_MenuBarControlTypeId     : return new EMenuBar(element);
    case UIA_MenuControlTypeId        : return new EMenu(element);
    case UIA_MenuItemControlTypeId    : return new EMenuItem(element);
    case UIA_PaneControlTypeId        : return new EPane(element);
    case UIA_ProgressBarControlTypeId : return new EProgressBar(element);

    case UIA_RadioButtonControlTypeId : return new ERadio(element);
    case UIA_ScrollBarControlTypeId   : return new EScrollBar(element);
    case UIA_SeparatorControlTypeId   : return new ESeparator(element);
    case UIA_SliderControlTypeId      : return new ESlider(element);
    case UIA_SpinnerControlTypeId     : return new ESpinner(element);

    case UIA_SplitButtonControlTypeId : return new ESplitButton(element);
    case UIA_TabControlTypeId         : return new ETab(element);
    case UIA_TabItemControlTypeId     : return new ETabItem(element);
    case UIA_TableControlTypeId       : return new ETable(element);
    case UIA_TextControlTypeId        : return new EText(element);

    case UIA_ThumbControlTypeId       : return new EThumb(element);
    case UIA_TitleBarControlTypeId    : return new ETitleBar(element);
    case UIA_ToolBarControlTypeId     : return new EToolBar(element);
    case UIA_ToolTipControlTypeId     : return new EToolTip(element);
    case UIA_TreeControlTypeId        : return new ETree(element);

    case UIA_TreeItemControlTypeId    : return new ETreeItem(element);
    case UIA_WindowControlTypeId      : return new EWindow(element);
    default : return new EUnknown(element);
  }
}
