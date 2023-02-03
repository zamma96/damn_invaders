#include <stdio.h>
#include <string>
#include "View.h"
#include "Model.h"
#include <cassert>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace ViewEntities;
using namespace Entities;
using namespace GameEntities;

//--- Constant ---//
const int enemies_frame 					= 2;
const int enemies_frame_delay 				= 30;
const int player_frame 						= 1;
const int player_frame_delay  				= 1;
const int player_bullet_frame   			= 1;
const int player_bullet_frame_delay 		= 1;
const int enemy_bullet_frame				= 4;
const int enemy_bullet_frame_delay 			= 15;

const int enemy_bullets_type 				= 3;

const int shield_frame						= 1;
const int shield_frame_delay				= 1;

const string hud_font_path					="assets/font/space_invaders.ttf";
const int hud_font_size						= 9;


string green_bar_path 						="green_bar.png";

const int type_one_explosion_width			= 12;
const int type_one_explosion_height			= 8;
const int type_one_explosion_frame 			= 2;
const int type_one_explosion_frame_delay	= 15;
string type_one_explosion_path				="type_one_explosion.png";


const int type_two_explosion_width			= 9;
const int type_two_explosion_height			= 9;
const int type_two_explosion_frame 			= 2;
const int type_two_explosion_frame_delay	= 15;
string type_two_explosion_path				="type_two_explosion.png";

const int type_three_explosion_width		= 9;
const int type_three_explosion_height		= 9;
const int type_three_explosion_frame 		= 2;
const int type_three_explosion_frame_delay	= 15;
string type_three_explosion_path			="type_three_explosion.png";

//audio constants//
string main_music_one_path					="fastinvader1.wav";
string main_music_two_path					="fastinvader2.wav";
string main_music_three_path				="fastinvader3.wav";
string main_music_four_path					="fastinvader4.wav";

//--- 	Drawable 	---//
Drawable::Drawable(string path, SDL_Renderer* renderer, SDL_PixelFormat* format,int frameNumber, int frameDelay)
{
	this->path = path;
	this->format = format;
	this->renderer = renderer;
	this->frameNumber = frameNumber;
	this->frameDelay = frameDelay;
	this->currentFrame = 0;
}

void Drawable::free()
{
	if(this->texture != NULL)
	{
		SDL_DestroyTexture(this->texture);
		this->texture = NULL;
	}
}

