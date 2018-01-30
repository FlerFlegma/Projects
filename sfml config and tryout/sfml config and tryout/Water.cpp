#include "Water.h"

Water::Water(double input_outflow_time, double pipe_outflow_time):water_input_outflow(input_outflow_time),water_pipe_outflow(pipe_outflow_time),direction(4),stage(0),time_left(input_outflow_time)
{
	time(&start);
}

int Water::Move_Water(Element * elem)
{
	int k;
	Pipe *pipe = dynamic_cast<Pipe*>(elem);
	if (pipe == NULL)
	{
		return 0;
	}
	else
	{
		k = pipe->water_fill(direction);
		if (k)
		{
			pipe->update();
			if ((k == 1) || (k == 2))
			{
				direction = k + 2;
			}
			if ((k == 3) || (k == 4))
			{
				direction = k - 2;
			}
			return k;
		}
		else
		{
			return 0;
		}
	}
}

int Water::Water_Loop(Element * elem)
{
	time_t stop;
	time(&stop);
	if (!stage)
	{
		if (difftime(stop, start) >= water_input_outflow)
		{
			time(&start);
			stage = 1;
			return Move_Water(elem);
		}
		else
		{
			time_left = water_input_outflow - difftime(stop, start);
			return -1;
		}
	}
	else
	{
		if (difftime(stop, start) >= water_pipe_outflow)
		{
			time(&start);
			return Move_Water(elem);
		}
		else
		{
			time_left = water_pipe_outflow - difftime(stop, start);
			return -1;
		}
	}
}

double Water::get_time_left()
{
	return time_left;
}

void Water::water_speed_up()
{
	water_input_outflow = 1.0;
	water_pipe_outflow = 1.0;
}
