#include "window.h"
#include <iostream>

Window::Window(const std::string &cim, int magassag, int szelesseg):
	_cim(cim), _magassag(magassag), _szelesseg(szelesseg) 
{
	if(!init()){
		closed=true;
	}
}

Window::~Window()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(ablak);
	SDL_QUIT;
}

bool Window::init(){
	closed=false;
	ablak=nullptr;
	renderer=nullptr;

	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER)!=0){
		std::cerr <<"Nem sikerült initializálni az SDL-t!\n";
		return 0;
	}
	
	ablak=SDL_CreateWindow(_cim.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _szelesseg, _magassag, 0);
	if(ablak==nullptr){
		std::cerr <<"Nem sikerült létrehozni az ablakot!\n";
		return 0;
	}


	renderer = SDL_CreateRenderer(ablak,-1,SDL_RENDERER_ACCELERATED);
	if(renderer==nullptr){
		std::cerr <<"Nem sikerült létrehozni a renderelõt'\n";
		return 0;
	}
	return true;
}

void Window::esemenyVar(SDL_Event &esemeny){
	
		switch(esemeny.type){
		case SDL_QUIT:
			closed=true;
			break;
		default:
			break;
		}
}

void Window::clear() const{
	SDL_RenderPresent(renderer);
	SDL_SetRenderDrawColor(renderer, 100,100,100,240);
	SDL_RenderClear(renderer);

}