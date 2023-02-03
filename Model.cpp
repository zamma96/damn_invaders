
#include <stdio.h>
#include <string>
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

const int 	basic_player_ship_width 	= 13;
const int 	basic_player_ship_height 	= 8;
const int 	basic_player_ship_hp		= 10;
const int 	basic_player_ship_damage    = 5;
const int 	basic_player_ship_velocity	= 1;
const float basic_player_ship_cooldown  = 0.7;
string basic_player_texture_path 		= "player_ship.png";
string player_bullet_texture_path		= "simple_bullet.png";
const int   basic_player_bullet_height  = 5;
const int 	basic_player_bullet_width	= 1;
const int 	player_ship_bullet_offset   = 4;

const int 	player_bullet_velocity 		= 4;


//--- parametrized ships values ---//
string basic_bullet_texture_path		= "enemy_bullet_";
const int   basic_enemy_bullet_height 	= 7;
const int 	basic_enemy_bullet_width	= 3;
const float 	basic_enemy_bullet_velocity	= 1.5;
//--- Class One "Octopus" Ship ---// 

const int 	class_one_width 			= 12;
const int 	class_one_height 			= 8;

const int 	class_one_points			= 10;
const int 	class_one_hp 				= 5;
const int 	class_one_damage 			= 10;
const int 	class_one_velocity 			= 1;
const float class_one_cooldown 			= 1.0;
const string* class_one_name 			= new string("Class One");
string class_one_texture_path 			= "octopus_ship_complete.png";

//--- Class Two "Crab" Ship ---// 

const int 	class_two_width 			= 11;
const int 	class_two_height 			= 8;

const int 	class_two_points			= 20;
const int 	class_two_hp 				= 5;
const int 	class_two_damage 			= 10;
const int 	class_two_velocity 			= 1;
const float class_two_cooldown 			= 1.0;
const string* class_two_name 			= new string("Class Two");
string class_two_texture_path 			= "crab_ship_complete.png";

//--- Class Three "Squid" Ship ---// 

const int 	class_three_width 			= 8;
const int 	class_three_height 			= 8;

const int 	class_three_points			= 30;
const int 	class_three_hp 				= 5;
const int 	class_three_damage 			= 10;
const int 	class_three_velocity 		= 1;
const float class_three_cooldown 		= 1.0;
const string* class_three_name 			= new string("Class Three");
string class_three_texture_path 		= "squid_ship_complete.png";



//--- Parametrized Boards Values ---//
//--- Classic Board ---//
//mp = mid-pivoted -> it appears that text elements are not bottom right alligned, but mid right.
const int 	classic_board_height 		= 256;
const int 	classic_board_width 		= 224;
const int   classic_board_score_y		= 12;
const int   classic_board_score_x		= 9;
const int 	classic_board_hiscore_x 	= 81;
const int   classic_board_score2_x		= 153;
const int 	classic_board_score_number_y= 28;
const int   classic_board_score_number_x= 25;
const int 	classic_board_hs_number_x 	= 89;
const int 	classic_upperHud 			= 36;
const int 	classic_lowerHud 			= 240;
const int 	classic_lifes_y				= 241;
const int 	classic_lifes_x				= 26;
const int   classic_credit_x			= 137;
const int   classic_credit_y			= 241; //mp
const int 	classic_lifes_number_x		= 9;
const int 	classic_enemyYAreaCenter 	= 96;
const int 	classic_shield_y 			= 208;
const int 	classic_shield_x			= 30; //to be calculated
const int   classic_shield_offset		= 30; //to be calculated
const int 	classic_shipYCenter 		= 220;
const int 	classic_enemyXOffset 		= 15;
const int 	classic_enemyYOffset 		= 20;
const int 	classic_enemyHeight 		= 8;
const int 	classic_xCenter 			= 112;
const int 	classic_enemyLeftBorder		= 15;
const int 	classic_enemyRightBorder 	= 209;
const int   classic_player_x_spawn      = 20;
const int  	classic_special_ship_y		= 44; //mp
const int 	classic_bullet_land_offset  = 5;

//--- parametrized ClassicSpaceBattle values ---//
const int 	classic_push_distance 		= 3;
const int 	classic_down_distance	 	= 4;
const int 	classic_player_lifes		= 3;
const int 	classic_number_of_shields	= 4;
//number of frames between movements of enemies; the lower, the faster they move
const int   classic_movement_ratio		= 2;

//--- parametrized game values ---///
const int global_fps 					= 60;
const int enemy_shots_delay				= 40;


//--- parametrized Shield values ---//

//first row is bottom row in a graphical visualization
const vector<vector<int>> classic_shield_types 	= { {5,5,6,0,0,0,7,5,5},
													{5,5,5,5,5,5,5,5,5},
													{5,5,5,5,5,5,5,5,5},
													{1,2,5,5,5,5,5,4,3} };
const int shield_rows					= 4;
const int shield_columns				= 9;
string intact_shield_prefix				= "shield/intact_shield_";
string broken_shield_prefix				= "shield/broken_shield_";
const int broken_cardinality			= 8;


