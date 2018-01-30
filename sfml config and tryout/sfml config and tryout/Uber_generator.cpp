#include "Uber_generator.h"

Uber_generator::Uber_generator(int x, int y, int *generator, int how_many_elements)
{
	max_gen = 0;
	for (int i = 0;i < 4;i++)
	{
		generator_tableaux[i] = generator[i];
		max_gen += generator[i];
	}

	position_of_the_generator_x=x;
	position_of_the_generator_y=y;

	amount_of_elem = how_many_elements;

	UBER_GENERATOR = new Element*[amount_of_elem];
	for (int i = 0;i < amount_of_elem;i++)
	{
		UBER_GENERATOR[i] = pipe_assigner_to_UBER_GENERATOR();
		if (UBER_GENERATOR[i]==nullptr)
		{
			std::cout << "Generator assignment error in constructor" << std::endl;
		}
		else
		{
			UBER_GENERATOR[i]->set_position(position_of_the_generator_x, position_of_the_generator_y + i * 50);
		}
	}
}

Uber_generator::~Uber_generator()
{
	for (int i = 0;i < 4;i++)
	{
		if (UBER_GENERATOR[i] != NULL)
			delete UBER_GENERATOR[i];
	}
	delete []UBER_GENERATOR;
}

int Uber_generator::pipe_generator()
{
	int number, nr_of_pipe = 1;
	number = std::rand() % max_gen;
	number++;
	while (number > generator_tableaux[nr_of_pipe - 1])
	{
		if (nr_of_pipe == 4)
		{
			break;
		}
		number -= generator_tableaux[nr_of_pipe - 1];
		nr_of_pipe++;
	}
	return nr_of_pipe;
}

Element * Uber_generator::pipe_assigner_to_UBER_GENERATOR()
{
	switch (pipe_generator())
	{
	case 1:
	{
		int number = std::rand() % 4;
		switch (number)
		{
		case 0:
		{
			Pipe_RU* ptr = new Pipe_RU(0, 0);
			return ptr;
			break;
		}
		case 1:
		{
			Pipe_RD* ptr = new Pipe_RD(0, 0);
			return ptr;
			break;
		}
		case 2:
		{
			Pipe_LU* ptr = new Pipe_LU(0, 0);
			return ptr;
			break;
		}
		case 3:
		{
			Pipe_LD* ptr = new Pipe_LD(0, 0);
			return ptr;
			break;
		}
		default:
		{
			return nullptr;
			break;
		}
		}
		break;
	}
	case 2:
	{
		int number = std::rand() % 2;
		if (number == 0)
		{
			Pipe_UD* ptr = new Pipe_UD(0, 0);
			return ptr;
		}
		else if (number == 1)
		{
			Pipe_RL* ptr = new Pipe_RL(0, 0);
			return ptr;
		}
		else
		{
			return nullptr;
		}
	}
	case 3:
	{
		int number = std::rand() % 2;
		if (number == 0)
		{
			Pipe_RU_LD* ptr = new Pipe_RU_LD(0, 0);
			return ptr;
		}
		else if (number == 1)
		{
			Pipe_RD_LU* ptr = new Pipe_RD_LU(0, 0);
			return ptr;
		}
		else
		{
			return nullptr;
		}
	}
	case 4:
	{
		Pipe_UD_RL* ptr = new Pipe_UD_RL(0, 0);
		return ptr;
	}
	default:
	{
		return nullptr;
		break;
	}
	}
	return nullptr;
}

sf::Sprite Uber_generator::UBER_GENERATOR_get_image(int x)
{
	return UBER_GENERATOR[x]->get_image();
}

Element * Uber_generator::FIFO()
{
	Element *ptr;
	ptr=UBER_GENERATOR[amount_of_elem - 1];
	for (int i = (amount_of_elem - 1);i > 0;i--)
	{
		UBER_GENERATOR[i] = UBER_GENERATOR[i - 1];
		if(UBER_GENERATOR[i]==nullptr)
		{
			std::cout << "Moving element in generator error" << std::endl;
		}
		else
		{
			UBER_GENERATOR[i]->move_elem(0, 50);
		}
	}
	UBER_GENERATOR[0] = pipe_assigner_to_UBER_GENERATOR();
	if (UBER_GENERATOR[0] == nullptr)
	{
		std::cout << "New element in pipe generator was not properly allocated" << std::endl;
		return nullptr;
	}
	if (ptr == nullptr)
	{
		std::cout << "Element leaving the generator does not exist" << std::endl;
		return nullptr;
	}
	return ptr;
}

int Uber_generator::get_amount_of_elem()
{
	return amount_of_elem;
}
