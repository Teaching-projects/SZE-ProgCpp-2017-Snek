#pragma once
#include "window.h"
#include "snake.h"
#include "NeuralisHalo.h"
#include "Jatek.h"
#include <iostream>
#include <vector>
#undef main

Uint32 idozit(Uint32 ido, void *adat){
	SDL_Event event;
	event.type=SDL_USEREVENT;
	SDL_PushEvent(&event);
	return ido;
}
void esemeny(Window &ablak, Jatek &j1){
	SDL_Event event;

	if(SDL_PollEvent(&event)){
		j1.update(event);
		ablak.esemenyVar(event);
		/*kigyo.esemenyVar(event);*/
	}
}

int main(int argc, char **argv)
{
	srand (time(NULL));
	int elozoido=SDL_GetTicks();
	int frame=0;
	std::vector<unsigned> felepites;
	felepites.push_back(24);
	felepites.push_back(16);
	felepites.push_back(16);
	felepites.push_back(3);
	Window ablak("SNAKE AI", 720,1028);
	//Snake kigyo(500,350,ablak.getRenderer(), felepites);
	Jatek j1(20,ablak.getRenderer(),felepites);
	SDL_TimerID idozito=SDL_AddTimer(1,idozit,NULL);
	while(!ablak.isClosed()){
		//kigyo.kiir();
		//kigyo.latasRajzol();
		//ablak.clear();
		//esemeny(ablak,kigyo);
		j1.kiir();
		ablak.clear();
		esemeny(ablak,j1);
			if(SDL_GetTicks()>=elozoido+1000){
				std::cout<<frame<<"\n";
				frame=0;
				elozoido=SDL_GetTicks();
			}
			frame++;
	}
	return 0;
}