const int unit_shield_width				= 2;
const int unit_shield_height			= 4;

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

//--------- RealEntity -------//

RealEntity::RealEntity(int x,int y,int width, int height) : Entity(x,y,width,height) {}

RealEntity::~RealEntity()
{
	// printf("destroying real entity");
}

void RealEntity::draw()
{
	printf("x->%d ",x);
	printf("y->%d\n",y);

}


//-------- Living Entity --------//

LivingEntity::LivingEntity(int x,int y,int width, int height) : RealEntity(x,y,width,height)
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

PlayerShip::PlayerShip(int x,int y,int width, int height, int hp, int damage, int velocity, float cooldown,string* name,string texturePath) : Ship(x,y,width,height,hp,damage,velocity,cooldown, texturePath,player_bullet_texture_path)
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
ClassOneShip::ClassOneShip(int x,int y,int scale_ratio,int pushDistance, int downDistance) : EnemyShip(x,y,class_one_width*scale_ratio,class_one_height*scale_ratio,class_one_points,class_one_hp,class_one_damage,class_one_velocity,class_one_cooldown,pushDistance,downDistance,class_one_name,class_one_texture_path,basic_bullet_texture_path) {}

void ClassOneShip::getClassName()
{
	EnemyShip::printSummary();
}

//----------------------------//
//------- ClassTwoShip -------//
//----------------------------//

ClassTwoShip::ClassTwoShip(int x,int y,int scale_ratio,int pushDistance, int downDistance) : EnemyShip(x,y,class_two_width*scale_ratio,class_two_height*scale_ratio,class_two_points,class_two_hp,class_two_damage,class_two_velocity,class_two_cooldown,pushDistance,downDistance,class_two_name,class_two_texture_path,basic_bullet_texture_path) {}

void ClassTwoShip::getClassName()
{
	EnemyShip::printSummary();
}

//----------------------------//
//------ ClassThreeShip ------//
//----------------------------//

ClassThreeShip::ClassThreeShip(int x,int y,int scale_ratio,int pushDistance, int downDistance) : EnemyShip(x,y,class_three_width*scale_ratio,class_three_height*scale_ratio,class_three_points,class_three_hp,class_three_damage,class_three_velocity,class_three_cooldown,pushDistance,downDistance,class_three_name,class_three_texture_path,basic_bullet_texture_path) {}

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
	this->rows = shield_rows;
	this->columns = shield_columns;
	this->unitShieldWidth = unit_shield_width;
	this->unitShieldHeight = unit_shield_height;
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
			createShield(x,y,classic_shield_types[i][j],i,j);
		}
	}

}

void Shield::createShield(int x, int y, int type, int row, int column)
{
	string intactTexturePath = intact_shield_prefix;
	string brokenTexturePath = randomBrokenPath();
	ShieldUnit* current;
	// string complete = intact_shield_prefix+"1.png";
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
				current = new ShieldUnit(x,y,unit_shield_width*this->scale_ratio,unit_shield_height*this->scale_ratio,intactTexturePath+"1.png",brokenTexturePath,true);
				break;
			}
		case 2:
			{
				current = new ShieldUnit(x,y,unit_shield_width*this->scale_ratio,unit_shield_height*this->scale_ratio,intactTexturePath+"2.png",brokenTexturePath,false);
				break;
			}
		case 3:
			{
				current = new ShieldUnit(x,y,unit_shield_width*this->scale_ratio,unit_shield_height*this->scale_ratio,intactTexturePath+"3.png",brokenTexturePath,true);
				break;
			}
		case 4:
			{
				current = new ShieldUnit(x,y,unit_shield_width*this->scale_ratio,unit_shield_height*this->scale_ratio,intactTexturePath+"4.png",brokenTexturePath,false);
				break;
			}
		case 5:
			{
				current = new ShieldUnit(x,y,unit_shield_width*this->scale_ratio,unit_shield_height*this->scale_ratio,intactTexturePath+"5.png",brokenTexturePath,false);
				break;
			}
		case 6:
			{
				current = new ShieldUnit(x,y,unit_shield_width*this->scale_ratio,unit_shield_height*this->scale_ratio,intactTexturePath+"6.png",brokenTexturePath,true);
				break;
			}
		case 7:
			{
				current = new ShieldUnit(x,y,unit_shield_width*this->scale_ratio,unit_shield_height*this->scale_ratio,intactTexturePath+"7.png",brokenTexturePath,true);
				break;
			}
		default:
			{
				//no shield must be done
				printf("row: %d, column: %d\n",row,column);
				break;
			}
	}

	std::shared_ptr<ShieldUnit> shieldUnitPointer(current);
	this->shieldParts.at(row).at(column) = shieldUnitPointer;
}

