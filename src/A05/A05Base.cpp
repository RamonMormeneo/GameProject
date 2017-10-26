#include <SDL.h>		// Always needs to be included for an SDL app
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdlib.h>
#include <time.h>
//Game general information
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define FPS1 60
#define FPS2 60


int main(int, char*[]) {

	//new
	srand(time(NULL));
	int numCoins=0;
	bool showplay = false;
	bool showexit = false;
	int coinsX[3];
	int coinsY[3];
	
	for (int i = 0; i < 3; i++)
	{
		coinsX[i] = rand() % (700-0);
		coinsY[i] = 160+ rand() % (551-160);
		numCoins++;
	}
	int player1score = 0;
	int player2score = 0;
	// --- INIT ---
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) throw "No es pot inicialitzar SDL subsystems";
	const Uint8 ImgFlags(IMG_INIT_PNG | IMG_INIT_JPG);
	if (!(IMG_Init(ImgFlags) & ImgFlags)) throw "Error: SDL_image init";

	if (TTF_Init() != 0)  throw "No es pot inicialitzar SDL_ttf";

	const Uint8 mixFlag{ MIX_INIT_MP3 | MIX_INIT_OGG };
	if (!(Mix_Init(mixFlag)&mixFlag)) throw "Error:SDL_mixer init";
	// --- WINDOW ---
	SDL_Window *window{ SDL_CreateWindow("SDL...", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN) };
	if (window == nullptr) throw "No es pot inicialitzar SDL_Window";

	// --- RENDERER ---
	SDL_Renderer *renderer{ SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) };
	if (renderer == nullptr) throw "No es pot inicialitzar SDL_Renderer";

	// --- SPRITES ---
	//menu
	SDL_Texture *bgTexture{ IMG_LoadTexture(renderer, "../../res/img/bg.jpg") };
	if (bgTexture == nullptr) throw " No s'han pogut carregar les textures";
	SDL_Rect bgRect{ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	//ingame
	SDL_Texture *bgTexture2{ IMG_LoadTexture(renderer, "../../res/img/bgCastle.jpg") };
	if (bgTexture2 == nullptr) throw " No s'han pogut carregar les textures";
	SDL_Rect bgRect2{ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	// --- Animated Sprite ---
	SDL_Texture *playerTexture1{ IMG_LoadTexture (renderer,"../../res/img/kintoun.png") };
	if (playerTexture1 == nullptr) throw " No s'han pogut crear les textures";
	SDL_Rect playerRect1{ 0, 0, 100, 50 };
	SDL_Rect playerTarget1{ 0, 0, 100, 100 };
	//new
		//coin1
	SDL_Texture *playerTexture3{ IMG_LoadTexture(renderer,"../../res/img/gold.png") };
	if (playerTexture3 == nullptr) throw " No s'han pogut crear les textures";
	SDL_Rect playerRect3{ coinsX[0], coinsY[0], 100, 50 };
	SDL_Rect playerTarget3{ coinsX[0], coinsY[0], 100, 100 };
		//coin2
	SDL_Texture *playerTexture4{ IMG_LoadTexture(renderer,"../../res/img/gold.png") };
	if (playerTexture3 == nullptr) throw " No s'han pogut crear les textures";
	SDL_Rect playerRect4{ coinsX[1], coinsY[1], 100, 50 };
	SDL_Rect playerTarget4{ coinsX[1], coinsY[1], 100, 100 };
		//coin3
	SDL_Texture *playerTexture5{ IMG_LoadTexture(renderer,"../../res/img/gold.png") };
	if (playerTexture5 == nullptr) throw " No s'han pogut crear les textures";
	SDL_Rect playerRect5{ coinsX[2], coinsY[2], 100, 50 };
	SDL_Rect playerTarget5{ coinsX[2], coinsY[2], 100, 100 };
	//P1
	SDL_Texture *playerTexture(IMG_LoadTexture(renderer, "../../res/img/spCastle.png"));
	SDL_Rect playerRect, playerPosition;
	int textWidth, textHeight, frameWidth, frameHeight;
	SDL_QueryTexture(playerTexture, NULL, NULL, &textWidth, &textHeight);
	frameWidth = textWidth / 12;
	frameHeight = textHeight / 8;
	playerPosition.x = SCREEN_WIDTH - 50;
	playerPosition.y = 160;
	playerRect.x = playerRect.y = 0;
	playerPosition.h = playerRect.h = frameHeight;
	playerPosition.w = playerRect.w = frameWidth;
	int frameTime = 0;
	//P2
	SDL_Texture *playerTexture2(IMG_LoadTexture(renderer, "../../res/img/spCastle.png"));
	SDL_Rect playerRect2, playerPosition2;
	int textWidth2, textHeight2, frameWidth2, frameHeight2;
	SDL_QueryTexture(playerTexture2, NULL, NULL, &textWidth2, &textHeight2);
	frameWidth2 = textWidth2 / 12;
	frameHeight2 = textHeight2 / 8;
	playerPosition2.x = 0;
	playerPosition2.y = 500;
	playerRect2.x = 0;
	playerRect2.y = frameHeight2 * 4;
	playerPosition2.h = playerRect2.h = frameWidth2;
	playerPosition2.w = playerRect2.w = frameHeight2;
	int frameTime2 = 0;
	//points1
	SDL_Texture *pointsTexture(IMG_LoadTexture(renderer, "../../res/img/num.png"));
	SDL_Rect pointsRect, pointsPosition;
	int textWidth3, textHeight3, frameWidth3, frameHeight3;
	SDL_QueryTexture(pointsTexture, NULL, NULL, &textWidth3, &textHeight3);
	frameWidth3 = textWidth3/10;
	frameHeight3 = textHeight3;
	pointsPosition.x = pointsPosition.y = 0;
	pointsRect.x = 0;
	pointsRect.y = 0;
	pointsPosition.h = pointsRect.h = frameHeight3;
	pointsPosition.w = pointsRect.w = frameWidth3;
	//points2
	SDL_Texture *pointsTexture2(IMG_LoadTexture(renderer, "../../res/img/num.png"));
	SDL_Rect pointsRect2, pointsPosition2;
	int textWidth4, textHeight4, frameWidth4, frameHeight4;
	SDL_QueryTexture(pointsTexture2, NULL, NULL, &textWidth4, &textHeight4);
	frameWidth4 = textWidth4 / 10;
	frameHeight4 = textHeight4;
	pointsPosition2.x = pointsPosition2.y = 0;
	pointsRect2.x = 0;
	pointsRect2.y = 0;
	pointsPosition2.h = pointsRect2.h = frameHeight4;
	pointsPosition2.w = pointsRect2.w = frameWidth4;
	// --- TEXT ---
	TTF_Font *font{ TTF_OpenFont("../../res/ttf/saiyan.ttf",80) };
	if (font == nullptr)throw "No es pot inicialitzar SDL_ttf font";
	SDL_Surface *tmpSurf1{ TTF_RenderText_Blended(font,"Play",SDL_Color{ 0,50,0,255 }) };
	SDL_Surface *tmpSurf2{ TTF_RenderText_Blended(font,"Exit",SDL_Color{ 50,0,0,255 }) };
	SDL_Surface *tmpSurf3{ TTF_RenderText_Blended(font,"Play",SDL_Color{ 0,255,0,255 }) };
	SDL_Surface *tmpSurf4{ TTF_RenderText_Blended(font,"Exit",SDL_Color{ 255,0,0,255 }) };
	SDL_Surface *tmpSurf5{ TTF_RenderText_Blended(font,"PP F:",SDL_Color{ 255,0,0,255 }) };
	SDL_Surface *tmpSurf6{ TTF_RenderText_Blended(font,"PP S:",SDL_Color{ 255,0,0,255 }) };
	if (tmpSurf1 == nullptr || tmpSurf2 == nullptr)throw "No es pot inicialitzar SDL_ttf font";
	SDL_Texture *textTexture1{ SDL_CreateTextureFromSurface(renderer,tmpSurf1) };
	SDL_Texture *textTexture2{ SDL_CreateTextureFromSurface(renderer,tmpSurf2) };
	SDL_Texture *textTexture3{ SDL_CreateTextureFromSurface(renderer,tmpSurf3) };
	SDL_Texture *textTexture4{ SDL_CreateTextureFromSurface(renderer,tmpSurf4) };
	SDL_Texture *textTexture5{ SDL_CreateTextureFromSurface(renderer,tmpSurf5) };
	SDL_Texture *textTexture6{ SDL_CreateTextureFromSurface(renderer,tmpSurf6) };
	SDL_Rect textRect1{ 350,150,tmpSurf1->w,tmpSurf1->h };
	SDL_Rect textRect2{ 350,250,tmpSurf2->w,tmpSurf2->h };
	SDL_Rect textRect3{ 350,150,tmpSurf3->w,tmpSurf3->h };
	SDL_Rect textRect4{ 350,250,tmpSurf4->w,tmpSurf4->h };
	SDL_Rect textRect5{ 0,0,tmpSurf5->w,tmpSurf5->h };
	SDL_Rect textRect6{ 0,tmpSurf5->h ,tmpSurf6->w,tmpSurf6->h };
	SDL_FreeSurface(tmpSurf1);
	SDL_FreeSurface(tmpSurf2);
	SDL_FreeSurface(tmpSurf3);
	SDL_FreeSurface(tmpSurf4);
	SDL_FreeSurface(tmpSurf5);
	SDL_FreeSurface(tmpSurf6);
	TTF_CloseFont(font);
	// --- AUDIO ---
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
	{
		throw "No es pot inicialitzar SDL_ttf font";
	}
	Mix_Music *soudtrack{ Mix_LoadMUS("../../res/au/mainTheme.mp3") };
	if (!soudtrack) throw "No es pot inicialitzar SDL_ttf font";
	Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
	Mix_PlayMusic(soudtrack, -1);
	// --- GAME LOOP ---
	SDL_Event event;
	bool isRunning = true;
	bool OnMenu = true;
	bool startGame = false;
	bool p1getcoin = false;
	bool p2getcoin = false;
	bool movingp1 = false;
	bool movingp2 = false;
	int p1points = 0;
	int p2points = 0;
	pointsPosition.x = tmpSurf5->w;
	pointsPosition.y = 0;
	pointsPosition2.x = tmpSurf5->w;
	pointsPosition2.y = tmpSurf5->h;
	while (isRunning)
	{
		if (OnMenu)
		{
			// HANDLE EVENTS
			while (SDL_PollEvent(&event)) {
				switch (event.type) {
				case SDL_QUIT:		isRunning = false; break;
				case SDL_KEYDOWN:	if (event.key.keysym.sym == SDLK_ESCAPE) isRunning = false; break;
				case SDL_MOUSEMOTION: playerTarget1.x = event.motion.x - playerRect1.w / 2; playerTarget1.y = event.motion.y - playerRect1.h / 2; if (event.motion.x >= 350 && event.motion.y >= 150 && event.motion.x <= 350 + tmpSurf1->w&& event.motion.y <= 150 + tmpSurf1->h) showplay = true; else showplay = false; if (event.motion.x >= 350 && event.motion.y >= 250 && event.motion.x <= 350 + tmpSurf1->w&& event.motion.y <= 250 + tmpSurf1->h) showexit = true; else showexit = false;  break;
				case SDL_MOUSEBUTTONDOWN: if (event.motion.x >= 350 && event.motion.y >= 150 && event.motion.x <= 350 + tmpSurf1->w&& event.motion.y <= 150 + tmpSurf1->h) { OnMenu = false; startGame = true; }if (event.motion.x >= 350 && event.motion.y >= 250 && event.motion.x <= 350 + tmpSurf1->w&& event.motion.y <= 250 + tmpSurf1->h) isRunning = false;	break;
				default:;
				}
			}
			// UPDATE

			playerRect1.x += (playerTarget1.x - playerRect1.x) / 10;
			playerRect1.y += (playerTarget1.y - playerRect1.y) / 10;
			// DRAW
			//Background
			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, bgTexture, nullptr, &bgRect);
			if (showplay)
			{
				SDL_RenderCopy(renderer, textTexture3, nullptr, &textRect3);
			}
			else
			{
				SDL_RenderCopy(renderer, textTexture1, nullptr, &textRect1);
			}
			if (showexit)
			{
				SDL_RenderCopy(renderer, textTexture4, nullptr, &textRect4);
			}
			else
			{
				SDL_RenderCopy(renderer, textTexture2, nullptr, &textRect2);
			}
			
			SDL_RenderCopy(renderer, playerTexture1, nullptr, &playerRect1);

			//Animated Sprite

			SDL_RenderPresent(renderer);

		}

		if (startGame)
		{
			//new

			// HANDLE EVENTS
			while (SDL_PollEvent(&event)) {
				switch (event.type) {
				case SDL_QUIT:		isRunning = false; break;
				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_ESCAPE)
					{
						isRunning = false;
					}
					
					if (event.key.keysym.sym == SDLK_UP)
					{
						if (playerPosition.y >= 160)
						{
							playerPosition.y -= 1;
						}
						playerRect.y = 3 * frameHeight;
						frameTime++;
						if (FPS1 / frameTime <= 9)
						{
							frameTime = 0;
							playerRect.x += frameWidth;
							if (playerRect.x >= textWidth / 9)
							{
								playerRect.x = 0;
							}

						}

					}
					if (event.key.keysym.sym == SDLK_DOWN)
					{
						if (playerPosition.y <= SCREEN_HEIGHT - 50)
						{
							playerPosition.y += 1;
						}
						playerRect.y = 0;
						frameTime++;
						if (FPS1 / frameTime <= 9)
						{
							frameTime = 0;
							playerRect.x += frameWidth;
							if (playerRect.x >= textWidth / 9)
							{
								playerRect.x = 0;
							}

						}
					}
					else if (event.key.keysym.sym == SDLK_LEFT)
					{
						if (playerPosition.x >= 0)
						{
							playerPosition.x -= 1;
						}
						playerRect.y = frameHeight;
						frameTime++;
						if (FPS1 / frameTime <= 9)
						{
							frameTime = 0;
							playerRect.x += frameWidth;
							if (playerRect.x >= textWidth / 9)
							{
								playerRect.x = 0;
							}

						}
					}
					else if (event.key.keysym.sym == SDLK_RIGHT)
					{
						if (playerPosition.x <= SCREEN_WIDTH - 100)
						{
							playerPosition.x += 1;
						}
						playerRect.y = 2 * frameHeight;
						frameTime++;
						if (FPS1 / frameTime <= 9)
						{
							frameTime = 0;
							playerRect.x += frameWidth;
							if (playerRect.x >= textWidth / 9)
							{
								playerRect.x = 0;
							}

						}
					}
					else if (event.key.keysym.sym == SDLK_w)
					{
						if (playerPosition2.y >= 160)
						{
							playerPosition2.y -= 1;
						}
						playerRect2.y = 7 * frameHeight;
						frameTime2++;
						if (FPS2 / frameTime2 <= 9)
						{
							frameTime2 = 0;
							playerRect2.x += frameWidth2;
							if (playerRect2.x >= textWidth2 / 9)
							{
								playerRect2.x = 0;
							}
						}

					}
					else if (event.key.keysym.sym == SDLK_s)
					{
						if (playerPosition2.y <= SCREEN_HEIGHT - 50)
						{
							playerPosition2.y += 1;
						}
						playerRect2.y = 4 * frameHeight;
						frameTime2++;
						if (FPS2 / frameTime2 <= 9)
						{
							frameTime2 = 0;
							playerRect2.x += frameWidth2;
							if (playerRect2.x >= textWidth2 / 9)
							{
								playerRect2.x = 0;
							}
						}
					}
					else if (event.key.keysym.sym == SDLK_a)
					{
						if (playerPosition2.x >= 0)
						{
							playerPosition2.x -= 1;
						}
						playerRect2.y = 5 * frameHeight;
						frameTime2++;
						if (FPS2 / frameTime2 <= 9)
						{
							frameTime2 = 0;
							playerRect2.x += frameWidth2;
							if (playerRect2.x >= textWidth2 / 9)
							{
								playerRect2.x = 0;
							}
						}
					}

					else if (event.key.keysym.sym == SDLK_d)
					{
						if (playerPosition2.x <= SCREEN_WIDTH - 100)
						{
							playerPosition2.x += 1;
						}
						playerRect2.y = 6 * frameHeight;
						frameTime2++;
						if (FPS2 / frameTime2 <= 9)
						{
							frameTime2 = 0;
							playerRect2.x += frameWidth2;
							if (playerRect2.x >= textWidth2 / 9)
							{
								playerRect2.x = 0;
							}
						}
					}
					break;
				default: break;
				}
				//coins+p1
				if (playerPosition.x>=playerRect3.x && playerPosition.y>= playerRect3.y && playerPosition.x <= playerRect3.x + playerRect3.w && playerPosition.y <= playerRect3.y + playerRect3.h)
				{
					player1score++;
					int xsav = playerRect3.x;
					int ysav = playerRect3.y;
					playerRect3.x= rand() % (700 - 0);
					playerRect3.y= 160 + rand() % (551 - 160);
					while ((playerRect3.y == ysav && playerRect3.x == xsav) || &playerRect3 == &playerRect4 || &playerRect3 == &playerRect5 || &playerRect3 == &playerRect || &playerRect3 == &playerRect2)
					{
						playerRect3.x = rand() % (700 - 0);
						playerRect3.y = 160 + rand() % (551 - 160);
					}
					p1getcoin = true;
					p1points++;
				}
				if (playerPosition.x >= playerRect4.x && playerPosition.y >= playerRect4.y && playerPosition.x <= playerRect4.x + playerRect4.w && playerPosition.y <= playerRect4.y + playerRect4.h)
				{
					player1score++;
					int xsav = playerRect4.x;
					int ysav = playerRect4.y;
					playerRect4.x = rand() % (700 - 0);
					playerRect4.y = 160 + rand() % (551 - 160);
					while ((playerRect4.y == ysav && playerRect4.x == xsav) || &playerRect3 == &playerRect4 || &playerRect4 == &playerRect5 || &playerRect4 == &playerRect || &playerRect4 == &playerRect2)
					{
						playerRect4.x = rand() % (700 - 0);
						playerRect4.y = 160 + rand() % (551 - 160);
					}
					p1getcoin = true;
					p1points++;
				}
				if (playerPosition.x >= playerRect5.x && playerPosition.y >= playerRect5.y && playerPosition.x <= playerRect5.x + playerRect5.w && playerPosition.y <= playerRect5.y + playerRect5.h)
				{
					player1score++;
					int xsav = playerRect5.x;
					int ysav = playerRect5.y;
					playerRect5.x = rand() % (700 - 0);
					playerRect5.y = 160 + rand() % (551 - 160);
					while ((playerRect5.y == ysav && playerRect5.x == xsav) || &playerRect5 == &playerRect4 || &playerRect3 == &playerRect5 || &playerRect5 == &playerRect || &playerRect5 == &playerRect2)
					{
						playerRect5.x = rand() % (700 - 0);
						playerRect5.y = 160 + rand() % (551 - 160);
					}
					p1getcoin = true;
					p1points++;
				}
				//cdoisn+p2
				if (playerPosition2.x >= playerRect3.x && playerPosition2.y >= playerRect3.y && playerPosition2.x <= playerRect3.x + playerRect3.w && playerPosition2.y <= playerRect3.y + playerRect3.h)
				{
					player2score++;
					int xsav = playerRect3.x;
					int ysav = playerRect3.y;
					playerRect3.x = rand() % (700 - 0);
					playerRect3.y = 160 + rand() % (551 - 160);
					while ((playerRect3.y == ysav && playerRect3.x == xsav) || &playerRect3 == &playerRect4 || &playerRect3 == &playerRect5 || &playerRect3 == &playerRect || &playerRect3 == &playerRect2)
					{
						playerRect3.x = rand() % (700 - 0);
						playerRect3.y = 160 + rand() % (551 - 160);
					}
					p2getcoin = true;
					p2points++;
				}
				if (playerPosition2.x >= playerRect4.x && playerPosition2.y >= playerRect4.y && playerPosition2.x <= playerRect4.x + playerRect4.w && playerPosition2.y <= playerRect4.y + playerRect4.h)
				{
					player1score++;
					int xsav = playerRect4.x;
					int ysav = playerRect4.y;
					playerRect4.x = rand() % (700 - 0);
					playerRect4.y = 160 + rand() % (551 - 160);
					while ((playerRect4.y == ysav && playerRect4.x == xsav) || &playerRect3 == &playerRect4 || &playerRect4 == &playerRect5 || &playerRect4 == &playerRect || &playerRect4 == &playerRect2)
					{
						playerRect4.x = rand() % (700 - 0);
						playerRect4.y = 160 + rand() % (551 - 160);
					}
					p2getcoin = true;
					p2points++;
				}
				if (playerPosition2.x >= playerRect5.x && playerPosition2.y >= playerRect5.y && playerPosition2.x <= playerRect5.x + playerRect5.w && playerPosition2.y <= playerRect5.y + playerRect5.h)
				{
					player1score++;
					int xsav = playerRect5.x;
					int ysav = playerRect5.y;
					playerRect5.x = rand() % (700 - 0);
					playerRect5.y = 160 + rand() % (551 - 160);
					while ((playerRect5.y == ysav && playerRect5.x == xsav) || &playerRect5 == &playerRect4 || &playerRect3 == &playerRect5 || &playerRect5 == &playerRect || &playerRect5 == &playerRect2)
					{
						playerRect5.x = rand() % (700 - 0);
						playerRect5.y = 160 + rand() % (551 - 160);
					}
					p2getcoin = true;
					p2points++;
				}
				//+scorep1
				if (p1getcoin)
				{
					pointsRect.x += frameWidth3;
					p1getcoin = false;
				}
				if (p2getcoin)
				{
					pointsRect2.x += frameWidth4;
					p2getcoin = false;
				}
				if (p2points==10 || p1points==10)
				{
					isRunning = false;
				}

			}
		
			// UPDATE

			SDL_RenderClear(renderer);
			//DRAW
			SDL_RenderCopy(renderer, bgTexture2, nullptr, &bgRect);
			
			SDL_RenderCopy(renderer, playerTexture3, nullptr, &playerRect3);
			SDL_RenderCopy(renderer, playerTexture4, nullptr, &playerRect4);
			SDL_RenderCopy(renderer, playerTexture5, nullptr, &playerRect5);
			SDL_RenderCopy(renderer, textTexture5, nullptr, &textRect5);
			SDL_RenderCopy(renderer, textTexture6, nullptr, &textRect6);
			SDL_RenderCopy(renderer, playerTexture, &playerRect, &playerPosition);
			SDL_RenderCopy(renderer, pointsTexture, &pointsRect, &pointsPosition);
			SDL_RenderCopy(renderer, pointsTexture2, &pointsRect2, &pointsPosition2);
			SDL_RenderCopy(renderer, playerTexture2, &playerRect2, &playerPosition2);

			SDL_RenderPresent(renderer);

		}


	}
	// --- DESTROY ---
	SDL_DestroyTexture(playerTexture);
	SDL_DestroyTexture(playerTexture2);
	SDL_DestroyTexture(pointsTexture);
	SDL_DestroyTexture(textTexture1);
	SDL_DestroyTexture(textTexture3);
	SDL_DestroyTexture(textTexture2);
	SDL_DestroyTexture(textTexture4);
	Mix_CloseAudio();

	// --- QUIT ---
	SDL_Quit();
	IMG_Quit();
	TTF_Quit();
	Mix_Quit();
	return 0;
}