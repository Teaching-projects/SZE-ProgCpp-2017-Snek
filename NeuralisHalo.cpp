#include "NeuralisHalo.h"


Neuron::Neuron(unsigned kimenetdb, unsigned index){

	for (int i = 0; i < kimenetdb; i++)
	{
		kimenetiSulyok.push_back(randomSuly());
	}

	_index=index;
}

void Neuron::futtat(const Reteg &elozoReteg){
	double osszeg=0.0;

	for (int i = 0; i < elozoReteg.size(); i++)
	{
		osszeg+=elozoReteg[i].getKimenet()*elozoReteg[i].kimenetiSulyok[_index];
	}

	kimenet=Neuron::aktivacio(osszeg);
}

double Neuron::aktivacio(double x){

	return x / (1 + abs(x));
}

NeuronHalo::NeuronHalo(const std::vector<unsigned> &felepites){
	unsigned retegSzam=felepites.size();

	for (int i = 0; i < retegSzam; i++)
	{
		retegek.push_back(Reteg());
		unsigned kimenetdb;
		if(i==felepites.size()-1){
			kimenetdb=0;
		}else{
			kimenetdb=felepites[i+1];
		}

		for (int j = 0; j < felepites[i]; j++)
		{
			retegek.back().push_back(Neuron(kimenetdb,j));
		}
	}
}

void NeuronHalo::futtat(std::vector<double> &bemenetiErtek){
	for (int i = 0; i < bemenetiErtek.size(); i++)
	{
		retegek[0][i].setKimenet(bemenetiErtek[i]);
	}

	for (int i = 1; i < retegek.size(); i++)
	{
		Reteg &elozoReteg=retegek[i-1];
		for (int j = 0; j < retegek[i].size(); j++)
		{
			retegek[i][j].futtat(elozoReteg);
		}
	}
}

void NeuronHalo::getEredmeny(std::vector<double> &eredmeny) const{
	eredmeny.clear();

	for (int i = 0; i < retegek.back().size(); i++)
	{
		eredmeny.push_back(retegek.back()[i].getKimenet());
	}
}