string Shield::randomBrokenPath()
{
	
	//could not work
	string suffix = std::to_string(std::rand() % broken_cardinality);
	// string complete = broken_shield_prefix+suffix+".png";
	// std::cout << complete <<std::endl;
	return broken_shield_prefix+suffix+".png";

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

ClassicBoard::ClassicBoard(int scale_ratio) : Board(classic_board_width,classic_board_height,scale_ratio)
{
	this->upperHud 			= classic_upperHud*scale_ratio;
	this->lowerHud 			= classic_lowerHud*scale_ratio;
	this->enemyYAreaCenter 	= classic_enemyYAreaCenter*scale_ratio;
	this->shieldY 			= classic_shield_y*scale_ratio;
	this->shieldX    		= classic_shield_x*scale_ratio;
	this->shieldOffset		= classic_shield_offset*scale_ratio;
	this->shipYCenter 		= classic_shipYCenter*scale_ratio;
	this->enemyXOffset 		= classic_enemyXOffset*scale_ratio;
	this->enemyYOffset 		= classic_enemyYOffset*scale_ratio;
	this->enemyHeight 		= classic_enemyHeight*scale_ratio;
	this->xCenter 			= classic_xCenter*scale_ratio;
	this->enemyLeftBorder   = classic_enemyLeftBorder*scale_ratio;
	this->enemyRightBorder 	= classic_enemyRightBorder*scale_ratio;
	this->scoreY 			= classic_board_score_y*scale_ratio;
	this->scoreX            = classic_board_score_x*scale_ratio;
	this->highScoreX		= classic_board_hiscore_x*scale_ratio;
	this->score2X 			= classic_board_score2_x*scale_ratio;
	this->scoreNumberY 		= classic_board_score_number_y*scale_ratio;
	this->scoreNumberX 		= classic_board_score_number_x*scale_ratio;
	this->hiScoreNumberX	= classic_board_hs_number_x*scale_ratio;
	this->lifesY            = classic_lifes_y*scale_ratio;
	this->lifesX       		= classic_lifes_x*scale_ratio;
	this->creditX           = classic_credit_x*scale_ratio;
	this->creditY           = classic_credit_y*scale_ratio;
	this->lifesNumberX      = classic_lifes_number_x*scale_ratio;
	this->playerXSpawn      = classic_player_x_spawn*scale_ratio;
	this->specialShipY      = classic_special_ship_y*scale_ratio;
	this->bulletLandOffset  = classic_bullet_land_offset*scale_ratio;

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
	if(!(this->currentTicks >= (this->lastShotTicks+(this->playerShip->getCooldown()*global_fps))))
	{
		return false;
	}		
	//the x of the bullet must be carefully calculated so we put it in a variable
	int bullet_x = (this->playerShip->getX()+(this->playerShip->getWidth()/2)-((basic_player_bullet_width*this->scale_ratio)/2));
	std::shared_ptr<Bullet> p1(new Bullet(bullet_x,this->playerShip->getY() - player_ship_bullet_offset*this->scale_ratio,basic_player_bullet_width*this->scale_ratio, basic_player_bullet_height*this->scale_ratio,basic_player_ship_damage,player_bullet_velocity*this->scale_ratio,-1));
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
	this->currentTicks 			= global_fps;
	this->lastEnemyShotTicks    = global_fps*3;		//two seconds of delay before the enemy starts to shoot
	this->enemyShotsDelay		= enemy_shots_delay;
	this->gamePhase				= INIT;
	this->playerLifes    		= classic_player_lifes;
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
				nextShip = new ClassOneShip(x,y,this->gameBoard->getScaleRatio(),classic_push_distance*this->gameBoard->getScaleRatio(),classic_down_distance*this->gameBoard->getScaleRatio());
			}
			else if(currentClass == CLASS_TWO)
			{
				nextShip = new ClassTwoShip(x,y,this->gameBoard->getScaleRatio(),classic_push_distance*this->gameBoard->getScaleRatio(),classic_down_distance*this->gameBoard->getScaleRatio());
			}
			else if(currentClass == CLASS_THREE)
			{
				nextShip = new ClassThreeShip(x,y,this->gameBoard->getScaleRatio(),classic_push_distance*this->gameBoard->getScaleRatio(),classic_down_distance*this->gameBoard->getScaleRatio());
			}
			else
			{
				printf("COULD NOT FIND CLASS_SHIP!");
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
	std::shared_ptr<PlayerShip> player(new PlayerShip(this->gameBoard->getPlayerXSpawn(),this->gameBoard->getShipYCenter(),basic_player_ship_width*this->gameBoard->getScaleRatio(),basic_player_ship_height*this->gameBoard->getScaleRatio(),basic_player_ship_hp,basic_player_ship_damage,basic_player_ship_velocity*this->scale_ratio,basic_player_ship_cooldown,new string("Player One"),basic_player_texture_path));
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
		if(this->currentTicks%classic_movement_ratio == 0)
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
	int bullet_x = (ship->getX()+(ship->getWidth()/2)-((basic_player_bullet_width*this->scale_ratio)/2));
	std::shared_ptr<Bullet> p1(new Bullet(bullet_x,ship->getY()+ship->getHeight(),basic_enemy_bullet_width*this->scale_ratio, basic_enemy_bullet_height*this->scale_ratio,ship->getAmmoDamage(),basic_enemy_bullet_velocity*this->scale_ratio,1));
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
	return basic_bullet_texture_path;
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