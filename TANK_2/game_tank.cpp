#include "game_tank.h"

image::image() {
	imagePath = "";
	desRectImage.x = 0;
	desRectImage.y = 0;
}

//setupImage() Cai dat chi so anh nhu: vi tri, duong dan
void image::setupImage(string image_path, int positionX, int positionY) {
	imagePath = image_path;
	tempSurfaceImage = IMG_Load(imagePath.c_str());
	textureImage = SDL_CreateTextureFromSurface(renderer, tempSurfaceImage);
	SDL_FreeSurface(tempSurfaceImage);

	SDL_QueryTexture(textureImage, NULL, NULL, &sourceRectImage.w, &sourceRectImage.h);
	sourceRectImage.x = 0;
	sourceRectImage.y = 0;
	desRectImage.x = positionX;
	desRectImage.y = positionY;
	desRectImage.w = sourceRectImage.w;
	desRectImage.h = sourceRectImage.h;
}
//showImage() Hien thi anh len man hinh
void image::showImage(double angle = 0) {
	SDL_RenderCopyEx(renderer, textureImage, &sourceRectImage, &desRectImage, angle, NULL, SDL_FLIP_NONE);
}

void button::setupButton(string image_path, int posX, int posY) {
	buttonImage.setupImage(image_path, posX - 150, posY - 50);
}

void button::showButton() {
	buttonImage.showImage();
}

bool button::isHover() {
	int posX = buttonImage.desRectImage.x;
	int posY = buttonImage.desRectImage.y;
	if (posMouseX > posX && posMouseX < posX + 300 && posMouseY > posY && posMouseY < posY + 100) {
		return true;
	}
	return false;
}

void text::setupText(string strText, int sizeText, int posX, int posY, SDL_Color fg = { 0, 0, 0 }) {
	font = TTF_OpenFont("data_game/font/ArchivoBlack.otf", sizeText);
	Surface = TTF_RenderText_Solid(font, strText.c_str(), fg);
	Texture = SDL_CreateTextureFromSurface(renderer, Surface);
	TTF_SizeText(font, strText.c_str(), &SrcRest.w, &SrcRest.h);
	SrcRest.x = 0;
	SrcRest.y = 0;
	DesRect.x = posX;
	DesRect.y = posY;
	DesRect.w = SrcRest.w;
	DesRect.h = SrcRest.h;
	SDL_FreeSurface(Surface);
}

void text::setPositionText(int posX, int posY) {
	DesRect.x = posX;
	DesRect.y = posY;
}

void text::showText() {
	SDL_RenderCopy(renderer, Texture, &SrcRest, &DesRect);
}

void bullet::createBulletImage(int positionX, int positionY, DIRECTION directionBullet, bool isMyTank) {
	if (isMyTank)
		bulletImage.setupImage("data_game/image/bullet.png", positionX, positionY);
	else
		bulletImage.setupImage("data_game/image/bullet_enemy.png", positionX, positionY);
	isMyTankBullet = isMyTank;
	direction = directionBullet;
}

void bullet::showBulletImage() {
	bulletImage.showImage(0);
}

//createBullet() tao mot vien dan theo toa do positionX, positionY va huong di chuyen directionBullet
void createBullet(int positionX, int positionY, DIRECTION directionBullet, bool isMyTankBullet) {
	bullet newBullet;
	newBullet.createBulletImage(positionX, positionY, directionBullet, isMyTankBullet);
	listBullet.push_back(newBullet);
}
//deleteBullet() Xoa dan khi cham tuong
void deleteBullet(int positionBullet) {
	createExplosion(listBullet[positionBullet].bulletImage.desRectImage.x - 18, listBullet[positionBullet].bulletImage.desRectImage.y - 18);
	listBullet.erase(listBullet.begin() + positionBullet);
	cout << "Delete vector bullet " << positionBullet << endl;
}
//updateAllBullet() Cap nhat vi tri dan
void updateAllBullet() {
	for (int i = 0; i < listBullet.size(); i++) {
		if (listBullet[i].direction == UP) {
			listBullet[i].bulletImage.desRectImage.y--;
		}
		else if (listBullet[i].direction == DOWN) {
			listBullet[i].bulletImage.desRectImage.y++;
		}
		else if (listBullet[i].direction == LEFT) {
			listBullet[i].bulletImage.desRectImage.x--;
		}
		else if (listBullet[i].direction == RIGHT) {
			listBullet[i].bulletImage.desRectImage.x++;
		}
		if (listBullet[i].bulletImage.desRectImage.x > WINDOWS_WIDTH || listBullet[i].bulletImage.desRectImage.x < 0 || listBullet[i].bulletImage.desRectImage.y > WINDOWS_HEIGHT || listBullet[i].bulletImage.desRectImage.y < 0) {
			deleteBullet(i);
			i--;
		}
	}
}
//showAllBullet() Hien thi tat ca dan len man hinh
void showAllBullet() {
	for (int i = 0; i < listBullet.size(); i++) {
		listBullet[i].showBulletImage();
	}
}

