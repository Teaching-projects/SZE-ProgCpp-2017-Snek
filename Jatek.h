#pragma once
#include "snake.h"
#include <algorithm>

class Jatek
{
public:
	Jatek(unsigned darab, SDL_Renderer* renderer, std::vector<unsigned>& felepites);
	void addFal(int x, int y, int h, int w, SDL_Texture* kep);
	void update(SDL_Event &esemeny);
	void kiir();
	int getKigyodb(){return kigyok.size();}
	~Jatek();
private:
	std::vector<Snake> kigyok;
	std::vector<fal> falak;
	SDL_Texture* kep;
	SDL_Texture* egerkep;
	SDL_Renderer* _renderer;
};