#include "game_tank.h"

int main(int argc, char * argv[]) {
	srand(time(0));
	SDL_Init_All();		//Khoi tao SDL
	GAME_Init_All();	//Khoi tao game: map, tank,...
	updateRightMenu();	//Khoi tao menu ben phai: score, so xe tang, ten nguoi choi
	handleInputName();	//Xu li nhap ten nguoi choi

	renderGame();

	//SDL Quit
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	TTF_Quit();
	SDL_Quit();
	return 0;
}