#pragma once
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <stdlib.h> 
#include <time.h> 
#include <numeric>
#include "NeuralisHalo.h"
#include <math.h>
#include <limits>
#include <exception>

struct helyek{
	int x;
	int y;
	double szog;
};
struct fal{
	SDL_Rect rect;
	SDL_Texture* kep;
};
struct eger{
	SDL_Rect rect;
	bool keelUjHely;
};


class KigyoResz
{
public:
	KigyoResz(int x, int y, double szog);
	~KigyoResz();
	void updateHely(KigyoResz elozo);
	void kiir(SDL_Renderer *renderer, SDL_Texture* kep );
	std::vector<helyek>& getHelyek();
	void setSrcrect(int x, int y,int h, int w){srcrect.x=x;srcrect.y=y; srcrect.h=h;srcrect.w=w;};
	void setDstrect(int x, int y){dstrect.x=x; dstrect.y=y;};
	void setSzog(double szog){_szog=szog; if(szog>=360){_szog=0;}};
	double getSzog(){return _szog;};
	SDL_Rect getDstrect(){return dstrect;};
	void addHely(helyek hely){_hely.push_back(hely);};
private:
	std::vector<helyek> _hely;
	double _szog;
	SDL_Rect srcrect;
	SDL_Rect dstrect;
};

class Snake
{
public:
	Snake(int x, int y,SDL_Renderer *renderer, std::vector<unsigned> felepites);
	~Snake();
	void kiir(SDL_Texture* kep,SDL_Texture* egerkep, SDL_Renderer *renderer);
	void update(SDL_Renderer* _renderer);
	void addResz(int x, int y, double szog);
	void addEger(int x, int y, int h, int w);
	bool utkozes(fal _fal);
	void egerUtkozes();
	void ujEgerHely();
	void latasRajzol(SDL_Renderer* _renderer);
	bool pontHaromszogben(SDL_Point pont, SDL_Point a, SDL_Point b, SDL_Point c);
	bool falHaromszogben(SDL_Point a, SDL_Point b, double &hossz);
	double dot(SDL_Point a, SDL_Point b);
	long getElozoIdo();
	double getFittness();
	void getGenek(std::vector<double>& genek);
	void setGenek(std::vector<double>& genek);
	void setLatas(bool ertek){latas=ertek;};
	NeuronHalo&	getAgy(){return agy;};
private:
	double tx, ty;
	std::vector<KigyoResz> reszek;
	eger _eger;
	std::vector<double> latasAdat;
	NeuronHalo agy;
	long elozoIdo;
	long elethossz;
	int kigyoHossz;
	bool latas;
};


