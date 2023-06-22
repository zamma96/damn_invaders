#include "Model.h"
#include "View.h"
#include "Controller.h"
#include <string>
#include <stdio.h>
#include <vector>
#include <SDL.h>
#define SDL_MAIN_HANDLED
//#undef main
using std::string;

using namespace Entities;
using namespace GameEntities;
using namespace ViewEntities;
using namespace Controller;
using namespace Utilities;

//---- Const Variables ----//
const int GAME_SCALE_RATIO 			= 2;

const int FRAME_RATE 				= 60;

const int SCREEN_TICKS_PER_FRAME 	= 1000/FRAME_RATE;	

const int PAUSE_COOLDOWN_TICKS		= 250;

/* This vector specifies the class of ship per each line. First element is the most bottom line of enemies, going upwards. */
const vector<EnemyShipClasses> CLASSIC_SHIP_CLASSES{CLASS_ONE,CLASS_ONE,CLASS_TWO,CLASS_TWO,CLASS_THREE};


/* Creates a CSBController given the scale_ratio for the view. 
   A Classic Space Battle is infact designed to reproduce the 1974 game 1:1.
   It means that every dimension and sprite will be the same of the original;
   The final effect could result different, for more info check docs.
   Since 224*256 is pretty small nowadays, we scale everything by the value of scale_ratio */
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

	this->pauseTimer.start();
	

}

void ClassicSpaceBattleController::close()
{

	delete this->model;
	delete this->view;
	this->model = NULL;
	this->view = NULL;

}

bool ClassicSpaceBattleController::play()
{	
	//We check if win conditions are reached
	this->model->checkWinConditions();					

	//Then we see which phase is resulted by the last check
	ClassicGamePhases currentPhase = this->model->getGamePhase();

	switch(currentPhase)
	{	
		//if we are in the playing phase
		case PLAYING:
			{
				processInput();	//we process player input
				break;
			}
		//if the game is lost
		case LOSS:
			{
				printf("The game has been lost\n");
				//we return true, to communicate that the game has entered a terminal phase
				return true;
				break;
			}
		case WIN:
			{
				printf("The game has been won\n");
				//we return true, to communicate that the game has entered a terminal phase
				return true;
				break;
			}
		case PAUSED:
			{
				
				processInputInPause();
				break;
			}
		case INIT:
			{	//if the game is initializing, we do nothing
				return false;
				break;
			}
		default:
			{
				//this snippet of code should'nt be reachable
				printf("what is going on? default gamestate!?\n");
				return false;
				break;
			}

	}
	
	/*Then we update all the game logic of the model*/
	this->model->update();

	/*Once we're done, we call the update of the view so that it can changes according to the changes in the model.*/
	this->view->update();

	//return false means that the game has not entered a terminal phase
	return false; 

}


bool ClassicSpaceBattleController::restartGame(int scale_ratio)
{
	//By default, the game will restart successfully
	bool success = true;

	//we save current model in a variable
	ClassicSpaceBattle* temp = this->model;

	//we create a new model
	this->model = new ClassicSpaceBattle(CLASSIC_SHIP_CLASSES,scale_ratio = scale_ratio	);
	
	//we delete the old model
	delete temp;
	
	//we warn the view to change it's model and to restart. If successfully, it will return true
	success = this->view->changeModelAndRestart(this->model);
	
	this->pauseTimer.stop();
	this->pauseTimer.start();

	return success;


}
void ClassicSpaceBattleController::processInput()
{
	//We get the current KeyState to process input
	const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );

	//if we press left, we move the player left
	if( currentKeyStates[ SDL_SCANCODE_LEFT ] )
	{
		this->model->movePlayer(-1,false);
	}
	//if we press right, we move the player right
	else if( currentKeyStates[ SDL_SCANCODE_RIGHT ] )
	{
		
		this->model->movePlayer(1,false);
	}
	//if we press space, we shoot with the guns
	else if ( currentKeyStates[ SDL_SCANCODE_SPACE ])
	{
		//if the creating of the bullet have success
		if(this->model->createPlayerBullet())
		{
			//we must inform the view that a new bullet is inside the game model
			this->view->addNewPlayerBullet();
		}
	}
	else if (currentKeyStates[SDL_SCANCODE_P] && this->pauseTimer.getTicks() > PAUSE_COOLDOWN_TICKS)
	{
		this->pauseTimer.stop();
		this->pauseTimer.start();
		this->model->pauseGame();
	}

	
}

void ClassicSpaceBattleController::processInputInPause()
{
	//We get the current KeyState to process input
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	printf("porco dio i tick sono %i", this->pauseTimer.getTicks());
	if (currentKeyStates[SDL_SCANCODE_P] && this->pauseTimer.getTicks() > PAUSE_COOLDOWN_TICKS)
	{
		this->model->unPauseGame();
		this->pauseTimer.stop();
		this->pauseTimer.start();
	}
}

int main(int argc, char* argv[])
{
	//we create the controller
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

	

			if(controller->play())
			{
				//if the game is over
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