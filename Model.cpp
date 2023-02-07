
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
//--- parametrized playerShip values ---//

const int 	BASIC_PLAYER_SHIP_WIDTH 	= 13;
const int 	BASIC_PLAYER_SHIP_HEIGHT 	= 8;
const int 	BASIC_PLAYER_SHIP_HP		= 10;
const int 	BASIC_PLAYER_SHIP_DAMAGE    = 5;
const int 	BASIC_PLAYER_SHIP_VELOCITY	= 1;
const float BASIC_PLAYER_SHIP_COOLDOWN  = 0.7;
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
const float 	BASIC_ENEMY_BULLET_VELOCITY	= 1.5;
//--- Class One "Octopus" Ship ---// 

const int 	CLASS_ONE_WIDTH 			= 12;
const int 	CLASS_ONE_HEIGHT 			= 8;

const int 	CLASS_ONE_POINTS			= 10;
const int 	CLASS_ONE_HP 				= 5;
const int 	CLASS_ONE_DAMAGE 			= 10;
const int 	CLASS_ONE_VELOCITY 			= 1;
const float CLASS_ONE_COOLDOWN 			= 1.0;
const string* CLASS_ONE_NAME 			= new string("Class One");
string CLASS_ONE_TEXTURE_PATH 			= "octopus_ship_complete.png";

//--- Class Two "Crab" Ship ---// 

const int 	CLASS_TWO_WIDTH 			= 11;
const int 	CLASS_TWO_HEIGHT 			= 8;

const int 	CLASS_TWO_POINTS			= 20;
const int 	CLASS_TWO_HP 				= 5;
const int 	CLASS_TWO_DAMAGE 			= 10;
const int 	CLASS_TWO_VELOCITY 			= 1;
const float CLASS_TWO_COOLDOWN 			= 1.0;
const string* CLASS_TWO_NAME 			= new string("Class Two");
string CLASS_TWO_TEXTURE_PATH 			= "crab_ship_complete.png";

//--- Class Three "Squid" Ship ---// 

const int 	CLASS_THREE_WIDTH 			= 8;
const int 	CLASS_THREE_HEIGHT 			= 8;

const int 	CLASS_THREE_POINTS			= 30;
const int 	CLASS_THREE_HP 				= 5;
const int 	CLASS_THREE_DAMAGE 			= 10;
const int 	CLASS_THREE_VELOCITY 		= 1;
const float CLASS_THREE_COOLDOWN 		= 1.0;
const string* CLASS_THREE_NAME 			= new string("Class Three");
string CLASS_THREE_TEXTURE_PATH 		= "squid_ship_complete.png";



//--- Parametrized Boards Values ---//
//--- Classic Board ---//
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

//first row is bottom row in a graphical visualization
const vector<vector<int>> CLASSIC_SHIELD_TYPES 	= { {5,5,6,0,0,0,7,5,5},
													{5,5,5,5,5,5,5,5,5},
													{5,5,5,5,5,5,5,5,5},
													{1,2,5,5,5,5,5,4,3} };
const int SHIELD_ROWS					= 4;
const int SHIELD_COLUMNS				= 9;
string INTACT_SHIELD_PREFIX				= "shield/intact_shield_";
string BROKEN_SHIELD_PREFIX				= "shield/broken_shield_";
const int BROKEN_CARDINALITY			= 8;


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
	this->hp = hp;
	this->damage = damage;
	this->velocity = velocity;
	this->cooldown = cooldown;
	this->texturePath = texturePath;
	this->bulletTexturePath = bulletTexturePath;
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
	// printf("I received %d damage!",damage);
	this->hp = this->hp-damage;
	// printf("My remaining hp are %d!",this->hp);
	return (this->hp <= 0);
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

//dull implementation
bool Ship::readyToShoot(){ return false;}

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

EnemyShip::EnemyShip(int x,int y,int width, int height,int points, int hp, int damage, int velocity, float cooldown,int pushDistance, int downDistance,const string* shipClass,string texturePath,string bulletTexturePath) : Ship(x,y,width,height,hp,damage,velocity,cooldown,texturePath,bulletTexturePath)
{
	this->pushDistance = pushDistance;
	this ->downDistance = downDistance;
	//the ships always start facing right direction
	direction = 1;
	this->shipClass = shipClass;
	this->points = points;
	
}


