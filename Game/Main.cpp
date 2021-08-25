#include "Game.h"
#include <fstream>

class Base
{
public:
	virtual void Read(std::istream& stream) = 0;
	virtual void Write(std::ostream& stream) = 0;
};

class A : public Base
{
public:

	virtual void Read(std::istream& stream) override
	{
		stream >> health ;
		stream >> speed;
	}

	virtual void Write(std::ostream& stream) override
	{
		stream << health << std::endl;
		stream << speed << std::endl;
	}

private:
	int health;
	float speed;
};


int main(int, char**)
{


	Game game;
	game.Initialize();



	

	//serialization
	A a;

	//a.Read(std::cin);
	std::fstream stream("config.txt", std::ios::out |std::ios::in);
	if (stream.is_open())
	{
		a.Read(stream);
		//a.Write(stream);

		stream.close();
	}
		

	a.Write(std::cout);

	//

	bool quit = false;
	SDL_Event event;
	

	while (!quit && !game.IsQuit())
	{
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}

		game.Update();
		game.Draw();
	}
	
	
	SDL_Quit();

	return 0;
}