SDL_Surface* Drawable::loadSurface(std::string path )
{
	//The final optimized image
	SDL_Surface* optimizedSurface = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface( loadedSurface, this->format, 0 );
		if( optimizedSurface == NULL )
		{
			printf( "Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	return optimizedSurface;
}



//--- Drawable Object ---//

DrawableObject::DrawableObject(std::shared_ptr<LivingEntity> entity,string path,SDL_PixelFormat* format,SDL_Renderer* renderer,int frameNumber,int frameDelay) : Drawable(path,renderer,format,frameNumber,frameDelay)
{

	this->entity = entity;
	this->dstRectangle.w = this->entity->getWidth();
	this->dstRectangle.h = this->entity->getHeight();
	
	this->loadMedia();
	

}


DrawableObject::~DrawableObject()
{
	free();
	this->srcRectangles.clear();
	this->entity = NULL;
	this->format = NULL;
}

//load the media
bool DrawableObject::loadMedia()
{
	//Loading success flag
	bool success = true;

	string globalpath = "assets/";
	// globalpath->append(this->path);
	//Load PNG surface
	SDL_Surface* pngSurface = loadSurface( globalpath + this->path);
	if( pngSurface == NULL )
	{
		printf( "Failed to load PNG image!\n" );
		success = false;
		return success;
	}
	else
	{
		this->texture = SDL_CreateTextureFromSurface(this->renderer,pngSurface);
	}

	SDL_FreeSurface(pngSurface);


	//---Original Dimensions and Source calculation ---//
	int originWidth;
	int originHeight;

	
	SDL_QueryTexture(this->texture,NULL,NULL,&originWidth,&originHeight);
	
	originWidth = originWidth/this->frameNumber;



	//we add the different rectangles
	for(int i = 0;i < frameNumber; i++)
	{
		SDL_Rect curr;
		curr.h = originHeight;
		curr.w = originWidth;
		curr.x = originWidth*i;
		curr.y = 0;
		this->srcRectangles.push_back(curr);
	}
	return success;
}


bool DrawableObject::draw()
{

	if(!this->entity->isDrawable())
	{
		//if the entity we are trying to draw doesnt exist anymore, we return false,
		//so that the View can destroy us :)
		return false;
	}
	this->dstRectangle.x = this->entity->getX();
	this->dstRectangle.y = this->entity->getY();	


	
	int index = this->currentFrame/this->frameDelay;
	
	SDL_Rect currFrameSrc = this->srcRectangles.at(index);
	
	SDL_RenderCopy(this->renderer,this->texture,&currFrameSrc,&dstRectangle);
	this->currentFrame++;
	if(currentFrame/this->frameDelay  >= this->frameNumber)
	{
		currentFrame = 0;
	}

	return true;
}

int DrawableObject::getObjectX()
{
	if(this->entity.get() != NULL)
		return this->entity->getX();
	else 
		return 0;
}

int DrawableObject::getObjectY()
{
	if(this->entity.get() != NULL)
		return this->entity->getY();
	else 
		return 0;
}



//--- DrawableText ---//
DrawableText::DrawableText(TTF_Font* font,SDL_Color textColor,string text,int x,int y,SDL_PixelFormat* format, SDL_Renderer* renderer) : Drawable("",renderer,format,1,1)
{
	this->font = font;
	this->textColor = textColor;
	this->text = text;
	this->x = x;
	this->y = y;
	this->loadMedia();
}

DrawableText::~DrawableText()
{
	this->free();
	this->renderer = NULL;
	this->format = NULL;
	this->font = NULL;

}


void DrawableText::changeText(string text)
{
	this->free();

	this->text = text;
	loadMedia();
}

bool DrawableText::loadMedia()
{
	SDL_Surface* textSurface = TTF_RenderText_Solid(this->font,this->text.c_str(),this->textColor);
	if(textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n",TTF_GetError() );
	}
	else
	{
		this->texture = SDL_CreateTextureFromSurface(this->renderer,textSurface);
		if(this->texture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL_Error: %s\n",SDL_GetError() );
		}
		else
		{
			this->width = textSurface->w;
			this->height = textSurface->h;
		}

		SDL_FreeSurface(textSurface);
	}
	return this->texture != NULL;
}

bool DrawableText::draw()
{
	SDL_Rect renderQuad = {this->x,this->y,this->width,this->height};
	SDL_RenderCopy(this->renderer,this->texture,NULL,&renderQuad);
	return true;
}


//---- PureDrawable ----//
PureDrawable::PureDrawable(int x, int y, int width, int height, string path, SDL_PixelFormat* format, SDL_Renderer* renderer, int frameNumber, int frameDelay) : Drawable(path,renderer,format,frameNumber,frameDelay)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->loadMedia();

}

PureDrawable::~PureDrawable()
{
	this->free();
	this->renderer = NULL;
	this->format = NULL;

}

//load the media
bool PureDrawable::loadMedia()
{
	//Loading success flag
	bool success = true;

	string globalpath = "assets/";
	
	//Load PNG surface
	SDL_Surface* pngSurface = loadSurface( globalpath + this->path);
	if( pngSurface == NULL )
	{
		printf( "Failed to load PNG image!\n" );
		success = false;
		return success;
	}
	else
	{
		this->texture = SDL_CreateTextureFromSurface(this->renderer,pngSurface);
	}

	SDL_FreeSurface(pngSurface);


	//---Original Dimensions and Source calculation ---//
	int originWidth;
	int originHeight;

	
	SDL_QueryTexture(this->texture,NULL,NULL,&originWidth,&originHeight);
	
	originWidth = originWidth/this->frameNumber;



	//we add the different rectangles
	for(int i = 0;i < frameNumber; i++)
	{
		SDL_Rect curr;
		curr.h = originHeight;
		curr.w = originWidth;
		curr.x = originWidth*i;
		curr.y = 0;
		this->srcRectangles.push_back(curr);
	}

	return success;
}



bool PureDrawable::draw()
{

	int index = this->currentFrame/this->frameDelay;
	
	SDL_Rect currFrameSrc = this->srcRectangles.at(index);
	
	SDL_Rect renderQuad = {this->x,this->y,this->width,this->height};

	SDL_RenderCopy(this->renderer,this->texture,&currFrameSrc,&renderQuad);
	this->currentFrame++;
	if(currentFrame/this->frameDelay  >= this->frameNumber)
	{
		currentFrame = 0;
	}

	return true;

}

//----   ExplosionDrawable  ----//
ExplosionDrawable::ExplosionDrawable(int x, int y, int width, int height,string path,SDL_PixelFormat* format,SDL_Renderer* renderer,int frameNumber,int frameDelay) : PureDrawable(x,y,width,height,path,format,renderer,frameNumber,frameDelay)
{
	this->animationOver = false;
}

bool ExplosionDrawable::draw()
{


	
	int index = this->currentFrame/this->frameDelay;
	SDL_Rect currFrameSrc;
	if(index<this->frameNumber)
	{
		currFrameSrc = this->srcRectangles.at(index);
	}
	SDL_Rect renderQuad = {this->x,this->y,this->width,this->height};

	SDL_RenderCopy(this->renderer,this->texture,&currFrameSrc,&renderQuad);
	
	this->currentFrame++;

	if(currentFrame/this->frameDelay  >= this->frameNumber)
	{
		this->currentFrame = 0;
		this->animationOver = true;
	}

	return !this->animationOver;

}

//----- TypeOneExplosionDrawable ------//
TypeOneExplosionDrawable::TypeOneExplosionDrawable(int x, int y, int width, int height,SDL_PixelFormat* format,SDL_Renderer* renderer) : ExplosionDrawable(x,y,width,height,type_one_explosion_path,format,renderer,type_one_explosion_frame,type_one_explosion_frame_delay) {}

//----- TypeOneExplosionDrawable ------//
TypeTwoExplosionDrawable::TypeTwoExplosionDrawable(int x, int y, int width, int height,SDL_PixelFormat* format,SDL_Renderer* renderer) : ExplosionDrawable(x,y,width,height,type_two_explosion_path,format,renderer,type_two_explosion_frame,type_two_explosion_frame_delay) {}

//----- TypeOneExplosionDrawable ------//
TypeThreeExplosionDrawable::TypeThreeExplosionDrawable(int x, int y, int width, int height,SDL_PixelFormat* format,SDL_Renderer* renderer) : ExplosionDrawable(x,y,width,height,type_three_explosion_path,format,renderer,type_three_explosion_frame,type_three_explosion_frame_delay) {}


//----  	AudioSource 	----//
AudioSource::AudioSource(string path)
{
	this->path = path;
	this->loadMedia();
}
AudioSource::~AudioSource()
{
	this->free();
}

void AudioSource::loadMedia()
{

	string globalPath = "assets/audio/"+this->path;
	printf(globalPath.c_str());
	this->sound = Mix_LoadWAV(globalPath.c_str());
	if (this->sound == NULL)
	{
		printf( "Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
	}
}

void AudioSource::play()
{
	Mix_PlayChannel(-1,this->sound,0);
}

void AudioSource::free()
{
	Mix_FreeChunk(this->sound);	
	this->sound = NULL;
}

//----	 SpaceBattleView 	----//
ClassicSpaceBattleView::ClassicSpaceBattleView(ClassicSpaceBattle* spaceBattle)
{
	this->model = spaceBattle;
	this->player = nullptr;
	this->lastScore = 0;
	this->lifes = this->model->getPlayerLifes();
	int hudElements = HudLiveElements::NR_ELEMENTS;
	for(int i = 0; i < hudElements ; i++)
	{
		this->changingText.push_back(nullptr);
	}
	basicInit();

}

ClassicSpaceBattleView::~ClassicSpaceBattleView()
{
	delete this->player;
	this->player = nullptr;
	this->model = nullptr;
	close();
}

bool ClassicSpaceBattleView::basicInit()
{
	bool success = true;

	std::srand(std::time(nullptr));

	//Window, Render Init
	//Initialize SDL
	if( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		this->window = SDL_CreateWindow( "Damn Invaders Alpha", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->model->getGameBoard()->getWidth(), this->model->getGameBoard()->getHeight(), SDL_WINDOW_SHOWN );
		if(this->window == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			this->renderer = SDL_CreateRenderer(this->window,-1,SDL_RENDERER_PRESENTVSYNC);
			int imgFlags = IMG_INIT_PNG;
			if( !( IMG_Init( imgFlags ) & imgFlags ) )
			{
				printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
				success = false;
			}
			else
			{
				this->screenSurface = SDL_GetWindowSurface(this->window);
			}
			if( TTF_Init() == -1 )
			{
				printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
				success = false;
			}
			//opening font
			this->hudFont = TTF_OpenFont(hud_font_path.c_str(),hud_font_size*this->model->getGameBoard()->getScaleRatio());
			if( this->hudFont == NULL)
			{
				printf("Failed to load font! SDL_ttf Error: %s\n",TTF_GetError() );
				success = false;
			}
			 //Initialize SDL_mixer
			if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
			{
					printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
					success = false;
			}
			else
			{

			}
		

		}
	}

	return spaceBattleInit(success);
	
}


bool ClassicSpaceBattleView::spaceBattleInit(bool success)
{
	
	// Drawable Entities Creation
	// --Enemies--//
	std::shared_ptr<EnemyShip> currEnemy;
	for(int i = 0; i < this->model->getRowsOfEnemies(); i++)
	{
		for(int j = 0; j < this -> model->getEnemiesPerRow(); j++)
		{
			currEnemy = this->model->getEnemyPointerByRowAndColumn(i,j);
			this->enemies.push_back(new DrawableObject(currEnemy,currEnemy->getTexturePath(),this->screenSurface->format,this->renderer,enemies_frame,enemies_frame_delay));
			
		}
	}
	currEnemy = NULL;

	//--Player Ship--//
	this->player = new DrawableObject(this->model->getPlayerShipSharedPointer(),this->model->getPlayerShip()->getTexturePath(),this->screenSurface->format,this->renderer,player_frame,player_frame_delay);
	
	//--Other Entities--//
	this->shields.resize(this->model->getNumberOfShields(),vector<std::pair<DrawableObject*,DrawableObject*>>(0));
	createShields();
	createHudElements();
	audioInit(success);


	return success;
}

void ClassicSpaceBattleView::createShields()
{
	int number_of_shields = this->model->getNumberOfShields();
	for(int i = 0;i < number_of_shields; i++)
	{
		initializeSingleShield(i);
	}
}


void ClassicSpaceBattleView::initializeSingleShield(int index)
{ 
	std::shared_ptr<Shield> currentShield = this->model->getShield(index);
	for(int i = 0; i < currentShield->getShieldRows(); i++)
	{
		for(int j = 0; j < currentShield->getShieldColumns(); j++)
		{
			if(i == 0 && ( j == 3 | j == 4 | j==5 ) )
			{
				std::pair<DrawableObject*,DrawableObject*> currentPair(NULL,NULL);
				this->shields[index].push_back(currentPair);
				continue;
			}
			// printf("%d,%d\n",i,j);
			DrawableObject* intactDrawable = new DrawableObject(currentShield->getShieldUnitByIndex(i,j),currentShield->getShieldUnitByIndex(i,j)->getIntactTexturePath(),this->screenSurface->format,this->renderer,shield_frame,shield_frame_delay);
			DrawableObject* brokenDrawable = new DrawableObject(currentShield->getShieldUnitByIndex(i,j),currentShield->getShieldUnitByIndex(i,j)->getBrokenTexturePath(),this->screenSurface->format,this->renderer,shield_frame,shield_frame_delay);
			std::pair<DrawableObject*,DrawableObject*> currentPair(intactDrawable,brokenDrawable);
			this->shields[index].push_back(currentPair);
		}
	}
}

bool ClassicSpaceBattleView::audioInit(bool result)
{
	//main music
	this->mainMusic.push(new AudioSource(main_music_one_path));
	this->mainMusic.push(new AudioSource(main_music_two_path));
	this->mainMusic.push(new AudioSource(main_music_three_path));
	this->mainMusic.push(new AudioSource(main_music_four_path));
	result = true;
}

void ClassicSpaceBattleView::createHudElements()
{
	//test method
	SDL_Color color = {255,255,255};
	
	//score text
	this->fixedDrawableElements.push_back(new DrawableText(this->hudFont,color,"SCORE < 1 >",this->model->getGameBoard()->getScoreX(),this->model->getGameBoard()->getScoreY(),this->screenSurface->format,this->renderer));
	//hi-score text
	this->fixedDrawableElements.push_back(new DrawableText(this->hudFont,color,"HI - SCORE",this->model->getGameBoard()->getHighScoreX(),this->model->getGameBoard()->getScoreY(),this->screenSurface->format,this->renderer));
	//score 2 text
	this->fixedDrawableElements.push_back(new DrawableText(this->hudFont,color,"SCORE < 2 >",this->model->getGameBoard()->getScore2X(),this->model->getGameBoard()->getScoreY(),this->screenSurface->format,this->renderer));

	//green line
	this->fixedDrawableElements.push_back(new PureDrawable(0,this->model->getGameBoard()->getLowerHud(),this->model->getGameBoard()->getWidth(),this->model->getGameBoard()->getScaleRatio()*1,green_bar_path,this->screenSurface->format,this->renderer,1,1));
	//credit texty
	this->fixedDrawableElements.push_back(new DrawableText(this->hudFont,color,"CREDIT   00",this->model->getGameBoard()->getCreditX(),this->model->getGameBoard()->getCreditY(),this->screenSurface->format,this->renderer));
	
	//fake hiscore points
	this->fixedDrawableElements.push_back(new DrawableText(this->hudFont,color,"0000",this->model->getGameBoard()->getHighScoreNumberX(),this->model->getGameBoard()->getScoreNumberY(),this->screenSurface->format,this->renderer));

	//points score and lifes text
	this->changingText[SCORE] = new DrawableText(this->hudFont,color,"0000",this->model->getGameBoard()->getScoreNumberX(),this->model->getGameBoard()->getScoreNumberY(),this->screenSurface->format,this->renderer);
	this->changingText[LIFES] = new DrawableText(this->hudFont,color,std::to_string(this->lifes),this->model->getGameBoard()->getLifesNumberX(),this->model->getGameBoard()->getLifesY(),this->screenSurface->format,this->renderer);	

	//ship sprites
	for(int i = 1; i < this->lifes; i++)
	{
		this->lifesShips.push_back(new PureDrawable(this->model->getGameBoard()->getLifesX()+((i-1)*(this->model->getPlayerShip()->getWidth()+2*this->model->getGameBoard()->getScaleRatio())),this->model->getGameBoard()->getLifesY(),this->model->getPlayerShip()->getWidth(),this->model->getPlayerShip()->getHeight(),this->model->getPlayerShip()->getTexturePath(),this->screenSurface->format,this->renderer,1,1));
	}

}

void ClassicSpaceBattleView::close()
{
	TTF_CloseFont(this->hudFont);
	this->hudFont = NULL;
	SDL_DestroyWindow(this->window);
	SDL_DestroyRenderer(this->renderer);
	this->window = NULL;
	this->renderer = NULL;
	SDL_FreeSurface(this->screenSurface);
	IMG_Quit();
	SDL_Quit();
	Mix_Quit();

}


void ClassicSpaceBattleView::addNewPlayerBullet()
{

	this->bullets.push_back(new DrawableObject(this->model->getLastBullet(),this->model->getPlayerShip()->getBulletTexturePath(),this->screenSurface->format,this->renderer,player_bullet_frame,player_bullet_frame_delay));
}


void ClassicSpaceBattleView::update()
{

	SDL_RenderClear(this->renderer);

	renderExplosions();

	renderBullets();

	renderPlayer();

	renderEnemies();

	renderEntities();

	renderShields();

	renderHUD();

	SDL_RenderPresent(this->renderer);

	audioUpdate();
}

bool ClassicSpaceBattleView::changeModelAndRestart(ClassicSpaceBattle* model)
{
	//cleaning my entities
	this->enemies.clear();
	this->entities.clear();
	this->bullets.clear();
	this->shields.clear();
	this->changingText.clear();
	this->lifesShips.clear();
	while(!this->explosions.empty())
	{
		ExplosionDrawable* temp = this->explosions.front();
		this->explosions.pop();
		delete temp;

	}
	this->fixedDrawableElements.clear();
	this->player = nullptr;
	this->model = model;
	this->lastScore = 0;
	this->lifes = this->model->getPlayerLifes();
	return spaceBattleInit(true);
}

void ClassicSpaceBattleView::renderEnemies()
{
	for(int i = 0;i < enemies.size(); i++)
	{
		if(!this->enemies.at(i)->draw())
		{
			//not only destroy it, but also add an explosion animation
			//addExplosion(this->enemies.at(i)->getObjectX(),this->enemies.at(i)->getObjectY());
			//if the object I'm trying to draw doesn't exist anymore
			//we should destroy it
			delete this->enemies.at(i);
			this->enemies.erase(enemies.begin() + i);
			

		}
		
	}
	return;
}


void ClassicSpaceBattleView::renderPlayer()
{
	this->player->draw();
	return;
}

void ClassicSpaceBattleView::renderEntities()
{
	// printf("entities size: %d\n",this->entities.size());
	for(int i = 0; i < this->entities.size();i++)
	{
		if(!this->entities.at(i)->draw())
		{
			// printf("deleting entity in VIEW\n");
			delete this->entities.at(i);
			this->entities.erase(entities.begin() + i);
		}
	}
	return;
}

void ClassicSpaceBattleView::renderShields()
{
	int columns;
	for(int i = 0; i < this->shields.size(); i++)
	{
		columns = this->model->getShield(i)->getShieldColumns();
		for(int j = 0; j < this->shields[i].size() ; j++)
		{

			int row = std::floor(j/columns);
			int column = j%columns;
			if(row == 0 && ( column == 3 |column == 4| column==5)) //0,3;0,4;0,5 are not part of the shield
			{
				continue;
			}
			if(this->model->getShield(i)->getShieldUnitByIndex(row,column)->isDestroyed())
			{
				this->shields[i][j].second->draw();
			}
			else
			{
				this->shields[i][j].first->draw();
			}

		}
	}

}


void ClassicSpaceBattleView::renderBullets()
{

	// printf("bullets are %d\n, in reality %d\n",this->bullets.size(),this->model->getBulletsSize());
	//are there new bullets in the screen?
	if(this->bullets.size() < this->model->getBulletsSize())
	{
		//if there are new bullets, we add it
		//(this methods works when at most one bullet per frame is added. but this is an intended behaviour)
		string bullet_texture_path = this->model->getEnemyBasicBulletPath() + generateEnemyBulletSuffix() +".png";
		this->bullets.push_back(new DrawableObject(this->model->getLastBullet(),
													bullet_texture_path,
													this->screenSurface->format,
													this->renderer,
													enemy_bullet_frame,
													enemy_bullet_frame_delay));

		
	}
	for(int i = 0; i < this->bullets.size();i++)
	{
		if(!this->bullets.at(i)->draw())
		{
			//if we delete a bullet, we must add an explosion
			addExplosion(this->bullets.at(i)->getObjectX(),this->bullets.at(i)->getObjectY());
			// printf("deleting entity in VIEW\n");
			delete this->bullets.at(i);
			this->bullets.erase(bullets.begin() + i);
		}
	}
	return;
}


void ClassicSpaceBattleView::renderExplosions()
{
	
	if(this->explosions.size()==0)
	{
		return;
	}
	else
	{
		for(int i = 0; i < this->explosions.size();i++)
		{
			if(!this->explosions.front()->draw())
			{
				//if the element must be deleted
				ExplosionDrawable* temp = this->explosions.front();
				this->explosions.pop();
				delete temp;
			}
			else
			{
				ExplosionDrawable* temp = this->explosions.front();
				this->explosions.pop();
				this->explosions.push(temp);
			}
		}
	}
	return;
}
void ClassicSpaceBattleView::renderHUD()
{

	for(int i = 0; i < this->fixedDrawableElements.size();i++)
	{
		this->fixedDrawableElements[i]->draw();
	}
	
	
	
	//score and lifes updates
	if(this->lastScore != this->model->getScore())
	{
		this->changingText[SCORE]->changeText(generateScoreString());
	}
	this->changingText[SCORE]->draw();
	//we update also life sprites here
	if(this->lifes != this->model->getPlayerLifes())
	{
		this->changingText[LIFES]->changeText(std::to_string(this->model->getPlayerLifes()));
		if(this->lifes>1)
		{
			PureDrawable* temp = this->lifesShips.back();
			this->lifesShips.pop_back();
			delete temp;
			// this->lifesShips.erase(this->lifesShips.end());
		}
		this->lifes = this->model->getPlayerLifes();


	}
	this->changingText[LIFES]->draw();

	if(lifesShips.size()!=0)
	{
		for(int i = 0;i < this->lifesShips.size(); i++)
		{
			this->lifesShips[i]->draw();
		}
	}


	return;
}

void ClassicSpaceBattleView::audioUpdate()
{
	//audio update; the music goes faster the less aliens there are
	AudioSource* currAudio = this->mainMusic.front();
	this->mainMusic.pop();
	this->mainMusic.push(currAudio);
	currAudio->play();
}

void ClassicSpaceBattleView::addExplosion(int x, int y)
{
	int scale_ratio = this->model->getGameBoard()->getScaleRatio();
	//we add different kind of explosion based on the y coordinate:
	//	-if it is near the upper hud, it is a type three explosion
	//	-if it is near the lower hud, it is a type two explosion
	//	-otherwise it is a type one explosion

	//all the explosion are adjusted to have the center in the x,y coordinate
	if(y <= this->model->getGameBoard()->getSpecialShipY() && y >= this->model->getGameBoard()->getUpperHud())
	{
		this->explosions.push(new TypeThreeExplosionDrawable((x-type_three_explosion_width*scale_ratio/2),y,type_three_explosion_width*scale_ratio,type_three_explosion_height*scale_ratio,this->screenSurface->format,this->renderer));
	}
	else if(y >= this->model->getGameBoard()->getShipYCenter() && y <= this->model->getGameBoard()->getLowerHud())
	{
		this->explosions.push(new TypeTwoExplosionDrawable((x-type_two_explosion_width*scale_ratio/2),y,type_two_explosion_width*scale_ratio,type_two_explosion_height*scale_ratio,this->screenSurface->format,this->renderer));
	}
	else
	{
		this->explosions.push(new TypeOneExplosionDrawable((x-type_one_explosion_width*scale_ratio/2),y,type_one_explosion_width*scale_ratio,type_one_explosion_height*scale_ratio,this->screenSurface->format,this->renderer));
	}
	return;
}

string ClassicSpaceBattleView::generateScoreString()
{
	this->lastScore = this->model->getScore();
	int tempScore = this->lastScore%1000;
	string scoreString = std::to_string(tempScore);
	string result = "0000";
	for(int i = 0; i < scoreString.size() ; i++)
	{

		result[result.size()-i-1] = scoreString[scoreString.size()-i-1];
	}
	return result;
}

string ClassicSpaceBattleView::generateEnemyBulletSuffix()
{
	int number = (std::rand() % enemy_bullets_type);
	return std::to_string(number + 1);
	
}


