#pragma once
#include <string>
#include <vector>
#include <SDL_image.h>
#include <SDL.h>
#include "Model.h"
#include <queue>
#include <memory>

using std::queue;
using std::string;
using std::vector;


/* A Ship Class is a specific kind of ship. They differ in size and sprite.
	Class One is also known as "Octopus","Eclipse" or simply Large Invader
	Class Two is also known as "Crab" or simply Medium Invader
	Class Three is also known as "Squid" or simply Small Invader */
enum EnemyShipClasses
	{
		CLASS_ONE,
		CLASS_TWO,
		CLASS_THREE,
		NUMBER_OF_CLASSES
	};	


/* The classic movement is a pattern in which the aliens moves in the old game.
   It works like this: Each frame, from bottom to top, one alien is pushed toward a direction (left or right).
   When one alien reaches the border, Ending Push phase starts, to let all the remaining ship to complete their 
   movement. Then, Down phase begins, where the alien get's pushed down, towards the shields. After all the 
   aliens are pushed down, Push phase begins again, facing the opposite direction of last push phase.*/
enum ClassicMovementPhases
	{
		PUSH,
		ENDING_PUSH,
		DOWN
	};

/*The different states in which a game can be */
enum ClassicGamePhases
	{
		INIT,
		LOSS,
		PAUSED,
		WIN,
		PLAYING
	};

/* These are general utilities used in the game for game logic purposes.*/
namespace Utilities
{
	class SDLTimer{
		public:
			SDLTimer();

			//timer actions
			void start();
			void stop();
			void pause();
			void unpause();

			//return timer time
			Uint32 getTicks();

			//Check status time
			bool isStarted();
			bool isPaused();
		private:
			//Ticks at timer start
			Uint32 startTicks;

			//Ticks at paused timer
			Uint32 pausedTicks;

			//Timer status
			bool paused;
			bool started;
	};

}

namespace Entities
{

	/*An Entity of the game. It has x,y coordinates, width and height.*/
	class Entity{
		protected:
			//x and y of the entity (upper-left corner)
			int x, y;
			//the width and height of the entity, that can be seen as the dimensions of the sprite
			int width, height;
		public:
			Entity(int,int,int,int);
			//public deconstructor
			virtual ~Entity() {};
			int getX();
			int getY();
			int getWidth();
			int getHeight();
			
	};

	
	/*	A living Enity is simply an Entity that can be drawn. This class is linked with the View logic, which will always have reference,
		if needed, to Living Entities. If a LivingEntity isDrawable, it means that has to be drawn, otherwise it must not be drawn.
		In addition, a Living Entity can change its X,Y coordinates over time (setX, setY).	*/
	class LivingEntity : public Entity{
		private:
			bool drawable;
		public:
			LivingEntity(int,int,int,int);
			void setX(int);
			void setY(int);
			bool isDrawable();
			void setDrawable(bool);
	};

	/*	A shield is comprised of many Shield Units. This is how we achieve a shield that destroy both graphically and logically, like
		in the original game. This is the only aspect of the game that is not reproduced 1:1 since having a pixel-precise destruction of 
		the shields was far too complex than the scope of this game and also the gameplay wouldn't gain anything from it.
		There are 8 kinds of shield unit in total, to accurately recreate the original shield.*/
	class ShieldUnit : public LivingEntity{
		private:
			bool destroyed;			//Wheter this shield unit is destroyed or not
			string intactPath;		//path of intact shield unit texture
			string brokenPath;		//path of broken shield unit texture
			bool halfShield;		//some shield unit are half the size of the classic unit. This is used to precisely manage collision
		public:
			//x,y,width,height,intactPath,brokenPath,halfShield
			ShieldUnit(int,int,int,int,string,string,bool);
			bool isDestroyed();
			bool isHalfShield();
			void destroy();
			string getIntactTexturePath();
			string getBrokenTexturePath();
	};




	/* Bullet represent a bullet that can only travel vertically, in a tipical SpaceInvaders Fashion. */
	class Bullet : public LivingEntity{
		private:
			//the bullet damage
			int damage;
			//the velocity of the bullet
			int velocity;
			//direction is +1 if its going down, -1 otherwise
			int direction;
		public:
			//x,y,width,length,damage,velocity, direction
			Bullet(int,int,int,int,int,int,int);
			int getDamage();
			int getBulletDirection();
			void update();
	};

