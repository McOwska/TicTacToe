/*This source code copyrighted by Lazy Foo' Productions (2004-2022)
and may not be redistributed without written permission.*/

//Using SDL, standard IO, and strings
#include <SDL.h>
#include <stdio.h>
#include <string>
#include <iostream>
using namespace std;
//Screen dimension constants
const int SCREEN_WIDTH = 300;
const int SCREEN_HEIGHT = 300;
const int BUTTON_WIDTH = 100;
const int BUTTON_HEIGHT = 100;
const int TOTAL_BUTTONS = 9;
//Key press surfaces constants
enum Symbol
{
	X,
	O,
	defaultS,
	total
};

//Starts up SDL and creates window
bool init();



//Frees media and shuts down SDL
void close();

//Loads individual image


//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The images that correspond to a keypress
SDL_Surface* SymbolSurface[total];

//Current displayed image
SDL_Surface* gCurrentSurface = NULL;
SDL_Surface* BoardSurface = NULL;


bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow("TicTacToe", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Get window surface
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}

	return success;
}

void close()
{
	//Deallocate surfaces
	for (int i = 0; i < total; ++i)
	{
		SDL_FreeSurface(SymbolSurface[i]);
		SymbolSurface[i] = NULL;
	}

	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

SDL_Surface* loadSurface(std::string path)
{
	//Load image at specified path
	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
	}

	return loadedSurface;
}

void loadMedia()
{
	//Loading success flag

	SymbolSurface[X] = loadSurface("X.bmp");
	SymbolSurface[O] = loadSurface("O.bmp");
	SymbolSurface[defaultS] = loadSurface("default.bmp");
	BoardSurface = loadSurface("board.bmp");
	
}

class Board {
private:
	char board[3][3];
public:
	Board() {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				board[i][j] = '_';
			}
		}
	}

	void print() {
		cout << "-----------------------" << endl;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				cout << board[i][j] << " ";
			}
			cout << endl;
		}
		cout << "-----------------------" << endl;
	}
	char isRunning(int temp) {
		int flag = 0;
		for (int i = 0; i < 3; i++) {
			if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != '_') {
				return board[i][0];
			}
			if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != '_') {
				return board[0][i];
			}
		}
		if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != '_') {
			return board[0][0];
		}
		if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[2][0] != '_') {
			return board[1][1];
		}
		if (temp == 9) {
			return 'r';
		}
		return '!';
	}

	void move(int x, int y, int player) {
		if (x > 2 || y > 2) {
			throw out_of_range("index out of range");
		}
		if (board[x][y] != '_') {
			cout << "pole zajete: ";
			
			throw out_of_range("index out of range");
		}
		char players_char;
		if (player == 1) {
			players_char = 'o';
		}
		else {
			players_char = 'x';
		}
		board[x][y] = players_char;
	}



};

int main(int argc, char* args[])
{
	//Start up SDL and create window
	
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		loadMedia();
	   SDL_Event s;
		SDL_Renderer* renderer = SDL_CreateRenderer(gWindow, -1, 0);
		SDL_Surface* startSurface = loadSurface("start.bmp");
		SDL_Texture* startTexture = SDL_CreateTextureFromSurface(renderer, startSurface);
		SDL_RenderCopy(renderer, startTexture, NULL, NULL);
		SDL_RenderPresent(renderer);
		
		bool quits = false;
		while (!quits) {
			SDL_PollEvent(&s);
			if (s.type == SDL_MOUSEBUTTONDOWN) {
				int x, y;
				SDL_GetMouseState(&x, &y);
				if (y > 100 && y < 210 && x > 20 && x < 270) {
					quits = true;
				}
			}
		}



			bool quit = false;

			SDL_Event e;

			gCurrentSurface = BoardSurface;
			Board board1;
			int temp = 0;
			//board1.print();
			
			SDL_Surface* newSurface = NULL;
			SDL_Surface* boardSurface = loadSurface("board.bmp");
			//SDL_Renderer* renderer = SDL_CreateRenderer(gWindow, -1, 0);
			SDL_Texture* boardTexture = SDL_CreateTextureFromSurface(renderer, boardSurface);
			SDL_RenderCopy(renderer, boardTexture, NULL, NULL);
			SDL_RenderPresent(renderer);

			char result = 'R';
			while (!quit)
			{
				int board_x = 0, board_y = 0;
				//Handle events on queue
				SDL_PollEvent(&e);
					//User requests quit

					if (e.type == SDL_MOUSEBUTTONDOWN)
					{
						int x, y;
						SDL_GetMouseState(&x, &y);
					
						board_x = x / 100;
						board_y = y / 100;
						
					board1.move(board_y, board_x, temp % 2);
					switch (temp % 2) {
					case 0:
						newSurface = SymbolSurface[X];
						break;
					case 1:
						newSurface = SymbolSurface[O];
						break;
					default:
						true;

					}
					temp++;

					SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, newSurface);
					SDL_Rect dstrect = { board_x * 100 + 5, board_y * 100 + 5, 90, 90 };
					newSurface = NULL;
					SDL_RenderCopy(renderer, texture, NULL, &dstrect);
					//SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);
					SDL_RenderPresent(renderer);
					//SDL_UpdateWindowSurface(gWindow);
					
					if (board1.isRunning(temp) == 'r') {
						//cout << "REMIS" << endl;
						//return 0;
						SDL_Delay(500);
						quit = true;
					}
					if (board1.isRunning(temp) == 'x' || board1.isRunning(temp) == 'o') {
						if (board1.isRunning(temp) == 'x') {
							SDL_Delay(500);
							result = 'X';

						}
						else {
							SDL_Delay(500);
							result = 'O';

						}
						//cout << "gracz " << board1.isRunning(temp) << " wygral" << endl;
						
						quit = true;
					}
					
					}
					
				
				
			}
			SDL_Surface* ResultSurface = NULL;
			if (result == 'X') {
				ResultSurface = loadSurface("Xwon.bmp");
			}
			else {
				if (result == 'O') {
					ResultSurface = loadSurface("Owon.bmp");
				}
				else {
					ResultSurface = loadSurface("remis.bmp");
				}
			
			}
			SDL_Texture* ResultTexture = SDL_CreateTextureFromSurface(renderer, ResultSurface);
			SDL_RenderCopy(renderer, ResultTexture, NULL, NULL);
			SDL_RenderPresent(renderer);
			SDL_Delay(3000);
		
	}

	close();

	return 0;
}