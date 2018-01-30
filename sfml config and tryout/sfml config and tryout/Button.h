#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Button
{
private:
	int pos_x;
	int pos_y;
	sf::Texture pic1;
	sf::Sprite image1;
	sf::Texture pic2;
	sf::Sprite image2;
	std::string m_name1;
	std::string m_name2;
	bool is_active;
public:
	Button(int x, int y, std::string name);
	void activate();
	void deactivate();
	sf::Sprite get_image();
	bool get_is_active();
};