	/*	A Ship is a special Living Entity that models a Space Ship. As such, it has HP, damage values... etc.
		This class is virtual but represent the common ground between the Enemy Ships and the Player Ship.   */
	class Ship : public LivingEntity{
		protected:
			int hp,damage,velocity;			//Health Points, Damage and Velocity of the Ship
			float cooldown;					//Cooldown for the cannon
			string texturePath;				//The path of the texture
			string bulletTexturePath;		//The path of the bullet texture

		public:
			//x,y,width,height,hp,damage,velocity,cooldown,texture_path,bulletTexturePath
			Ship(int,int,int,int,int,int,int,float,string,string);
			int getHp();
			bool inferDamage(int);			//infer damage to the ship. If the ship is destroyed, returns true
			float getCooldown();
			int getAmmoDamage();
			int getVelocity();
			void setVelocity(int);
			virtual void printSummary();
			string getTexturePath();
			string getBulletTexturePath();
	};


	class PlayerShip : public Ship{
		protected:
			//memory management?
			string* playerName;
		public:
			//x,y,width,height,hp,damage,velocity,cooldown,playerName,texture_path
			PlayerShip(int,int,int,int,int,int,int,float,string*,string);
			~PlayerShip();
			void printSummary();
			void moveHorizontally(int);

	};

	class EnemyShip : public Ship{

			/*  push distance and down distance are given by the SpaceBattle class
				as argument to the constructors; they represent the basic movement of
				a classic space invaders ship	*/
			int pushDistance,downDistance; 

			/* Direction codifies where the ship is moving.it is a positive 1 if it's going
			   right, -1 if its going left.		*/ 
			int direction;

			
			int points;					//point given upon destruction

		protected:
			string shipClass;
		public:
			//x,y,width,height,hp,damage,velocity,cooldown,pushDistance,downDistance,shipClass,texture_path,bullet_texture_path
			EnemyShip(int,int,int,int,int,int,int,int,float,int,int,string,string,string);
			void printSummary();
			int getPoints();

			bool isGoingRight();		//returns true is the ship is currently moving to the right	
			
			void push();				//Used to move the enemyship in the "classic movement". The ship is moved by pushDistance left or right 
			void down();				//Used to move the enemyship in the "classic movement". The ship is moved down by downDistance 
			void flip();				//Revert the direction of the ship
			int getPushDistance();
			virtual void getClassName() = 0;	//EnemyShip is a virtual class
			
	};

	//this is a "real" enemy ship, a Class One (Octopus) ship
	class ClassOneShip : public EnemyShip{
		private:
			
		public:
			//x,y,scale_ratio,push_distance,down_distance
			ClassOneShip(int,int,int,int,int);
			void getClassName();

	};

	class ClassTwoShip : public EnemyShip{
		private:
			
		public:
			//x,y,scale_ratio,push_distance,down_distance
			ClassTwoShip(int,int,int,int,int);
			void getClassName();

	};

	class ClassThreeShip : public EnemyShip{
		private:
			
		public:
			//x,y,scale_ratio,push_distance,down_distance
			ClassThreeShip(int,int,int,int,int);
			void getClassName();

	};

	/*	A Shield blocks the projectiles both from the enemy ships and the player. It gets damaged every time it is hit after a bullet.
		We could see a Shield as a mosaic of Shield Units. A bullet always hits a single shield unit, and that unit gets destroyed and
		change its texture to show graphically that it's destroyed.
		A Shield gets constructed given a starting x,y and the scale ratio.
		The constructor takes care of the creation of the various shield units that composes it self. 
		There are 7 different shield units to match the geometric shape of the original space invaders shield. 
		Overall a shield is comprised of (4 * 9 shield units) - 3. For more info check docs. 
	*/
	class Shield {
		private:
			int startingX,startingY;
			int rows,columns;				//rows and columns of Shield Units
			int scale_ratio;
			int unitShieldWidth;
			int unitShieldHeight;
			vector<vector<std::shared_ptr<ShieldUnit>>> shieldParts;  //Vector containing all the shield parts of the shield.

