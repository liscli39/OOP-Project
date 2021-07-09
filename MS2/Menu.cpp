#include "Menu.h"
#include "utils.h"
#include <string.h>

using namespace std;
namespace sdds
{
  void Menu::display() const
  {
    cout << m_text << endl;
    cout << "0- Exit" << endl;
  }

  Menu::Menu(const char *MenuContent, int NoOfSelections)
  {
    m_text = nullptr;

    if (MenuContent != nullptr)
    {
      m_text = new char[strlen(MenuContent) + 1];
      strcpy(m_text, MenuContent);
    }

    m_noOfSel = NoOfSelections;
  }

  Menu::Menu(const Menu &menu)
  {
    m_text = nullptr;

    if (menu.m_text != nullptr)
    {
      m_text = new char[strlen(menu.m_text) + 1];
      strcpy(m_text, menu.m_text);
    }

    m_noOfSel = menu.m_noOfSel;
  }

  Menu::~Menu()
  {
    delete[] m_text;
    m_text = nullptr;
    m_noOfSel = 0;
  }

  int &Menu::operator>>(int &Selection)
  {
    display();
    Selection = getInt(0, m_noOfSel, "> ", "Invalid option ", true);
    return Selection;
  }
}