#pragma once
#include <SFML/Graphics.hpp>
#include "Level.h"
#include "Menu.h"

class Game
{
private:
	Level *level;
	sf::RenderWindow app_window;
	int mode;
	bool game_on;
	Main_Menu main_menu;
	Level_Select_Menu level_select_menu;
	Settings_Menu settings_menu;
	int settings[6];
	int dim_x;
	int dim_y;
	bool prompt_on;
	sf::Texture prompt_pic;
	sf::Sprite prompt;
public:
	Game();	
	void main_loop();
	void mode_0_pre(sf::Vector2i mouse_pos);
	void mode_0_eventer(sf::Event zdarzenie);
	void mode_0_drawer();
	void mode_1_pre(sf::Vector2i mouse_pos);
	void mode_1_eventer(sf::Event zdarzenie);
	void mode_1_drawer();
	void mode_2_eventer(sf::Event zdarzenie);
	void mode_2_drawer_and_post();
	void mode_3_pre(sf::Vector2i mouse_pos);
	void mode_3_eventer(sf::Event zdarzenie);
	void mode_3_drawer();
	void draw_text_from_string(std::string the_name, int pos_x, int pos_y, int size, int number_of_letters=-1);
	void draw_list();
	bool test_level_file(std::string file_name);
	void turn_the_level_on(std::string file_name);
};