			int shieldWidth,shieldHeight;	//Overall width and height of the shield
			void init();
			// x, y, type of shield, row, column
			void createShield(int,int,int,int,int);		//this method creates a single shield unit. it is used internally during initialization.
			
			/*	This method returns a randomized path of the brokenTexture. There are 8 different "broken shield unit" textures, and 
				to recreate a beautiful destroyed shield. Since it is randomized, every shield will look different when destroyed.*/
			string randomBrokenPath();					

		protected:
		public:
			//starting x,y; scale_ratio
			Shield(int,int,int);
			~Shield();
			int getShieldRows();
			int getShieldColumns();
			int getShieldWidth();
			int getShieldHeight();
			std::shared_ptr<ShieldUnit> getShieldUnitByIndex(int,int);
	};
}

namespace GameEntities
{
	using namespace Entities;
	/*	A board represents the logic structure of a battle playground.
	*	In this base superclass, it only represent a rectangle with width, height and the scale_ratio.
	*/
	class Board {
		protected:
			int width,height;
			int scale_ratio;
		public:
			Board(int,int,int);
			int getBaseWidth();
			int getWidth();
			int getBaseHeight();
			int getHeight();
			int getScaleRatio();
			void printSummary();

	};

	/*	A classic board is the "battle field" of the classic 1978 space invaders game.
	*	As such, this class contains all the information that the model and the view needs.
	*	We can see it as a container for fundamental information regarding the battle field.
	*/
	class ClassicBoard : public Board {
		
		//The Upper Hud area between 0 and upperHud
		int upperHud;
		//The Lower Hud area is between 256 and lowerHud
		int lowerHud;
		//The y coordinate of the centre of enemy spawn area
		int enemyYAreaCenter;
		//The y coordinate of the bottom of the shield spawn area
		int shieldY;
		//the x coordinate of the starting x of the shields
		int shieldX;
		//the horizontal offset between shields
		int shieldOffset;
		//the y coordinate of the centre of the player spawn area
		int shipYCenter;
		//the space between enemy centres in the x Axis
		int enemyXOffset;
		//the space between enemy centres in the y Axis
		int enemyYOffset;
		//the height of an enemy
		int enemyHeight;
		//the x coordinate of the centre of the screen
		int xCenter;
		//the x coordinate of the left enemy border
		int enemyLeftBorder;
		//the x coordinate of the right enemy border
		int enemyRightBorder;
		//the y coordinate of "score" text (shared with highscore and score2)
		int scoreY;
		//the x coordinate of "score" text
		int scoreX;
		//the x coordinate of hi-score text
		int highScoreX;
		//the x coordinate of score 2 text
		int score2X;
		//the y coordinate of the points down "score"
		int scoreNumberY;
		//the x coordinate of the points down "score"
		int scoreNumberX;
		//the x coordinate of the points down "hiscore"
		int hiScoreNumberX;
		//the y coordinate of the lifes sprites (it is good also for CREDIT writing)
		int lifesY;
		//the x coordinate of the lifes sprites
		int lifesX;
		//the x coordinate of the credit writing
		int creditX;
		//the y coordinate of the credit writing
		int creditY;
		//the x coordinate of the lifes number
		int lifesNumberX;
		//the x coordinate of where the player spawns
		int playerXSpawn;
		//the y coordinate of the special Ship
		int specialShipY;
		//An offset used to indicate the area where bullets should explode near the hud
		int bulletLandOffset;


