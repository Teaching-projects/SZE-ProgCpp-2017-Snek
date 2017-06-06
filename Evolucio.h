#pragma once
#include "snake.h"
struct egyed{
	std::vector<double> genek;
	double fittness;
};

class Evolucio
{
public:
	Evolucio(std::vector<egyed> egyedek);
	std::vector<std::vector<double>> getGenek(){return ujGenek;};
	std::vector<double> keresztezes(std::vector<double> szuloA, std::vector<double> szuloB);
	void mutacio(std::vector<double>& gen, int valsz);
	void kivalasztas(std::vector<double>& kivalsztottak);
	void futtat(int valszM, int valszK);
	void kiir();
private:
	std::vector<egyed> _egyedek;
	std::vector<std::vector<double>> ujGenek;
};