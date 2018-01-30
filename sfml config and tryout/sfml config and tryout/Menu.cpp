#include "Menu.h"

Main_Menu::Main_Menu():Select_Level(475,150,"MM_Select_Level.png"),Settings(475,450,"MM_Settings.png"),Exit(475,600,"MM_Exit.png"){}

Button& Main_Menu::get_Select_Level()
{
	return Select_Level;
}

Button& Main_Menu::get_Settings()
{
	return Settings;
}

Button& Main_Menu::get_Exit()
{
	return Exit;
}

Level_Select_Menu::Level_Select_Menu():Load_Level(800,675,"SLM_Load_Level.png"),Back(100,675,"SLM_Back.png"),Prev(200,575,"SLM_Prev.png"),Next(310,575,"SLM_Next.png")
{
	underliner_pic.loadFromFile("Underliner.png");
	underliner_image.setTexture(underliner_pic);
	underliner_image.setPosition(200, 75);
}

void Level_Select_Menu::file_reader()
{
	file_list.erase(file_list.begin(), file_list.end());
	std::string the_name;
	for (auto &p : std::experimental::filesystem::directory_iterator("."))
	{
		the_name = p.path().string();
		if (the_name.find(".lvl") != std::string::npos)
		{
			the_name = the_name.substr(2, the_name.size() - 6);
			std::cout << the_name << std::endl;
			file_list.push_back(the_name);
		}
	}
	number_of_files = file_list.size();
	if (number_of_files == 0)
	{
		number_of_sites = 1;
	}
	else
	{
		number_of_sites = 1 + number_of_files / 20;
		if ((number_of_files % 20) == 0)
		{
			number_of_sites--;
		}
	}
	current_site = 1;
	current_file = 1;
}

std::string Level_Select_Menu::get_file_string(int i)
{
	if (number_of_files == 0)
	{
		return "Failed to load any files";
	}
	else
	{
		return file_list[20*(current_site-1)+i];
	}
}

int Level_Select_Menu::how_much_elements_on_the_site()
{
	if(current_site==number_of_sites)
	{
		return file_list.size() - 20 * (current_site-1);
	}
	else
	{
		return 20;
	}
}

void Level_Select_Menu::change_current_site(int mode)
{
	switch (mode)
	{
	case 0:
	{
		if (current_site > 1)
		{
			change_current_file(2);
			current_site--;
		}
		break;
	}
	case 1:
	{
		if (current_site < number_of_sites)
		{
			change_current_file(2);
			current_site++;
		}
		break;
	}
	case 2:
	{
		current_site = 1;
		break;
	}
	default:
	{
		break;
	}
	}
}

void Level_Select_Menu::change_current_file(int mode)
{
	switch (mode)
	{
		case 0:
		{
			if (current_file > 1)
			{
				current_file--;
				underliner_image.move(0, -25);
			}
			break;
		}
		case 1:
		{
			if ((current_file < (file_list.size() - 20 * (current_site - 1)))&&(current_file<20))
			{
				current_file++;
				underliner_image.move(0, 25);
			}
			break;
		}
		case 2:
		{
			current_file = 1;
			underliner_image.setPosition(200, 75);
			break;
		}
		default:
		{
			break;
		}
	}
}

sf::Sprite Level_Select_Menu::get_underliner()
{
	return underliner_image;
}

std::string Level_Select_Menu::get_current_level()
{
	std::string file_name = file_list[20 * (current_site - 1) + current_file - 1];
	file_name.append(".lvl");
	return file_name;
}

Button & Level_Select_Menu::get_Load_Level()
{
	return Load_Level;
}

Button & Level_Select_Menu::get_Back()
{
	return Back;
}

Button & Level_Select_Menu::get_Next()
{
	return Next;
}

Button & Level_Select_Menu::get_Prev()
{
	return Prev;
}

Settings_Menu::Settings_Menu():Back(500,650,"SLM_Back.png")
{
	test_settings_file_state();
	font.loadFromFile("ariblk.ttf");
	load_settings_from_the_file(temporary_generator);
	UPs = new Button*[6];
	DOWNs = new Button*[6];
	amount = new sf::Text*[6];
	pic = new sf::Texture*[6];
	image = new sf::Sprite*[6];
	for (int i = 0; i < 6; i++)
	{
		pic[i] = new sf::Texture();
	}
	pic[0]->loadFromFile("kolanko_LD_100x100.png");
	pic[1]->loadFromFile("rurka_pion_100x100.png");
	pic[2]->loadFromFile("kolanko_RU_LD_100x100.png");
	pic[3]->loadFromFile("rurka_pion_poziom_100x100.png");
	pic[4]->loadFromFile("Timer_input.png");
	pic[5]->loadFromFile("Timer_pipe.png");
	for (int i = 0; i < 6; i++)
	{
		UPs[i] = new Button(50 + i * 200, 50, "Up.png");
		DOWNs[i] = new Button(50 + i * 200, 450, "Down.png");
		amount[i] = new sf::Text(std::to_string(temporary_generator[i]), font);
		amount[i]->setPosition(50 + i * 200, 350);
		amount[i]->setFillColor(sf::Color::White);
		image[i] = new sf::Sprite(*pic[i]);
		image[i]->setPosition(50 + i * 200, 200);
	}
}