		public:
			ClassicBoard(int);
			inline int getUpperHud(){ return this->upperHud; };
			inline int getLowerHud(){ return this->lowerHud; };
			inline int getLifesX(){ return this->lifesX;};
			inline int getLifesY(){ return this->lifesY;};
			inline int getCreditX(){ return this->creditX;};
			inline int getCreditY(){ return this->creditY;};
			inline int getLifesNumberX(){return this->lifesNumberX;};
			inline int getEnemyYAreaCenter(){ return this->enemyYAreaCenter; };
			inline int getShieldY(){ return this->shieldY; };
			inline int getShieldX(){ return this->shieldX; };
			inline int getShieldOffset(){ return this->shieldOffset;};
			inline int getShipYCenter(){ return this->shipYCenter; };
			inline int getEnemyXOffset(){ return this->enemyXOffset; };
			inline int getEnemyYOffset(){ return this->enemyYOffset; };
			inline int getEnemyHeight(){ return this->enemyHeight; };
			inline int getXCenter(){ return this->xCenter; };
			inline int getEnemyLeftBorder() { return this -> enemyLeftBorder;};
			inline int getEnemyRightBorder() { return this-> enemyRightBorder;};
			inline int getScoreY() {return this->scoreY;}
			inline int getScoreX() {return this->scoreX;}
			inline int getHighScoreX() {return this->highScoreX;}
			inline int getScore2X()	{return this->score2X;}
			inline int getScoreNumberY(){return this->scoreNumberY;}
			inline int getScoreNumberX(){return this->scoreNumberX;}
			inline int getHighScoreNumberX(){return this->hiScoreNumberX;}
			inline int getPlayerXSpawn(){return this->playerXSpawn;}
			inline int getSpecialShipY(){return this->specialShipY;}
			inline int getBulletLandOffset(){ return this->bulletLandOffset;}
	};


	

	//---Space Battle--//
	/*	A Space Battle could be seen as everything on top of a Board. For example, in chess, the board is the chessboard.
	*   The pieces, the rules and all the moves that takes from the start to the end,are all part of something that here we call "Space Battle".
	*	SpaceBattle is a virtual superclass that represents a generic space battle. In this sense it contains everything that we think a space battle must have,
	*	like some enemies, a playership, bullets, some win conditions, etc.
	*/
	class SpaceBattle {

		protected:

			// These three vectors contain the pointers of the entities indicated.
			vector<vector<std::shared_ptr<EnemyShip>>> enemies;
			std::shared_ptr<PlayerShip> playerShip;
			vector<std::shared_ptr<Bullet>> bullets; 

			/* Saying that "every SpaceBattle must have a GameBoard"
			   seems like a very reasonable constraint for a battle. 
			   But since every board is going to be potentially very 
			   different, and we have very fews methods inside superclass
			   board, probably makes more sense to say something like
			   "A ClassicSpaceBattle must have a ClassicBoard". If we don't
			   do so, we need to cast the gameBoard to its type everytime*/
			//Board* gameBoard;

			//BUT we need at least to know the scale ratio, otherwise it's a problem creating bullets (usually this info is recovered from the board)
			int scale_ratio;

			Utilities::SDLTimer* playerCooldownTimer;		//A timer used to regulate the cooldown of the player guns.
			Uint32 lastShotTicks;
			Uint32 currentTicks;
			Uint32 lastEnemyShotTicks;
			int    enemyShotsDelay;							//delay between shots of the enemy in ticks (60*second)
		public: 
			//there are still methods to be added as superclass of spacebattle
			//also private methods such as checkCollision, checkWin... etc
			//SpaceBattle();
			virtual void init() = 0;
			virtual void update() = 0;
			virtual void checkWinConditions() = 0;
			bool checkCollision(LivingEntity*, LivingEntity*);
			bool createPlayerBullet();
			void movePlayer(int,bool);
			int  getBulletsSize();
			std::shared_ptr<LivingEntity> getLastBullet();
			
	};

	/*	A Classic Space Battle represent the space battle of the 1978 space invaders.
	 *	It has x enemies deployed on y lines, and each line is of a specific class.
	 *  It contains shields (usually 4) and a special red ship that sometimes cross the board.
	 *  Lose conditions: All lifes depleted, Enemy ships touch the ground.
	 *  Win conditions: All enemies destroyed.
	 *  --------
	 *  This implementation allows for some personalization of the battle field;
	 *  You can check the constructor for more info about it; But careful, because
	 *	the information you give must be consistent (You cannot give 5 rows of enemies and specify just 1 ship class line for example)
	 *  The deploying of the enemy and shields should be arranged by itself, but undesired results are a possibility.
	 */
	class ClassicSpaceBattle : public SpaceBattle {

