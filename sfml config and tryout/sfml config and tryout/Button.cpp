#include "Button.h"

Button::Button(int x, int y, std::string name) :pos_x(x), pos_y(y), is_active(0)
{
	if (!pic1.loadFromFile(name))
	{
		std::cout << "ERROR" << std::endl;
	}
	else
	{
		m_name1 = name;
		image1.setTexture(pic1);
		image1.setPosition(pos_x, pos_y);
		m_name2=m_name1.substr(0, m_name1.size() - 4);
		m_name2.append("_active.png");
		if (!pic2.loadFromFile(m_name2))
		{
			std::cout << "ERROR!" << std::endl;
		}
		else
		{
			image2.setTexture(pic2);
			image2.setPosition(pos_x, pos_y);
		}
	}
}

void Button::activate()
{
	if (!is_active)
	{
		is_active = 1;
	}
}

void Button::deactivate()
{
	if (is_active)
	{
		is_active = 0;
	}
}

sf::Sprite Button::get_image()
{
	if (is_active)
	{
		return image2;
	}
	else
	{
		return image1;
	}
}

bool Button::get_is_active()
{
	return is_active;
}
