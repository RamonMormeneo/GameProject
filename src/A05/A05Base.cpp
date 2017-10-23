#include <SDL.h>		// Always needs to be included for an SDL app
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
//Game general information
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define FPS1 60
#define FPS2 60


int main(int, char*[]) {

	
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

	SDL_Texture *bgTexture{ IMG_LoadTexture(renderer, "../../res/img/bg.jpg") };
	if (bgTexture == nullptr) throw " No s'han pogut carregar les textures";
	SDL_Rect bgRect{ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
		// --- Animated Sprite ---
	
	/*SDL_Texture *playerTexture{ IMG_LoadTexture (renderer,"../../res/img/kintoun.png") };
	if (playerTexture == nullptr) throw " No s'han pogut crear les textures";
	SDL_Rect playerRect{ 0, 0, 100, 50 };
	SDL_Rect playerTarget{ 0, 0, 100, 100 };*/
	//P1
	SDL_Texture *playerTexture(IMG_LoadTexture(renderer, "../../res/img/spCastle.png"));
	SDL_Rect playerRect, playerPosition;
	int textWidth, textHeight, frameWidth, frameHeight;
	SDL_QueryTexture(playerTexture, NULL, NULL, &textWidth, &textHeight);
	frameWidth = textWidth / 12;
	frameHeight = textHeight / 8;
	playerPosition.x = playerPosition.y = 0;
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
	playerPosition2.x = playerPosition2.y = 0;
	playerRect2.x = 0;
	playerRect2.y = frameHeight2*4;
	playerPosition2.h = playerRect2.h = frameHeight2;
	playerPosition2.w = playerRect2.w = frameWidth2;
	int frameTime2 = 0;
	// --- TEXT ---
	TTF_Font *font{ TTF_OpenFont("../../res/ttf/saiyan.ttf",80) };
	if(font==nullptr)throw "No es pot inicialitzar SDL_ttf font";
	SDL_Surface *tmpSurf1{ TTF_RenderText_Blended(font,"Play",SDL_Color{0,255,0,255} ) };
	SDL_Surface *tmpSurf2{ TTF_RenderText_Blended(font,"Exit",SDL_Color{255,0,0,255}) };
	if (tmpSurf1 == nullptr||tmpSurf2==nullptr)throw "No es pot inicialitzar SDL_ttf font";
	SDL_Texture *textTexture1{ SDL_CreateTextureFromSurface(renderer,tmpSurf1) };
	SDL_Texture *textTexture2{ SDL_CreateTextureFromSurface(renderer,tmpSurf2) };
	SDL_Rect textRect1{ 350,150,tmpSurf1->w,tmpSurf1->h };
	SDL_Rect textRect2{ 350,250,tmpSurf2->w,tmpSurf2->h };
	SDL_FreeSurface(tmpSurf1);
	SDL_FreeSurface(tmpSurf2);
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
	SDL_Event event;;
	bool isRunning = true;
	bool OnMenu = true;
	bool startGame = false;
	bool movingp1 = false;
	bool movingp2 = false;
	while (isRunning)
	{
		if(OnMenu)
		{
			// HANDLE EVENTS
			while (SDL_PollEvent(&event)) {
				switch (event.type) {
				case SDL_QUIT:		isRunning = false; break;
				case SDL_KEYDOWN:	if (event.key.keysym.sym == SDLK_ESCAPE) isRunning = false; break;
				//case SDL_MOUSEMOTION: playerTarget.x = event.motion.x - playerRect.w / 2; playerTarget.y = event.motion.y - playerRect.h / 2; break;
				case SDL_MOUSEBUTTONDOWN: if (event.motion.x >= 350 && event.motion.y >= 150 && event.motion.x <= 350 + tmpSurf1->w&& event.motion.y <= 150 + tmpSurf1->h) { OnMenu = false; startGame = true; }if (event.motion.x >= 350 && event.motion.y >= 250 && event.motion.x <= 350 + tmpSurf1->w&& event.motion.y <= 250 + tmpSurf1->h) isRunning = false;	break;
				default:;
				}
			}
			// UPDATE
			
			//playerRect.x += (playerTarget.x - playerRect.x) / 10;
			//playerRect.y += (playerTarget.y - playerRect.y) / 10;
			// DRAW
				//Background
			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, bgTexture, nullptr, &bgRect);
			SDL_RenderCopy(renderer, textTexture1, nullptr, &textRect1);
			SDL_RenderCopy(renderer, textTexture2, nullptr, &textRect2);
			//SDL_RenderCopy(renderer, playerTexture, nullptr, &playerRect);

			//Animated Sprite
			
			SDL_RenderPresent(renderer);

		}
		
		if (startGame)
		{
			
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
						if (playerPosition.y >= 0)
						{
							playerPosition.y -=1 ;
						}
						movingp1 = true;
						playerRect.y = 3 * frameHeight;
						
					}
					if (event.key.keysym.sym == SDLK_DOWN)
					{
						if (playerPosition.y <= SCREEN_HEIGHT-50)
						{
							playerPosition.y += 1;
						}
						playerRect.y = 0;
						movingp1 = true;
					}
					else if (event.key.keysym.sym == SDLK_LEFT)
					{
						if (playerPosition.x >= 0)
						{
							playerPosition.x -= 1;
						}
						playerRect.y = frameHeight;
						movingp1 = true;
					}
					else if (event.key.keysym.sym == SDLK_RIGHT)
					{
						if (playerPosition.x <= SCREEN_WIDTH-100)
						{
							playerPosition.x += 1;
						}
						playerRect.y = 2 * frameHeight;
						movingp1 = true;
					}
					else if (event.key.keysym.sym == SDLK_w)
					{
						movingp2 = true;
						if (playerPosition2.y >= 0)
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
						playerRect2.y = 5*frameHeight;
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
				default:movingp1 = false; movingp2 = false; break;
				}
			}
			// UPDATE
			/*playerRect.x += (playerTarget.x - playerRect.x) / 10;
			playerRect.y += (playerTarget.y - playerRect.y) / 10;*/
			
			if (movingp1)
			{
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
			else if (movingp2)
			{
				frameTime2++;
			
			}
			SDL_RenderClear(renderer);
			//DRAW
			SDL_RenderCopy(renderer, bgTexture, nullptr, &bgRect);
			//SDL_RenderCopy(renderer, playerTexture, nullptr, &playerRect);
		
			SDL_RenderCopy(renderer, playerTexture, &playerRect, &playerPosition);
			SDL_RenderCopy(renderer, playerTexture2, &playerRect2, &playerPosition2);
			
			SDL_RenderPresent(renderer);
		
		}
	

	}
	// --- DESTROY ---
	SDL_DestroyTexture(playerTexture);
	SDL_DestroyTexture(playerTexture2);
	SDL_DestroyTexture(textTexture1);
	SDL_DestroyTexture(textTexture2);
	Mix_CloseAudio();

	// --- QUIT ---
	SDL_Quit();
	IMG_Quit();
	TTF_Quit();
	Mix_Quit();
	return 0;
}