#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Element
{
protected:
	int pos_x;
	int pos_y;
	bool overwritting_possibility;
	sf::Texture pic;
	sf::Sprite image;
public:
	Element(int x, int y);
	virtual ~Element(){}
	void move_elem(int x, int y);
	void set_position(int x, int y);
	sf::Sprite get_image();
	int get_x();
	int get_y();
	bool get_overwritting_possibility();
};

class Square_pointer :public Element
{
protected:
	int min_x;
	int min_y;
public:
	Square_pointer(int x, int y);
	void pointer_mover(int mode,int x_dim, int y_dim);
};

class Void_elem : public Element
{
public:
	Void_elem(int x, int y);
};

class Terrain : public Element
{
public:
	Terrain(int x, int y);
};

class Pipe : public Element
{
protected:
	int input1;
	int output1;
	bool water1;
public:
	Pipe(int x, int y);
	virtual ~Pipe() {}
	virtual int water_fill(int input);
	virtual void update() = 0;
};

class Pipe_UD : public Pipe
{
public:
	Pipe_UD(int x, int y);
	void update();
};

class Pipe_RL : public Pipe
{
public:
	Pipe_RL(int x, int y);
	void update();
};

class Pipe_RU : public Pipe
{
public:
	Pipe_RU(int x, int y);
	void update();
};

class Pipe_RD : public Pipe
{
public:
	Pipe_RD(int x, int y);
	void update();
};

class Pipe_LU : public Pipe
{
public:
	Pipe_LU(int x, int y);
	void update();
};

class Pipe_LD : public Pipe
{
public:
	Pipe_LD(int x, int y);
	void update();
};

class Pipe_UD_RL : public Pipe
{
protected:
	int input2;
	int output2;
	bool water2;
public:
	Pipe_UD_RL(int x, int y);
	int water_fill(int input);
	void update();
};

class Pipe_RU_LD : public Pipe
{
protected:
	int input2;
	int output2;
	bool water2;
public:
	Pipe_RU_LD(int x, int y);
	int water_fill(int input);
	void update();
};

class Pipe_RD_LU : public Pipe
{
protected:
	int input2;
	int output2;
	bool water2;
public:
	Pipe_RD_LU(int x, int y);
	int water_fill(int input);
	void update();
};

class INPUT : public Pipe
{
public:
	INPUT(int x, int y);
	int water_fill(int input);
	void update();
};

class OUTPUT : public Pipe
{
public:
	OUTPUT(int x, int y);
	int water_fill(int input);
	void update();
};
