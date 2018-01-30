#pragma once
#include "Button.h"
#include <vector>
#include <algorithm>
#include <filesystem>
#include <fstream>

class Main_Menu
{
private:
	Button Select_Level;
	Button Settings;
	Button Exit;
public:
	Main_Menu();
	Button& get_Select_Level();
	Button& get_Settings();
	Button& get_Exit();
};

class Level_Select_Menu
{
private:
	Button Load_Level;
	Button Back;
	Button Next;
	Button Prev;
	std::vector<std::string> file_list;
	int number_of_files;
	int number_of_sites;
	int current_site;
	int current_file;
	sf::Texture underliner_pic;
	sf::Sprite underliner_image;
public:
	Level_Select_Menu();
	void file_reader();
	std::string get_file_string(int i);
	int how_much_elements_on_the_site();
	void change_current_site(int mode);//0 decrease, 1 increase, 2 reset
	void change_current_file(int mode);//0 decrease, 1 increase, 2 reset

	sf::Sprite get_underliner();
	std::string get_current_level();
	
	Button& get_Load_Level();
	Button& get_Back();
	Button& get_Next();
	Button& get_Prev();
};

class Settings_Menu
{
private:
	Button **UPs;
	Button **DOWNs;
	Button Back;
	sf::Font font;
	sf::Text **amount;
	sf::Texture **pic;
	sf::Sprite **image;
	int temporary_generator[6];
	bool settings_file_state;
public:
	Settings_Menu();
	~Settings_Menu();
	bool get_settings_file_state();
	void test_settings_file_state();
	void load_settings_from_the_file(int *settings);
	Button& get_Back();
	Button* get_UP(int i);//i describes the number of element
	Button* get_DOWN(int i);
	sf::Text* get_amount(int i);
	sf::Sprite* get_image(int i);
	void increase(int i);//as above
	void decrease(int i);
	bool save_settings_to_the_file();
};
