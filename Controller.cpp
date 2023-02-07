#include "Model.h"
#include "View.h"
#include "Controller.h"
#include <string>
#include <stdio.h>
#include <vector>
#include <SDL.h>
#undef main
using std::string;

using namespace Entities;
using namespace GameEntities;
using namespace ViewEntities;
using namespace Controller;
using namespace Utilities;

//---- Global Variables ----//
const int GAME_SCALE_RATIO 			= 4;
const int FRAME_RATE 				= 60;
const int SCREEN_TICKS_PER_FRAME 	= 1000/FRAME_RATE;	
const vector<EnemyShipClasses> CLASSIC_SHIP_CLASSES{CLASS_ONE,CLASS_ONE,CLASS_TWO,CLASS_TWO,CLASS_THREE};

ClassicSpaceBattleController::ClassicSpaceBattleController(int scale_ratio)
{
	init(scale_ratio);
}

ClassicSpaceBattleController::~ClassicSpaceBattleController()
{
	close();
}

void ClassicSpaceBattleController::init(int scale_ratio)
{
	//-- Model Creation --//

	
	
	this->model = new ClassicSpaceBattle(CLASSIC_SHIP_CLASSES,scale_ratio = scale_ratio	);

	//-- View Creation --//
	this->view = new ClassicSpaceBattleView(model);

	this->gameOver = false;

}

void ClassicSpaceBattleController::close()
{

	delete this->model;
	delete this->view;
	this->model = NULL;
	this->view = NULL;

}

bool ClassicSpaceBattleController::play(SDL_Event e)
{	

	this->model->checkWinConditions();
	ClassicGamePhases currentPhase = this->model->getGamePhase();
	switch(currentPhase)
	{	
		case PLAYING:
			{
				processInput();
				break;
			}
		case LOSS:
			{
				printf("The game has been lost\n");
				return true;
				break;
			}
		case WIN:
			{
				printf("The game has been won\n");
				return true;
				break;
			}
		case PAUSED:
			{
				return false;
				break;
			}
		case INIT:
			{
				return false;
				break;
			}
		default:
			{
				printf("what is going on? default gamestate!?\n");
				return false;
				break;
			}

	}
	

	this->model->update();
	this->view->update();
	return false; 

}

void ClassicSpaceBattleController::setGameOver(bool value)
{
	this->gameOver = value;
}

bool ClassicSpaceBattleController::restartGame(int scale_ratio)
{
	printf("restarting the game :) \n");

	bool success = true;
	ClassicSpaceBattle* temp = this->model;
	this->model = new ClassicSpaceBattle(CLASSIC_SHIP_CLASSES,scale_ratio = scale_ratio	);
	this->gameOver = false;
	success = this->view->changeModelAndRestart(this->model);
	return success;


}
void ClassicSpaceBattleController::processInput()
{
	//Process Input
	const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
	if( currentKeyStates[ SDL_SCANCODE_LEFT ] )
	{
		//if we press left, we move the player left
		this->model->movePlayer(-1,false);
		
	}
	else if( currentKeyStates[ SDL_SCANCODE_RIGHT ] )
	{
		//if we press right, we move the player right
		this->model->movePlayer(1,false);
	}
	else if ( currentKeyStates[ SDL_SCANCODE_SPACE ])
	{
		//this->model->movePlayer(1,false);
		if(this->model->createPlayerBullet())
		{
			this->view->addNewPlayerBullet();
		}
	}

	
}

int main(int argc, char const *argv[])
{

	ClassicSpaceBattleController* controller = new ClassicSpaceBattleController(GAME_SCALE_RATIO);
	bool quit = false;

	SDL_Event e;

	//global timer
	SDLTimer timer;

	//frame counter
	SDLTimer capTimer;
	int countedFrames = 0;
	timer.start();

	while( !quit )
	{
			capTimer.start();
	//Handle events on queue
			while( SDL_PollEvent( &e ) != 0 )
			{
				//User requests quit
				if( e.type == SDL_QUIT )
				{
					quit = true;
				}
			}

			
		
			//Calculate and correct fps
			float avgFPS = countedFrames / ( timer.getTicks() / 1000.f );
			if( avgFPS > 2000000 )
			{
				avgFPS = 0;
			}

			// printf("avgFPS is %f\n",avgFPS);

			if(controller->play(e))
			{
				//if the game is over
				controller->setGameOver(true);
				controller->restartGame(GAME_SCALE_RATIO);
			}
			countedFrames++;

			int frameTicks = capTimer.getTicks();
			if( frameTicks < SCREEN_TICKS_PER_FRAME )
			{
				//Wait remaining time
                    SDL_Delay( SCREEN_TICKS_PER_FRAME - frameTicks );
			}


	}
	
	delete controller;


	return 0;	
}