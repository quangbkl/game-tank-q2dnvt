#ifndef GAME_TANK
#define GAME_TANK
#include "include_and_define.h"
#include "high_score.h"
#include "number_to_string.h"

//Class chua anh de hien thi len man hinh
class image {
public:
	string imagePath;
	SDL_Surface* tempSurfaceImage = NULL;
	SDL_Texture* textureImage = NULL;
	SDL_Rect sourceRectImage;
	SDL_Rect desRectImage;

	image();
	void setupImage(string image_path, int positionX, int positionY);	//Cai dat chi so anh
	void showImage(double angle);										//Copy vao rendener de hien thi len man hinh

private:

};

//Class nut bam
class button {
public:
	image buttonImage;

	void setupButton(string image_path, int posX, int posY);	//Cai dat chi so
	void showButton();	//Copy vao rendener de hien thi len man hinh
	bool isHover();		//Kiem tra xem chuot co dat o button nay khong

private:

};

//Class in chu len man hinh
class text {
public:
	TTF_Font * font = NULL;
	SDL_Color fg = { 0, 0, 0 };
	SDL_Surface* Surface = NULL;
	SDL_Texture* Texture = NULL;
	SDL_Rect SrcRest;
	SDL_Rect DesRect;

	void setupText(string strText, int sizeText, int posX, int posY, SDL_Color fg);	//Cai dat chi so
	void setPositionText(int posX, int posY);	//Thiet lap vi tri text
	void showText();							//Copy vao rendener de hien thi len man hinh

private:

};

class HIGHSCORE {
public:
	SDL_Surface* tempSurfaceImage = NULL;
	SDL_Texture* textureImage = NULL;
	SDL_Rect sourceRectImage;
	SDL_Rect desRectImage;
	int maxWidth;
	bool isShow = false;
	text highScoreText, username;

	void setupHighScore();
	void updateHighScore(int _numberScore);
	void showHighScore();

private:
};

static HIGHSCORE highScore;

class EXPLOSION {
public:
	SDL_Surface * tempSurfaceImage = NULL;
	SDL_Texture* textureImage = NULL;
	SDL_Rect sourceRectImage;
	SDL_Rect desRectImage;
	int positionXY = 0;

	void createExplosion(int posX, int posY);
	void showExplosion();

private:
};

static vector<EXPLOSION> listExplosion;

void createExplosion(int posX, int posY);
void deleteExplosion(int positionExplosion);
void updateExplosion();
void showExplosion();

//Class vien dan
class bullet {
public:
	image bulletImage;		//Hinh anh cua vien dan
	bool isMyTankBullet;	//Kiem tra xem co phai dan cua xe tang minh khong
	DIRECTION direction;	//Huong di chuyen vien dan

	//createBulletImage() thiet lap chi so cho vien dan
	void createBulletImage(int positionX, int positionY, DIRECTION directionBullet, bool isMyTank);
	//showBulletImage() hien thi dan len man hinh
	void showBulletImage();

private:

};

static image backgroundImage, backgroundGameOver, backgroundPauseGame, backgroundRightMenu;

static text textSoccer, textNumberTank, textName;

static vector<bullet> listBullet;	//vector luu danh sach dan

//createBullet() tao mot vien dan theo toa do positionX, positionY va huong di chuyen directionBullet
void createBullet(int positionX, int positionY, DIRECTION directionBullet, bool isMyTankBullet);
//deleteBullet() Xoa dan khi cham tuong
void deleteBullet(int positionBullet);
//updateAllBullet() Cap nhat vi tri dan
void updateAllBullet();
//showAllBullet() Hien thi tat ca dan len man hinh
void showAllBullet();

//Class xe tang
class tank {
public:
	image tankImage;		//Luu hinh anh xe tang
	bool isMyTank;			//Kiem tra co phai xe tang cua minh khong
	bool isDie;				//Kiem tra chet chua
	int fuel;				//Nhien lieu xe tang, dung de thiet lap toc do di chuyen
	int gunpowder;			//Thuoc sung xe tang, dung de thiet lap toc do ban dan
	DIRECTION direction;	//Huong di chuyen cua xe tang

	//tank() thiet lap chi so mac dinh cua xe tang
	tank();
	//createTankImage() thiet lap chi so xe tang
	void createTankImage(int positionX, int positionY, bool isMyTankCreate);
	//showTankImage() hien thi xe tang len man hinh
	void showTankImage();
	//createBulletInTank() tao moi mot vien dan tu xe tang nay
	void createBulletInTank();
	//moveTheTank() di chuyen xe tang: len, xuong, trai, phai
	void moveTheTank(DIRECTION directionOfMoving);
	//setDirection() cai dat huong di chuyen, dung cho xe tang may
	void setDirection(DIRECTION _direction);

private:

};

static tank myTank;

static vector<tank> listEnemyTanks;	//Luu danh sach xe tang dich

static vector<image> listBarrieMap;	//Luu danh sach vat can

//void drawBarrierMap();			//Chuyen ma tran barrierMap thanh hinh anh
//void showBarrierMap();			//Hien thi vat can len man hinh
void tankMapInit();				//Lay xe tang minh vao ma tran tankMap[][] de xu li di chuyen
void directionMapReset();

void showRightMenu();			//Menu score, ten nguoi choi, menu nay o ben phai
void updateRightMenu();

void createEnemyTank();			//Tao moi mot xe tang dich
void deleteEnemyTank(int positionEnemyTank);	//Xoa mot xe tang
void updateEnemyTank();
void showAllEnemyTank();

void handleCollisionBulletVsBarrie();	//Xu li va cham dan vs vat can
bool findAndDeleteBulletBetweenTanks(tank tankInFunction); //Tim vien dan nao o giua xe tang roi xoa no di return true neu tim thay, return true thi xoa xe tang truyen vao
void handleCollisionTanksVsBullet();
//handleCollisionBulletVsBullet() xu li va cham dan voi dan
void handleCollisionBulletVsBullet();
//handleCollision() xu li va cham
void handleCollision();
//resetGame() khi Game Over thi chay ham nay
void resetGame();

static button btn_play, btn_play_hover, btn_soccer, btn_soccer_hover, btn_exit, btn_exit_hover;

void menuInit();					//Khoi tao menu
void handleOnClickMenLeftMouseu();	//Bat su kien click chuot
void showMenu();

void SDL_Init_All();
void GAME_Init_All();

void handleGameEvents();	//Xu li xu kien bam phim

void showGameOver();

void showPauseGame();
void handleInputName();		//Xu li nhap ten nguoi choi

void renderGame();			//Than chuong trinh

#endif