#include "MenuExporter.h"
#include "UIA/EMenu.h"


MenuExporter::MenuExporter(EMenuBar* menubar, Element* window, Client* client, QObject* parent)
  : QObject(parent), window(window), client(client), currentItem(NULL), TIMEOUT(100)
{
  QList<Element*> tempItems = client->getImmediateChildren(menubar);
  foreach (Element* item, tempItems) {
    EMenuItem* menuItem = (EMenuItem*) item;
    if ( menuItem->supportExpandCollapse() )
      items.append(menuItem);
  }

  timer = new QTimer(this);
  timer->setSingleShot(true);
  connect(timer, SIGNAL( timeout() ), SLOT( tryAnalyzeMenu() ));

  prepareToLoadNextMenu();
}

void MenuExporter::prepareToLoadNextMenu()
{
  if ( items.isEmpty() ) {
    emit allMenusLoaded();
  } else {
    currentItem = items.takeFirst();
    currentItem->expandMenu();
    failAttempts = 0;
    timer->start(TIMEOUT);
  }
}

void MenuExporter::tryAnalyzeMenu()
{
  EMenu* menu = (EMenu*) client->getTopMenuElement(window);
  if (menu) {
    emit eventHappened( tr("XUL export: loaded items of menu '") + currentItem->getCachedName() + "'" );
    QList<Element*> menuItems = client->getImmediateChildren(menu);
    emit menuLoaded(currentItem, menuItems);
    currentItem->collapseMenu();
    delete currentItem;
    delete menu;
    prepareToLoadNextMenu();
  } else {
    ++failAttempts;

    if (failAttempts >= 10) {
      emit eventHappened( tr("XUL export: cannot find items of menu '") + currentItem->getCachedName() + "'", Log::WARNING);
      emit menuNotLoaded(currentItem);
      currentItem->collapseMenu();
      delete currentItem;
      prepareToLoadNextMenu();
    } else {
      timer->start(TIMEOUT);
    }
  }
}
