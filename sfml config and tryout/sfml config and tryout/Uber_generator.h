#pragma once
#include <SFML/Graphics.hpp>
#include "Elements.h"
#include <iostream>

class Uber_generator
{
private:
	Element **UBER_GENERATOR;
	int position_of_the_generator_x;
	int position_of_the_generator_y;
	int generator_tableaux[4];
	int max_gen;
	int amount_of_elem;
public:
	Uber_generator(int x, int y, int *generator, int how_many_elements);
	~Uber_generator();
	int pipe_generator();
	Element* pipe_assigner_to_UBER_GENERATOR();
	sf::Sprite UBER_GENERATOR_get_image(int x);
	Element* FIFO();
	int get_amount_of_elem();
};