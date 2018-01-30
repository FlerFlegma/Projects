#pragma once
#include <SFML/Graphics.hpp>
#include "Elements.h"
#include <iostream>
#include <ctime>

class Water
{
private:
	int direction;
	double water_input_outflow;
	double water_pipe_outflow;
	bool stage;
	time_t start;
	double time_left;
public:
	Water(double input_outflow_time, double pipe_outflow_time);
	int Move_Water(Element *elem);
	int Water_Loop(Element *elem);
	double get_time_left();
	void water_speed_up();
};