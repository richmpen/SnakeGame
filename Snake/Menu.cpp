#include "Menu.h"
#include <assert.h>

namespace Snake
{
	void InitMenuItem(MenuItem& item)
	{
		for (auto& child : item.children) 
		{
			child->parent = &item;
			InitMenuItem(*child);
		}
	}
	MenuItem* GetCurrentMenuContext(Menu& menu)
	{
		return menu.selectedItem ? menu.selectedItem->parent:&menu.rootitem;
	}
	void SelectMenuItem(Menu& menu, MenuItem* item)
	{
		assert(item != &menu.rootitem);

		if (menu.selectedItem == item)
		{
			return;
		}

		if (menu.selectedItem)
		{
			menu.selectedItem->text.setFillColor(menu.selectedItem->itemColor);
		}

		menu.selectedItem= item;
		if (menu.selectedItem)
		{
			menu.selectedItem->text.setFillColor(menu.selectedItem->itemHoverColor);
		}
	}
	bool SelectedNextMenuItem(Menu& menu)
	{
		if (menu.selectedItem)
		{
			MenuItem* parent = menu.selectedItem->parent;
			assert(parent);

			auto i = std::find(parent->children.begin(), parent->children.end(), menu.selectedItem);
			if (i != parent->children.begin())
			{
				SelectMenuItem(menu, *(--i));
				return true;
			}
		}
		return false;
	}
	bool SelectedPrevMenuItem(Menu& menu)
	{
		if (menu.selectedItem)
		{
			MenuItem* parent = menu.selectedItem->parent;
			assert(parent);

			auto i = std::find(parent->children.begin(), parent->children.end(), menu.selectedItem);
			if (i != parent->children.end() - 1)
			{
				SelectMenuItem(menu, *(++i));
				return true;
			}
		}
		return false;
	}
	bool OpenSelectedItem(Menu& menu)
	{
		if (menu.selectedItem && menu.selectedItem->children.size() > 0)
		{
			SelectMenuItem(menu, menu.selectedItem->children.front());
			return true;
		}
		return false;
	}
	bool CloseSelectedItem(Menu& menu)
	{
		if (menu.selectedItem && menu.selectedItem->parent && menu.selectedItem->parent != &menu.rootitem)
		{
			SelectMenuItem(menu, menu.selectedItem->parent);
			return true;
		}
		return false;
	}
	void DrawMenu(Menu& menu, sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f origin)
	{
		MenuItem* advancedItem = GetCurrentMenuContext(menu);

		std::vector<sf::Text*> texts;
		texts.reserve(advancedItem->children.size());
		for (auto& child : advancedItem->children)
		{
			if(child->activeItem)
			{
				texts.push_back(&child->text);
			}
		}
		DrawItemsList(window, texts, advancedItem->childrenSpacing, advancedItem->childrenOrientation, advancedItem->childrenAlignment, position, origin);
	}
}