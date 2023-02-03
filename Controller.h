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
			//this method is used to given control to that controller 
			//needs to be well designed
			virtual bool play(SDL_Event e) = 0;

	};
	class ClassicSpaceBattleController : BasicController{
		private:
			void init(int);
			void close();
			void processInput();
			ClassicSpaceBattle* model;
			ClassicSpaceBattleView* view;
			bool gameOver;


		public: 
			ClassicSpaceBattleController(int);
			~ClassicSpaceBattleController();
			bool play(SDL_Event e);
			void setGameOver(bool);
			bool restartGame(int);

	};
}