		private:
			int rowsOfEnemies;							//how many rows of enemies
			int numberOfShields;						//how many shields
			int enemiesPerRow;							//how many enemies per row
			int enemiesRemaining;						//how many enemies are still alive
			int playerLifes;							//how many lifes the player has
			int score;									//the score of the player 
			vector<EnemyShipClasses> classPerRow; 		//this vector specifies the kind of enemy per each line, element 0 is the bottom line.
			ClassicBoard* gameBoard;					//a classic space battle has a ClassicBoard.
			
			bool enemyLanded;							//have the enemy landed?
			bool playerShipDestroyed;					//is the player ship destroyed?

			/*	A queue containing all enemyships(including the destroyed as NULL), from bottom left to top right
				this is used to manage the classic movement, in which each frame only one ship moves (the next one on the queue) */
			queue<std::shared_ptr<EnemyShip>> enemyQueue;

			
			ClassicMovementPhases currentPhase;			//Classic movement is divided into phases: Push, Ending Push, Down
			ClassicGamePhases gamePhase;				//Also the game is divided into phases: Init, Gameover...

			std::shared_ptr<EnemyShip> firstShip;		//A pointer to the firstShip in the movement, used to manage classic movement

			vector<std::shared_ptr<Shield>> shields;	//A vector containing the shields

			/* Methods name are pretty straight forward. Implementation can be checked for more infos, if needed.
			 * I will use this space to make some consideration. I believe in fact that some of these methods should be in a more general class.
			 * checkBulletsCollisions, collisionWithEnemy, collisionWithPlayer seems not just useful for a classicSpaceBattle, but also for future battles.
			 * It is also true on the other hand, that in a classic battle, bullets only move vertically. It means that controls are easier, so it make sense
			 * to have a specific implementation for this kind of battle. For the scope of the game right now, this choice works just fine, but maybe in the
			 * future some changes will be needed. Maybe a new intermediate class, or maybe different battles will just be subclass of classic space battle.
			 */
			bool checkIfEnemyLanded(EnemyShip*);		
			void findEnemyInQueue(EnemyShip*);
			void createEnemies();
			void createPlayer();
			void createShields();
			void moveEnemiesClassic();
			void moveEnemies();
			void spawnEnemyBullet();
			void makeEnemyShoot(EnemyShip*);
			void moveBullets();
			void checkBulletsCollision();
			bool checkBulletCollisionWithEnemy(Bullet*);
			bool checkBulletCollisionWithPlayer(Bullet*);
			bool checkBulletCollisionWithShields(Bullet*);
			bool checkBulletCollisionWithSingleShield(Bullet*,int);
			bool checkEnemyCollisionWithSingleShield(EnemyShip*,int);
			bool checkBoundaryCollision(EnemyShip* current);
			bool enemiesDestroyed();
		public:
			//default values represents the 1978 battle.
			ClassicSpaceBattle(vector<EnemyShipClasses>,int scale_ratio = 3, int rowsOfEnemies = 5, int shields = 4, int enemiesPerRow = 10);
			void init();
			void initBasic();							//init basic initialize the classic game from the 1978 game
			void update();								//updates the logic of the game
			void checkWinConditions();					//check if win conditions are met
			void printSummary();						//prints a summary of the model. Used now just for test purposes
			int getRowsOfEnemies();					
			int getEnemiesPerRow();
			int getNumberOfShields();
			std::shared_ptr<Shield> getShield(int);		//return the i shield.
			PlayerShip* getPlayerShip();				
			std::shared_ptr<PlayerShip> getPlayerShipSharedPointer();
			ClassicBoard* getGameBoard();
			EnemyShip* getEnemyByRowAndColumn(int,int);
			std::shared_ptr<EnemyShip> getEnemyPointerByRowAndColumn(int,int);
			void movePlayer(int,bool);					//moves the player of (int) direction. (bool) vertically specifies if the move is vertical. not implemented yet.
			string getEnemyBasicBulletPath();
			ClassicGamePhases getGamePhase();
			int getPlayerLifes();
			int getScore();
			int getEnemiesRemaining();

	};


}	

