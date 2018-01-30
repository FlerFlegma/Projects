#include "Game.h"

Game::Game() :app_window(sf::VideoMode(1200, 800, 32), "Pipe Dream.jpg"), mode(0), game_on(1),prompt_on(0)
{
	prompt.setPosition(400, 200);
}

void Game::main_loop()
{
	if (app_window.isOpen())
	{
		app_window.display();
	}
	while (app_window.isOpen())
	{
		sf::Event zdarzenie;
		sf::Vector2i mouse_pos = sf::Mouse::getPosition(app_window);

		switch (mode)
		{
			case 0:
			{
				mode_0_pre(mouse_pos);
				break;
			}
			case 1:
			{
				mode_1_pre(mouse_pos);
				break;
			}
			case 3:
			{
				mode_3_pre(mouse_pos);
				break;
			}
			default:
			{
				break;
			}
		}
		while (app_window.pollEvent(zdarzenie))
		{
			if (zdarzenie.type == sf::Event::Closed)
			{
				app_window.close();
			}
			switch (mode)
			{
				case 0:
				{
					mode_0_eventer(zdarzenie);
					break;
				}
				case 1:
				{
					mode_1_eventer(zdarzenie);
					break;
				}
				case 2:
				{
					mode_2_eventer(zdarzenie);
					break;
				}
				case 3:
				{
					mode_3_eventer(zdarzenie);
					break;
				}
				default:
				{
					break;
				}
			}
		}
		app_window.clear(sf::Color(43,103,24,0));

		switch (mode)
		{
			case 0:
			{
				mode_0_drawer();
				break;
			}
			case 1:
			{
				mode_1_drawer();
				break;
			}
			case 2:
			{
				mode_2_drawer_and_post();
				break;
			}
			case 3:
			{
				mode_3_drawer();
				break;
			}
			default:
			{
				break;
			}
		}
		app_window.display();
	}
}

void Game::mode_0_pre(sf::Vector2i mouse_pos)
{
	main_menu.get_Select_Level().deactivate();
	main_menu.get_Settings().deactivate();
	main_menu.get_Exit().deactivate();
	if ((mouse_pos.x >= 475) && (mouse_pos.x <= 725))
	{
		if ((mouse_pos.y >= 150) && (mouse_pos.y <= 200))
		{
			main_menu.get_Select_Level().activate();
		}
		else if ((mouse_pos.y >= 450) && (mouse_pos.y <= 500))
		{
			main_menu.get_Settings().activate();
		}
		else if ((mouse_pos.y >= 600) && (mouse_pos.y <= 650))
		{
			main_menu.get_Exit().activate();
		}
	}
}

void Game::mode_0_eventer(sf::Event zdarzenie)
{
	if (zdarzenie.type == sf::Event::MouseButtonPressed && zdarzenie.mouseButton.button == sf::Mouse::Left)
	{
		if (main_menu.get_Exit().get_is_active())
		{
			app_window.close();
		}
		if (main_menu.get_Select_Level().get_is_active())
		{
			main_menu.get_Select_Level().deactivate();
			mode = 1;
			settings_menu.load_settings_from_the_file(settings);
			level_select_menu.file_reader();
			level_select_menu.change_current_file(2);
			level_select_menu.change_current_site(2);
		}
		if (main_menu.get_Settings().get_is_active())
		{
			main_menu.get_Settings().deactivate();
			//settings_menu.load_settings_from_the_file(settings);
			mode = 3;
		}
	}
}

void Game::mode_0_drawer()
{
	app_window.draw(main_menu.get_Select_Level().get_image());
	app_window.draw(main_menu.get_Settings().get_image());
	app_window.draw(main_menu.get_Exit().get_image());
}

void Game::mode_1_pre(sf::Vector2i mouse_pos)
{
	level_select_menu.get_Load_Level().deactivate();
	level_select_menu.get_Back().deactivate();
	level_select_menu.get_Prev().deactivate();
	level_select_menu.get_Next().deactivate();
	if ((mouse_pos.y >= 675) && (mouse_pos.y <= 725))
	{
		if ((mouse_pos.x >= 850) && (mouse_pos.x <= 1050))
		{
			level_select_menu.get_Load_Level().activate();
		}
		else if ((mouse_pos.x >= 150) && (mouse_pos.x <= 350))
		{
			level_select_menu.get_Back().activate();
		}
	}
	else if ((mouse_pos.y >= 575) && (mouse_pos.y <= 600))
	{
		if ((mouse_pos.x >= 200) && (mouse_pos.x <= 300))
		{
			level_select_menu.get_Prev().activate();
		}
		else if ((mouse_pos.x >= 310) && (mouse_pos.x <= 410))
		{
			level_select_menu.get_Next().activate();
		}
	}
}

