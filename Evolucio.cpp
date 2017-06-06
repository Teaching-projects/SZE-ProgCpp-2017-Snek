#include "Evolucio.h"

Evolucio::Evolucio(std::vector<egyed> egyedek):_egyedek(egyedek){}

void Evolucio::kivalasztas(std::vector<double>& kivalsztottak){
	int populacioMeret=0;
	std::vector<int> populacio;
	for (int i = 0; i < _egyedek.size(); i++)
	{
			populacioMeret+=_egyedek[i].fittness;
	}

	for (int i = 0; i < _egyedek.size(); i++)
	{
		for (int j = 0; j < (int)_egyedek[i].fittness; j++)
		{
			populacio.push_back(i);
		}
	}

	kivalsztottak.push_back(populacio[rand() % populacioMeret]);
	kivalsztottak.push_back(populacio[rand() % populacioMeret]);
}

std::vector<double> Evolucio::keresztezes(std::vector<double> szuloA, std::vector<double> szuloB){
	std::vector<double> gyerek;

	for (int i = 0; i < szuloA.size(); i++)
	{
		if(i%2){
			gyerek.push_back(szuloA[i]);
		}
		else{
			gyerek.push_back(szuloB[i]);
		}
	}

	return gyerek;
}

void Evolucio::mutacio(std::vector<double>& gen, int valsz){
	for (int i = 0; i < gen.size(); i++)
	{
		if((rand() %100) < valsz){
			gen[i]+= (double)rand() / RAND_MAX * (0.3)-0.15;
		}
	}
}

void Evolucio::futtat(int valszM, int valszK){
	std::vector<double> kivalasztottak;
	std::vector<double> ujGen;

	egyed e;
	e.fittness=0;
	for (int i = 0; i < _egyedek.size(); i++)
	{
		if(e.fittness < _egyedek[i].fittness){
			e=_egyedek[i];
		}
	}
	
	ujGenek.push_back(e.genek);
	for (int i = 1; i < _egyedek.size(); i++)
	{
		kivalasztottak.clear();
		ujGen.clear();

		kivalasztas(kivalasztottak);
		if(rand() %100 < valszK){
			ujGen=keresztezes(_egyedek[kivalasztottak[0]].genek , _egyedek[kivalasztottak[1]].genek);
		}
		else{
			ujGen=_egyedek[kivalasztottak[0]].genek;
		}
		mutacio(ujGen, valszM);
		ujGenek.push_back(ujGen);
	}
}
void Evolucio::kiir(){

	
	double fittness=0;
	long ossz=0;
	//std::ofstream outfile;
	//outfile.open("adatok200p40g0m0.csv", std::ios_base::app);
	for (int i = 0; i < _egyedek.size(); i++)
	{
		if(fittness < _egyedek[i].fittness){
			fittness=_egyedek[i].fittness;
		}
	}
	std::cout<<"A legjobb fittness:"<<fittness<<"\n";

	for (int i = 0; i < _egyedek.size(); i++)
	{
		ossz+=_egyedek[i].fittness;
	}
	std::cout<<"A generacio atlag fitnesse:"<<ossz/_egyedek.size()<<"\n";


	
	//outfile <<fittness<<";"<<ossz/_egyedek.size();
	//outfile << std::endl;
	//outfile.close();


}