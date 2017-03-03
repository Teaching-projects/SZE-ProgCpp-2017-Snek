#pragma once
#include "snake.h"

Snake::Snake(int x, int y, SDL_Renderer *renderer):
	_renderer(renderer) 
{
	
		kep=IMG_LoadTexture(_renderer,"kep.bmp");
		//rect.h=40;
		//rect.w=40;
		//rect.x=x;
		//rect.y=y;
		//r2.h=40;
		//r2.w=40;
		//r2.x=0;
		//r2.y=0;
		KigyoResz k1(x,y,180);
		k1.setSrcrect(0,0,40,40);
		reszek.push_back(k1);
		tx=reszek[0].getDstrect().x+reszek[0].getDstrect().w;
		ty=reszek[0].getDstrect().y+reszek[0].getDstrect().h/2;
		
}

void Snake::kiir(){

	for(int i=0;i<reszek.size();i++){
		reszek[i].kiir(_renderer,kep);
	}
}

Snake::~Snake(){
	SDL_DestroyTexture(kep);
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
				//KigyoResz k1(reszek[reszek.size()].getDstrect().x,reszek[reszek.size()].getDstrect().y,reszek[reszek.size()].getSzog());
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
			//rect.y=ty-rect.h/2;

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

			//if(h.size()>=20){
			//	r.x=h[0].x;
			//	r.y=h[0].y;
			//	szog1=h[0].szog;
			//	h.erase(h.begin());
			//	
			//}
  
		

			//std::cout <<"size:"<<h.size()<<"\n";
			//std::cout <<"\t"<<"Y:"<<r.y<<"\n";
			break;
		}
}

void Snake::addResz(int x, int y, double szog){
	KigyoResz k1(x,y,szog);
	reszek.push_back(k1);
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
}
std::vector<helyek>& KigyoResz::getHelyek(){
	return _hely;
}

KigyoResz::~KigyoResz(){

}