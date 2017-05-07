#pragma once
#include "window.h"
#include "snake.h"
#include "NeuralisHalo.h"
#include "Jatek.h"
#include <iostream>
#include <vector>
#undef main


void esemenykezeles(Window &ablak, int& leptek, Jatek &j1){
		SDL_Event event;
		if(SDL_PollEvent(&event)){
			ablak.esemenyVar(event);
		}
		if(event.key.keysym.sym==SDLK_1){
			leptek=10;
		}else if(event.key.keysym.sym==SDLK_2){
			leptek=5;
		}else if(event.key.keysym.sym==SDLK_3){
			leptek=0;
		}else if(event.key.keysym.sym==SDLK_l){
			j1.setLatas(true);
		}else if(event.key.keysym.sym==SDLK_k){
			j1.setLatas(false);
		}
}

int main(int argc, char **argv)
{
	srand (time(NULL));
	int elozoido=SDL_GetTicks();
	int leptek=0;
	std::vector<unsigned> felepites;
	felepites.push_back(24);
	felepites.push_back(16);
	felepites.push_back(16);
	felepites.push_back(2);
	Window ablak("SNAKE AI", 720,1028);
	//SDL_TimerID idozito=SDL_AddTimer(1,idozit,NULL);
	Jatek j1(400,1000,ablak.getRenderer(),felepites);
	while(!ablak.isClosed()){
			esemenykezeles(ablak,leptek,j1);
			if(SDL_GetTicks()>=elozoido+leptek){
				j1.kiir();
				ablak.clear();
				j1.update();
				elozoido=SDL_GetTicks();
			}
	}
	return 0;
}