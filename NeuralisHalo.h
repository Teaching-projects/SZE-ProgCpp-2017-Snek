#pragma once
#include <vector>
#include <cstdlib>

class Neuron;
typedef std::vector<Neuron> Reteg;

class Neuron
{
public:
	Neuron(unsigned kimenetdb, unsigned index);
	static double randomSuly(void){return 2 * ((((float) rand()) / (float) RAND_MAX)) -1; };
	void futtat(const Reteg &elozoReteg);
	void setKimenet(double ertek){kimenet=ertek; };
	double getKimenet(void)const {return kimenet; };
	//std::vector<double> getKimenetiSulyok(void)const {return kimenetiSulyok; };
	static double aktivacio(double x);
	std::vector<double> kimenetiSulyok;
private:
	double kimenet;
	unsigned _index;
};

class NeuronHalo{
public:
	NeuronHalo(const std::vector<unsigned> &felepites);
	void futtat(std::vector<double> &bemenetiErtek);
	void getEredmeny(std::vector<double> &eredmeny) const;
	void getSulyok(std::vector<double>& sulyok);
	void setSulyok(std::vector<double> sulyok);
private:
	std::vector<Reteg> retegek;
};