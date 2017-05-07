#include "Jatek.h"

Jatek::Jatek(unsigned darab,unsigned generacio, SDL_Renderer* renderer, std::vector<unsigned>& felepites):
	_renderer(renderer), _darab(darab), _felepites(felepites), _generacio(generacio)
{
	SDL_Texture* kep1,*kep2;
	kep=IMG_LoadTexture(_renderer,"kep.bmp");
	egerkep=IMG_LoadTexture(renderer,"eger.bmp");
	legjobbFittness=0;
	jelenlegiGeneracio=0;
	for (int i = 0; i < _darab; i++)
	{
		kigyok.push_back(Snake(500,300,_renderer,felepites));
		//kigyok[i].setGenek(beolvasEgyed("legjobb7.txt"));
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

void Jatek::update(){

			if(kigyok.size()==0 && jelenlegiGeneracio<=_generacio){
				std::vector<std::vector<double>> ujGenek;
				Evolucio e(egyedek);
				e.kiir();
				e.futtat();
				ujGenek=e.getGenek();
				kigyok.clear();
				egyedek.clear();
				for (int i = 0; i < _darab; i++)
				{
					kigyok.push_back(Snake(500,300,_renderer,_felepites));
					kigyok.back().setGenek(ujGenek[i]);
				}
				jelenlegiGeneracio++;
				std::cout<<"Jelenlegi Generacio:"<<jelenlegiGeneracio<<"\n\n";
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
				if(e.fittness>legjobbFittness){
					kigyok[i].getAgy().mentFajlba("legjobb9.txt");
					legjobbFittness=e.fittness;
				}
				kigyok.erase(kigyok.begin()+i);
					break;
				}
			}
		}

	for (int i = 0; i < kigyok.size(); i++)
	{
			if(kigyok[i].getElozoIdo()>=2000){
				egyed e;
				e.fittness=kigyok[i].getFittness();
				kigyok[i].getGenek(e.genek);
				egyedek.push_back(e);
				if(e.fittness>legjobbFittness){
					kigyok[i].getAgy().mentFajlba("legjobb9.txt");
					legjobbFittness=e.fittness;
				}
				kigyok.erase(kigyok.begin()+i);
			}
	}

	for (int i = 0; i < kigyok.size(); i++)
	{
		kigyok[i].update(_renderer);
	}

}
void Jatek::kiir(){
	for (int i = 0; i < kigyok.size(); i++)
	{
		//kigyok[i].update(_renderer);
		kigyok[i].kiir(kep, egerkep,_renderer);
	}
	for (int i = 0; i < falak.size(); i++)
	{
		SDL_RenderCopyEx(_renderer,falak[i].kep,NULL,&falak[i].rect,0,nullptr,SDL_FLIP_NONE);
	}
}
void Jatek::setLatas(bool ertek){
	for (int i = 0; i < kigyok.size(); i++)
	{
		kigyok[i].setLatas(ertek);
	}
}
std::vector<double> Jatek::beolvasEgyed(std::string fajlNev){
	std::ifstream is(fajlNev);
	std::istream_iterator<double> start(is), end;
	std::vector<double> sulyok(start, end);
	is.close();
	return sulyok;
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