tank::tank() {
	direction = UP;
	isDie = false;
	fuel = 50;
	gunpowder = 50;
}
//createTankImage() thiet lap chi so xe tang
void tank::createTankImage(int positionX, int positionY, bool isMyTankCreate) {
	if (isMyTankCreate)
		tankImage.setupImage("data_game/image/tank.png", positionX, positionY);
	else
		tankImage.setupImage("data_game/image/tank_enemy.png", positionX, positionY);
	isMyTank = isMyTankCreate;
}
//showTankImage() hien thi xe tang len man hinh
void tank::showTankImage() {
	double angle = 0;
	if (direction == LEFT)
		angle = -90;
	if (direction == DOWN)
		angle = 180;
	if (direction == RIGHT)
		angle = 90;
	tankImage.showImage(angle);
	fuel++;			//Dieu chi do kho game tang do kho thi fuel += 2, fuel += 3, fuel += 4,...
	gunpowder++;
}
//createBulletInTank() tao moi mot vien dan tu xe tang nay
void tank::createBulletInTank() {
	if ((isMyTank && gunpowder > LOAD_TIME_BULLET_MY_TANK) || (!isMyTank && gunpowder > LOAD_TIME_BULLET)) {
		createBullet(tankImage.desRectImage.x + 18, tankImage.desRectImage.y + 18, direction, isMyTank);
		Mix_PlayChannel(-1, soundShooting, 0);
		gunpowder = 0;
	}
}
void tank::moveTheTank(DIRECTION directionOfMoving) {
	int posX = tankImage.desRectImage.x / 50;
	int posY = tankImage.desRectImage.y / 50;
	tankMap[posY][posX] = 0;
	if (direction != directionOfMoving && directionOfMoving != NONE) {
		direction = directionOfMoving;
	}
	else {
		if (directionOfMoving == UP) {
			posY = (posY + MATRIX_HEIGHT - 1) % MATRIX_HEIGHT;
			if (tankMap[posY][posX] != 1 && barrierMap[posY][posX] != 1)
				tankImage.desRectImage.y = (tankImage.desRectImage.y + WINDOWS_HEIGHT - 50) % WINDOWS_HEIGHT;
			else
				posY = (posY + 1) % MATRIX_HEIGHT;
		}
		else if (directionOfMoving == DOWN) {
			posY = (posY + 1) % MATRIX_HEIGHT;
			if (tankMap[posY][posX] != 1 && barrierMap[posY][posX] != 1)
				tankImage.desRectImage.y = (tankImage.desRectImage.y + 50) % WINDOWS_HEIGHT;
			else
				posY = (posY + MATRIX_HEIGHT - 1) % MATRIX_HEIGHT;
		}
		else if (directionOfMoving == RIGHT) {
			posX = (posX + 1) % MATRIX_WIDTH;
			if (tankMap[posY][posX] != 1 && barrierMap[posY][posX] != 1)
				tankImage.desRectImage.x = (tankImage.desRectImage.x + 50) % WINDOWS_WIDTH;
			else
				posX = (posX + MATRIX_WIDTH - 1) % MATRIX_WIDTH;
		}
		else if (directionOfMoving == LEFT) {
			posX = (posX + MATRIX_WIDTH - 1) % MATRIX_WIDTH;
			if (tankMap[posY][posX] != 1 && barrierMap[posY][posX] != 1)
				tankImage.desRectImage.x = (tankImage.desRectImage.x + WINDOWS_WIDTH - 50) % WINDOWS_WIDTH;
			else
				posX = (posX + 1) % MATRIX_WIDTH;
		}
		fuel = 0;
	}
	tankMap[posY][posX] = 1;
}

