#include "Jatek.h"


Jatek::Jatek(unsigned darab,unsigned generacio, SDL_Renderer* renderer, std::vector<unsigned>& felepites):
	_renderer(renderer), _darab(darab), _felepites(felepites), _generacio(generacio)
{
	SDL_Texture* kep1,*kep2;
	kep=IMG_LoadTexture(_renderer,"kep.bmp");
	egerkep=IMG_LoadTexture(renderer,"eger.bmp");
	jelenlegiGeneracio=0;
	for (int i = 0; i < _darab; i++)
	{
		kigyok.push_back(Snake(500,300,_renderer,felepites));
	}

		kep1=IMG_LoadTexture(_renderer,"fal.bmp");
		kep2=IMG_LoadTexture(_renderer,"fal2.bmp");
		addFal(0,0,10,1028,kep1);
		addFal(0,710,10,1028,kep1);
		addFal(0,0,720,10,kep2);
		addFal(1018,0,720,10,kep2);
}

void Jatek::addFal(int x, int y, int h, int w, SDL_Texture* kep){
	SDL_Rect tRect;
	tRect.x=x;
	tRect.y=y;
	tRect.h=h;
	tRect.w=w;
	fal tfal;
	tfal.rect=tRect;
	tfal.kep=kep;
	falak.push_back(tfal);
}

			}

		for (int i = 0; i <kigyok.size(); i++)
		{

			for (int j = 0; j < falak.size(); j++)
			{
				if(kigyok[i].utkozes(falak[j])){
				egyed e;
				e.fittness=kigyok[i].getFittness();
				kigyok[i].getGenek(e.genek);
				egyedek.push_back(e);
					kigyok.erase(kigyok.begin()+i);
					break;
				}
			}
		}
	for (int i = 0; i < kigyok.size(); i++)
	{
				egyed e;
				e.fittness=kigyok[i].getFittness();
				kigyok[i].getGenek(e.genek);
				egyedek.push_back(e);
				kigyok.erase(kigyok.begin()+i);
			}
	}

}

void Jatek::kiir(){
	for (int i = 0; i < kigyok.size(); i++)
	{
		kigyok[i].update(_renderer);
		kigyok[i].kiir(kep, egerkep,_renderer);
	}
	for (int i = 0; i < falak.size(); i++)
	{
		SDL_RenderCopyEx(_renderer,falak[i].kep,NULL,&falak[i].rect,0,nullptr,SDL_FLIP_NONE);
	}
}
Jatek::~Jatek(){
	SDL_DestroyTexture(kep);
	for (int i = 0; i < falak.size(); i++)
	{
		SDL_DestroyTexture(falak[i].kep);
	}
	for (int i = 0; i < kigyok.size(); i++)
	{
		kigyok[i].~Snake();
	}
	SDL_DestroyTexture(egerkep);
	SDL_DestroyRenderer(_renderer);
}