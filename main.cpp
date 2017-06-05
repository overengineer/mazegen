/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, math, and strings
#include <SDL.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include <time.h>
#include "mazegen.h"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image as texture
SDL_Texture* loadTexture(std::string path);

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		sprintf_s( error_msg,"SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			sprintf_s(error_msg, "Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			sprintf_s(error_msg, "Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				sprintf_s(error_msg, "Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Nothing to load
	return success;
}

void close()
{
	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

int main(int argc, char* args[])
{

	//ShowWindow(GetConsoleWindow(), SW_HIDE);
	int xTile, yTile, wTile, hTile,nTile=SIZE,mTile=SIZE,xMarginTile=250,yMarginTile=140;
	int xCount, yCount;
	double xSizeTile = 0.99, ySizeTile = 0.99,  xScaleTile = 1.55, yScaleTile = 1.92;
	SDL_Rect fillRect;

	char foo=PATH;
	for (xCount = 0;xCount < SIZE;xCount++) {
		for (yCount = 0;yCount < SIZE;yCount++) {
			map[xCount][yCount] = PATH;
		}
	}

	bool quit = false;
	bool success = true;
	bool finish = false;

	//Start up SDL and create window
	if (!init())
	{
		sprintf_s(error_msg, "Failed to initialize!\n");
		success = false;
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			sprintf_s(error_msg, "Failed to load media!\n");
			success = false;
		}
		else
		{
			//Main loop flag

			quit = false;
			//Event handler
			SDL_Event e;
			//While application is running
			while (!quit)
			{

				finish = false;
				mazegen();
				yAvatar = 1;
				xAvatar = 1;
				map[SIZE - 2][SIZE - 2] = FINISH;
				while (!finish) {

					map[xAvatar][yAvatar] = PATH;
					//Handle events on queue
					while (SDL_PollEvent(&e) != 0)
					{
						switch (e.type) {
							//User requests quit
						case SDL_QUIT:
							finish = true;
							quit = true;
							break;
						case SDL_KEYDOWN:

							//Select surfaces based on key press
							switch (e.key.keysym.sym)
							{
							case SDLK_u:
								yScaleTile -= 0.1;
								break;
							case SDLK_j:
								yScaleTile += 0.1;
								break;
							case SDLK_h:
								xScaleTile -= 0.1;
								break;
							case SDLK_k:
								xScaleTile += 0.1;
								break;

							case SDLK_UP:
								if (!iswall(map[xAvatar][yAvatar - 1])) {
									yAvatar--;
								}
								break;
							case SDLK_DOWN:
								if (!iswall(map[xAvatar][yAvatar + 1])) {
									yAvatar++;
								}
								break;
							case SDLK_RIGHT:
								if (!iswall(map[xAvatar + 1][yAvatar])) {
									xAvatar++;
								}
								break;
							case SDLK_LEFT:
								if (!iswall(map[xAvatar - 1][yAvatar])) {
									xAvatar--;
								}
								break;

							case SDLK_w:
								ySizeTile -= 0.01;
								break;
							case SDLK_s:
								ySizeTile += 0.01;
								break;
							case SDLK_a:
								xSizeTile -= 0.01;
								break;
							case SDLK_d:
								xSizeTile += 0.01;
								break;

							case SDLK_KP_8:
								yMarginTile--;
								break;
							case SDLK_KP_5:
								yMarginTile++;
								break;
							case SDLK_KP_4:
								xMarginTile--;
								break;
							case SDLK_KP_6:
								xMarginTile++;
								break;
							default:
								break;
							}
						default:
							break;
						}


					}

					if (map[xAvatar][yAvatar] == FINISH) {
						finish = true;
					}
					map[xAvatar][yAvatar] = AVA;

					//Clear screen
					SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
					SDL_RenderClear(gRenderer);
					
					hTile = (int)(yScaleTile*SCREEN_HEIGHT / mTile);
					wTile = (int)(xScaleTile*SCREEN_WIDTH / nTile);
					for (xCount = 0;xCount < nTile;xCount++) {
						for (yCount = 0;yCount < mTile;yCount++) {
							xTile = xMarginTile + (xCount - xAvatar)*wTile;
							yTile = yMarginTile + (yCount - yAvatar)*hTile;

							//Render red filled quad
							fillRect = { xTile, yTile, (int)(xSizeTile*wTile), (int)(ySizeTile*hTile) };
							SDL_SetRenderDrawColor(gRenderer, 0xFF * (iswall(map[xCount][yCount]) || map[xCount][yCount] == FINISH), 0xFF * (map[xCount][yCount] == PATH || map[xCount][yCount] == FINISH), 0xFF * (map[xCount][yCount] == AVA), 0xFF);
							SDL_RenderFillRect(gRenderer, &fillRect);
						}
					}

					//Update screen
					SDL_RenderPresent(gRenderer);
				}
			}
		}
	}

	//Free resources and close SDL
	close();
	if (success == false) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "MAZEGEN ERROR", error_msg, gWindow);
	}

	return 0;
}
