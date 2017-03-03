#pragma once

#include <string>
#include <SDL.h>
#include <SDL_image.h>
//#include <SDL_mixer.h>

class Window{
public:
	Window(const std::string &cim, int magassag, int szelesseg);
	~Window();
	inline bool isClosed() const {return closed;}
	void esemenyVar(SDL_Event &esemeny);
	SDL_Renderer* getRenderer() const {return renderer;}
	void clear() const;
	
private:
	bool init();

private:
	std::string _cim;
	int _magassag;
	int _szelesseg;
	bool closed;
	SDL_Window *ablak;
	SDL_Renderer *renderer;
};