int EnemyShip::getPoints()
{
	return this->points;
}

bool EnemyShip::isGoingRight()
{
	return (this->direction>0);
}

int EnemyShip::getDirection()
{
	return this->direction;
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
	printf("Ship Class is %s\n",this->shipClass->c_str());
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
	this->startingX = startingX;
	this->startingY = startingY;
	this->scale_ratio = scale_ratio;
	this->rows = SHIELD_ROWS;
	this->columns = SHIELD_COLUMNS;
	this->unitShieldWidth = UNIT_SHIELD_WIDTH;
	this->unitShieldHeight = UNIT_SHIELD_HEIGHT;
	this->shieldWidth =	(this->unitShieldWidth*this->scale_ratio)*this->columns;
	this->shieldHeight = (this->unitShieldHeight*this->scale_ratio)*this->rows;
	this->shieldParts.resize(this->rows,vector<std::shared_ptr<ShieldUnit>>(this->columns));
	this->init();
}

void Shield::init()
{
	int x,y;
	for(int i = 0; i < this->rows; i++)
	{
		for(int j = 0; j < this->columns; j++)
		{
			x = this->startingX	+ (j*(this->unitShieldWidth*this->scale_ratio));
			y = this->startingY - (i*(this->unitShieldHeight*this->scale_ratio));
			createShield(x,y,CLASSIC_SHIELD_TYPES[i][j],i,j);
		}
	}

}

void Shield::createShield(int x, int y, int type, int row, int column)
{
	string intactTexturePath = INTACT_SHIELD_PREFIX;
	string brokenTexturePath = randomBrokenPath();
	ShieldUnit* current;
	// string complete = INTACT_SHIELD_PREFIX+"1.png";
	// std::cout << complete <<std::endl;
	switch(type)
	{
	
		case 0:
			{
				current = NULL; 
				break;
			}
		case 1:
			{
				current = new ShieldUnit(x,y,UNIT_SHIELD_WIDTH*this->scale_ratio,UNIT_SHIELD_HEIGHT*this->scale_ratio,intactTexturePath+"1.png",brokenTexturePath,true);
				break;
			}
		case 2:
			{
				current = new ShieldUnit(x,y,UNIT_SHIELD_WIDTH*this->scale_ratio,UNIT_SHIELD_HEIGHT*this->scale_ratio,intactTexturePath+"2.png",brokenTexturePath,false);
				break;
			}
		case 3:
			{
				current = new ShieldUnit(x,y,UNIT_SHIELD_WIDTH*this->scale_ratio,UNIT_SHIELD_HEIGHT*this->scale_ratio,intactTexturePath+"3.png",brokenTexturePath,true);
				break;
			}
		case 4:
			{
				current = new ShieldUnit(x,y,UNIT_SHIELD_WIDTH*this->scale_ratio,UNIT_SHIELD_HEIGHT*this->scale_ratio,intactTexturePath+"4.png",brokenTexturePath,false);
				break;
			}
		case 5:
			{
				current = new ShieldUnit(x,y,UNIT_SHIELD_WIDTH*this->scale_ratio,UNIT_SHIELD_HEIGHT*this->scale_ratio,intactTexturePath+"5.png",brokenTexturePath,false);
				break;
			}
		case 6:
			{
				current = new ShieldUnit(x,y,UNIT_SHIELD_WIDTH*this->scale_ratio,UNIT_SHIELD_HEIGHT*this->scale_ratio,intactTexturePath+"6.png",brokenTexturePath,true);
				break;
			}
		case 7:
			{
				current = new ShieldUnit(x,y,UNIT_SHIELD_WIDTH*this->scale_ratio,UNIT_SHIELD_HEIGHT*this->scale_ratio,intactTexturePath+"7.png",brokenTexturePath,true);
				break;
			}
		default:
			{
				return;
				
			}
	}

	std::shared_ptr<ShieldUnit> shieldUnitPointer(current);
	this->shieldParts.at(row).at(column) = shieldUnitPointer;
}

string Shield::randomBrokenPath()
{
	
	//could not work
	string suffix = std::to_string(std::rand() % BROKEN_CARDINALITY);
	// string complete = BROKEN_SHIELD_PREFIX+suffix+".png";
	// std::cout << complete <<std::endl;
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
	// std::cout << this->shieldParts[row][column]->getBrokenTexturePath() <<std::endl;
	return this->shieldParts[row][column];
}