void tank::setDirection(DIRECTION _direction) {
	direction = _direction;
}

void drawBarrierMap() {
	image barrieMapImage;
	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 16; j++) {
			if (barrierMap[i][j] == 1) {
				barrieMapImage.setupImage("data_game/image/barrie.png", j * 50, i * 50);
				listBarrieMap.push_back(barrieMapImage);
			}
		}
	}
}
void showBarrierMap() {
	for (int i = 0; i < listBarrieMap.size(); i++) {
		listBarrieMap[i].showImage();
	}
}
void tankMapInit() {
	int rowOfMatrix = WINDOWS_HEIGHT / 50;
	int colOfMatrix = WINDOWS_WIDTH / 50;
	for (int i = 0; i < rowOfMatrix; i++) {
		for (int j = 0; j < colOfMatrix; j++) {
			tankMap[i][j] = 0;
		}
	}

	int positionMyTankInMatrixX = myTank.tankImage.desRectImage.x / 50;
	int positionMyTankInMatrixY = myTank.tankImage.desRectImage.y / 50;
	tankMap[positionMyTankInMatrixY][positionMyTankInMatrixX] = 1;
}
void directionMapReset() {
	for (int i = 0; i < MATRIX_HEIGHT; i++) {
		for (int j = 0; j < MATRIX_WIDTH; j++) {
			directionMap[i][j] = 1;
			if (barrierMap[i][j] == 1) {
				directionMap[i][j] = 0;
			}
		}
	}
}

void showRightMenu() {
	backgroundRightMenu.showImage();
	textSoccer.showText();
	textNumberTank.showText();
	textName.showText();
}
void updateRightMenu() {
	SDL_Color colorRightText = { 131, 215, 253 };
	string strSoccer = "Score: " + numberToString(numScore);
	string strNumberTank = "Number tank: " + numberToString(listEnemyTanks.size());
	string strName = "" + textUsername;
	textSoccer.setupText(strSoccer.c_str(), 18, WINDOWS_WIDTH + 20, 170, colorRightText);
	textNumberTank.setupText(strNumberTank.c_str(), 18, WINDOWS_WIDTH + 20, 220, colorRightText);
	textName.setupText(strName.c_str(), 18, WINDOWS_WIDTH + 80, 93, colorRightText);
}

