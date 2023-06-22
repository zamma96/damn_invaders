#include "Model.h"
#include "View.h"
#include <string>
#include <stdio.h>
#include <vector>
using std::string;

using namespace Entities;
using namespace GameEntities;
using namespace ViewEntities;
/* Alpha version of the controller */


namespace Controller
{
	class BasicController{
		public:
			//BasicController();
			//virtual ~BasicController() = 0;
			virtual bool play() = 0;

	};
	class ClassicSpaceBattleController : BasicController{
		private:
			void init(int);						//Initialize the Controller, given the Scale Ratio of the original game desired 
			
			void close();						//Handles memory when the object is destroyed
			
			void processInput();				//Handles the input and modifies the model according to it
			
			void processInputInPause();			//Handles the input when game is paused

			ClassicSpaceBattle* model;			//The model (Forced to be a ClassicSpaceBattle since is a CSBController)
			ClassicSpaceBattleView* view;		//The View
			

			Utilities::SDLTimer pauseTimer;				//timer used for pause


		public: 
			ClassicSpaceBattleController(int);	//Constructor

			~ClassicSpaceBattleController();	//Destructor

			bool play();						//Plays one frame of the game
			
				
			bool restartGame(int);				//Restarts the game with the given Scale_Ratio

	};
}
