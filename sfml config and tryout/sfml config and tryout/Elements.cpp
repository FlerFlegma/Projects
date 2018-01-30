#include "Elements.h"

Element::Element(int x, int y)
{
	pos_x = x;
	pos_y = y;
}

//class: Element
void Element::move_elem(int x, int y)
{
	pos_x += x;
	pos_y += y;
	image.move(x, y);
}

void Element::set_position(int x, int y)
{
	pos_x = x;
	pos_y = y;
	image.setPosition(pos_x, pos_y);
}

sf::Sprite Element::get_image()
{
	return image;
}

int Element::get_x()
{
	return pos_x;
}

int Element::get_y()
{
	return pos_y;
}

bool Element::get_overwritting_possibility()
{
	return overwritting_possibility;
}

//class Square pointer
Square_pointer::Square_pointer(int x, int y):Element(x, y)
{
	min_x = x;
	min_y = y;
	if (!pic.loadFromFile("pointer_2_50x50.png"))
		std::cout << "ERROR" << std::endl;
	image.setTexture(pic);
	image.setPosition(pos_x, pos_y);
}

void Square_pointer::pointer_mover(int mode, int x_dim, int y_dim)
{
	switch (mode)
	{
		case 1:
		{
			if (((pos_y - min_y) / 50) > 0)
			{
				move_elem(0, -50);
			}
			break;
		}
		case 2:
		{
			if (((pos_x - min_x) / 50) < (x_dim - 1))
			{
				move_elem(50, 0);
			}
			break;
		}
		case 3:
		{
			if (((pos_y - min_y) / 50) < (y_dim - 1))
			{
				move_elem(0, 50);
			}
			break;
		}
		case 4:
		{
			if (((pos_x - min_x) / 50) > 0)
			{
				move_elem(-50, 0);
			}
			break;
		}
		default:
			break;
	}
}

//class: Void_elem
Void_elem::Void_elem(int x, int y):Element(x,y)
{
	overwritting_possibility = 1;
	if (!pic.loadFromFile("void_elem_50x50.png"))
		std::cout << "ERROR" << std::endl;
	image.setTexture(pic);
	image.setPosition(pos_x, pos_y);
}

//class Terrain
Terrain::Terrain(int x, int y) :Element(x, y)
{
	overwritting_possibility = 0;
	if (!pic.loadFromFile("terrain_50x50.png"))
		std::cout << "ERROR" << std::endl;
	image.setTexture(pic);
	image.setPosition(pos_x, pos_y);
}

//Pipe classess

Pipe::Pipe(int x, int y) :Element(x, y) { water1 = 0; }

int Pipe::water_fill(int input)
{
	if (water1)
	{
		return 0;
	}
	else
	{
		if (input == output1)
		{
			std::swap(input1, output1);
		}
		if (input1 == input)
		{
			overwritting_possibility = 0;
			water1 = 1;
			return output1;
		}
	}
	return 0;
}

Pipe_UD::Pipe_UD(int x, int y): Pipe(x, y)
{
	input1 = 1;
	output1 = 3;
	overwritting_possibility = 1;
	if (!pic.loadFromFile("rurka_pion_50x50.png"))
		std::cout << "ERROR" << std::endl;
	image.setTexture(pic);
	image.setPosition(pos_x, pos_y);
}

void Pipe_UD::update()
{
	if (!water1)
	{
		if (!pic.loadFromFile("rurka_pion_50x50.png"))
			std::cout << "ERROR" << std::endl;
		image.setTexture(pic);
		image.setPosition(pos_x, pos_y);
	}
	else
	{
		if (!pic.loadFromFile("rurka_pion_woda_50x50.png"))
			std::cout << "ERROR" << std::endl;
		image.setTexture(pic);
		image.setPosition(pos_x, pos_y);
	}
}

Pipe_RL::Pipe_RL(int x, int y) : Pipe(x, y)
{
	input1 = 2;
	output1 = 4;
	overwritting_possibility = 1;
	if (!pic.loadFromFile("rurka_poziom_50x50.png"))
		std::cout << "ERROR" << std::endl;
	image.setTexture(pic);
	image.setPosition(pos_x, pos_y);
}