void createEnemyTank() {
	int posX = rand() % MATRIX_WIDTH;
	int posY = rand() % MATRIX_HEIGHT;
	while (!(tankMap[posY][posX] != 1 && barrierMap[posY][posX] != 1))
	{
		posX = rand() % MATRIX_WIDTH;
		posY = rand() % MATRIX_HEIGHT;
	}

	if (tankMap[posY][posX] != 1 && barrierMap[posY][posX] != 1) {
		tank newEnemyTank;
		newEnemyTank.createTankImage(posX * 50, posY * 50, false);
		listEnemyTanks.push_back(newEnemyTank);
		tankMap[posY][posX] = 1;
	}
	updateRightMenu();
}
void deleteEnemyTank(int positionEnemyTank) {
	int posX = listEnemyTanks[positionEnemyTank].tankImage.desRectImage.x / 50;
	int posY = listEnemyTanks[positionEnemyTank].tankImage.desRectImage.y / 50;
	tankMap[posY][posX] = 0;
	if (listEnemyTanks[positionEnemyTank].isDie) {
		// isDie == true la bi ban chet, con isDie == false la bi xoa khi reset game
		numScore++;
		highScore.updateHighScore(numScore);
	}
	listEnemyTanks.erase(listEnemyTanks.begin() + positionEnemyTank);
	cout << "Delete vector enemy tank " << positionEnemyTank << endl;

	updateRightMenu();
}
void updateEnemyTank() {
	directionMapReset();
	for (int i = 0; i < listEnemyTanks.size(); i++) {
		if (listEnemyTanks[i].isDie) {
			deleteEnemyTank(i);
			i--;
		}
		int posX = listEnemyTanks[i].tankImage.desRectImage.x / 50;
		int posY = listEnemyTanks[i].tankImage.desRectImage.y / 50;
		int posMyTankX = myTank.tankImage.desRectImage.x / 50;
		int posMyTankY = myTank.tankImage.desRectImage.y / 50;

		string textDirection;
		textDirection = findTheDirectionMove(directionMap, posY, posX, posMyTankY, posMyTankX);
		if (listEnemyTanks[i].gunpowder > LOAD_TIME_BULLET) {
			if (textDirection == "kill") {
				if (posX < posMyTankX) {
					listEnemyTanks[i].setDirection(RIGHT);
				}
				else  if (posX > posMyTankX) {
					listEnemyTanks[i].setDirection(LEFT);
				}
				if (posY < posMyTankY) {
					listEnemyTanks[i].setDirection(DOWN);
				}
				else  if (posY > posMyTankY) {
					listEnemyTanks[i].setDirection(UP);
				}
				listEnemyTanks[i].createBulletInTank();
			}
		}

		int randomNumberBullet = rand() % (FPS * 3);
		int randomDirectionTank = rand() % (FPS);
		if (listEnemyTanks[i].fuel > DIFFICULTY_GAME) {
			DIRECTION directionEnemyTank = NONE;
			if (textDirection == "up")
				directionEnemyTank = UP;
			if (textDirection == "down")
				directionEnemyTank = DOWN;
			if (textDirection == "right")
				directionEnemyTank = RIGHT;
			if (textDirection == "left")
				directionEnemyTank = LEFT;

			listEnemyTanks[i].moveTheTank(directionEnemyTank);
		}
		if (!randomNumberBullet)
			listEnemyTanks[i].createBulletInTank();

		posX = listEnemyTanks[i].tankImage.desRectImage.x / 50;
		posY = listEnemyTanks[i].tankImage.desRectImage.y / 50;
		directionMap[posY][posX] = 0;
	}

	//Random tao xe tang
	int randomCreateTank = rand() % (FPS * 10);
	if (!randomCreateTank && listEnemyTanks.size() < MAX_NUMBER_TANK) {
		createEnemyTank();
	}
}
void showAllEnemyTank() {
	for (int i = 0; i < listEnemyTanks.size(); i++) {
		listEnemyTanks[i].showTankImage();
	}
}

