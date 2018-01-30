#pragma once
#include <SFML/Graphics.hpp>
#include "Elements.h"
#include "Uber_generator.h"
#include "Water.h"
#include <fstream>
#include <iostream>
#include <string> 

class Level
{
private:
	Element ***ARRAY;
	Square_pointer square_pointer;
	Uber_generator uber_generator;
	Water water;
	int x_dim;
	int y_dim;
	int w_pos_x;//water
	int w_pos_y;//water
	int position_on_the_board_x;
	int position_on_the_board_y;
	bool level_ON;
	bool success;
	int score;
	sf::Font Font;
	sf::Text score_text;
	sf::Text score_text_2;
	sf::Text time_text;
public:
	Level(std::string file_name, int position_x, int position_y, int dim_x, int dim_y, int *generator, int pos_of_gen_x, int pos_of_gen_y, int how_many_gen_elem, double input_outflow_time, double pipe_outflow_time, int score_pos_x, int score_pos_y, int time_pos_x, int time_pos_y);
	~Level();
	void pointer_move(int mode);
	void new_pipe_from_generator_inserter();
	sf::Sprite Array_elem_get_image(int x,int y);
	sf::Sprite pointer_get_image();
	sf::Sprite uber_generator_get_image(int x);
	int get_x_dim();
	int get_y_dim();
	int get_amount_of_elem();
	void water_flow_control();
	bool get_level_ON();
	bool get_success();
	void score_add(int how_much);
	sf::Text get_score_text();
	sf::Text get_score_text_2();
	sf::Text get_time_text();
	void water_speed_up();
};