
#include <stdio.h>
#include <string>
#include <cmath>
#include "Model.h"
#include <cassert>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>


using std::string;
using namespace Entities;
using namespace GameEntities;
using namespace Utilities;

/*
 * This implementation make a large use of parametrized variables used to:
 *	-Accurately recreate the 1978 game, both visually and gameplay wise.
 *  -Give room to the developer to tweak all these values in order to create the desired gameplay experience.
 *  -Easily change assets path 
 * 
 * Each variable has a name describing what it is, so they will not be commented.
 * -------------------------------
 *
 * Note: I designed the game by incorporating into the model information that are relevant for the view.
 * For example, apart from the size of the various entities, also the texture paths are fields.
 * This design choice must not be seen as the best possible. It's just a choice I made.
 */

//--- parametrized playerShip values ---//

const int 	BASIC_PLAYER_SHIP_WIDTH 	= 13;
const int 	BASIC_PLAYER_SHIP_HEIGHT 	= 8;
const int 	BASIC_PLAYER_SHIP_HP		= 10;
const int 	BASIC_PLAYER_SHIP_DAMAGE    = 5;
const int 	BASIC_PLAYER_SHIP_VELOCITY	= 1;
const float BASIC_PLAYER_SHIP_COOLDOWN  = 0.7f;
string BASIC_PLAYER_TEXTURE_PATH 		= "player_ship.png";
string PLAYER_BULLET_TEXTURE_PATH		= "simple_bullet.png";
const int   BASIC_PLAYER_BULLET_HEIGHT  = 5;
const int 	BASIC_PLAYER_BULLET_WIDTH	= 1;
const int 	PLAYER_SHIP_BULLET_OFFSET   = 4;

const int 	PLAYER_BULLET_VELOCITY 		= 4;


//--- parametrized ships values ---//
string BASIC_BULLET_TEXTURE_PATH		= "enemy_bullet_";
const int   BASIC_ENEMY_BULLET_HEIGHT 	= 7;
const int 	BASIC_ENEMY_BULLET_WIDTH	= 3;
const int 	BASIC_ENEMY_BULLET_VELOCITY	= 1;
//--- Class One "Octopus" Ship ---// 

const int 	CLASS_ONE_WIDTH 			= 12;
const int 	CLASS_ONE_HEIGHT 			= 8;

const int 	CLASS_ONE_POINTS			= 10;
const int 	CLASS_ONE_HP 				= 5;
const int 	CLASS_ONE_DAMAGE 			= 10;
const int 	CLASS_ONE_VELOCITY 			= 1;
const float CLASS_ONE_COOLDOWN 			= 1.0;
string CLASS_ONE_NAME 					= "Class One";
string CLASS_ONE_TEXTURE_PATH 			= "octopus_ship_complete.png";

//--- Class Two "Crab" Ship ---// 

const int 	CLASS_TWO_WIDTH 			= 11;
const int 	CLASS_TWO_HEIGHT 			= 8;

const int 	CLASS_TWO_POINTS			= 20;
const int 	CLASS_TWO_HP 				= 5;
const int 	CLASS_TWO_DAMAGE 			= 10;
const int 	CLASS_TWO_VELOCITY 			= 1;
const float CLASS_TWO_COOLDOWN 			= 1.0;
string CLASS_TWO_NAME 					=" Class Two";
string CLASS_TWO_TEXTURE_PATH 			= "crab_ship_complete.png";

//--- Class Three "Squid" Ship ---// 

const int 	CLASS_THREE_WIDTH 			= 8;
const int 	CLASS_THREE_HEIGHT 			= 8;

const int 	CLASS_THREE_POINTS			= 30;
const int 	CLASS_THREE_HP 				= 5;
const int 	CLASS_THREE_DAMAGE 			= 10;
const int 	CLASS_THREE_VELOCITY 		= 1;
const float CLASS_THREE_COOLDOWN 		= 1.0;
string CLASS_THREE_NAME 				= "Class Three";
string CLASS_THREE_TEXTURE_PATH 		= "squid_ship_complete.png";



//--- Parametrized Boards Values ---//
//--- Classic Board ---//
// Almost all these values are calculated by measuring the original 1978 game pixel by pixel.
// Some refers to game logic entities, some others to visual sprites like Score, Credits, etc.
//mp = mid-pivoted -> it appears that text elements are not bottom right alligned, but mid right.
const int 	CLASSIC_BOARD_HEIGHT 		= 256;
const int 	CLASSIC_BOARD_WIDTH 		= 224;
const int   CLASSIC_BOARD_SCORE_Y		= 12;
const int   CLASSIC_BOARD_SCORE_X		= 9;
const int 	CLASSIC_BOARD_HISCORE_X 	= 81;
const int   CLASSIC_BOARD_SCORE2_X		= 153;
const int 	CLASSIC_BOARD_SCORE_NUMBER_Y= 28;
const int   CLASSIC_BOARD_SCORE_NUMBER_X= 25;
const int 	CLASSIC_BOARD_HS_NUMBER_X 	= 89;
const int 	CLASSIC_UPPERHUD 			= 36;
const int 	CLASSIC_LOWERHUD 			= 240;
const int 	CLASSIC_LIFES_Y				= 241;
const int 	CLASSIC_LIFES_X				= 26;
const int   CLASSIC_CREDIT_X			= 137;
const int   CLASSIC_CREDIT_Y			= 241; //mp
const int 	CLASSIC_LIFES_NUMBER_X		= 9;
const int 	CLASSIC_ENEMY_Y_AREA_CENTER	= 96;
const int 	CLASSIC_SHIELD_Y 			= 208;
const int 	CLASSIC_SHIELD_X			= 30; //to be calculated
const int   CLASSIC_SHIELD_OFFSET		= 30; //to be calculated
const int 	CLASSIC_SHIP_Y_CENTER 		= 220;
const int 	CLASSIC_ENEMY_X_OFFSET 		= 15;
const int 	CLASSIC_ENEMY_Y_OFFSET 		= 20;
const int 	CLASSIC_ENEMY_HEIGHT 		= 8;
const int 	CLASSIC_X_CENTER 			= 112;
const int 	CLASSIC_ENEMY_LEFT_BORDER	= 15;
const int 	CLASSIC_ENEMY_RIGHT_BORDER 	= 209;
const int   CLASSIC_PLAYER_X_SPAWN      = 20;
const int  	CLASSIC_SPECIAL_SHIP_Y		= 44; //mp
const int 	CLASSIC_BULLET_LAND_OFFSET  = 5;

//--- parametrized ClassicSpaceBattle values ---//
const int 	CLASSIC_PUSH_DISTANCE 		= 3;
const int 	CLASSIC_DOWN_DISTANCE	 	= 4;
const int 	CLASSIC_PLAYER_LIFES		= 3;
const int 	CLASSIC_NUMBER_OF_SHIELDS	= 4;
//number of frames between movements of enemies; the lower, the faster they move
const int   CLASSIC_MOVEMENT_RATIO		= 2;

