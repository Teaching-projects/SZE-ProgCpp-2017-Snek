#pragma once
#include "window.h"
#include "snake.h"
#include <iostream>
#undef main

Uint32 idozit(Uint32 ido, void *adat){
	SDL_Event event;
	event.type=SDL_USEREVENT;
	SDL_PushEvent(&event);
	return ido;
}
void esemeny(Window &ablak, Snake &kigyo){
	SDL_Event event;

	if(SDL_PollEvent(&event)){
		
		ablak.esemenyVar(event);
		kigyo.esemenyVar(event);
	}
}

int main(int argc, char **argv)
{
	srand (time(NULL));
	int elozoido=SDL_GetTicks();
	int frame=0;
	Window ablak("SNAKE AI", 720,1028);
	Snake kigyo(500,350,ablak.getRenderer());
	SDL_TimerID idozito=SDL_AddTimer((33/10)*10,idozit,NULL);
	while(!ablak.isClosed()){
		kigyo.kiir();
		kigyo.latasRajzol();
		ablak.clear();
		esemeny(ablak,kigyo);
		if(SDL_GetTicks()>=elozoido+1000){
			std::cout<<frame<<"\n";
			frame=0;
			elozoido=SDL_GetTicks();
		}
		frame++;
	}

	return 0;
}