#pragma once
#include "snake.h"
#include "Evolucio.h"
#include <algorithm>
#include <iterator>
#include <string>

class Jatek
{
public:
	Jatek(SDL_Renderer* renderer, std::vector<unsigned>& felepites);
	void addFal(int x, int y, int h, int w, SDL_Texture* kep);
	void update();
	void kiir();
	int getKigyodb(){return kigyok.size();}
	void setLatas(bool ertek);
	std::vector<double> beolvasEgyed(std::string fajlNev);
	void adatBeker();
	~Jatek();
private:
	unsigned jelenlegiGeneracio;
	unsigned legjobbFittness;
	int egyedDb;
	int generacio;
	double mutacio;
	double keresztezes;
	std::string legjobb;
	std::string kezdo;
	std::vector<Snake> kigyok;
	std::vector<fal> falak;
	std::vector<unsigned> _felepites;
	std::vector<egyed> egyedek;
	SDL_Texture* kep;
	SDL_Texture* egerkep;
	SDL_Renderer* _renderer;
};