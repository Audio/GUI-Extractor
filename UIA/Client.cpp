#include "Client.h"


Client::Client()
{
}

Client::~Client()
{
  UIA->Release();
  CoUninitialize();
  emit error("UIA instance has been deallocated");
}

void Client::initialize()
{
  CoInitialize(NULL);
  HRESULT hr = CoCreateInstance(__uuidof(CUIAutomation), NULL, CLSCTX_INPROC_SERVER, __uuidof(IUIAutomation), (void**) &UIA);

  if ( FAILED(hr) )
    emit error("Initialization of UIA Failed");
  else
    emit error("UIA instance has been successfuly created");
}

QList<Element*> Client::topLevelWindows()
{
  QList<Element*> windows;

  IUIAutomationElement* root = NULL;
  HRESULT hr = UIA->GetRootElement(&root);
  if ( FAILED(hr) || !root )
    goto cleanup;

  IUIAutomationTreeWalker* wallker = NULL;
  UIA->get_ContentViewWalker(&wallker);
  if (!wallker)
    goto cleanup;

  IUIAutomationElement* element;
  wallker->GetFirstChildElement(root, &element);
  if (!element)
    goto cleanup;

  while (element) {
    Element* el = new Element(element);
    windows.append(el);

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