void handleCollisionBulletVsBarrie() {
	for (int i = 0; i < listBullet.size(); i++) {
		int posX = (listBullet[i].bulletImage.desRectImage.x + 5) / 50;
		int posY = (listBullet[i].bulletImage.desRectImage.y + 5) / 50;
		if (barrierMap[posY][posX] == 1) {
			deleteBullet(i);
			i--;
		}
	}
}
bool findAndDeleteBulletBetweenTanks(tank tankInFunction) {
	for (int i = 0; i < listBullet.size(); i++) {
		int posBulletX, posBulletY, tankX, tankY;
		posBulletX = listBullet[i].bulletImage.desRectImage.x / 50;
		posBulletY = listBullet[i].bulletImage.desRectImage.y / 50;
		tankX = tankInFunction.tankImage.desRectImage.x / 50;
		tankY = tankInFunction.tankImage.desRectImage.y / 50;
		if ((listBullet[i].isMyTankBullet != tankInFunction.isMyTank) && posBulletX == tankX && posBulletY == tankY) {
			deleteBullet(i);
			i--;
			return true;
		}
	}
	return false;
}
void handleCollisionTanksVsBullet() {
	//Xu li va cham xe tang cua minh
	if (findAndDeleteBulletBetweenTanks(myTank)) {
		cout << "Game Over" << endl;
		isGameOver = true;
	}
	//Xu li va cham tank dich
	for (int i = 0; i < listEnemyTanks.size(); i++) {
		if (findAndDeleteBulletBetweenTanks(listEnemyTanks[i])) {
			listEnemyTanks[i].isDie = true;
			deleteEnemyTank(i);
			i--;
		}
	}
}
//handleCollisionBulletVsBullet() xu li va cham dan voi dan
void handleCollisionBulletVsBullet() {
	for (int i = 0; i < listBullet.size(); i++) {
		for (int j = i + 1; j < listBullet.size(); j++) {
			int distanceX = abs(listBullet[i].bulletImage.desRectImage.x - listBullet[j].bulletImage.desRectImage.x);
			int distanceY = abs(listBullet[i].bulletImage.desRectImage.y - listBullet[j].bulletImage.desRectImage.y);
			if (distanceX < 5 && distanceY < 5 && listBullet[i].isMyTankBullet != listBullet[j].isMyTankBullet) {
				deleteBullet(j);
				deleteBullet(i);
				i -= 2;
				break;
			}
		}
	}
}
//handleCollision() xu li va cham
void handleCollision() {
	handleCollisionBulletVsBullet();
	handleCollisionTanksVsBullet();
	handleCollisionBulletVsBarrie();
}
void resetGame() {
	while (listEnemyTanks.size() > 0) {
		deleteEnemyTank(0);
	}
	while (listBullet.size() > 0) {
		deleteBullet(0);
	}
	while (listExplosion.size() > 0) {
		deleteExplosion(0);
	}
	myTank.tankImage.desRectImage.x = 50;
	myTank.tankImage.desRectImage.y = 250;
	tankMapInit();
	numScore = 0;
	updateRightMenu();
}

void menuInit() {
	btn_play.setupButton("data_game/image/play.png", 400, 250);
	btn_soccer.setupButton("data_game/image/score.png", 400, 400);
	btn_exit.setupButton("data_game/image/exit.png", 400, 550);
	btn_play_hover.setupButton("data_game/image/play_hover.png", 400, 250);
	btn_soccer_hover.setupButton("data_game/image/score_hover.png", 400, 400);
	btn_exit_hover.setupButton("data_game/image/exit_hover.png", 400, 550);
}
void handleOnClickMenLeftMouseu() {
	if (btn_play.isHover() && (isGameOver || isPauseGame)) {
		cout << "Play\n";
		if (isGameOver) {
			resetGame();
		}
		isGameOver = false;
		isPauseGame = false;
		highScore.isShow = false;
	}
	else {
		if (!isGameOver)
			isPauseGame = true;
	}
	if (btn_soccer.isHover()) {
		cout << "Soccer\n";
		highScore.isShow = true;
		//cout << strTextName << endl;
	}
	if (btn_exit.isHover()) {
		cout << "Exit\n";
		isRunning = false;
	}
}
void showMenu() {
	if (btn_play.isHover())
		btn_play_hover.showButton();
	else
		btn_play.showButton();
	if (btn_soccer.isHover())
		btn_soccer_hover.showButton();
	else
		btn_soccer.showButton();
	if (btn_exit.isHover())
		btn_exit_hover.showButton();
	else
		btn_exit.showButton();
}

void SDL_Init_All() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		cout << "Unable to initialize SDL " << SDL_GetError() << endl;
		return;
	}
	//Initialize the truetype font API.
	if (TTF_Init() < 0)
	{
		cout << TTF_GetError() << endl;
		return;
	}
	//Create window
	window = SDL_CreateWindow("Quang BKL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOWS_WIDTH + WINDOWS_WIDTH_NAVBAR, WINDOWS_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		cout << "Could not create window " << SDL_GetError() << endl;
		return;
	}

	//create a renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		cout << "Could not create render " << SDL_GetError() << endl;
		return;
	}

	//Init SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
	{
		cout << Mix_GetError() << endl;
		return;
	}

	//Load Sound Effect
	soundShooting = Mix_LoadWAV("data_game/audio/shoot.wav");
	if (soundShooting == NULL)
	{
		cout << Mix_GetError() << endl;
		return;
	}

	//Nhac nen
	musicGround = Mix_LoadMUS("data_game/audio/AvengersInfinityWarTrailer1Music.mp3");
	if (musicGround == NULL)
	{
		cout << Mix_GetError() << endl;
	}
	Mix_PlayMusic(musicGround, -1);

	//set background color
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}
void GAME_Init_All() {
	backgroundImage.setupImage("data_game/image/background.png", 0, 0);

	myTank.createTankImage(50, 250, true);
	createEnemyTank();
	tankMapInit();
	//drawBarrierMap();
	menuInit();

	backgroundPauseGame.setupImage("data_game/image/bg-pause.png", 0, 0);
	backgroundGameOver.setupImage("data_game/image/background_game_over.png", 0, 0);
	backgroundRightMenu.setupImage("data_game/image/right-menu.png", WINDOWS_WIDTH, 0);

	highScore.setupHighScore();
}

