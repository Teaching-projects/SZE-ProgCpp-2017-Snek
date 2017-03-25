#pragma once
#include "snake.h"
//tavolság arány
double tavolsag(SDL_Point point1, SDL_Point point2)
{
	double distance = sqrt( (point1.x - point2.x) * (point1.x - point2.x) +
                            (point1.y - point2.y) * (point1.y - point2.y));
	//std::cout<< distance/400<<"\n";
    return distance;
}

Snake::Snake(int x, int y, SDL_Renderer *renderer, std::vector<unsigned> felepites):
	 agy(felepites)
{
		KigyoResz k1(x,y,180);
		k1.setSrcrect(0,0,40,40);
		reszek.push_back(k1);
		tx=reszek[0].getDstrect().x+reszek[0].getDstrect().w;
		ty=reszek[0].getDstrect().y+reszek[0].getDstrect().h/2;
		addEger(300,300,40,40);
		ujEgerHely();
		_eger.keelUjHely=false;
		elozoIdo=0;
		elethossz=SDL_GetTicks();
		kigyoHossz=1;
		latas=false;
}

void Snake::kiir(SDL_Texture* kigyokep, SDL_Texture* egerkep, SDL_Renderer *renderer){

	for(int i=reszek.size()-1;i>=0;i--){
		reszek[i].kiir(renderer,kigyokep);
	}
	SDL_RenderCopyEx(renderer,egerkep,NULL,&_eger.rect,0,nullptr,SDL_FLIP_NONE);

}

Snake::~Snake(){
	//SDL_DestroyTexture(kep);
	//for (int i = 0; i < falak.size(); i++)
	//{
	//	SDL_DestroyTexture(falak[i].kep);
	//}
	//SDL_DestroyTexture(kep);
	//SDL_DestroyRenderer(_renderer);
}


void Snake::addResz(int x, int y, double szog){
	KigyoResz k1(x,y,szog);
	reszek.push_back(k1);
}

void Snake::addEger(int x, int y, int h, int w){
	SDL_Rect tRect;
	tRect.x=x;
	tRect.y=y;
	tRect.h=h;
	tRect.w=w;
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
		//std::cout<<"Ütközés egerrel\n";
	   if((kigyoHossz+10) % 10 == 0){
		kigyoHossz++;
		reszek.push_back(KigyoResz(reszek[reszek.size()-1].getDstrect().x,reszek[reszek.size()-1].getDstrect().y,reszek[reszek.size()-1].getSzog()));
		if(reszek.size()>2){
			reszek[reszek.size()-1].setSrcrect(60,0,40,20);
			reszek[reszek.size()-2].setSrcrect(40,0,40,20);
			}
		elozoIdo=0;
		ujEgerHely();

	   }else{
		   kigyoHossz++;
		   elozoIdo=0;
		   ujEgerHely();
	   }
	}
}

bool Snake::utkozes(fal _fal){
if (reszek[0].getDstrect().x < _fal.rect.x + _fal.rect.w &&
   reszek[0].getDstrect().x + reszek[0].getDstrect().w > _fal.rect.x &&
   reszek[0].getDstrect().y < _fal.rect.y + _fal.rect.h &&
   reszek[0].getDstrect().h + reszek[0].getDstrect().y > _fal.rect.y) {
		//std::cout<<"Ütközés fallal\n";
		return 1;
	}
	return 0;
}