Settings_Menu::~Settings_Menu()
{
	for (int i = 0; i < 6; i++)
	{
		delete UPs[i];
		delete DOWNs[i];
		delete amount[i];
		delete image[i];
		delete pic[i];
	}
	delete[] UPs;
	delete[] DOWNs;
	delete[] amount;
	delete[] image;
	delete[] pic;
}

bool Settings_Menu::get_settings_file_state()
{
	return settings_file_state;
}

void Settings_Menu::test_settings_file_state()
{
	settings_file_state = 1;
	std::ifstream file;
	file.open("Settings.txt");
	if (!file.is_open())
	{
		std::cout << "Error! Settings file was not found" << std::endl;
		settings_file_state = 0;
	}
	else
	{
		int some_int;
		int counter = 0;
		while (file >> some_int)
		{
			if (some_int <= 0)
			{
				settings_file_state = 0;
				break;
			}
			counter++;
			if (counter>6)
			{
				break;
			}
		}
		if (counter != 6)
		{
			settings_file_state = 0;
		}
		if (!settings_file_state)
		{
			std::cout << "File Settings contains improper values" << std::endl;
		}
	}
	file.close();
}

void Settings_Menu::load_settings_from_the_file(int * settings)
{
	test_settings_file_state();
	if (get_settings_file_state())
	{
		std::ifstream file;
		file.open("Settings.txt");
		for (int i = 0;i < 6;i++)
		{
			file >> settings[i];
		}
		file.close();
	}
	else
	{
		settings[0] = 6;
		settings[1] = 6;
		settings[2] = 5;
		settings[3] = 5;
		settings[4] = 30;
		settings[5] = 7;
	}
}

Button & Settings_Menu::get_Back()
{
	return Back;
}

Button * Settings_Menu::get_UP(int i)
{
	if ((i >= 0) && (i <= 5))
		return UPs[i];
	else
		return nullptr;
}

Button * Settings_Menu::get_DOWN(int i)
{
	if ((i >= 0) && (i <= 5))
		return DOWNs[i];
	else
		return nullptr;
}

sf::Text* Settings_Menu::get_amount(int i)
{
	return amount[i];
}

sf::Sprite * Settings_Menu::get_image(int i)
{
	return image[i];
}

void Settings_Menu::increase(int i)
{
	if (i < 4)
	{
		if (temporary_generator[i] < 10)
		{
			temporary_generator[i]++;
			amount[i]->setString(std::to_string(temporary_generator[i]));
		}
	}
	else if(i==4)
	{
		if (temporary_generator[i] < 60)
		{
			temporary_generator[i]++;
			amount[i]->setString(std::to_string(temporary_generator[i]));
		}
	}
	else if (i == 5)
	{
		if (temporary_generator[i] < 10)
		{
			temporary_generator[i]++;
			amount[i]->setString(std::to_string(temporary_generator[i]));
		}
	}
}

void Settings_Menu::decrease(int i)
{
	if (i < 4)
	{
		if (temporary_generator[i] > 1)
		{
			temporary_generator[i]--;
			amount[i]->setString(std::to_string(temporary_generator[i]));
		}
	}
	else if (i == 4)
	{
		if (temporary_generator[i] > 10)
		{
			temporary_generator[i]--;
			amount[i]->setString(std::to_string(temporary_generator[i]));
		}
	}
	else if (i == 5)
	{
		if (temporary_generator[i] > 3)
		{
			temporary_generator[i]--;
			amount[i]->setString(std::to_string(temporary_generator[i]));
		}
	}
}

bool Settings_Menu::save_settings_to_the_file()
{
	std::ofstream file;
	file.open("Settings.txt");
	if (file.is_open())
	{
		for (int i = 0;i < 6;i++)
		{
			file << temporary_generator[i] << " ";
		}
		file.close();
		return 1;
	}
	return 0;
}