void Pipe_RL::update()
{
	if (!water1)
	{
		if (!pic.loadFromFile("rurka_poziom_50x50.png"))
			std::cout << "ERROR" << std::endl;
		image.setTexture(pic);
		image.setPosition(pos_x, pos_y);
	}
	else
	{
		if (!pic.loadFromFile("rurka_poziom_woda_50x50.png"))
			std::cout << "ERROR" << std::endl;
		image.setTexture(pic);
		image.setPosition(pos_x, pos_y);
	}
}

Pipe_RU::Pipe_RU(int x, int y) : Pipe(x, y)
{
	input1 = 2;
	output1 = 1;
	overwritting_possibility = 1;
	if (!pic.loadFromFile("kolanko_RU_50x50.png"))
		std::cout << "ERROR" << std::endl;
	image.setTexture(pic);
	image.setPosition(pos_x, pos_y);
}

void Pipe_RU::update()
{
	if (!water1)
	{
		if (!pic.loadFromFile("kolanko_RU_50x50.png"))
			std::cout << "ERROR" << std::endl;
		image.setTexture(pic);
		image.setPosition(pos_x, pos_y);
	}
	else
	{
		if (!pic.loadFromFile("kolanko_RU_woda_50x50.png"))
			std::cout << "ERROR" << std::endl;
		image.setTexture(pic);
		image.setPosition(pos_x, pos_y);
	}
}

Pipe_RD::Pipe_RD(int x, int y) : Pipe(x, y)
{
	input1 = 2;
	output1 = 3;
	overwritting_possibility = 1;
	if (!pic.loadFromFile("kolanko_RD_50x50.png"))
		std::cout << "ERROR" << std::endl;
	image.setTexture(pic);
	image.setPosition(pos_x, pos_y);
}

void Pipe_RD::update()
{
	if (!water1)
	{
		if (!pic.loadFromFile("kolanko_RD_50x50.png"))
			std::cout << "ERROR" << std::endl;
		image.setTexture(pic);
		image.setPosition(pos_x, pos_y);
	}
	else
	{
		if (!pic.loadFromFile("kolanko_RD_woda_50x50.png"))
			std::cout << "ERROR" << std::endl;
		image.setTexture(pic);
		image.setPosition(pos_x, pos_y);
	}
}

Pipe_LU::Pipe_LU(int x, int y) : Pipe(x, y)
{
	input1 = 4;
	output1 = 1;
	overwritting_possibility = 1;
	if (!pic.loadFromFile("kolanko_LU_50x50.png"))
		std::cout << "ERROR" << std::endl;
	image.setTexture(pic);
	image.setPosition(pos_x, pos_y);
}

void Pipe_LU::update()
{
	if (!water1)
	{
		if (!pic.loadFromFile("kolanko_LU_50x50.png"))
			std::cout << "ERROR" << std::endl;
		image.setTexture(pic);
		image.setPosition(pos_x, pos_y);
	}
	else
	{
		if (!pic.loadFromFile("kolanko_LU_woda_50x50.png"))
			std::cout << "ERROR" << std::endl;
		image.setTexture(pic);
		image.setPosition(pos_x, pos_y);
	}
}

Pipe_LD::Pipe_LD(int x, int y) : Pipe(x, y)
{
	input1 = 4;
	output1 = 3;
	overwritting_possibility = 1;
	if (!pic.loadFromFile("kolanko_LD_50x50.png"))
		std::cout << "ERROR" << std::endl;
	image.setTexture(pic);
	image.setPosition(pos_x, pos_y);
}

void Pipe_LD::update()
{
	if (!water1)
	{
		if (!pic.loadFromFile("kolanko_LD_50x50.png"))
			std::cout << "ERROR" << std::endl;
		image.setTexture(pic);
		image.setPosition(pos_x, pos_y);
	}
	else
	{
		if (!pic.loadFromFile("kolanko_LD_woda_50x50.png"))
			std::cout << "ERROR" << std::endl;
		image.setTexture(pic);
		image.setPosition(pos_x, pos_y);
	}
}