void handleGameEvents() {
	while (SDL_PollEvent(&mainEvent))
	{
		switch (mainEvent.type)
		{

			//User - requested quit
		case SDL_QUIT:
		{
			isRunning = false;
			break;
		}

		//Mouse button pressed
		case SDL_MOUSEBUTTONDOWN:
		{
			if (mainEvent.button.button == SDL_BUTTON_LEFT)
			{
				printf("Left Mouse Clicked\n");
			}
			else if (mainEvent.button.button == SDL_BUTTON_RIGHT)
			{
				printf("Right Mouse Clicked\n");
			}
			break;
		}

		//Mouse button released
		case SDL_MOUSEBUTTONUP:
		{

			if (mainEvent.button.button == SDL_BUTTON_LEFT)
			{
				handleOnClickMenLeftMouseu();
				printf("Left Mouse Released\n");
			}
			else if (mainEvent.button.button == SDL_BUTTON_RIGHT)
			{
				printf("Right Mouse Released\n");
			}
			break;
		}

		//Mouse moved
		case SDL_MOUSEMOTION:
		{
			posMouseX = mainEvent.motion.x;
			posMouseY = mainEvent.motion.y;
			printf("Current Position Mouse: (%d, %d)\n", mainEvent.motion.x, mainEvent.motion.y);
			break;
		}

		//Mouse wheel motion
		case SDL_MOUSEWHEEL:
		{
			printf("Mouse Wheel Motion\n");
			break;
		}

		//Key pressed
		case SDL_KEYDOWN:
		{
			cout << mainEvent.key.keysym.sym << " pressed" << endl;
			break;
		}

		//Key released
		case SDL_KEYUP:
		{
			int key_up_value = mainEvent.key.keysym.sym;
			//getTextName(mainEvent.key.keysym.sym);
			cout << key_up_value << " released" << endl;
			if (!isGameOver) {
				if (key_up_value == ' ') {
					myTank.createBulletInTank();
				}
				if (key_up_value == 1073741906) {	//1073741906 la ma char phim mui ten len
					myTank.moveTheTank(UP);
				}
				if (key_up_value == 1073741905) {	//1073741905 la ma char phim mui ten xuong
					myTank.moveTheTank(DOWN);
				}
				if (key_up_value == 1073741904) {	//1073741904 la ma char phim mui ten trai
					myTank.moveTheTank(LEFT);
				}
				if (key_up_value == 1073741903) {	//1073741903 la ma char phim mui ten phai
					myTank.moveTheTank(RIGHT);
				}
			}
			else {
				if (key_up_value == 13) {
					isGameOver = false;
					resetGame();
				}
			}
			if (isPauseGame) {
				if (key_up_value == 13)
					isPauseGame = false;
			}

			break;
		}
		default:
			break;
		}
	}
}

void showGameOver() {
	backgroundGameOver.showImage(0);
	showMenu();
}

