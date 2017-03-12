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
	static double aktivacio(double x);
private:
	double kimenet;
	std::vector<double> kimenetiSulyok;
	unsigned _index;
};

class NeuronHalo{
public:
	NeuronHalo(const std::vector<unsigned> &felepites);
	void futtat(std::vector<double> &bemenetiErtek);
	void getEredmeny(std::vector<double> &eredmeny) const;
private:
	std::vector<Reteg> retegek;
};