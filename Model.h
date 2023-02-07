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

enum EnemyShipClasses
	{
		CLASS_ONE,
		CLASS_TWO,
		CLASS_THREE,
		NUMBER_OF_CLASSES
	};	

enum ClassicMovementPhases
	{
		PUSH,
		ENDING_PUSH,
		DOWN
	};

enum ClassicGamePhases
	{
		INIT,
		LOSS,
		PAUSED,
		WIN,
		PLAYING
	};
//we cannot set by default an array for a function, so we declare this for basic init
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
			// virtual void draw() = 0;
	};

	

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


	class ShieldUnit : public LivingEntity{
		private:
			bool destroyed;
			string intactPath;
			string brokenPath;
			bool halfShield;
		public:
			//x,y,width,height,intactPath,brokenPath,halfShield
			ShieldUnit(int,int,int,int,string,string,bool);
			bool isDestroyed();
			bool isHalfShield();
			void destroy();
			string getIntactTexturePath();
			string getBrokenTexturePath();
	};




	/* Bullet represent a bullet that can only travel vertically, 
	/* in a tipical SpaceInvaders Fashion. Maybe it will be evolved later */
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

	class Ship : public LivingEntity{
		protected:
			int hp,damage,velocity;
			float cooldown;
			string texturePath;
			string bulletTexturePath;

		public:
			Ship(int,int,int,int,int,int,int,float,string,string);
			int getHp();
			bool inferDamage(int);
			int getPoints();
			float getCooldown();
			//here we have two methods that somehow communicate the same information. Maybe we should get rid of one?
			bool isGoingRight();
			int getDirection();
			int getAmmoDamage();
			int getVelocity();
			void setVelocity(int);
			bool readyToShoot();	//it does not have internal clock, the classic game space should be in charge of saying if he's able to shoot again or not
			virtual void printSummary();
			string getTexturePath();
			string getBulletTexturePath();
	};


	class PlayerShip : public Ship{
		protected:
			//memory management?
			string* playerName;
		public:
			PlayerShip(int,int,int,int,int,int,int,float,string*,string);
			void printSummary();
			void moveHorizontally(int);

	};

	class EnemyShip : public Ship{
			/*push distance and down distance are given by the SpaceBattle class
			as argument to the constructors; they represent the basic movement of
			a classic space invaders ship */
			int pushDistance,downDistance; 
			//Direction codifies where the ship is moving. it is a positive 1 if it's going
			//right, -1 if its going left. 
			int direction;
			//point given upon destruction
			int points;
		protected:
			//memory management?
			const string* shipClass;
		public:
			//x,y,width,height,hp,damage,velocity,cooldown,pushDistance,downDistance,texture_path
			EnemyShip(int,int,int,int,int,int,int,int,float,int,int,const string*,string,string);
			void printSummary();
			int getPoints();

			//here we have two methods that somehow communicate the same information. Maybe we should get rid of one?
			bool isGoingRight();
			int getDirection();
			
			void push();
			void down();
			void flip();
			int getPushDistance();
			virtual void getClassName() = 0;
			
	};

	//this is a "real" enemy ship, a Class One (Octopus) ship
	class ClassOneShip : public EnemyShip{
		private:
			
		public:
			//x,y
			ClassOneShip(int,int,int,int,int);
			void getClassName();

	};

	class ClassTwoShip : public EnemyShip{
		private:
			
		public:
			//x,y
			ClassTwoShip(int,int,int,int,int);
			void getClassName();

	};

	class ClassThreeShip : public EnemyShip{
		private:
			
		public:
			//x,y
			ClassThreeShip(int,int,int,int,int);
			void getClassName();

	};

	class Shield {
		private:
			int startingX,startingY;
			int rows,columns;
			int scale_ratio;
			int unitShieldWidth;
			int unitShieldHeight;
			vector<vector<std::shared_ptr<ShieldUnit>>> shieldParts;

			int shieldWidth,shieldHeight;
			void init();
			// x, y, type of shield, row, column
			void createShield(int,int,int,int,int);
			string randomBrokenPath();

		protected:
		public:
			//starting x,y; scale_ratio
			Shield(int,int,int);
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

	class SpaceBattle {

		protected:
			vector<vector<std::shared_ptr<EnemyShip>>> enemies;
			std::shared_ptr<PlayerShip> playerShip;
			//it will be bullets and other entities such shields, must be completed
			vector<std::shared_ptr<Bullet>> bullets; 

			/* Saying that "every SpaceBattle must have a GameBoard"
			   seems like a very reasonable constraint for a battle. 
			   But since every board is going to be potentially very 
			   different, and we have very fews methods inside superclass
			   board, probably makes more sense to say something like
			   "A ClassicSpaceBattle must have a ClassicBoard". If we don't
			   do so, we need to cast the gameBoard to its type everytime*/
			//Board* gameBoard;

			 //BUT we need at least to know the scale ratio, otherwise it's a problem creating bullets
			int scale_ratio;

			Utilities::SDLTimer* playerCooldownTimer;
			Uint32 lastShotTicks;
			Uint32 currentTicks;
			Uint32 lastEnemyShotTicks;
			int    enemyShotsDelay; //delay between shots of the enemy in ticks (60*second)
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

	// extern vector<EnemyShipClasses> classic_ship_classes;
	class ClassicSpaceBattle : public SpaceBattle {

		private:
			int rowsOfEnemies;
			int numberOfShields;
			int enemiesPerRow;
			int playerLifes;
			//the game score
			int score;
			vector<EnemyShipClasses> classPerRow; 	
			ClassicBoard* gameBoard;
			
			bool enemyLanded;
			bool playerShipDestroyed;

			//A queue containing all enemyships (including the destroyed as NULL),from bottom left to top right
			//used for classic movement
			queue<std::shared_ptr<EnemyShip>> enemyQueue;

			
			//phases for the classic movement
			ClassicMovementPhases currentPhase;
			//phases of the game 
			ClassicGamePhases gamePhase;

			std::shared_ptr<EnemyShip> firstShip;

			vector<std::shared_ptr<Shield>> shields;

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
			//scale_ratio,enemies
			ClassicSpaceBattle(vector<EnemyShipClasses>,int scale_ratio = 3, int rowsOfEnemies = 5, int shields = 4, int enemiesPerRow = 10);
			void init();
			//init basic initialize the classic game from the 1978 game
			void initBasic();
			void update();
			void checkWinConditions();
			void printSummary();
			int getRowsOfEnemies();
			int getEnemiesPerRow();
			int getNumberOfShields();
			std::shared_ptr<Shield> getShield(int);
			PlayerShip* getPlayerShip();
			std::shared_ptr<PlayerShip> getPlayerShipSharedPointer();
			ClassicBoard* getGameBoard();
			EnemyShip* getEnemyByRowAndColumn(int,int);
			std::shared_ptr<EnemyShip> getEnemyPointerByRowAndColumn(int,int);
			void movePlayer(int,bool);
			string getEnemyBasicBulletPath();
			ClassicGamePhases getGamePhase();
			int getPlayerLifes();
			int getScore();

	};


}	