Pipe_UD_RL::Pipe_UD_RL(int x, int y):Pipe(x,y)
{
	input1 = 1;
	output1 = 3;
	input2 = 2;
	output2 = 4;
	water2 = 0;
	overwritting_possibility = 1;
	if (!pic.loadFromFile("rurka_pion_poziom_50x50.png"))
		std::cout << "ERROR" << std::endl;
	image.setTexture(pic);
	image.setPosition(pos_x, pos_y);
}

int Pipe_UD_RL::water_fill(int input)
{
	int k = Pipe::water_fill(input);
	if (k)
	{
		return k;
	}
	else
	{
		if(water2)
		{
			return 0;
		}
		else
		{
			if (input == output2)
			{
				std::swap(input2, output2);
			}
			if (input2 == input)
			{
				overwritting_possibility = 0;
				water2 = 1;
				return output2;
			}
		}
	}
	return 0;
}

void Pipe_UD_RL::update()
{
	if (!water1)
	{
		if (!water2)
		{
			if (!pic.loadFromFile("rurka_pion_poziom_50x50.png"))
				std::cout << "ERROR" << std::endl;
			image.setTexture(pic);
			image.setPosition(pos_x, pos_y);
		}
		else
		{
			if (!pic.loadFromFile("rurka_pion_poziom_woda_poziom_50x50.png"))
				std::cout << "ERROR" << std::endl;
			image.setTexture(pic);
			image.setPosition(pos_x, pos_y);
		}
	}
	else
	{
		if (!water2)
		{
			if (!pic.loadFromFile("rurka_pion_poziom_woda_pion_50x50.png"))
				std::cout << "ERROR" << std::endl;
			image.setTexture(pic);
			image.setPosition(pos_x, pos_y);
		}
		else
		{
			if (!pic.loadFromFile("rurka_pion_poziom_woda_full_50x50.png"))
				std::cout << "ERROR" << std::endl;
			image.setTexture(pic);
			image.setPosition(pos_x, pos_y);
		}
	}
}

Pipe_RU_LD::Pipe_RU_LD(int x, int y):Pipe(x,y)
{
	input1 = 1;
	output1 = 2;
	input2 = 3;
	output2 = 4;
	water2 = 0;
	overwritting_possibility = 1;
	if (!pic.loadFromFile("kolanko_RU_LD_50x50.png"))
		std::cout << "ERROR" << std::endl;
	image.setTexture(pic);
	image.setPosition(pos_x, pos_y);
}

int Pipe_RU_LD::water_fill(int input)
{
	int k = Pipe::water_fill(input);
	if (k)
	{
		return k;
	}
	else
	{
		if (water2)
		{
			return 0;
		}
		else
		{
			if (input == output2)
			{
				std::swap(input2, output2);
			}
			if (input2 == input)
			{
				overwritting_possibility = 0;
				water2 = 1;
				return output2;
			}
		}
	}
	return 0;
}

void Pipe_RU_LD::update()
{
	if (!water1)
	{
		if (!water2)
		{
			if (!pic.loadFromFile("kolanko_RU_LD_50x50.png"))
				std::cout << "ERROR" << std::endl;
			image.setTexture(pic);
			image.setPosition(pos_x, pos_y);
		}
		else
		{
			if (!pic.loadFromFile("kolanko_RU_LD_woda_LD_50x50.png"))
				std::cout << "ERROR" << std::endl;
			image.setTexture(pic);
			image.setPosition(pos_x, pos_y);
		}
	}
	else
	{
		if (!water2)
		{
			if (!pic.loadFromFile("kolanko_RU_LD_woda_RU_50x50.png"))
				std::cout << "ERROR" << std::endl;
			image.setTexture(pic);
			image.setPosition(pos_x, pos_y);
		}
		else
		{
			if (!pic.loadFromFile("kolanko_RU_LD_woda_full_50x50.png"))
				std::cout << "ERROR" << std::endl;
			image.setTexture(pic);
			image.setPosition(pos_x, pos_y);
		}
	}
}