void Snake::latasRajzol(SDL_Renderer* _renderer){
	double hossz;
	int tempx,tempy;
	latasAdat.clear();
	SDL_Point pont,a,b,c;
	pont.x=_eger.rect.x+_eger.rect.w/2;
	pont.y=_eger.rect.y+_eger.rect.h/2;

	for (int i = -90; i <= 90; i+=15)
	{

		tempx=cos((reszek[0].getSzog()-180+i)*(M_PI/180))*400;
		tempy=sin((reszek[0].getSzog()-180+i)*(M_PI/180))*400;
		a.x=reszek[0].getDstrect().x+reszek[0].getDstrect().w/2;
		a.y=reszek[0].getDstrect().y+reszek[0].getDstrect().h/2;

		b.x=reszek[0].getDstrect().x+reszek[0].getDstrect().w/2+tempx;
		b.y=reszek[0].getDstrect().y+reszek[0].getDstrect().h/2+tempy;
		if(latas){
		SDL_SetRenderDrawColor(_renderer, 200,10,10,240);
		SDL_RenderDrawLine(_renderer,a.x , a.y , b.x ,  b.y);
		}
		tempx=cos((reszek[0].getSzog()-180+i-15)*(M_PI/180))*400;
		tempy=sin((reszek[0].getSzog()-180+i-15)*(M_PI/180))*400;
		c.x=reszek[0].getDstrect().x+reszek[0].getDstrect().w/2+tempx;
		c.y=reszek[0].getDstrect().y+reszek[0].getDstrect().h/2+tempy;


		if(pontHaromszogben(pont,a,b,c)&&i>-90){
			if(latas){
			SDL_SetRenderDrawColor(_renderer, 10,250*tavolsag(a,pont)/300,10,240);
			SDL_RenderDrawLine(_renderer,a.x,a.y,b.x,b.y);
			SDL_RenderDrawLine(_renderer,a.x,a.y,c.x,c.y);
			}
			latasAdat.push_back(1-tavolsag(a,pont)/400);
		}else if(i>-90){
			latasAdat.push_back(0);
			
		}
		
		if(falHaromszogben(a,b, hossz) && i>-90){
			if(latas){
				tempx=cos((reszek[0].getSzog()-180+i-7.5)*(M_PI/180))*hossz/2;
				tempy=sin((reszek[0].getSzog()-180+i-7.5)*(M_PI/180))*hossz/2;
				c.x=reszek[0].getDstrect().x+reszek[0].getDstrect().w/2+tempx;
				c.y=reszek[0].getDstrect().y+reszek[0].getDstrect().h/2+tempy;

				SDL_SetRenderDrawColor(_renderer, 10,30,180,240);
				SDL_RenderDrawLine(_renderer,a.x,a.y,c.x,c.y);
			}
			latasAdat.push_back(1-hossz/400);
		}else if(i>-90){
			latasAdat.push_back(0);
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
bool Snake::falHaromszogben(SDL_Point a, SDL_Point b, double &hossz){

	if(b.y<5){
		b.y=5;
		hossz=tavolsag(a,b);
		return true;
	}else if(b.y>715){
		b.y=715;
		hossz=tavolsag(a,b);
		return true;
	}else if(b.x<5){
		b.x=5;
		hossz=tavolsag(a,b);
		return true;
	}else if(b.x>1023){
		b.x=1023;
		hossz=tavolsag(a,b);
		return true;
	}

	return false;
}
double Snake::dot(SDL_Point a, SDL_Point b){
	double ap[]={a.x,a.y};
	double bp[]={b.x,b.y};

	return std::inner_product(std::begin(ap), std::end(ap), std::begin(bp), 0.0);
}
void Snake::update(SDL_Renderer* _renderer){
	if(_eger.keelUjHely){
		ujEgerHely();
	}
	else{
		egerUtkozes();
	}
	elozoIdo++;
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
			
  			for(int i=1;i<reszek.size();i++){
				reszek[i].updateHely(reszek[i-1]);
			}
				latasRajzol(_renderer);
				std::vector<double> eredmeny;
				agy.futtat(latasAdat);
				agy.getEredmeny(eredmeny);

				reszek[0].setSzog(reszek[0].getSzog()+(eredmeny[0]-eredmeny[1])*7);
}
long Snake::getElozoIdo(){
	return elozoIdo;
}
double Snake::getFittness(){
	double temp=(SDL_GetTicks()-elethossz)/1000;
	return temp+kigyoHossz*10;
}
void Snake::getGenek(std::vector<double>& genek){
	agy.getSulyok(genek);
}

void Snake::setGenek(std::vector<double>& genek){
	agy.setSulyok(genek);
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