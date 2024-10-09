#pragma once
#include "Mathematics.h"

namespace Snake
{
	struct MenuItem
	{
		sf::Text text;
		sf::Text promptText;
		sf::Sprite checkbox;
		
		std::vector<MenuItem*> children;
		MenuItem* parent = nullptr;
		bool activeItem = true;

		sf::Color itemColor = sf::Color::White;
		sf::Color itemHoverColor = sf::Color(76, 201, 176);

		Orientation childrenOrientation = Orientation::Vertical;
		Alignment childrenAlignment = Alignment::Min;
		float childrenSpacing = 0.f;
	};
	
	struct Menu
	{
		MenuItem rootitem;
		MenuItem* selectedItem = nullptr;
	};

	void InitMenuItem(MenuItem& item);
	MenuItem* GetCurrentMenuContext(Menu& menu);
	void SelectMenuItem(Menu& menu, MenuItem* item);
	bool SelectedNextMenuItem(Menu& menu);
	bool SelectedPrevMenuItem(Menu& menu);
	bool OpenSelectedItem(Menu& menu);
	bool CloseSelectedItem(Menu& menu);
	void DrawMenu(Menu& menu, sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f origin);
}
