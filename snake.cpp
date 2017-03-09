#pragma once
#include "snake.h"

Snake::Snake(int x, int y, SDL_Renderer *renderer):
	_renderer(renderer) 
{
	
		kep=IMG_LoadTexture(_renderer,"kep.bmp");
		KigyoResz k1(x,y,180);
		k1.setSrcrect(0,0,40,40);
		reszek.push_back(k1);
		tx=reszek[0].getDstrect().x+reszek[0].getDstrect().w;
		ty=reszek[0].getDstrect().y+reszek[0].getDstrect().h/2;
		SDL_Texture* kep1,*kep2, *egerKep;
		kep1=IMG_LoadTexture(_renderer,"fal.bmp");
		kep2=IMG_LoadTexture(_renderer,"fal2.bmp");
		egerKep=IMG_LoadTexture(_renderer,"eger.bmp");
		addFal(0,0,10,1028,kep1);
		addFal(0,710,10,1028,kep1);
		addFal(0,0,720,10,kep2);
		addFal(1018,0,720,10,kep2);
		addEger(300,300,40,40,egerKep);
}

void Snake::kiir(){

	for(int i=0;i<reszek.size();i++){
		reszek[i].kiir(_renderer,kep);
	}
	for (int i = 0; i < falak.size(); i++)
	{
		SDL_RenderCopyEx(_renderer,falak[i].kep,NULL,&falak[i].rect,0,nullptr,SDL_FLIP_NONE);
		SDL_SetRenderDrawColor(_renderer, 200,10,10,240);
		SDL_RenderDrawRect(_renderer,&falak[i].rect);
	}
	SDL_RenderCopyEx(_renderer,_eger.kep,NULL,&_eger.rect,0,nullptr,SDL_FLIP_NONE);
	SDL_SetRenderDrawColor(_renderer, 200,10,10,240);
	SDL_RenderDrawRect(_renderer,&_eger.rect);
}

Snake::~Snake(){
	SDL_DestroyTexture(kep);
	for (int i = 0; i < falak.size(); i++)
	{
		SDL_DestroyTexture(falak[i].kep);
	}
	SDL_DestroyTexture(_eger.kep);
	SDL_DestroyRenderer(_renderer);
}

void Snake::esemenyVar(SDL_Event &esemeny){
	int i;
	switch(esemeny.type){
		case SDL_KEYDOWN:
			switch (esemeny.key.keysym.sym)
			{
			case SDLK_LEFT:
				reszek[0].setSzog(reszek[0].getSzog()-7);
				break;

			case SDLK_RIGHT:
				reszek[0].setSzog(reszek[0].getSzog()+7);
				break;

			case SDLK_SPACE:
 				reszek.push_back(KigyoResz(reszek[reszek.size()-1].getDstrect().x,reszek[reszek.size()-1].getDstrect().y,reszek[reszek.size()-1].getSzog()));
				if(reszek.size()>2){
				reszek[reszek.size()-1].setSrcrect(60,0,40,20);
				reszek[reszek.size()-2].setSrcrect(40,0,40,20);
				}
				break;
			default:
				break;
			}
		case SDL_USEREVENT:
			tx+=cos((reszek[0].getSzog()-180)*(M_PI/180))*3;
			ty+=sin((reszek[0].getSzog()-180)*(M_PI/180))*3;
	
			reszek[0].setDstrect( tx-reszek[0].getDstrect().w, ty-reszek[0].getDstrect().h/2 );

			helyek h1;
			h1.x=reszek[0].getDstrect().x;
			h1.y=reszek[0].getDstrect().y;
			h1.szog=reszek[0].getSzog();
			reszek[0].addHely(h1);
 			if(reszek[0].getHelyek().size()>=15){
				reszek[0].getHelyek().erase(reszek[0].getHelyek().begin());
			}
			
  			for(i=1;i<reszek.size();i++){
				reszek[i].updateHely(reszek[i-1]);
			}
			for (int i = 0; i < falak.size(); i++)
			{
				utkozes(falak[i]);
			}
			break;
		}
}

void Snake::addResz(int x, int y, double szog){
	KigyoResz k1(x,y,szog);
	reszek.push_back(k1);
}

void Snake::addFal(int x, int y, int h, int w, SDL_Texture* kep){
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

void Snake::addEger(int x, int y, int h, int w, SDL_Texture* kep){
	SDL_Rect tRect;
	tRect.x=x;
	tRect.y=y;
	tRect.h=h;
	tRect.w=w;
	fal tfal;
	tfal.rect=tRect;
	_eger.kep=kep;
	_eger.rect=tRect;
}

bool Snake::utkozes(fal _fal){
if (reszek[0].getDstrect().x < _fal.rect.x + _fal.rect.w &&
   reszek[0].getDstrect().x + reszek[0].getDstrect().w > _fal.rect.x &&
   reszek[0].getDstrect().y < _fal.rect.y + _fal.rect.h &&
   reszek[0].getDstrect().h + reszek[0].getDstrect().y > _fal.rect.y) {
		std::cout<<"Ütközés fallal\n";
		return 1;
	}
if (reszek[0].getDstrect().x < _eger.rect.x + _eger.rect.w &&
   reszek[0].getDstrect().x + reszek[0].getDstrect().w > _eger.rect.x &&
   reszek[0].getDstrect().y < _eger.rect.y + _eger.rect.h &&
   reszek[0].getDstrect().h + reszek[0].getDstrect().y > _eger.rect.y) {
		std::cout<<"Ütközés egerrel\n";
		return 1;
	}
	return 0;
}

KigyoResz::KigyoResz(int x, int y, double szog)
{
	dstrect.x=x;
	dstrect.y=y;
	dstrect.h=40;
	dstrect.w=40;
	_szog=szog;

	srcrect.x=40;
	srcrect.y=0;
	srcrect.h=40;
	srcrect.w=20;
}

void KigyoResz::updateHely(KigyoResz elozo){


	if(elozo.getHelyek().size()>=14){
		dstrect.x=elozo.getHelyek()[0].x;
		dstrect.y=elozo.getHelyek()[0].y;
		_szog=elozo.getHelyek()[0].szog;
		elozo.getHelyek().erase(elozo._hely.begin()+1);
		_hely.push_back(elozo.getHelyek()[0]);
		if(_hely.size()>=15){_hely.erase(_hely.begin());};
	}
}

void KigyoResz::kiir(SDL_Renderer *renderer, SDL_Texture* kep ){
 	SDL_RenderCopyEx(renderer,kep,&srcrect,&dstrect,_szog,nullptr,SDL_FLIP_NONE);
	SDL_SetRenderDrawColor(renderer, 200,10,10,240);
	SDL_RenderDrawRect(renderer,&dstrect);
}
std::vector<helyek>& KigyoResz::getHelyek(){
	return _hely;
}

KigyoResz::~KigyoResz(){
	
}