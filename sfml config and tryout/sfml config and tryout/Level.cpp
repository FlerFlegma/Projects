#include "Level.h"

Level::Level(std::string file_name, int position_x, int position_y, int dim_x, int dim_y, int *generator, int pos_of_gen_x, int pos_of_gen_y, int how_many_gen_elem, double input_outflow_time, double pipe_outflow_time, int score_pos_x, int score_pos_y, int time_pos_x, int time_pos_y):square_pointer(position_x,position_y), uber_generator(pos_of_gen_x,pos_of_gen_y,generator, how_many_gen_elem),water(input_outflow_time, pipe_outflow_time)
{
	std::ifstream file;
	file.open(file_name);
	if (file.is_open())
	{
		level_ON = 1;

		x_dim = dim_x;
		y_dim = dim_y;

		ARRAY = new Element**[x_dim];
		for (int i = 0;i < x_dim;i++)
		{
			ARRAY[i] = new Element*[y_dim];
		}
		position_on_the_board_x = position_x;
		position_on_the_board_y = position_y;

		Font.loadFromFile("ariblk.ttf");
		time_text.setFont(Font);
		score_text.setFont(Font);
		score_text_2.setFont(Font);
		time_text.setPosition(time_pos_x, time_pos_y);
		time_text.setString(std::to_string((int)water.get_time_left()));
		time_text.setFillColor(sf::Color::White);
		score_text.setPosition(score_pos_x, score_pos_y);
		score = 0;
		score_text.setString(std::to_string(score));
		score_text.setFillColor(sf::Color::White);
		score_text_2.setFillColor(sf::Color::White);
		score_text_2.setPosition(score_pos_x, score_pos_y);

		for (int i = 0;i < y_dim;i++)
		{
			for (int j = 0;j < x_dim;j++)
			{
				char reader;
				do
				{
					file >> reader;
				} while ((reader > '3') || (reader < '0'));
				
				switch (reader)
				{
				case '0':
				{
					ARRAY[j][i] = new Void_elem(j * 50 + position_on_the_board_x, i * (50) + position_on_the_board_y);
					if (ARRAY[j][i] ==nullptr)
					{
						std::cout << "Creation error" << std::endl;
					}
					break;
				}
				case '1':
				{
					ARRAY[j][i] = new Terrain(j * 50 + position_on_the_board_x, i * (50) + position_on_the_board_y);
					if (ARRAY[j][i] == nullptr)
					{
						std::cout << "Creation error" << std::endl;
					}
					break;
				}
				case '2':
				{
					ARRAY[j][i] = new INPUT(j * 50 + position_on_the_board_x, i * (50) + position_on_the_board_y);
					w_pos_x = j;
					w_pos_y = i;
					if (ARRAY[j][i] == nullptr)
					{
						std::cout << "Creation error" << std::endl;
					}
					break;
				}
				case '3':
				{
					ARRAY[j][i] = new OUTPUT(j * 50 + position_on_the_board_x, i * (50) + position_on_the_board_y);
					if (ARRAY[j][i] == nullptr)
					{
						std::cout << "Creation error" << std::endl;
					}
					break;
				}
				default:
					break;
				}
			}
		}
		file.close();
	}
	else
	{
		std::cout << "File is not opened!" << std::endl;
	}
}

Level::~Level()
{
	for (int i = 0;i < x_dim;i++)
	{
		for (int j = 0;j < y_dim;j++)
		{
			delete ARRAY[i][j];
		}
		delete ARRAY[i];
	}
	delete ARRAY;
}

void Level::pointer_move(int mode)
{
	square_pointer.pointer_mover(mode, x_dim, y_dim);
}

void Level::new_pipe_from_generator_inserter()
{
	int x = square_pointer.get_x();
	int y = square_pointer.get_y();

	
	if (ARRAY[(x - position_on_the_board_x) / 50][(y - position_on_the_board_y) / 50]->get_overwritting_possibility())
	{
		Pipe *ptr= dynamic_cast<Pipe*>(ARRAY[(x - position_on_the_board_x) / 50][(y - position_on_the_board_y) / 50]);
		if (ptr != NULL)
		{
			score_add(-25);
		}
		delete ARRAY[(x - position_on_the_board_x) / 50][(y - position_on_the_board_y) / 50];
		ARRAY[(x - position_on_the_board_x) / 50][(y - position_on_the_board_y) / 50] = uber_generator.FIFO();
		ARRAY[(x - position_on_the_board_x) / 50][(y - position_on_the_board_y) / 50]->set_position(x, y);
		if (ARRAY[(x - position_on_the_board_x) / 50][(y - position_on_the_board_y) / 50] == nullptr)
		{
			std::cout << "Inserting error" << std::endl;
		}
	}
	
}

sf::Sprite Level::Array_elem_get_image(int x, int y)
{
	return ARRAY[x][y]->get_image();
}

sf::Sprite Level::pointer_get_image()
{
	return square_pointer.get_image();
}

sf::Sprite Level::uber_generator_get_image(int x)
{
	return uber_generator.UBER_GENERATOR_get_image(x);
}

int Level::get_x_dim()
{
	return x_dim;
}

int Level::get_y_dim()
{
	return y_dim;
}

int Level::get_amount_of_elem()
{
	return uber_generator.get_amount_of_elem();
}

void Level::water_flow_control()
{
	int k;
	if ((w_pos_x < x_dim) && (w_pos_x >= 0) && (w_pos_y < y_dim) && (w_pos_y >= 0))
	{
		 k = water.Water_Loop(ARRAY[w_pos_x][w_pos_y]);
	}
	else
	{
		k = 0;
	}

	if ((k > 0) && (k < 5))
	{
		score_add(100);
	}
	if (k == 5)
	{
		score_add(1000);
	}
	time_text.setString(std::to_string((int)water.get_time_left()));

	switch (k)
	{
		case -1:
		{
			break;
		}
		case 0:
		{
			success = 0;
			std::cout << "You lost! Good luck next time!" << std::endl;
			level_ON = 0;
			score_text_2.setString(std::to_string(score));
			break;
		}
		case 1:
		{
			w_pos_y--;
			break;
		}
		case 2:
		{
			w_pos_x++;
			break;
		}
		case 3:
		{
			w_pos_y++;
			break;
		}
		case 4:
		{
			w_pos_x--;
			break;
		}
		case 5:
		{
			success = 1;
			std::cout << "You won! You will beat Mario one day!" << std::endl;
			level_ON = 0;
			score_text_2.setString(std::to_string(score));
			break;
		}
		default:
		{
			break;
		}
	}
}

bool Level::get_level_ON()
{
	return level_ON;
}

bool Level::get_success()
{
	return success;
}

void Level::score_add(int how_much)
{
	score += how_much;
	score_text.setString(std::to_string(score));
}

sf::Text Level::get_score_text()
{
	return score_text;
}

sf::Text Level::get_score_text_2()
{
	return score_text_2;
}

sf::Text Level::get_time_text()
{
	return time_text;
}

void Level::water_speed_up()
{
	water.water_speed_up();
}