//------- GameEntities ------//

//------ Board -------//

Board::Board(int width,int height, int scale_ratio)
{
	this -> width = width*scale_ratio;
	this -> height = height*scale_ratio;
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

	if(!vertical)
	{
		this->playerShip->moveHorizontally(direction);
	}
	else
	{

	}
}

int SpaceBattle::getBulletsSize()
{
	return this->bullets.size();
}


bool SpaceBattle::checkCollision(LivingEntity* one, LivingEntity* two)
{
	//we need to check if the two entities are overlapping
	//we will try a first basic implementation
	//we want to check if entity one hits entity two. 
	//we need to check if any pixel of entity one is included between the
	//rectangle of entity 2
	// if(one == NULL | two == NULL)
	// {
	// 	return false;
	// }
	int currX,currY;
	int twoX,twoY;
	for(int i = 0; i < one->getWidth();i++)
	{
		for(int j=0; j<one->getHeight();j++)
		{
			currX = i+one->getX();
			currY = one->getY()+j; //THIS NEEDS TO BE CHECKED WE STILL DOWN KNOW IF X,Y ARE UPPER RIGHT OR BOTTOM RIGHT CORNER
			twoX  = two->getX();
			twoY  = two->getY();
			if((currX >= twoX) && (currX <= twoX+two->getWidth()) && (currY >= twoY) && (currY <= twoY + two->getHeight()))
			{
				return true;
			}   
		}
	}
	return false;
}

std::shared_ptr<LivingEntity> SpaceBattle::getLastBullet()
{
	return this->bullets.back();
}

bool SpaceBattle::createPlayerBullet()
{

	//we need to address the cooldown otherwise we can spam bullets
	if(!(this->currentTicks >= (this->lastShotTicks+(this->playerShip->getCooldown()*GLOBAL_FPS))))
	{
		return false;
	}		
	//the x of the bullet must be carefully calculated so we put it in a variable
	int bullet_x = (this->playerShip->getX()+(this->playerShip->getWidth()/2)-((BASIC_PLAYER_BULLET_WIDTH*this->scale_ratio)/2));
	std::shared_ptr<Bullet> p1(new Bullet(bullet_x,this->playerShip->getY() - PLAYER_SHIP_BULLET_OFFSET*this->scale_ratio,BASIC_PLAYER_BULLET_WIDTH*this->scale_ratio, BASIC_PLAYER_BULLET_HEIGHT*this->scale_ratio,BASIC_PLAYER_SHIP_DAMAGE,PLAYER_BULLET_VELOCITY*this->scale_ratio,-1));
	this->bullets.push_back(p1);
	this->lastShotTicks = this->currentTicks;
	return true;
	
}


