#include "Client.h"


Client::Client()
{
}

Client::~Client()
{
  uia->Release();
  CoUninitialize();
  emit error("UIA instance has been deallocated");
}

void Client::initialize()
{
  CoInitialize(NULL);
  HRESULT hr = CoCreateInstance(__uuidof(CUIAutomation), NULL, CLSCTX_INPROC_SERVER, __uuidof(IUIAutomation), (void**) &uia);

  if ( FAILED(hr) )
    emit error("Initialization of UIA Failed");
  else
    emit error("UIA instance has been successfuly created");
}

QList<IUIAutomationElement*> Client::topLevelWindows()
{
  QList<IUIAutomationElement*> windows;

  IUIAutomationElement* root = NULL;
  HRESULT hr = uia->GetRootElement(&root);
  if ( FAILED(hr) || root == NULL )
    goto cleanup;

  IUIAutomationTreeWalker* wallker = NULL;
  uia->get_ContentViewWalker(&wallker);
  if (!wallker)
    goto cleanup;

  IUIAutomationElement* element;
  wallker->GetFirstChildElement(root, &element);
  if (!element)
    goto cleanup;

  while (element) {
    // TODO call Release() !!!
    windows.append(element);

    IUIAutomationElement* next = NULL;
    wallker->GetNextSiblingElement(element, &next);
    element = next;
  }

cleanup:
  if (root)
    root->Release();

  if (wallker)
    wallker->Release();

  return windows;
}

QString Client::getElementName(IUIAutomationElement* element)
{
  BSTR name;
  HRESULT hr = element->get_CurrentName(&name);
  return ( SUCCEEDED(hr) ? bstrToQString(name) : "FAILLLL" );
}

QString Client::bstrToQString(const BSTR& bstr)
{
  if (!bstr)             // TODO jinak to pada na assertu
    return "?? WTF ??";

  std::wstring str = (LPCWSTR) bstr;
  QString qstr = QString::fromStdWString(str);
  SysFreeString(bstr);
  return qstr;
}
