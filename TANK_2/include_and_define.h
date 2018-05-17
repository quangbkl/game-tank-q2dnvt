#ifndef INCLUDE_AND_DEFINE
#define INCLUDE_AND_DEFINE

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "search_the_road.h"

#define WINDOWS_WIDTH 800			//Chieu rong man hinh game 800px
#define WINDOWS_WIDTH_NAVBAR 250	//Chieu rong menu ben phai 250px
#define WINDOWS_HEIGHT 650			//Chieu cao cua so windows 650px
#define MATRIX_WIDTH 16				//
#define MATRIX_HEIGHT 13			//Chieu cao ma tran
#define DIFFICULTY_GAME 25			//Cang thap thi game cang kho choi, day la thoi gian di chuyen
#define LOAD_TIME_BULLET 50			//Thoi gian nap dan, cang thap game cang kho choi, nen de tren 20 neu khong game lag
#define LOAD_TIME_BULLET_MY_TANK 50	//Thoi gian nap dan xe tang minh
#define MAX_NUMBER_TANK 2			//Tong so xe tang toi da tren man hinh

enum DIRECTION { RIGHT, UP, LEFT, DOWN, NONE };

static SDL_Window* window = NULL;
static SDL_Event mainEvent;
static SDL_Renderer* renderer = NULL;
static SDL_Surface* tempSurface = NULL;
static SDL_Texture* texture = NULL;
static SDL_Rect sourceRect;
static SDL_Rect desRect;
static Mix_Chunk* soundShooting = NULL;
static Mix_Music *musicGround = NULL;

static string textUsername = "";
static bool isRunning = true;
static bool isGameOver = false;
static bool isPauseGame = false;

static const int FPS = 120;
static const int DELAY_TIME = 1000 / FPS;

static Uint32 frameStart;
static Uint32 frameTime;
static Uint32 countTextTime;

static int posMouseX = 0;								//Vi tri X chuot
static int posMouseY = 0;								//Vi tri Y chuot

												//barrierMap luu danh sach vat can
static int barrierMap[MATRIX_HEIGHT][MATRIX_WIDTH] = {
	{ 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0 },
	{ 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
	{ 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1 },
	{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};
static int tankMap[MATRIX_HEIGHT][MATRIX_WIDTH];		//Luu danh sach xe tang
static int bulletMap[MATRIX_HEIGHT][MATRIX_WIDTH];		//Luu danh sach dan
static int directionMap[MATRIX_HEIGHT][MATRIX_WIDTH];	//Luu xe tang va vat can, dung de xu li di chuyen tang may

static int numScore = 0;								//Luu diem cao

#endif // !INCLUDE_AND_DEFINE
