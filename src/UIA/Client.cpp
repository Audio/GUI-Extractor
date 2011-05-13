#include "Client.h"
#include "ElementFactory.h"
#include <QtCore/QtConcurrentRun>


Client::Client()
  : UIA(NULL), future(), watcher()
{
  connect(&watcher, SIGNAL( finished() ), SLOT( getTopLevelWindows() ));
}

Client::~Client()
{
  UIA->Release();
  CoUninitialize();
  emit eventHappened( tr("UI Automation has been disabled") );
}

void Client::init()
{
  CoInitialize(NULL);
  HRESULT hr = CoCreateInstance(__uuidof(CUIAutomation), NULL, CLSCTX_INPROC_SERVER, __uuidof(IUIAutomation), (void**) &UIA);

  if ( FAILED(hr) )
    emit eventHappened( tr("Initialization of UI Automation has failed"), Log::WARNING );
  else
    emit eventHappened( tr("UI Automation has been initialized") );
}

Element* Client::getRootElement()
{
  IUIAutomationElement* root = NULL;
  HRESULT hr = UIA->GetRootElement(&root);
  if ( FAILED(hr) || !root ) {
    emit eventHappened( tr("Cannot obtain the Desktop element"), Log::WARNING );
    if (root)
      root->Release();

    return NULL;
  }

  return ElementFactory::getElement(root);
}

Element* Client::getTopMenuElement(Element* window)
{
  QList<Element*> children = getImmediateChildren(window);

  foreach (Element* child, children) {
    if ( child->getType() == "menu" )
      return child;
  }

  return NULL;
}

QList<Element*> Client::getImmediateChildren(Element* parent, bool deleteParent)
{
  QList<Element*> children;

  IUIAutomationTreeWalker* walker = NULL;
  UIA->get_RawViewWalker(&walker);
  if (!walker)
    return children;

  IUIAutomationElement* element;
  walker->GetFirstChildElement( parent->getUIAElement(), &element );

  while (element) {
    children.append( ElementFactory::getElement(element) );
    IUIAutomationElement* next = NULL;
    walker->GetNextSiblingElement(element, &next);
    element = next;
  }

  walker->Release();

  if (deleteParent) {
    delete parent;
    parent = NULL;
  }

  return children;
}

void Client::loadTopLevelWindows()
{
  Element* root = getRootElement();
  if (root) {
    future = QtConcurrent::run(this, &Client::getImmediateChildren, root, true);
    watcher.setFuture(future);
  }
}

void Client::getTopLevelWindows() {
  const int COUNT = future.result().size() - 1;
  emit eventHappened( tr("Found ") + QString::number(COUNT) + tr(" top-level windows.") );
  emit topLevelWindowsLoaded( future.result() );
}