//------ Classic Space Battle -----//
ClassicSpaceBattle::ClassicSpaceBattle(vector<EnemyShipClasses> classes,int scale_ratio, int rowsOfEnemies, int shields, int enemiesPerRow)
{

	assert(classes.size()==(rowsOfEnemies));
	this->gameBoard 			= new ClassicBoard(scale_ratio);
	this->rowsOfEnemies 		= rowsOfEnemies;
	this-> numberOfShields 		= shields;
	this-> enemiesPerRow 		= enemiesPerRow;
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
	std::srand(std::time(nullptr));


	//creating Enemies
	createEnemies();
	this->firstShip = enemyQueue.front();
	//creating player
	//what if we pass a player in input when creating the battle?
	createPlayer();
	//creating shields
	createShields();
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
	int startX = this->gameBoard->getXCenter();
	int enemyYOffset = this->gameBoard->getEnemyYOffset();
	int enemyXOffset = this->gameBoard->getEnemyXOffset();
	startX = startX - enemyXOffset/2;

	
	//startY differs upon the number of rows of enemies
	//If we have an odd number of rows
	if(this->rowsOfEnemies%2 == 1)
	{
		/* startY = enemyYAreaCenter +((rows-1)/2)*enemyOffset
		*/
		startY = this->gameBoard->getEnemyYAreaCenter() + ((this->rowsOfEnemies-1)/2)*enemyYOffset;
	}
	else //if we have a pair number of rows
	{
		/* startY = enemyYAreaCenter + 1/2(enemyOffset) + ((rows-2)/2)*enemyOffset
		*/
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
	//assert(this->numberOfShields>0);
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

void ClassicSpaceBattle::update()
{
	if(this->gamePhase == PLAYING)
	{
		if(this->playerShipDestroyed)
		{
			this->playerShip->setX(this->gameBoard->getPlayerXSpawn());
			this->playerShipDestroyed = false;
		}
		//we increment the ticks
		this->currentTicks++;
		//Update contains all the logic of the game itself, like moving bullets, moving enemyships, etc.
		if(this->currentTicks%CLASSIC_MOVEMENT_RATIO == 0)
		{
			moveEnemiesClassic();
		}
		moveBullets();
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

/* moveEnemiesClassic aims to reproduce the classic behaviour of enemy ships in the game */
/* Each frame, one ship (starting from bottom row, most left one) is pushed to the new  */
/* position. What does it mean? that the less ships there are, the faster they go. This  */
/* was a bug in the original game but the designer found it entertaining so it was kept  */	
void ClassicSpaceBattle::moveEnemiesClassic()
{


	//are we in push or down phase? 
	//push phase occurs in normal condition
	//down phase occurs when one element has reached the left or right border
	//so we should push element. when one element reach the current border, then the
	// next cycle they all go down
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

		if(currentShip != NULL && currentShip->isDrawable())
		{
			found = true;
		}
		this->enemyQueue.pop();
		this->enemyQueue.push(currentShip);
	}
	if(this->currentPhase == PUSH)
	{
		//if im in push phase
		currentShip->push();
		if(checkBoundaryCollision(currentShip.get()))
		{
			//after the push I check the boundaries to see if i'm at the border
			this->currentPhase = ENDING_PUSH;
		}
	}
	else if(this->currentPhase == ENDING_PUSH)
	{
		currentShip->push();
		
	}
	else if(this->currentPhase == DOWN)
	{
		currentShip->down();
		currentShip->flip();
		if(checkIfEnemyLanded(currentShip.get()))
		{
			this->enemyLanded = true;
		}

	}
	return;
}

void ClassicSpaceBattle::moveEnemies()
{

}

void ClassicSpaceBattle::spawnEnemyBullet()
{
	//this method spawns an enemy bullet by a random "first line" enemy
	//which column will shoot?
	int random_column = (std::rand() % (this->enemiesPerRow));
	int line = 0;
	bool found = false;
	int starting_column = random_column;
	//we have to find an enemy that is not null, starting from that column and going right to left
	while(!found)
	{
		if(this->enemies.at(line).at(random_column)!=nullptr)
		{
			found = true;
		}
		else
		{
			if(line != this->rowsOfEnemies-1)
			{
				line++;
			}
			else
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

	//random_column and line stores the coordinates of the enemy shooting
	makeEnemyShoot(getEnemyByRowAndColumn(line,random_column));






}

void ClassicSpaceBattle::makeEnemyShoot(EnemyShip* ship)
{
	//Simple supportive method to complete "spawn enemy bullet" to help readability of code
	int bullet_x = (ship->getX()+(ship->getWidth()/2)-((BASIC_PLAYER_BULLET_WIDTH*this->scale_ratio)/2));
	std::shared_ptr<Bullet> p1(new Bullet(bullet_x,ship->getY()+ship->getHeight(),BASIC_ENEMY_BULLET_WIDTH*this->scale_ratio, BASIC_ENEMY_BULLET_HEIGHT*this->scale_ratio,ship->getAmmoDamage(),BASIC_ENEMY_BULLET_VELOCITY*this->scale_ratio,1));
	this->bullets.push_back(p1);
	this->lastEnemyShotTicks = this->currentTicks;
	return;

}

void ClassicSpaceBattle::checkBulletsCollision()
{

	bool explored = false;
	int left_index = 0;
	//index used to check collision between bullets
	int left_ausiliar_index = left_index;
	int right_index = this->bullets.size() - 1;

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
			if(i == 0 && ( j == 3 |j == 4| j==5)) //0,3;0,4;0,5 are not part of the shield
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
			if(i == 0 && ( j == 3 |j == 4| j==5)) //0,3;0,4;0,5 are not part of the shield
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
	if(this->playerLifes == 0 | this->enemyLanded)
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
	printf("\n We have %d shields; %d enemies divided in %d rows",this->shields,this->enemiesPerRow*this->rowsOfEnemies,this->rowsOfEnemies);
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