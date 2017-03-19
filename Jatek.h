#pragma once
#include "snake.h"
#include "Evolucio.h"
#include <algorithm>

class Jatek
{
public:
	Jatek(unsigned darab,unsigned generacio, SDL_Renderer* renderer, std::vector<unsigned>& felepites);
	void addFal(int x, int y, int h, int w, SDL_Texture* kep);
	void update(SDL_Event &esemeny);
	void kiir();
	int getKigyodb(){return kigyok.size();}
	~Jatek();
private:
	unsigned _darab;
	unsigned _generacio;
	unsigned jelenlegiGeneracio;
	std::vector<Snake> kigyok;
	std::vector<fal> falak;
	std::vector<unsigned> _felepites;
	std::vector<egyed> egyedek;
	SDL_Texture* kep;
	SDL_Texture* egerkep;
	SDL_Renderer* _renderer;
};