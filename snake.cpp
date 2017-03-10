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
		_eger.keelUjHely=false;
}

void Snake::kiir(){

	for(int i=reszek.size()-1;i>=0;i--){
		reszek[i].kiir(_renderer,kep);
	}
	for (int i = 0; i < falak.size(); i++)
	{
		SDL_RenderCopyEx(_renderer,falak[i].kep,NULL,&falak[i].rect,0,nullptr,SDL_FLIP_NONE);
	}
	SDL_RenderCopyEx(_renderer,_eger.kep,NULL,&_eger.rect,0,nullptr,SDL_FLIP_NONE);
	//int tempx,tempy;
	//tempx=cos((reszek[0].getSzog()-180)*(M_PI/180))*300;
	//tempy=sin((reszek[0].getSzog()-180)*(M_PI/180))*300;
	//SDL_SetRenderDrawColor(_renderer, 200,10,10,240);
	//SDL_RenderDrawLine(_renderer,reszek[0].getDstrect().x+reszek[0].getDstrect().w/2 , reszek[0].getDstrect().y+reszek[0].getDstrect().h/2 , reszek[0].getDstrect().x+reszek[0].getDstrect().w/2+tempx ,  reszek[0].getDstrect().y+reszek[0].getDstrect().h/2+tempy);

	//int tempx1,tempy1;
	//tempx1=cos((reszek[0].getSzog()-180-15)*(M_PI/180))*300;
	//tempy1=sin((reszek[0].getSzog()-180-15)*(M_PI/180))*300;
	//SDL_RenderDrawLine(_renderer,reszek[0].getDstrect().x+reszek[0].getDstrect().w/2 , reszek[0].getDstrect().y+reszek[0].getDstrect().h/2 , reszek[0].getDstrect().x+reszek[0].getDstrect().w/2+tempx1 ,  reszek[0].getDstrect().y+reszek[0].getDstrect().h/2+tempy1);


	//int tempx2,tempy2;
	//tempx2=cos((reszek[0].getSzog()-180+15)*(M_PI/180))*300;
	//tempy2=sin((reszek[0].getSzog()-180+15)*(M_PI/180))*300;
	//SDL_RenderDrawLine(_renderer,reszek[0].getDstrect().x+reszek[0].getDstrect().w/2 , reszek[0].getDstrect().y+reszek[0].getDstrect().h/2 , reszek[0].getDstrect().x+reszek[0].getDstrect().w/2+tempx2 ,  reszek[0].getDstrect().y+reszek[0].getDstrect().h/2+tempy2);


	//int tempx3,tempy3;
	//tempx3=cos((reszek[0].getSzog()-180-30)*(M_PI/180))*300;
	//tempy3=sin((reszek[0].getSzog()-180-30)*(M_PI/180))*300;
	//SDL_RenderDrawLine(_renderer,reszek[0].getDstrect().x+reszek[0].getDstrect().w/2 , reszek[0].getDstrect().y+reszek[0].getDstrect().h/2 , reszek[0].getDstrect().x+reszek[0].getDstrect().w/2+tempx3 ,  reszek[0].getDstrect().y+reszek[0].getDstrect().h/2+tempy3);


	//int tempx4,tempy4;
	//tempx4=cos((reszek[0].getSzog()-180+30)*(M_PI/180))*300;
	//tempy4=sin((reszek[0].getSzog()-180+30)*(M_PI/180))*300;
	//SDL_RenderDrawLine(_renderer,reszek[0].getDstrect().x+reszek[0].getDstrect().w/2 , reszek[0].getDstrect().y+reszek[0].getDstrect().h/2 , reszek[0].getDstrect().x+reszek[0].getDstrect().w/2+tempx4 ,  reszek[0].getDstrect().y+reszek[0].getDstrect().h/2+tempy4);


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
			if(_eger.keelUjHely){
				ujEgerHely();
			}
			else{
				egerUtkozes();
			}
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

void Snake::ujEgerHely(){
	
	_eger.rect.x=rand() % 900 + 28;
	_eger.rect.y=rand() % 600 + 28;
	if(reszek[0].getDstrect().x < _eger.rect.x + _eger.rect.w &&
   reszek[0].getDstrect().x + reszek[0].getDstrect().w > _eger.rect.x &&
   reszek[0].getDstrect().y < _eger.rect.y + _eger.rect.h &&
   reszek[0].getDstrect().h + reszek[0].getDstrect().y > _eger.rect.y){
	_eger.rect.x=2000;
	_eger.rect.y=2000;
	_eger.keelUjHely=true;
	}
	else{
		_eger.keelUjHely=false;
	}

}

void Snake::egerUtkozes(){

	SDL_Rect tempKigyoFej, tempEger;
	int tx,ty;
	tempKigyoFej.w=15;
	tempKigyoFej.h=15;
	tx=reszek[0].getDstrect().x+reszek[0].getDstrect().w/2;
	ty=reszek[0].getDstrect().y+reszek[0].getDstrect().h/2;
	tempKigyoFej.x=tx-tempKigyoFej.w/2;
	tempKigyoFej.y=ty-tempKigyoFej.h/2;

	tempEger.x=_eger.rect.x;
	tempEger.y=_eger.rect.y+10;
	tempEger.h=_eger.rect.h-20;
	tempEger.w=_eger.rect.w-5;

if (tempKigyoFej.x < tempEger.x + tempEger.w &&
   tempKigyoFej.x + tempKigyoFej.w > tempEger.x &&
   tempKigyoFej.y < tempEger.y + tempEger.h &&
   tempKigyoFej.h + tempKigyoFej.y > tempEger.y && !_eger.keelUjHely) {
		std::cout<<"Ütközés egerrel\n";
		reszek.push_back(KigyoResz(reszek[reszek.size()-1].getDstrect().x,reszek[reszek.size()-1].getDstrect().y,reszek[reszek.size()-1].getSzog()));
		if(reszek.size()>2){
			reszek[reszek.size()-1].setSrcrect(60,0,40,20);
			reszek[reszek.size()-2].setSrcrect(40,0,40,20);
			}
		ujEgerHely();
	}
}

bool Snake::utkozes(fal _fal){
if (reszek[0].getDstrect().x < _fal.rect.x + _fal.rect.w &&
   reszek[0].getDstrect().x + reszek[0].getDstrect().w > _fal.rect.x &&
   reszek[0].getDstrect().y < _fal.rect.y + _fal.rect.h &&
   reszek[0].getDstrect().h + reszek[0].getDstrect().y > _fal.rect.y) {
		std::cout<<"Ütközés fallal\n";
		return 1;
	}
	return 0;
}

void Snake::latasRajzol(){

	int tempx,tempy;
	SDL_Point pont,a,b,c;
	pont.x=_eger.rect.x+_eger.rect.w/2;
	pont.y=_eger.rect.y+_eger.rect.h/2;

	for (int i = 0; i <= 90; i+=15)
	{

		tempx=cos((reszek[0].getSzog()-180-i)*(M_PI/180))*400;
		tempy=sin((reszek[0].getSzog()-180-i)*(M_PI/180))*400;
		SDL_SetRenderDrawColor(_renderer, 200,10,10,240);
		SDL_RenderDrawLine(_renderer,reszek[0].getDstrect().x+reszek[0].getDstrect().w/2 , reszek[0].getDstrect().y+reszek[0].getDstrect().h/2 , reszek[0].getDstrect().x+reszek[0].getDstrect().w/2+tempx ,  reszek[0].getDstrect().y+reszek[0].getDstrect().h/2+tempy);


		a.x=reszek[0].getDstrect().x+reszek[0].getDstrect().w/2;
		a.y=reszek[0].getDstrect().y+reszek[0].getDstrect().h/2;

		b.x=reszek[0].getDstrect().x+reszek[0].getDstrect().w/2+tempx;
		b.y=reszek[0].getDstrect().y+reszek[0].getDstrect().h/2+tempy;

		tempx=cos((reszek[0].getSzog()-180-i+15)*(M_PI/180))*400;
		tempy=sin((reszek[0].getSzog()-180-i+15)*(M_PI/180))*400;
		c.x=reszek[0].getDstrect().x+reszek[0].getDstrect().w/2+tempx;
		c.y=reszek[0].getDstrect().y+reszek[0].getDstrect().h/2+tempy;


		if(pontHaromszogben(pont,a,b,c)){
			SDL_SetRenderDrawColor(_renderer, 10,200,10,240);
			SDL_RenderDrawLine(_renderer,a.x,a.y,b.x,b.y);
			SDL_RenderDrawLine(_renderer,a.x,a.y,c.x,c.y);
		}
	}

	for (int i = 0; i <= 90; i+=15)
	{

		tempx=cos((reszek[0].getSzog()-180+i)*(M_PI/180))*400;
		tempy=sin((reszek[0].getSzog()-180+i)*(M_PI/180))*400;
		SDL_SetRenderDrawColor(_renderer, 200,10,10,240);
		SDL_RenderDrawLine(_renderer,reszek[0].getDstrect().x+reszek[0].getDstrect().w/2 , reszek[0].getDstrect().y+reszek[0].getDstrect().h/2 , reszek[0].getDstrect().x+reszek[0].getDstrect().w/2+tempx ,  reszek[0].getDstrect().y+reszek[0].getDstrect().h/2+tempy);

		a.x=reszek[0].getDstrect().x+reszek[0].getDstrect().w/2;
		a.y=reszek[0].getDstrect().y+reszek[0].getDstrect().h/2;

		b.x=reszek[0].getDstrect().x+reszek[0].getDstrect().w/2+tempx;
		b.y=reszek[0].getDstrect().y+reszek[0].getDstrect().h/2+tempy;

		tempx=cos((reszek[0].getSzog()-180+i-15)*(M_PI/180))*400;
		tempy=sin((reszek[0].getSzog()-180+i-15)*(M_PI/180))*400;
		c.x=reszek[0].getDstrect().x+reszek[0].getDstrect().w/2+tempx;
		c.y=reszek[0].getDstrect().y+reszek[0].getDstrect().h/2+tempy;


		if(pontHaromszogben(pont,a,b,c)){
			SDL_SetRenderDrawColor(_renderer, 10,200,10,240);
			SDL_RenderDrawLine(_renderer,a.x,a.y,b.x,b.y);
			SDL_RenderDrawLine(_renderer,a.x,a.y,c.x,c.y);
		}
	}
}

bool Snake::pontHaromszogben(SDL_Point pont, SDL_Point a, SDL_Point b, SDL_Point c){
	SDL_Point v0,v1,v2;
	//v0 = C - A
	v0.x=c.x-a.x;
	v0.y=c.y-a.y;
	
	//v1 = B - A
	v1.x=b.x-a.x;
	v1.y=b.y-a.y;

	//v2 = P - A
	v2.x=pont.x-a.x;
	v2.y=pont.y-a.y;

	// Compute dot products
	double dot00,dot01,dot02,dot11,dot12;
	dot00 = dot(v0, v0);
	dot01 = dot(v0, v1);
	dot02 = dot(v0, v2);
	dot11 = dot(v1, v1);
	dot12 = dot(v1, v2);

	// Compute barycentric coordinates
	double invDenom,u,v;
	invDenom = 1 / (dot00 * dot11 - dot01 * dot01);
	u = (dot11 * dot02 - dot01 * dot12) * invDenom;
	v = (dot00 * dot12 - dot01 * dot02) * invDenom;
	
	return (u >= 0) && (v >= 0) && (u + v < 1);

}
double Snake::dot(SDL_Point a, SDL_Point b){
	double ap[]={a.x,a.y};
	double bp[]={b.x,b.y};

	return std::inner_product(std::begin(ap), std::end(ap), std::begin(bp), 0.0);
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
		elozo.getHelyek().erase(elozo._hely.begin());
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