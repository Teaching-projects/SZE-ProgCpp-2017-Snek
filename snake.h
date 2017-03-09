#include <vector>
#include <stdlib.h>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>

struct helyek{
	int x;
	int y;
	double szog;
};
struct fal{
	SDL_Rect rect;
	SDL_Texture* kep;
};

class KigyoResz
{
public:
	KigyoResz(int x, int y, double szog);
	~KigyoResz();
	void updateHely(KigyoResz elozo);
	void kiir(SDL_Renderer *renderer, SDL_Texture* kep );
	std::vector<helyek>& getHelyek();
	void setSrcrect(int x, int y,int h, int w){srcrect.x=x;srcrect.y=y; srcrect.h=h;srcrect.w=w;};
	void setDstrect(int x, int y){dstrect.x=x; dstrect.y=y;};
	void setSzog(double szog){_szog=szog; if(szog>=360){_szog=0;}};
	double getSzog(){return _szog;};
	SDL_Rect getDstrect(){return dstrect;};
	void addHely(helyek hely){_hely.push_back(hely);};
private:
	std::vector<helyek> _hely;
	double _szog;
	SDL_Rect srcrect;
	SDL_Rect dstrect;
};

class Snake
{
public:
	Snake(int x, int y, SDL_Renderer *renderer);
	~Snake();
	void kiir();
	void update();
	void esemenyVar(SDL_Event &esemeny);
	void addResz(int x, int y, double szog);
	void addFal(int x, int y, int h, int w, SDL_Texture* kep);
private:
	SDL_Renderer *_renderer;
	SDL_Texture* kep;
	double tx, ty;
	std::vector<KigyoResz> reszek;
	std::vector<fal> falak;
	
};