//--- parametrized game values ---///
const int GLOBAL_FPS 					= 60;
const int ENEMY_SHOTS_DELAY				= 40;


//--- parametrized Shield values ---//
/*
 * Classic Shield Types is an encoding of the various Shield Units that compose a Shield
 * Each integer represent the ShieldUnitType. Graphically, the first row of the vector represent
 * the bottom row of the shield. For more info, check docs.
 */

const vector<vector<int>> CLASSIC_SHIELD_TYPES 	= { {5,5,6,0,0,0,7,5,5},
													{5,5,5,5,5,5,5,5,5},
													{5,5,5,5,5,5,5,5,5},
													{1,2,5,5,5,5,5,4,3} };
const int SHIELD_ROWS					= 4;
const int SHIELD_COLUMNS				= 9;
string INTACT_SHIELD_PREFIX				= "shield/intact_shield_0.png";
string BROKEN_SHIELD_PREFIX				= "shield/broken_shield_";
const int BROKEN_CARDINALITY			= 8;		//The number of broken unitShieldTexture


const int UNIT_SHIELD_WIDTH				= 2;
const int UNIT_SHIELD_HEIGHT			= 4;

//---------  ENTITY  ---------//

Entity::Entity(int x, int y, int width, int height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

int Entity::getX()
{
	return x;
}

int Entity::getY()
{
	return y;
}

int Entity::getWidth()
{
	return width;
}

int Entity::getHeight()
{
	return height;
}

//-------- Living Entity --------//

LivingEntity::LivingEntity(int x,int y,int width, int height) : Entity(x,y,width,height)
{
	//Living Entity are drawable as default behaviour
	this->drawable = true;
}

void LivingEntity::setX(int newX)
{
	this->x = newX;
}

void LivingEntity::setY(int newY)
{
	this->y = newY;
}

bool LivingEntity::isDrawable()
{
	return this->drawable;
}

void LivingEntity::setDrawable(bool drawable)
{
	this->drawable = drawable;
}

//---- Shield Unit ----//
ShieldUnit::ShieldUnit(int x, int y, int width, int height, string intactPath,string brokenPath,bool halfShield) : LivingEntity(x,y,width,height)
{
	this->destroyed = false;
	this->intactPath = intactPath;
	this->brokenPath = brokenPath;
	this->halfShield = halfShield;
}

bool ShieldUnit::isDestroyed()
{
	return this->destroyed;
}

bool ShieldUnit::isHalfShield()
{
	return this->halfShield;
}

void ShieldUnit::destroy()
{
	this->destroyed = true;
	return;
}

string ShieldUnit::getIntactTexturePath()
{
	return this->intactPath;
}

string ShieldUnit::getBrokenTexturePath()
{
	return this->brokenPath;
}

//--------------------//
//------ Bullet ------//
//--------------------//
Bullet::Bullet(int x,int y,int width,int height,int damage, int velocity,int direction) : LivingEntity(x,y,width,height)
{
	this->damage = damage;
	this->velocity = velocity;
	this->direction = direction;
}

//Updates the traveling of the bullet
void Bullet::update()
{
	this->y = this->y + (this->direction*this->velocity);
	//printf("The bullet is at y = %d\n",this->y);
}

int Bullet::getDamage()
{
	return this->damage;
}

int Bullet::getBulletDirection()
{
	return this->direction;
}

//--------------------//
//------- Ship -------//
//--------------------//


Ship::Ship(int x,int y,int width, int height, int hp, int damage, int velocity, float cooldown,string texturePath,string bulletTexturePath) : LivingEntity(x,y,width,height)
{
	this->hp					= hp;
	this->damage				= damage;
	this->velocity				= velocity;
	this->cooldown				= cooldown;
	this->texturePath			= texturePath;
	this->bulletTexturePath		= bulletTexturePath;
}

int Ship::getHp()
{
	return this->hp;
}

float Ship::getCooldown()
{
	return this->cooldown;
}

bool Ship::inferDamage(int damage)
{
	this->hp = this->hp-damage;	
	return (this->hp <= 0);		 //If hp goes below zero, it returns true, that means the ship is destroyed.
}

int Ship::getAmmoDamage()
{
	return this->damage;
}

int Ship::getVelocity()
{
	return this->velocity;
}

void Ship::setVelocity(int velocity)
{
	this->velocity = velocity;
}

void Ship::printSummary()
{
	printf("Ship stats:\n    Coordinates x: %d\n    Coordinates y: %d\n",this->x,this->y);
	printf("    HP:%d\n    Damage:%d\n    Velocity:%d\n",this->hp,this->damage,this->velocity);

}

string Ship::getTexturePath()
{
	return this->texturePath;
}

string Ship::getBulletTexturePath()
{
	return this->bulletTexturePath;
}

//------  PlayerShip  ------//

PlayerShip::PlayerShip(int x,int y,int width, int height, int hp, int damage, int velocity, float cooldown,string* name,string texturePath) : Ship(x,y,width,height,hp,damage,velocity,cooldown, texturePath,PLAYER_BULLET_TEXTURE_PATH)
{
	this->playerName = name;
}

PlayerShip::~PlayerShip()
{
	delete this->playerName;
}

void PlayerShip::printSummary()
{
	Ship::printSummary();
	printf("Ship name is %s\n",this->playerName->c_str());
}

void PlayerShip::moveHorizontally(int direction)
{
	//if direction is +1, then we go right
	//if direction is -1, then we go left
	this->x = this->x + (direction*velocity);

}

//------- EnemyShip -------//

EnemyShip::EnemyShip(int x,int y,int width, int height,int points, int hp, int damage, int velocity, float cooldown,int pushDistance, int downDistance,string shipClass,string texturePath,string bulletTexturePath) : Ship(x,y,width,height,hp,damage,velocity,cooldown,texturePath,bulletTexturePath)
{
	this->pushDistance			= pushDistance;
	this ->downDistance			= downDistance;
	//the ships always start facing right direction
	direction					= 1;
	this->shipClass				= shipClass;
	this->points				= points;
	
}


int EnemyShip::getPoints()
{
	return this->points;
}

bool EnemyShip::isGoingRight()
{
	return (this->direction>0);
}


/* The push method represents the classic, space invaders move of a ship. 
it just get pushed to the direction where it is facing, with a pushDistance magnitude*/
void EnemyShip::push()
{
	//the ship moves by pushDistance*velocity (default is 1). The increment is positive (going right) if direction is positive.
	this->x = (this->x + (velocity*pushDistance)*direction);
}

void EnemyShip::down()
{

	//TO DO to go down,we must increment o decrement y??
	this->y = this->y + downDistance;
}

void EnemyShip::flip()
{
	this->direction = this->direction * -1;
}

int EnemyShip::getPushDistance()
{
	return this->pushDistance;
}

void EnemyShip::printSummary()
{
	Ship::printSummary();
	printf("Ship Class is %s\n",this->shipClass);
}

//----------------------------//
//------- ClassOneShip -------//
//----------------------------//

/* The Constructor simply calls the superclass abstract constructor with parametrized datas regarding that kind of ship class */
ClassOneShip::ClassOneShip(int x,int y,int scale_ratio,int pushDistance, int downDistance) : EnemyShip(x,y,CLASS_ONE_WIDTH*scale_ratio,CLASS_ONE_HEIGHT*scale_ratio,CLASS_ONE_POINTS,CLASS_ONE_HP,CLASS_ONE_DAMAGE,CLASS_ONE_VELOCITY,CLASS_ONE_COOLDOWN,pushDistance,downDistance,CLASS_ONE_NAME,CLASS_ONE_TEXTURE_PATH,BASIC_BULLET_TEXTURE_PATH) {}

void ClassOneShip::getClassName()
{
	EnemyShip::printSummary();
}

//----------------------------//
//------- ClassTwoShip -------//
//----------------------------//

ClassTwoShip::ClassTwoShip(int x,int y,int scale_ratio,int pushDistance, int downDistance) : EnemyShip(x,y,CLASS_TWO_WIDTH*scale_ratio,CLASS_TWO_HEIGHT*scale_ratio,CLASS_TWO_POINTS,CLASS_TWO_HP,CLASS_TWO_DAMAGE,CLASS_TWO_VELOCITY,CLASS_TWO_COOLDOWN,pushDistance,downDistance,CLASS_TWO_NAME,CLASS_TWO_TEXTURE_PATH,BASIC_BULLET_TEXTURE_PATH) {}

void ClassTwoShip::getClassName()
{
	EnemyShip::printSummary();
}

//----------------------------//
//------ ClassThreeShip ------//
//----------------------------//

ClassThreeShip::ClassThreeShip(int x,int y,int scale_ratio,int pushDistance, int downDistance) : EnemyShip(x,y,CLASS_THREE_WIDTH*scale_ratio,CLASS_THREE_HEIGHT*scale_ratio,CLASS_THREE_POINTS,CLASS_THREE_HP,CLASS_THREE_DAMAGE,CLASS_THREE_VELOCITY,CLASS_THREE_COOLDOWN,pushDistance,downDistance,CLASS_THREE_NAME,CLASS_THREE_TEXTURE_PATH,BASIC_BULLET_TEXTURE_PATH) {}

void ClassThreeShip::getClassName()
{
	EnemyShip::printSummary();
}

//----------------------------//
//------ 	 Shield 	------//
//----------------------------//


Shield::Shield(int startingX,int startingY, int scale_ratio)
{
	this->startingX				= startingX;
	this->startingY				= startingY;
	this->scale_ratio			= scale_ratio;
	this->rows					= SHIELD_ROWS;
	this->columns				= SHIELD_COLUMNS;
	this->unitShieldWidth		= UNIT_SHIELD_WIDTH;
	this->unitShieldHeight		= UNIT_SHIELD_HEIGHT;
	this->shieldWidth			=(this->unitShieldWidth*this->scale_ratio)*this->columns;
	this->shieldHeight			=(this->unitShieldHeight*this->scale_ratio)*this->rows;
	this->shieldParts.resize(this->rows,vector<std::shared_ptr<ShieldUnit>>(this->columns));
	this->init();
}

Entities::Shield::~Shield()
{
	for (int i = 0; i < this->rows; i++)
	{
		this->shieldParts[i].clear();
	}
}

void Shield::init()
{
	int x,y;

	//for each row of shield units
	for(int i = 0; i < this->rows; i++)
	{
		//for each column of shield unit
		for(int j = 0; j < this->columns; j++)
		{	
			//we increment the x and y to properly calculate the coordinates of each unit shield
			x = this->startingX	+ (j*(this->unitShieldWidth*this->scale_ratio));
			y = this->startingY - (i*(this->unitShieldHeight*this->scale_ratio));

			//we create the unit shield given its coordinates
			createShield(x,y,CLASSIC_SHIELD_TYPES[i][j],i,j); 
		}
	}

}




void Shield::createShield(int x, int y, int type, int row, int column)
{
	// the intact and broken texture path
	string intactTexturePath = INTACT_SHIELD_PREFIX;
	string brokenTexturePath = randomBrokenPath();

	//we use a variable that holds the type number as a char (we add 48 to have to correct ascii value)
	char typeInChar = type + 48;

	//to specify the correct path, we must substitute the 23th character of the string template
	intactTexturePath[21] = typeInChar;


	ShieldUnit* current = NULL;
	bool halfShield = true;

	
	if (type == 2 || type == 4 || type == 5) //these types are not halfshields
	{
		halfShield = false;
	}

	if (type != 0) //if type == 0, the shield unit must remain null
	{
		current = new ShieldUnit(x, y, UNIT_SHIELD_WIDTH * this->scale_ratio, UNIT_SHIELD_HEIGHT * this->scale_ratio, intactTexturePath, brokenTexturePath, halfShield);
	}
	
	//we create the shared_ptr
	std::shared_ptr<ShieldUnit> shieldUnitPointer(current);
	//we add the pointer at the current row and column
	this->shieldParts.at(row).at(column) = shieldUnitPointer;
}

string Shield::randomBrokenPath()
{
	//we pick a random number between [0,BROKEN_CARDINALITY) and we convert it into a string
	string suffix = std::to_string(std::rand() % BROKEN_CARDINALITY); 
	return BROKEN_SHIELD_PREFIX+suffix+".png";

}

int Shield::getShieldRows()
{
	return this->rows;
}

int Shield::getShieldColumns()
{
	return this->columns;
}

int Shield::getShieldWidth()
{
	return this->shieldWidth;
}

int Shield::getShieldHeight()
{
	return this->shieldHeight;
}

std::shared_ptr<ShieldUnit> Shield::getShieldUnitByIndex(int row, int column)
{
	return this->shieldParts[row][column];
}

//------- GameEntities ------//

//------ Board -------//

Board::Board(int width,int height, int scale_ratio)
{
	this -> width		= width*scale_ratio;
	this -> height		= height*scale_ratio;
	this -> scale_ratio = scale_ratio;
}

int Board::getBaseWidth()
{
	return this->width/this->scale_ratio;
}

int Board::getBaseHeight()
{
	return this->height/this->scale_ratio;
}

int Board::getWidth()
{
	return this->width;
}

int Board::getHeight()
{
	return this->height;
}

int Board::getScaleRatio()
{
	return this->scale_ratio;
}

void Board::printSummary()
{
	printf("\n This board is of sizes %d x %d with a scale ratio of %d\n",this->width,this->height,this->scale_ratio);
}

//------- ClassicBoard -------//

ClassicBoard::ClassicBoard(int scale_ratio) : Board(CLASSIC_BOARD_WIDTH,CLASSIC_BOARD_HEIGHT,scale_ratio)
{
	this->upperHud 			= CLASSIC_UPPERHUD*scale_ratio;
	this->lowerHud 			= CLASSIC_LOWERHUD*scale_ratio;
	this->enemyYAreaCenter 	= CLASSIC_ENEMY_Y_AREA_CENTER*scale_ratio;
	this->shieldY 			= CLASSIC_SHIELD_Y*scale_ratio;
	this->shieldX    		= CLASSIC_SHIELD_X*scale_ratio;
	this->shieldOffset		= CLASSIC_SHIELD_OFFSET*scale_ratio;
	this->shipYCenter 		= CLASSIC_SHIP_Y_CENTER*scale_ratio;
	this->enemyXOffset 		= CLASSIC_ENEMY_X_OFFSET*scale_ratio;
	this->enemyYOffset 		= CLASSIC_ENEMY_Y_OFFSET*scale_ratio;
	this->enemyHeight 		= CLASSIC_ENEMY_HEIGHT*scale_ratio;
	this->xCenter 			= CLASSIC_X_CENTER*scale_ratio;
	this->enemyLeftBorder   = CLASSIC_ENEMY_LEFT_BORDER*scale_ratio;
	this->enemyRightBorder 	= CLASSIC_ENEMY_RIGHT_BORDER*scale_ratio;
	this->scoreY 			= CLASSIC_BOARD_SCORE_Y*scale_ratio;
	this->scoreX            = CLASSIC_BOARD_SCORE_X*scale_ratio;
	this->highScoreX		= CLASSIC_BOARD_HISCORE_X*scale_ratio;
	this->score2X 			= CLASSIC_BOARD_SCORE2_X*scale_ratio;
	this->scoreNumberY 		= CLASSIC_BOARD_SCORE_NUMBER_Y*scale_ratio;
	this->scoreNumberX 		= CLASSIC_BOARD_SCORE_NUMBER_X*scale_ratio;
	this->hiScoreNumberX	= CLASSIC_BOARD_HS_NUMBER_X*scale_ratio;
	this->lifesY            = CLASSIC_LIFES_Y*scale_ratio;
	this->lifesX       		= CLASSIC_LIFES_X*scale_ratio;
	this->creditX           = CLASSIC_CREDIT_X*scale_ratio;
	this->creditY           = CLASSIC_CREDIT_Y*scale_ratio;
	this->lifesNumberX      = CLASSIC_LIFES_NUMBER_X*scale_ratio;
	this->playerXSpawn      = CLASSIC_PLAYER_X_SPAWN*scale_ratio;
	this->specialShipY      = CLASSIC_SPECIAL_SHIP_Y*scale_ratio;
	this->bulletLandOffset  = CLASSIC_BULLET_LAND_OFFSET*scale_ratio;

}


//------ Space Battles ------//

void SpaceBattle::movePlayer(int direction,bool vertical)
{

	if(!vertical) //if it's a horizontal move, we call the moveHorizontal method
	{
		this->playerShip->moveHorizontally(direction);
	}
	else
	{
		//vertical movement to be implementd
	}
}

int SpaceBattle::getBulletsSize()
{
	return (int)this->bullets.size();
}


bool SpaceBattle::checkCollision(LivingEntity* one, LivingEntity* two)
{
	/*We have four condition that determines if this two rectangles DON'T Overlap.
	 * x1 indicates the leftmost x, while x2 indicates the rightmost x.
	 * y1 is the top coordinate, y2 is the bottom coordinate.
	 * A) one.x1 < two.x2
	 * B) one.x2 > two.x1
	 * C) one.y1 > two.y2
	 * D) one.y2 < two.y1
	 * The OR of this four coordinates garantees a non overlap.
	 * We return true if they do overlap
	 */
	bool a = (one->getX() < (two->getX() + two->getWidth()));
	bool b = ((one->getX() + one->getWidth()) > two->getX());
	bool c = (one->getY() < (two->getY() + two->getHeight()));
	bool d = ((one->getY() + one->getHeight()) > two->getY());

	return  (a && b && c && d);
}

std::shared_ptr<LivingEntity> SpaceBattle::getLastBullet()
{
	return this->bullets.back();
}

bool SpaceBattle::createPlayerBullet()
{

	//we check if the cooldown of the gun is respected. If its not, we don't create the bullet
	if(!(this->currentTicks >= (this->lastShotTicks+(this->playerShip->getCooldown()*GLOBAL_FPS))))
	{
		return false;
	}

	//bullet_x = playerShip.x + playerShip.width/2 - bullet.width/2
	int bullet_x = (this->playerShip->getX()+(this->playerShip->getWidth()/2)-((BASIC_PLAYER_BULLET_WIDTH*this->scale_ratio)/2));
	
	//we create the bullet and then we put it in the bullets vector.
	std::shared_ptr<Bullet> p1(new Bullet(bullet_x,this->playerShip->getY() - PLAYER_SHIP_BULLET_OFFSET*this->scale_ratio,BASIC_PLAYER_BULLET_WIDTH*this->scale_ratio, BASIC_PLAYER_BULLET_HEIGHT*this->scale_ratio,BASIC_PLAYER_SHIP_DAMAGE,PLAYER_BULLET_VELOCITY*this->scale_ratio,-1));
	this->bullets.push_back(p1);

	//we update the last shot tick
	this->lastShotTicks = this->currentTicks;
	return true;
	
}


//------ Classic Space Battle -----//
ClassicSpaceBattle::ClassicSpaceBattle(vector<EnemyShipClasses> classes,int scale_ratio, int rowsOfEnemies, int shields, int enemiesPerRow)
{

	assert(classes.size()==(rowsOfEnemies));
	this->gameBoard 			= new ClassicBoard(scale_ratio);
	this->rowsOfEnemies 		= rowsOfEnemies;
	this->numberOfShields 		= shields;
	this->enemiesPerRow 		= enemiesPerRow;
	this->enemiesRemaining      = enemiesPerRow*rowsOfEnemies;
	this->classPerRow 			= classes;
	this->enemies 				= vector<vector<std::shared_ptr<EnemyShip>>>(enemiesPerRow);
	this->currentPhase 			= PUSH;
	this->scale_ratio 			= scale_ratio;
	this->bullets 				= vector<std::shared_ptr<Bullet>>(0);
	this->shields 				= vector<std::shared_ptr<Shield>>(0);
	this->lastShotTicks			= 0;
	this->currentTicks 			= GLOBAL_FPS;
	this->lastEnemyShotTicks    = GLOBAL_FPS*3;		//two seconds of delay before the enemy starts to shoot
	this->enemyShotsDelay		= ENEMY_SHOTS_DELAY;
	this->gamePhase				= INIT;
	this->playerLifes    		= CLASSIC_PLAYER_LIFES;
	this->enemyLanded 			= false;
	this->playerShipDestroyed   = false;
	this->score 				= 0;
	init();
}

/* Init methods sets up the game having the board already selected 
*/
void ClassicSpaceBattle::init()
{
	//random seed for enemy bullet spawn
	std::srand((unsigned int)std::time(nullptr));


	//we create the enemies
	createEnemies();
	//we take the pointer of the first ship to move (bottom left ship) and we save it
	this->firstShip = enemyQueue.front();
	
	//we create the player
	//what if we pass a player in input when creating the battle?
	createPlayer();

	//we create the shields
	createShields();

	//we set gamePhase to "PLAYING"
	this->gamePhase	= PLAYING;
}

bool ClassicSpaceBattle::checkIfEnemyLanded(EnemyShip* ship)
{
	bool result = false;
	int i = 0;
	while((i < this->numberOfShields) && !result)
	{
		result = checkEnemyCollisionWithSingleShield(ship,i++);
	}
	return result;
}

void ClassicSpaceBattle::findEnemyInQueue(EnemyShip* ship)
{

	std::shared_ptr<EnemyShip>  actual_first_ship = this->enemyQueue.front();
	std::shared_ptr<EnemyShip>	current_ship;
	bool found = false;
	if(actual_first_ship.get() == ship)//if the ship we are deleting is also the first in the movement
	{	
		this->enemyQueue.front()->setDrawable(false);
		return;
	}
	while(!found) //otherwise we check in all the queue
	{	
		current_ship = this->enemyQueue.front();
		this->enemyQueue.pop();
		if(current_ship.get() == ship) //if the current ship is the one we are deleting
		{
			found = true; //we found it
			
		}
		
		this->enemyQueue.push(current_ship); //otherwise we put it back in the queue
	
	}
	while(this->enemyQueue.front() != actual_first_ship) //after we found it, we must restore the queue to the starting situation
	{
		current_ship = this->enemyQueue.front();
		this->enemyQueue.pop();
		this->enemyQueue.push(current_ship);
	}
	return;

	//we must find the ship in the queue, but then also restore the queue to his previous state
	//so we must iterate through the whole queue
}

void ClassicSpaceBattle::createEnemies()
{	
	int startY;
	int startX		 = this->gameBoard->getXCenter();
	int enemyYOffset = this->gameBoard->getEnemyYOffset();
	int enemyXOffset = this->gameBoard->getEnemyXOffset();
	startX = startX - enemyXOffset/2;

	
	//startY differs upon the number of rows of enemies
	//If we have an odd number of rows
	if(this->rowsOfEnemies%2 == 1)
	{
		// startY = enemyYAreaCenter +((rows-1)/2)*enemyOffset
		
		startY = this->gameBoard->getEnemyYAreaCenter() + ((this->rowsOfEnemies-1)/2)*enemyYOffset;
	}
	else //if we have a pair number of rows
	{
		// startY = enemyYAreaCenter + 1/2(enemyOffset) + ((rows-2)/2)*enemyOffset
		
		startY = this->gameBoard->getEnemyYAreaCenter() + (enemyYOffset)*1/2 + ((this->rowsOfEnemies-2)*enemyYOffset);
	}
	//Also startX differs upon number of Enemies per Rows(instead of rows)
	//if we have a odd number of enemies
	if(this->enemiesPerRow%2 == 1)
	{
		startX = startX - ((enemiesPerRow-1)/2)*enemyXOffset;
	}
	else //if we have a pair number of enemies
	{
		startX = startX - 1/2*(enemyXOffset) - ((enemiesPerRow - 2)/2)*enemyXOffset;
	}


	int x = startX;
	int y = startY;
	EnemyShipClasses currentClass;
	for(int i=0; i < this->rowsOfEnemies; i++)
	{
		currentClass = this->classPerRow.at(i);
		x = startX;
		for(int j=0; j< this->enemiesPerRow; j++)
		{	

			EnemyShip* nextShip;
			if(currentClass == CLASS_ONE)
			{
				nextShip = new ClassOneShip(x,y,this->gameBoard->getScaleRatio(),CLASSIC_PUSH_DISTANCE*this->gameBoard->getScaleRatio(),CLASSIC_DOWN_DISTANCE*this->gameBoard->getScaleRatio());
			}
			else if(currentClass == CLASS_TWO)
			{
				nextShip = new ClassTwoShip(x,y,this->gameBoard->getScaleRatio(),CLASSIC_PUSH_DISTANCE*this->gameBoard->getScaleRatio(),CLASSIC_DOWN_DISTANCE*this->gameBoard->getScaleRatio());
			}
			else if(currentClass == CLASS_THREE)
			{
				nextShip = new ClassThreeShip(x,y,this->gameBoard->getScaleRatio(),CLASSIC_PUSH_DISTANCE*this->gameBoard->getScaleRatio(),CLASSIC_DOWN_DISTANCE*this->gameBoard->getScaleRatio());
			}
			else
			{
				printf("COULD NOT FIND CLASS_SHIP!");
				return;
			}
			std::shared_ptr<EnemyShip> nextShipPointer(nextShip);
			this->enemies[i].push_back(nextShipPointer);
			this->enemyQueue.push(this->enemies[i].at(j));
			x+=enemyXOffset;
		}

		y-=enemyYOffset;
	}
}

void ClassicSpaceBattle::createPlayer()
{
	std::shared_ptr<PlayerShip> player(new PlayerShip(this->gameBoard->getPlayerXSpawn(),this->gameBoard->getShipYCenter(),BASIC_PLAYER_SHIP_WIDTH*this->gameBoard->getScaleRatio(),BASIC_PLAYER_SHIP_HEIGHT*this->gameBoard->getScaleRatio(),BASIC_PLAYER_SHIP_HP,BASIC_PLAYER_SHIP_DAMAGE,BASIC_PLAYER_SHIP_VELOCITY*this->scale_ratio,BASIC_PLAYER_SHIP_COOLDOWN,new string("Player One"),BASIC_PLAYER_TEXTURE_PATH));
	this->playerShip = player;
}

void ClassicSpaceBattle::createShields()
{
	
	if(this->numberOfShields<=0)
	{
		return;
	}
	
	int startingX = this->gameBoard->getShieldX();
	int startingY = this->gameBoard->getShieldY();
	int offset 	  = this->gameBoard->getShieldOffset();
	int x 		  = startingX;
	int y 		  = startingY;
	Shield* currShield = new Shield(x,y,this->scale_ratio);
	std::shared_ptr<Shield> currShieldPointer(currShield);	
	int shieldWidth = currShield->getShieldWidth();
	this->shields.push_back(currShieldPointer);

	for(int i=1;i<this->numberOfShields;i++)
	{
		x = startingX + ((shieldWidth+offset)*i);
		currShield = new Shield(x,y,this->scale_ratio);
		std::shared_ptr<Shield> currShieldPointer(currShield);
		this->shields.push_back(currShieldPointer);
	}


}

void ClassicSpaceBattle::initBasic()
{

}

/* Update contains all the logic of the game itself, like moving bullets, moving enemyships, etc.
 */
void ClassicSpaceBattle::update()
{
	//if the game is on play phase
	if(this->gamePhase == PLAYING)
	{
		//if the playerShip has just been destroyed
		if(this->playerShipDestroyed)
		{
			//we set the ship X coordinates to its starting ones. Lifes have been already decreased in another part of code
			this->playerShip->setX(this->gameBoard->getPlayerXSpawn());
			this->playerShipDestroyed = false;
		}

		//we increment the ticks
		this->currentTicks++;
		
		//every CLASSIC_MOVEMENT_RATIO frames, we call the enemies movement method
		if(this->currentTicks%CLASSIC_MOVEMENT_RATIO == 0)
		{
			moveEnemiesClassic();
		}
		
		// we move the bullets
		moveBullets();

		//every "enemyShotsDelay" frame, we create a new bullet from the enemy
		if(this->currentTicks >= (this->lastEnemyShotTicks+this->enemyShotsDelay))
		{
			spawnEnemyBullet();
		}
	}
	else if(this->gamePhase == PAUSED)
	{
		return;
	}
	else if(this->gamePhase == WIN)
	{
		return;
	}
	else if(this->gamePhase == LOSS)
	{
		return;
	}
	
}

/* moveEnemiesClassic aims to reproduce the classic behaviour of enemy ships in the game 
 * Each frame, one ship (starting from bottom row, most left one) is pushed to the new  
 * position. What does it mean? that the less ships there are, the faster they go. This  
 * was a bug in the original game but the designer found it entertaining so it was kept  
 */	
void ClassicSpaceBattle::moveEnemiesClassic()
{


	/* are we in push or down phase? 
	 * push phase occurs in normal condition
	 * down phase occurs when one element has reached the left or right border
	 * so we should push element. when one element reach the current border, then the
	 * next cycle they all go down
	 */
	bool found = false;
	std::shared_ptr<EnemyShip>  currentShip;
	while(!found)
	{

		currentShip = this->enemyQueue.front();

		//if im in the DOWN phase and I meet again the first element, I must go in PUSH phase
		if(this->currentPhase == DOWN && currentShip == this->firstShip)
		{
			this->currentPhase = PUSH;
		}
		//if im in the ending push phase and I reached the first element, i must enter the Down phase
		else if(this->currentPhase == ENDING_PUSH && currentShip == this->firstShip )
		{
			this->currentPhase = DOWN;
		}
		//if the current ship is not null and is not destroyed (isDrawable deliver the same information)
		if(currentShip != NULL && currentShip->isDrawable())
		{
			found = true;
		}

		//we must take the element off the queue and back to it again
		this->enemyQueue.pop();
		this->enemyQueue.push(currentShip);
	}
	if(this->currentPhase == PUSH)
	{
		//if im in push phase
		currentShip->push();
		
		//if after the push, the ship is touching the border, then we must enter the ENDING_PUSH phase
		if(checkBoundaryCollision(currentShip.get()))
		{
			this->currentPhase = ENDING_PUSH;
		}
	}
	//if I'm in ending push phase, I just need to push the currentShip
	else if(this->currentPhase == ENDING_PUSH)
	{
		currentShip->push();
		
	}
	//if I'm in the DOWN phase, I must push the ship down and flip its direction
	else if(this->currentPhase == DOWN)
	{
		currentShip->down();
		currentShip->flip();
		//if after going down I'm touching the shields, then its gameover.
		if(checkIfEnemyLanded(currentShip.get()))
		{
			this->enemyLanded = true;
		}

	}
	return;
}

void ClassicSpaceBattle::moveEnemies()
{
	//anoter move method is still not implemented
}

/* This method spawns an enemy bullet from a random "first line" enemy
*/
void ClassicSpaceBattle::spawnEnemyBullet()
{
	
	int random_column = (std::rand() % (this->enemiesPerRow));	//we take a random column
	int line = 0;												//starting from line 0
	bool found = false;
	int starting_column = random_column;
	//we have to find an enemy that is not null, starting from that column and going right to left
	while(!found)
	{
		if(this->enemies.at(line).at(random_column)!=nullptr)	//if the enemy in coordinates [line][column] still exists, then we found who's gonna shoot next
		{
			found = true;
		}
		else
		{
			if(line != this->rowsOfEnemies-1)					//otherwise we change line to see if an enemy is present
			{
				line++;
			}
			else                                                //if all lines in that column have been explored, we change column.
			{
				random_column = (random_column + 1)%(this->enemiesPerRow);
				if(random_column == starting_column)
				{
					printf("Cant find an enemy to shoot! fatal error\n");
					return;
				}
				line = 0;
			}
		}
	}

		
	makeEnemyShoot(getEnemyByRowAndColumn(line,random_column));	//at this point, line and random_column stores the coordinates of a valid enemy






}
/* Simple supportive method to complete "spawnEnemyBullet()" to help readability of code
*/
void ClassicSpaceBattle::makeEnemyShoot(EnemyShip* ship)
{
	//we calculate the x coordinates of the bullet 
	int bullet_x = (ship->getX()+(ship->getWidth()/2)-((BASIC_PLAYER_BULLET_WIDTH*this->scale_ratio)/2));	

	//we create the bullet and save it in a shared_ptr 
	std::shared_ptr<Bullet> p1(new Bullet(bullet_x,ship->getY()+ship->getHeight(),BASIC_ENEMY_BULLET_WIDTH*this->scale_ratio, BASIC_ENEMY_BULLET_HEIGHT*this->scale_ratio,ship->getAmmoDamage(),BASIC_ENEMY_BULLET_VELOCITY*this->scale_ratio,1));

	//we add the pointer to the vectors of bullets
	this->bullets.push_back(p1);
	
	//we update the tick of the last time the enemy shoot to deal with cooldowns.
	this->lastEnemyShotTicks = this->currentTicks;
	return;

}

/*	This method checks collisions of a bullet with all kind of entities, including other bullets, boundaries and enemies/space ship.
*/
void ClassicSpaceBattle::checkBulletsCollision()
{

	bool explored = false;
	int left_index = 0;
	//index used to check collision between bullets
	int left_ausiliar_index = left_index;
	int right_index = (int)this->bullets.size() - 1;

	while(left_index <= right_index)
	{
		if(this->bullets.size()>1 && right_index>=(left_index+1) && !explored && this->bullets.at(left_index+1)!= nullptr)//check collision with other bullets(special case)
		{	
			//this condition is very easy to be met, so if for the current index is already checked,
			//we don't want to check it anymore
			explored = true;
			left_ausiliar_index = left_index+1;
			while(left_ausiliar_index <= right_index)
			{
				// if the bullets are going in opposite directions
				if(this->bullets.at(left_index)->getBulletDirection() != this->bullets.at(left_ausiliar_index)->getBulletDirection())
				{
					//if they collide
					if(checkCollision(this->bullets.at(left_index).get(),this->bullets.at(left_ausiliar_index).get()))
					{
						//if two bullets collides
						this->bullets.at(left_index)->setDrawable(false);
						this->bullets.at(left_ausiliar_index)->setDrawable(false);
						if(left_ausiliar_index==right_index)
						{
							this->bullets.at(left_ausiliar_index) = nullptr;
						}
						else
						{
							this->bullets.at(left_ausiliar_index) = this->bullets.at(right_index);
							this->bullets.at(right_index) = nullptr;
							
						}
							
						right_index -= 1;

						if(left_index == right_index)
						{
							this->bullets.at(left_index) = nullptr;
						}
						else
						{
							this->bullets.at(left_index) = this->bullets.at(right_index);
							this->bullets.at(right_index) = nullptr;
						}
						
						right_index -= 1;
						break;
					}
				}
				//printf("test %d\n",this->bullets.size());
				left_ausiliar_index += 1;
				
			}
		}
		//check collision with the border of the board
		else if((this->bullets.at(left_index)->getY() <= this->gameBoard->getUpperHud()+this->gameBoard->getBulletLandOffset()) && this->bullets.at(left_index)->getY() >= this->gameBoard->getUpperHud() || (this->bullets.at(left_index)->getY() >= (this->gameBoard->getLowerHud()-this->gameBoard->getBulletLandOffset())) && (this->bullets.at(left_index)->getY() <= this->gameBoard->getLowerHud()))
		{
			
			if(!(left_index == right_index))
			{
				
				//if we are not moving the rightmost element
				this->bullets.at(left_index)->setDrawable(false);
				this->bullets.at(left_index) = this->bullets.at(right_index);
				this->bullets.at(right_index) = nullptr;
				
				
				
			}
			else //if left index == right index
			{
				// delete this->bullets.at(left_index);
				this->bullets.at(left_index)->setDrawable(false);
				this->bullets.at(left_index) = nullptr;
				
			}
			right_index -= 1;

		} 
		//check if the bullets hit with a ship or entity
		else if(checkBulletCollisionWithEnemy(this->bullets.at(left_index).get()))
		{
				
			this->enemiesRemaining -= 1; //we decrease the counter of enemies
			if(!(left_index == right_index))
			{

				
				this->bullets.at(left_index)->setDrawable(false);
				this->bullets.at(left_index) = this->bullets.at(right_index);
				this->bullets.at(right_index) = nullptr;
			}
			else
			{
				this->bullets.at(left_index)->setDrawable(false);
				this->bullets.at(left_index) = nullptr;
			}
			right_index -= 1;
		}
		//check if the bullets hit the playership
		else if(checkBulletCollisionWithPlayer(this->bullets.at(left_index).get()))
		{
			if(!(left_index == right_index))
			{

				
				this->bullets.at(left_index)->setDrawable(false);
				this->bullets.at(left_index) = this->bullets.at(right_index);
				this->bullets.at(right_index) = nullptr;
			}
			else
			{
				this->bullets.at(left_index)->setDrawable(false);
				this->bullets.at(left_index) = nullptr;
			}
			right_index -= 1;
		}
		else if(checkBulletCollisionWithShields(this->bullets.at(left_index).get()))
		{
			if(!(left_index == right_index))
			{

				
				this->bullets.at(left_index)->setDrawable(false);
				this->bullets.at(left_index) = this->bullets.at(right_index);
				this->bullets.at(right_index) = nullptr;
			}
			else
			{
				this->bullets.at(left_index)->setDrawable(false);
				this->bullets.at(left_index) = nullptr;
			}
			right_index -= 1;
		}
		else
		{
			left_index += 1;
			explored = false;
		}

 
	}

	
	if(right_index == -1)
	{
		this->bullets.resize(0);
	
	}
	else if(right_index < (this->bullets.size()-1)) //if at least one element was deleted
	{
		this->bullets.resize(left_index);
	}
	
}

bool ClassicSpaceBattle::checkBulletCollisionWithEnemy(Bullet* bullet)
{

	for(int i=0; i < this->rowsOfEnemies; i++)
	{
		for(int j=0; j< this->enemiesPerRow; j++)
		{
			if(this->enemies.at(i).at(j) != nullptr && checkCollision(bullet,this->enemies.at(i).at(j).get()))
			{

				//if the bullets damage the enemies enough, we destroy it
				if(this->enemies.at(i).at(j)->inferDamage(bullet->getDamage()))
				{

					this->score += this->enemies.at(i).at(j)->getPoints();
					findEnemyInQueue(this->enemies.at(i).at(j).get());
					this->enemies.at(i).at(j)->setDrawable(false);
					this->enemies.at(i).at(j) = nullptr;
					//we must take out the element from the queue too
				}
				return true;

			}
		}
		
	}
	return false;
}

bool ClassicSpaceBattle::checkBulletCollisionWithPlayer(Bullet* bullet)
{


	if(checkCollision(bullet,this->playerShip.get()))
	{

		//if the bullets damage the enemies enough, we destroy it
		if(this->playerShip->inferDamage(bullet->getDamage()))
		{

			this->playerLifes--;
			this->playerShipDestroyed = true;

		}
		return true;

		
	}
	return false;
}

bool ClassicSpaceBattle::checkBulletCollisionWithShields(Bullet* bullet)
{
	bool result = false;
	int i = 0;
	while((i < this->numberOfShields) && !result)
	{
		result = checkBulletCollisionWithSingleShield(bullet,i++);
	}
	return result;
}

bool ClassicSpaceBattle::checkBulletCollisionWithSingleShield(Bullet* bullet,int index)
{
	bool result = false;
	for(int i = 0; i < this->shields[index]->getShieldRows(); i++)
	{
		for(int j = 0; j < this->shields[index]->getShieldColumns(); j++)
		{
			if(i == 0 && ( j == 3 || j == 4 || j==5)) //0,3;0,4;0,5 are not part of the shield
			{
				continue;
			}
			ShieldUnit* currUnit = this->shields[index]->getShieldUnitByIndex(i,j).get();
			if(!currUnit->isDestroyed())
			{
				result = checkCollision(bullet,currUnit);
			}
			if(result)
			{
				currUnit->destroy();
				return result;
			}
		}
	}
	return result;
}

bool ClassicSpaceBattle::checkEnemyCollisionWithSingleShield(EnemyShip* ship,int index)
{
	bool result = false;
	for(int i = 0; i < this->shields[index]->getShieldRows(); i++)
	{
		for(int j = 0; j < this->shields[index]->getShieldColumns(); j++)
		{
			if(i == 0 && ( j == 3 || j == 4 || j==5)) //0,3;0,4;0,5 are not part of the shield
			{
				continue;
			}
			ShieldUnit* currUnit = this->shields[index]->getShieldUnitByIndex(i,j).get();
			result = checkCollision(ship,currUnit);
		}
	}

	return result;
}

void ClassicSpaceBattle::moveBullets()
{
	for(int i = 0; i < this->bullets.size(); i++)
	{
		bullets.at(i)->update();
	}

	//check for bullets out of screen boundaries
	if(this->bullets.size()>0)
	{
		checkBulletsCollision();	
	}
	
	//printf("bullet size is %d\n",this->bullets.size());
}

void ClassicSpaceBattle::checkWinConditions()
{	
	if(this->playerLifes == 0 || this->enemyLanded)
	{
		this->gamePhase = LOSS;
	}
	else if(enemiesDestroyed())
	{
		this->gamePhase = WIN;
	}
}

void ClassicSpaceBattle::printSummary()
{
	printf("to be implemented");
}

PlayerShip* ClassicSpaceBattle::getPlayerShip()
{
	return this->playerShip.get();
}

std::shared_ptr<PlayerShip> ClassicSpaceBattle::getPlayerShipSharedPointer()
{
	return this->playerShip;
}

ClassicBoard* ClassicSpaceBattle::getGameBoard()
{
	return this->gameBoard;
}

std::shared_ptr<EnemyShip> ClassicSpaceBattle::getEnemyPointerByRowAndColumn(int row,int column)
{
	return this->enemies.at(row).at(column);
}

EnemyShip* ClassicSpaceBattle::getEnemyByRowAndColumn(int row, int column)
{
	//We do not check if index are in bound since this method is only called by someone who knows the dimensions
	//or should we?
	return this->enemies.at(row).at(column).get();

}

int ClassicSpaceBattle::getRowsOfEnemies()
{
	return this->rowsOfEnemies;
}

int ClassicSpaceBattle::getEnemiesPerRow()
{
	return this->enemiesPerRow;
}

int ClassicSpaceBattle::getNumberOfShields()
{
	return this->numberOfShields;
}

std::shared_ptr<Shield> ClassicSpaceBattle::getShield(int index)
{
	if(index < this->shields.size())
	{
		return this->shields[index];
	}
	return NULL;
}

void ClassicSpaceBattle::movePlayer(int direction,bool vertical)
{
	//Since Vertical Movement is out of our scope now, we dont check for vertical boundaries
	
	//before we call the superclass method, we must check if we go out of boundaries
	int predictedLeftBorder  = this->playerShip->getX() + this->playerShip->getVelocity()*direction;
	int predictedRightBorder = predictedLeftBorder +  this->playerShip->getWidth();//*this->playerShip->getVelocity()*direction;

	if(predictedRightBorder <= this->gameBoard->getWidth() && predictedLeftBorder>=0)
	{
		SpaceBattle::movePlayer(direction,vertical);
	}
}



bool ClassicSpaceBattle::checkBoundaryCollision(EnemyShip* current)
{
	if(current->isGoingRight())
	{
		
		if((current->getX() + current->getWidth())  > this->gameBoard->getEnemyRightBorder())
		{
			return true;
		}
	}
	else
	{
		if((current->getX() ) < this->gameBoard->getEnemyLeftBorder())
		{
			return true;
		}
	}

	return false;
}

bool ClassicSpaceBattle::enemiesDestroyed()
{
	for(int i=0; i < this->rowsOfEnemies; i++)
	{
		for(int j=0; j< this->enemiesPerRow; j++)
		{
			if(this->enemies.at(i).at(j) != nullptr)
			{
				return false;
			}
		}
	}
	return true;
}

/* This methods is used by the view to get the basic enemy bullet path. Since it changes randomly, it cannot be stored
   inside the enemy ship. It is not so much elegant since it just takes the parametrized global variable.
*/
string ClassicSpaceBattle::getEnemyBasicBulletPath()
{
	return BASIC_BULLET_TEXTURE_PATH;
}

ClassicGamePhases ClassicSpaceBattle::getGamePhase()
{
	return this->gamePhase;
}

int ClassicSpaceBattle::getPlayerLifes()
{
	return this->playerLifes;
}

int ClassicSpaceBattle::getScore()
{
	return this->score;
}

int ClassicSpaceBattle::getEnemiesRemaining()
{
	return this->enemiesRemaining;
}

void ClassicSpaceBattle::pauseGame()
{
	this->gamePhase = PAUSED;
}

void ClassicSpaceBattle::unPauseGame()
{
	this->gamePhase = PLAYING;
}

bool GameEntities::ClassicSpaceBattle::isGamePaused()
{
	return this->gamePhase == PAUSED;
}

//-----------------------------//
//-------- UTILITIES ----------//
//-----------------------------//

//--- SDLTimer ---//

SDLTimer::SDLTimer()
{
	startTicks = 0;
	pausedTicks = 0;

	paused = false;
	started = false;
}

void SDLTimer::start()
{
	//Start the timer
	started = true;

	//unpause the timer
	paused = false;

	startTicks = SDL_GetTicks();
	pausedTicks = 0;
}

void SDLTimer::stop()
{
    //Stop the timer
    started = false;

    //Unpause the timer
    paused = false;

    //Clear tick variables
    startTicks = 0;
    pausedTicks = 0;
}

void SDLTimer::pause()
{
    //If the timer is running and isn't already paused
    if( started && !paused )
    {
        //Pause the timer
        paused = true;

        //Calculate the paused ticks
        pausedTicks = SDL_GetTicks() - startTicks;
        startTicks = 0;
    }
}
void SDLTimer::unpause()
{
    //If the timer is running and paused
    if( started && paused )
    {
        //Unpause the timer
        paused = false;

        //Reset the starting ticks
        startTicks = SDL_GetTicks() - pausedTicks;

        //Reset the paused ticks
        pausedTicks = 0;
    }

}

Uint32 SDLTimer::getTicks()
{
    //The actual timer time
    Uint32 time = 0;

    //If the timer is running
    if( started )
    {
        //If the timer is paused
        if( paused )
        {
            //Return the number of ticks when the timer was paused
            time = pausedTicks;
        }
        else
        {
            //Return the current time minus the start time
            time = SDL_GetTicks() - startTicks;
        }
    }

    return time;
}

bool SDLTimer::isStarted()
{
    //Timer is running and paused or unpaused
    return started;
}

bool SDLTimer::isPaused()
{
    //Timer is running and paused
    return paused && started;
}