void showPauseGame() {
	backgroundPauseGame.showImage(0);
	showMenu();
}
void handleInputName() {
	bool quit = false;
	//Event handler
	SDL_Event e;

	//Set text color as black
	//SDL_Color textColor = { 180, 0, 197, 0xFF };
	SDL_Color textColor = { 131, 215, 253 };

	text textEnterName;
	textEnterName.setupText("Enter name: ", 48, 100, 100, textColor);
	textEnterName.setPositionText((WINDOWS_WIDTH - textEnterName.Surface->w) / 2, 200);

	//The current input text
	text textInputName;
	textInputName.setupText(" ", 48, 400, 300, textColor);

	text textFlashing;
	textFlashing.setupText("_", 48, 400, 300, textColor);

	//Enable text input
	SDL_StartTextInput();
	//While application is running
	while (!quit)
	{
		//The rerender text flag
		bool renderText = false;
		int countTextTime = 0;

		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
				isPauseGame = false;
				isRunning = false;
			}
			//Special key input
			else if (e.type == SDL_KEYDOWN)
			{
				//Handle backspace
				if (e.key.keysym.sym == SDLK_BACKSPACE && textUsername.length() > 0)
				{
					//lop off character
					textUsername.pop_back();
					renderText = true;
				}
				else if (e.key.keysym.sym == 13) {
					quit = true;
				}
				//Handle copy
				else if (e.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL)
				{
					SDL_SetClipboardText(textUsername.c_str());
				}
				//Handle paste
				else if (e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL)
				{
					textUsername = SDL_GetClipboardText();
					renderText = true;
				}
			}
			//Special text input event
			else if (e.type == SDL_TEXTINPUT)
			{
				//Not copy or pasting
				if (!((e.text.text[0] == 'c' || e.text.text[0] == 'C') && (e.text.text[0] == 'v' || e.text.text[0] == 'V') && SDL_GetModState() & KMOD_CTRL))
				{
					//Append character
					textUsername += e.text.text;
					renderText = true;
				}
			}
		}

		//Rerender text if needed
		if (renderText)
		{
			//Text is not empty
			if (textUsername != "")
			{
				//Render new text
				textInputName.setupText(textUsername.c_str(), 48, 100, 400, textColor);
				textInputName.setPositionText((WINDOWS_WIDTH - textInputName.Surface->w) / 2, 300);
				textFlashing.setPositionText(textInputName.DesRect.x + textInputName.Surface->w, textInputName.DesRect.y);
			}
			//Text is empty
			else
			{
				//Render space texture
				textInputName.setupText(" ", 48, 100, 100, textColor);
				textInputName.setPositionText((WINDOWS_WIDTH - textInputName.Surface->w) / 2, 300);
				textFlashing.setPositionText(textInputName.DesRect.x + textInputName.Surface->w, textInputName.DesRect.y);
			}
			updateRightMenu();
		}


		//Render
		SDL_RenderClear(renderer);
		backgroundPauseGame.showImage(0);
		textEnterName.showText();
		textInputName.showText();

		//Xu li dau nhay _
		countTextTime = SDL_GetTicks();
		if ((countTextTime / 200) % 2 == 0) {
			textFlashing.showText();
		}

		//Show right menu
		//handleRightMenu();
		showRightMenu();

		SDL_RenderPresent(renderer);
	}

	//Disable text input
	SDL_StopTextInput();
}

void EXPLOSION::createExplosion(int posX, int posY) {
	tempSurfaceImage = IMG_Load("data_game/image/explosion.png");
	textureImage = SDL_CreateTextureFromSurface(renderer, tempSurfaceImage);
	SDL_FreeSurface(tempSurfaceImage);
	SDL_QueryTexture(textureImage, NULL, NULL, &sourceRectImage.w, &sourceRectImage.h);
	sourceRectImage.x = 0;
	sourceRectImage.y = 0;
	sourceRectImage.w = 50;
	sourceRectImage.h = 50;
	desRectImage.x = posX;
	desRectImage.y = posY;
	desRectImage.w = sourceRectImage.w;
	desRectImage.h = sourceRectImage.h;
}

void EXPLOSION::showExplosion() {
	int posX = positionXY % 9;
	int posY = positionXY / 9;
	positionXY++;
	if (posX < 9 && posY < 9) {
		sourceRectImage.x = posX * 50;
		sourceRectImage.y = posY * 50;
	}
	SDL_RenderCopyEx(renderer, textureImage, &sourceRectImage, &desRectImage, 0, NULL, SDL_FLIP_NONE);
}