void Game::mode_1_eventer(sf::Event zdarzenie)
{
	if (prompt_on)
	{
		if (zdarzenie.type == sf::Event::MouseButtonPressed || zdarzenie.type == sf::Event::KeyPressed)
			prompt_on = 0;
	}
	else
	{
		if (zdarzenie.type == sf::Event::MouseButtonPressed && zdarzenie.mouseButton.button == sf::Mouse::Left)
		{
			if (level_select_menu.get_Back().get_is_active())
			{
				level_select_menu.get_Back().deactivate();
				mode = 0;
			}
			else if (level_select_menu.get_Next().get_is_active())
			{
				level_select_menu.change_current_site(1);
			}
			else if (level_select_menu.get_Prev().get_is_active())
			{
				level_select_menu.change_current_site(0);
			}
			else if (level_select_menu.get_Load_Level().get_is_active())
			{
				if (level_select_menu.how_much_elements_on_the_site() != 0)
				{
					level_select_menu.get_Load_Level().deactivate();
					turn_the_level_on(level_select_menu.get_current_level());
				}
			}
		}
		else if (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Up)
		{
			level_select_menu.change_current_file(0);
		}
		else if (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Down)
		{
			level_select_menu.change_current_file(1);
		}
		else if (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Return)
		{
			level_select_menu.get_Load_Level().deactivate();
			turn_the_level_on(level_select_menu.get_current_level());
		}
	}
}

void Game::mode_1_drawer()
{
	app_window.draw(level_select_menu.get_Load_Level().get_image());
	app_window.draw(level_select_menu.get_Back().get_image());
	app_window.draw(level_select_menu.get_Prev().get_image());
	app_window.draw(level_select_menu.get_Next().get_image());
	if (level_select_menu.how_much_elements_on_the_site() == 0)
	{
		draw_text_from_string("There are not any files in game folder", 200, 75,15);
	}
	else
	{
		draw_list();
	}
	if (prompt_on)
	{
		app_window.draw(prompt);
	}
}

void Game::mode_2_eventer(sf::Event zdarzenie)
{
	if (level->get_level_ON())
	{
		if (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Up)
		{
			level->pointer_move(1);
		}
		if (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Down)
		{
			level->pointer_move(3);
		}
		if (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Left)
		{
			level->pointer_move(4);
		}
		if (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Right)
		{
			level->pointer_move(2);
		}
		if (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Return)
		{
			level->new_pipe_from_generator_inserter();
		}
		if (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::S)
		{
			level->water_speed_up();
		}
	}
	else if (prompt_on)
	{
		if (zdarzenie.type == sf::Event::MouseButtonPressed || zdarzenie.type == sf::Event::KeyPressed)
		{
			prompt_on = 0;
			delete level;
			mode = 1;
		}
	}
}

void Game::mode_2_drawer_and_post()
{
	if (level->get_level_ON())
	{
		level->water_flow_control();
	}
	for (int j = 0;j < level->get_y_dim();j++)
	{
		for (int i = 0;i < level->get_x_dim();i++)
		{
			app_window.draw(level->Array_elem_get_image(i, j));
		}
	}

	for (int i = 0; i < level->get_amount_of_elem();i++)
	{
		app_window.draw(level->uber_generator_get_image(i));
	}

	app_window.draw(level->pointer_get_image());
	app_window.draw(level->get_score_text());
	app_window.draw(level->get_time_text());
	
	if ((!level->get_level_ON())&&(!prompt_on))
	{
		prompt_on = 1;
		if (level->get_success())
		{
			prompt_pic.loadFromFile("Success.png");
		}
		else
		{
			prompt_pic.loadFromFile("Fail.png");
		}
		prompt.setTexture(prompt_pic);
	}
	if (prompt_on)
	{
		app_window.draw(prompt);
		sf::Text score(level->get_score_text_2());
		score.setPosition(550, 425);
		app_window.draw(score);
	}
}

void Game::mode_3_pre(sf::Vector2i mouse_pos)
{
	for (int i = 0;i < 6;i++)
	{
		settings_menu.get_UP(i)->deactivate();
		settings_menu.get_DOWN(i)->deactivate();
	}
	settings_menu.get_Back().deactivate();
	if ((mouse_pos.y >= 50) && (mouse_pos.y <= 150))
	{
		int smart_x = (mouse_pos.x - 50) / 100;
		if (!(smart_x % 2))
		{
			if (settings_menu.get_UP(smart_x / 2))
			{
				settings_menu.get_UP(smart_x / 2)->activate();
			}
		}
	}
	else if ((mouse_pos.y >= 450) && (mouse_pos.y <= 550))
	{
		int smart_x = (mouse_pos.x - 50) / 100;
		if (!(smart_x % 2))
		{
			if (settings_menu.get_DOWN(smart_x / 2))
			{
				settings_menu.get_DOWN(smart_x / 2)->activate();
			}
		}
	}
	else if ((mouse_pos.x >= 500) && (mouse_pos.x <= 700) && (mouse_pos.y >= 650) && (mouse_pos.y < 700))
	{
		settings_menu.get_Back().activate();
	}
}

