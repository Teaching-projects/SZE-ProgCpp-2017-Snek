#include "Jatek.h"

Jatek::Jatek(SDL_Renderer* renderer, std::vector<unsigned>& felepites):
	_renderer(renderer), _felepites(felepites)
{
	adatBeker();
	SDL_Texture* kep1,*kep2;
	kep=IMG_LoadTexture(_renderer,"kep.bmp");
	egerkep=IMG_LoadTexture(renderer,"eger.bmp");
	legjobbFittness=0;
	jelenlegiGeneracio=0;
	for (int i = 0; i < egyedDb; i++)
	{
		kigyok.push_back(Snake(500,300,_renderer,felepites));
		if(kezdo!="0"){
			try{
				kigyok[i].setGenek(beolvasEgyed(kezdo));
			}catch(std::exception e){
				std::cout<<"Nem lehetett betölteni a kezdõ populáció tulajdonságát! Véletlenszerû tulajdonságokat kaptak!\n";
			};
		}
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

			if(kigyok.size()==0 && jelenlegiGeneracio<=generacio){
				std::vector<std::vector<double>> ujGenek;
				Evolucio e(egyedek);
				e.kiir();
				e.futtat(mutacio,keresztezes);
				ujGenek=e.getGenek();
				kigyok.clear();
				egyedek.clear();
				for (int i = 0; i < egyedDb; i++)
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
					kigyok[i].getAgy().mentFajlba(legjobb);
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
					kigyok[i].getAgy().mentFajlba(legjobb);
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
	if(!is){
		throw std::exception();
	}
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

void Jatek::adatBeker(){
	bool tovabb=false;
	while(!tovabb){
		std::cout<<"Adja meg az egyedek számát!(0-nál nagyobb egész szám)\n";
		std::cin>>egyedDb;
		tovabb=true;
		if(egyedDb<=0 || egyedDb>10000)
		{
			tovabb=false;
			std::cout<<"Bevitt adat helyetelen! Adja meg újra!\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}
	
	tovabb=false;
	while(!tovabb){
		std::cout<<"Adja meg hány generációig fusson az algoritmus!(0-nál nagyobb egész szám)\n";
		std::cin>>generacio;
		tovabb=true;
		if(generacio<=0 )
		{
			tovabb=false;
			std::cout<<"Bevitt adat helyetelen! Adja meg újra!\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}

	tovabb=false;
	while(!tovabb){
		std::cout<<"Adja meg az egyedek mutációjának a valszínûségét(0-nál nagyobb és 100-nál kisebb egész szám)!\n";
		std::cin>>mutacio;
		tovabb=true;
		if(mutacio<0 || mutacio>100)
		{
			tovabb=false;
			std::cout<<"Bevitt adat helyetelen! Adja meg újra!\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}
	
	tovabb=false;
	while(!tovabb){
		std::cout<<"Adja meg az egyedek keresztezésének valószínûségét!(0-nál nagyobb és 100-nál kisebb egész szám)\n";
		std::cin>>keresztezes;
		tovabb=true;
		if(keresztezes<0 || keresztezes>100)
		{
			tovabb=false;
			std::cout<<"Bevitt adat helyetelen! Adja meg újra!\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}

	tovabb=false;
	while(!tovabb){
		std::cout<<"Adja meg a fájl nevét amibe a szimuláció legjobb egyedét szeretné elmenteni!(pl: legjobb.txt)\n";
		std::cin>>legjobb;
		tovabb=true;
		std::ofstream outfile(legjobb);
		if(legjobb.substr(legjobb.find_last_of(".") + 1) != "txt" || !outfile)
		{
			tovabb=false;
			std::cout<<"Rosz fájlformátum vagy nem megfelelõ név! txt fájlformátumot adjon meg!\n";
			outfile.close();
		}else{
			outfile.close();
		}
	}

	std::cout<<"Ha szeretné, hogy a kezdõ populáció tulajdonságait egy meglévõ fájlból töltse be akkor adja meg a fájl nevét!(pl llegjobb4.txt)\nHa véletlen tulajdonságokat szeretne akkor írjon be egy 0-át!\n";
	std::cin>>kezdo;
}