void createExplosion(int posX, int posY) {
	EXPLOSION newExplosion;
	newExplosion.createExplosion(posX, posY);
	listExplosion.push_back(newExplosion);
}

void deleteExplosion(int positionExplosion) {
	listExplosion.erase(listExplosion.begin() + positionExplosion);
	cout << "Delete vector Explosion " << positionExplosion << endl;
}

void updateExplosion() {
	for (int i = 0; i < listExplosion.size(); i++) {
		if (listExplosion[i].positionXY >= 81) {
			deleteExplosion(i);
			i--;
		}
	}
}

void showExplosion() {
	for (int i = 0; i < listExplosion.size(); i++) {
		if (listExplosion[i].positionXY < 81) {
			listExplosion[i].showExplosion();
		}
	}
}

void HIGHSCORE::setupHighScore() {
	tempSurfaceImage = IMG_Load("data_game/image/frame_high_score.png");
	textureImage = SDL_CreateTextureFromSurface(renderer, tempSurfaceImage);
	SDL_FreeSurface(tempSurfaceImage);
	SDL_QueryTexture(textureImage, NULL, NULL, &sourceRectImage.w, &sourceRectImage.h);
	sourceRectImage.x = 0;
	sourceRectImage.y = 0;
	maxWidth = sourceRectImage.w;
	sourceRectImage.w = 0;
	desRectImage.x = WINDOWS_WIDTH + 9;
	desRectImage.y = 300;
	desRectImage.w = sourceRectImage.w;
	desRectImage.h = sourceRectImage.h;
	SDL_Color fg = { 131, 215, 253 };
	string strHighScore = getHighScore();
	string strHighScoreUser = getHighScoreUser();
	highScoreText.setupText(strHighScore, 24, desRectImage.x + 16, desRectImage.y + 13, fg);
	username.setupText(strHighScoreUser, 18, desRectImage.x + 80, desRectImage.y + 17, fg);
}

void HIGHSCORE::updateHighScore(int _numberScore) {
	//setHighScore() tra ve true neu _numberScore > HighScore
	if (setHighScore(_numberScore, textUsername)) {
		setupHighScore();
	}
}

void HIGHSCORE::showHighScore() {
	if (isShow) {
		if (sourceRectImage.w < maxWidth) {
			sourceRectImage.w++;
			desRectImage.w = sourceRectImage.w;
		}
		SDL_RenderCopyEx(renderer, textureImage, &sourceRectImage, &desRectImage, 0, NULL, SDL_FLIP_NONE);
		if (sourceRectImage.w >= maxWidth) {
			highScoreText.showText();
			username.showText();
		}
	}
	else {
		sourceRectImage.w = 0;
	}
}

void renderGame() {
	while (isRunning) {
		//Handle FPS
		frameStart = SDL_GetTicks();

		handleGameEvents();	//Xu li su kien bam nut
		SDL_RenderClear(renderer);
		//If the music is paused
		if (Mix_PlayingMusic() == 0) {
			Mix_PlayMusic(musicGround, -1);
		}

		if (!isGameOver && !isPauseGame) {
			updateAllBullet();	//Cap nhat dan
			updateEnemyTank();	//Cap nhat xe tang dich
			handleCollision();
			updateExplosion();
		}
		backgroundImage.showImage(0);
		//showBarrierMap();
		showAllBullet();	//Hien thi tat ca dan len man hinh
		showAllEnemyTank();	//Hien thi tat ca xe tang dich len man hinh
		myTank.showTankImage();	//Hien thi xe tang minh
		showExplosion();
		showRightMenu();
		highScore.showHighScore();
		if (isPauseGame) {
			showPauseGame();
		}
		else if (isGameOver) {
			showGameOver();
		}
		SDL_RenderPresent(renderer);

		frameTime = SDL_GetTicks() - frameStart;
		if (frameTime < DELAY_TIME) {
			SDL_Delay(DELAY_TIME - frameTime);
		}
	}
}