void Game::mode_3_eventer(sf::Event zdarzenie)
{
	if (zdarzenie.type == sf::Event::MouseButtonPressed && zdarzenie.mouseButton.button == sf::Mouse::Left)
	{
		for (int i = 0;i < 6;i++)
		{
			if (settings_menu.get_UP(i)->get_is_active())
			{
				settings_menu.increase(i);
			}
			else if (settings_menu.get_DOWN(i)->get_is_active())
			{
				settings_menu.decrease(i);
			}
		}
		if (settings_menu.get_Back().get_is_active())
		{
			settings_menu.get_Back().deactivate();
			mode = 0;
			settings_menu.save_settings_to_the_file();
		}
	}
}

void Game::mode_3_drawer()
{
	for (int i = 0;i < 6;i++)
	{
		app_window.draw(settings_menu.get_UP(i)->get_image());
		app_window.draw(settings_menu.get_DOWN(i)->get_image());
		app_window.draw(*settings_menu.get_amount(i));
		app_window.draw(*settings_menu.get_image(i));
		app_window.draw(settings_menu.get_Back().get_image());
	}
}

void Game::draw_text_from_string(std::string the_name, int pos_x, int pos_y, int size, int number_of_letters)
{
	std::string subtracted;
	if (number_of_letters != -1)
	{
		subtracted = the_name.substr(0, number_of_letters);
	}
	else
	{
		subtracted = the_name;
	}
	sf::Text the_text;
	sf::Font font;
	font.loadFromFile("ariblk.ttf");
	the_text.setFillColor(sf::Color::White);
	the_text.setFont(font);
	the_text.setPosition(pos_x, pos_y);
	the_text.setString(subtracted);
	the_text.setCharacterSize(size);
	app_window.draw(the_text);
}

void Game::draw_list()
{
	app_window.draw(level_select_menu.get_underliner());
	for (int i = 0;i < level_select_menu.how_much_elements_on_the_site();i++)
	{
		draw_text_from_string(level_select_menu.get_file_string(i),200,75+25*i,15,40);
	}
}

bool Game::test_level_file(std::string file_name)
{
	bool input_existence = 0, output_existence = 0;
	std::ifstream file;
	file.open(file_name);
	int number_of_columns = 0;
	int number_of_rows = 0;
	if (!file.is_open())
	{
		return 0;
	}
	char c;
	while (file >> c)
	{
		if (c == ',')
		{
			break;
		}
		else
		{
			if ((c >= '0') && (c <= '3'))
			{
				number_of_columns++;
				if (c == '2')
				{
					if (input_existence)
					{
						file.close();
						return 0;
					}
					else
					{
						input_existence = 1;
					}
				}
				else if (c == '3')
				{
					if (output_existence)
					{
						file.close();
						return 0;
					}
					else
					{
						output_existence = 1;
					}
				}
			}
		}
	}
	if (number_of_columns == 0)
	{
		file.close();
		return 0;
	}
	number_of_rows++;
	int some_counter = 0;
	while (file>>c)
	{
		if (c == ',')
		{
			if (some_counter != number_of_columns)
			{
				file.close();
				return 0;
			}
			else
			{
				some_counter = 0;
				number_of_rows++;
			}
		}
		else if ((c >= '0') && (c <= '3'))
		{
			some_counter++;
			if (c == '2')
			{
				if (input_existence)
				{
					file.close();
					return 0;
				}
				else
				{
					input_existence = 1;
				}
			}
			else if (c == '3')
			{
				if (output_existence)
				{
					file.close();
					return 0;
				}
				else
				{
					output_existence = 1;
				}
			}
		}
	}
	if ((!output_existence) || (!input_existence))
	{
		file.close();
		return 0;
	}
	dim_x = number_of_columns;
	dim_y = number_of_rows;
	return 1;
}

void Game::turn_the_level_on(std::string file_name)
{
	if (test_level_file(file_name))
	{
		mode = 2;
		int generator[4];
		for (int i = 0;i < 4;i++)
		{
			generator[i] = settings[i];
		}
		level = new Level(file_name, 100, 50, dim_x, dim_y, generator, 0, 0, 5, settings[4], settings[5], 600, 0, 300, 0);
	}
	else
	{
		prompt_on = 1;
		prompt_pic.loadFromFile("Error_Load_Level.png");
		prompt.setTexture(prompt_pic);
	}
}
