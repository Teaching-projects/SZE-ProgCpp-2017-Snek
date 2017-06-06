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
void NeuronHalo::getSulyok(std::vector<double>& sulyok){
	sulyok.reserve(retegek[0][0].kimenetiSulyok.size()*retegek[0].size() + retegek[1][0].kimenetiSulyok.size()*retegek[1].size() + retegek[2][0].kimenetiSulyok.size()*retegek[2].size());
	for (int i = 0; i < retegek.size()-1; i++)
	{
		for (int j = 0; j < retegek[i].size(); j++)
		{
			sulyok.insert( sulyok.end(), retegek[i][j].kimenetiSulyok.begin(), retegek[i][j].kimenetiSulyok.end() );
		}
	}
}
void NeuronHalo::setSulyok(std::vector<double> sulyok){
	int index=0;
	int meret;
	for (int i = 0; i < retegek.size()-1; i++)
	{
		for (int j = 0; j < retegek[i].size(); j++)
		{
			meret=retegek[i][j].kimenetiSulyok.size();
			if((index+meret) > sulyok.size() || index > sulyok.size()){
				throw std::exception();
			}
			retegek[i][j].kimenetiSulyok.clear();
			retegek[i][j].kimenetiSulyok.insert(retegek[i][j].kimenetiSulyok.begin(), sulyok.begin()+index, sulyok.begin()+index+meret );
			index+=meret;
		}
	}
}
void NeuronHalo::mentFajlba(std::string fajlNev){
	std::ofstream outfile;
	outfile.open(fajlNev);

	for (int i = 0; i < retegek.size()-1; i++)
	{
		for (int j = 0; j < retegek[i].size(); j++)
		{
			for (int k = 0; k < retegek[i][j].kimenetiSulyok.size(); k++)
			{
				outfile << retegek[i][j].kimenetiSulyok[k]<<"\t";
			}
			outfile << std::endl;
		}
	}
	outfile.close();

}