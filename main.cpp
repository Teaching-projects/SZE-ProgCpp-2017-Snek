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
	Window ablak("SNAKE AI", 720,1028);
	Snake kigyo(500,350,ablak.getRenderer());
	std::cout<<"test";
	SDL_TimerID idozito=SDL_AddTimer((33/10)*10,idozit,NULL);
	while(!ablak.isClosed()){
		kigyo.kiir();
		ablak.clear();
		esemeny(ablak,kigyo);
		
	}

	return 0;
}