Pipe_RD_LU::Pipe_RD_LU(int x, int y):Pipe(x,y)
{
	input1 = 3;
	output1 = 2;
	input2 = 1;
	output2 = 4;
	water2 = 0;
	overwritting_possibility = 1;
	if (!pic.loadFromFile("kolanko_RD_LU_50x50.png"))
		std::cout << "ERROR" << std::endl;
	image.setTexture(pic);
	image.setPosition(pos_x, pos_y);
}

int Pipe_RD_LU::water_fill(int input)
{
	int k = Pipe::water_fill(input);
	if (k)
	{
		return k;
	}
	else
	{
		if (water2)
		{
			return 0;
		}
		else
		{
			if (input == output2)
			{
				std::swap(input2, output2);
			}
			if (input2 == input)
			{
				overwritting_possibility = 0;
				water2 = 1;
				return output2;
			}
		}
	}
	return 0;
}

void Pipe_RD_LU::update()
{
	if (!water1)
	{
		if (!water2)
		{
			if (!pic.loadFromFile("kolanko_RD_LU_50x50.png"))
				std::cout << "ERROR" << std::endl;
			image.setTexture(pic);
			image.setPosition(pos_x, pos_y);
		}
		else
		{
			if (!pic.loadFromFile("kolanko_RD_LU_woda_LU_50x50.png"))
				std::cout << "ERROR" << std::endl;
			image.setTexture(pic);
			image.setPosition(pos_x, pos_y);
		}
	}
	else
	{
		if (!water2)
		{
			if (!pic.loadFromFile("kolanko_RD_LU_woda_RD_50x50.png"))
				std::cout << "ERROR" << std::endl;
			image.setTexture(pic);
			image.setPosition(pos_x, pos_y);
		}
		else
		{
			if (!pic.loadFromFile("kolanko_RD_LU_woda_full_50x50.png"))
				std::cout << "ERROR" << std::endl;
			image.setTexture(pic);
			image.setPosition(pos_x, pos_y);
		}
	}
}

INPUT::INPUT(int x, int y):Pipe(x,y)
{
	input1 = 4;
	output1 = 2;
	overwritting_possibility = 0;
	if (!pic.loadFromFile("input_50x50.png"))
		std::cout << "ERROR" << std::endl;
	image.setTexture(pic);
	image.setPosition(pos_x, pos_y);
}

int INPUT::water_fill(int input)
{
	if (water1)
	{
		return 0;
	}
	else
	{
		water1 = 1;
		overwritting_possibility = 0;
		return output1;
	}
	return 0;
}

void INPUT::update()
{
	if (!water1)
	{
		if (!pic.loadFromFile("input_50x50.png"))
			std::cout << "ERROR" << std::endl;
		image.setTexture(pic);
		image.setPosition(pos_x, pos_y);
	}
	else
	{
		if (!pic.loadFromFile("input_woda_50x50.png"))
			std::cout << "ERROR" << std::endl;
		image.setTexture(pic);
		image.setPosition(pos_x, pos_y);
	}
}

OUTPUT::OUTPUT(int x, int y) :Pipe(x, y)
{
	input1 = 4;
	output1 = 5;
	overwritting_possibility = 0;
	if (!pic.loadFromFile("output_50x50.png"))
		std::cout << "ERROR" << std::endl;
	image.setTexture(pic);
	image.setPosition(pos_x, pos_y);
}

int OUTPUT::water_fill(int input)
{
	if (water1)
	{
		return 0;
	}
	else
	{
		if (input1 == input)
		{
			overwritting_possibility = 0;
			water1 = 1;
			return output1;
		}
	}
	return 0;
}

void OUTPUT::update()
{
	if (!water1)
	{
		if (!pic.loadFromFile("output_50x50.png"))
			std::cout << "ERROR" << std::endl;
		image.setTexture(pic);
		image.setPosition(pos_x, pos_y);
	}
	else
	{
		if (!pic.loadFromFile("output_woda_50x50.png"))
			std::cout << "ERROR" << std::endl;
		image.setTexture(pic);
		image.setPosition(pos_x, pos_y);
	}
}
