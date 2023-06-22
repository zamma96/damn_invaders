#pragma once
#include <string>
#include <vector>
#include <SDL_image.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "Model.h"
#include <memory>
using std::string;
using std::vector;
using std::queue;

using namespace Entities;
using namespace GameEntities;



namespace ViewEntities
{
	enum HudLiveElements
	{
		SCORE,
		LIFES,
		NR_ELEMENTS
	};


	/*	Drawable is a virtual superclass that describe an object that can be drawn.
	 *  It exposes only two methods:
	 *		-draw(), which draws on the screen the object
	 *		-free(), that frees the object from memory
	 */
	class Drawable{
		protected:
			//the texture
			SDL_Texture* texture;
			//the texture path
			string path;
			//the renderer of the view
			SDL_Renderer* renderer;
			//information regarding the screen surface
			SDL_PixelFormat* format;
			//It is an array since it could be composed by different frames
			vector<SDL_Rect> srcRectangles;
			//how many frame this drawable has?
			int frameNumber;
			//how many frames per image?
			int frameDelay;
			//the current frame
			int currentFrame;
			SDL_Surface* loadSurface(string);
			virtual bool loadMedia() = 0;
		public:
			//Path, renderer, format, frameNumber, frameDelay
			Drawable(string, SDL_Renderer*,SDL_PixelFormat*,int,int);
			virtual bool draw() = 0;
			void free();
	};

	/*  Drawable Object is the first implementation of Drawable. It is the View Object used to draw living entities, such as Ship and bullets.
	 *  As such, it has a pointer to the entity which is drawing.
	 */
	class DrawableObject : public Drawable{
		private:

			//method used to load textures internally
			bool loadMedia();
			//not yet implemented
			void close();


		protected:
			//The entity drawn
			std::shared_ptr<LivingEntity> entity;
			//the source rectangle of the texture
			SDL_Rect srcRectangle;
			//the dest rectangle of the texture
			SDL_Rect dstRectangle;
			
			
		public:
			//Entity, path, format, renderer, frameNumber, frameDelay
			DrawableObject(std::shared_ptr<LivingEntity>,string,SDL_PixelFormat*,SDL_Renderer*,int,int);
			~DrawableObject();
			bool draw();
			int getObjectX();
			int getObjectY();

			


	};
	/* Text implementation of Drawable
	 *
	 */
	class DrawableText : public Drawable{
		private:
			//Text font
			TTF_Font* font;
			//Text color
			SDL_Color textColor;

			int width,height;
			int x,y;
			
			//path of the font 
			string fontPath;
			//text to be drawn
			string text;
			
			bool loadMedia();

		public:
			//TTF_font font, string text, x, y, format, renderer
			DrawableText(TTF_Font*,SDL_Color,string,int,int,SDL_PixelFormat*,SDL_Renderer*);
			~DrawableText();
			void changeText(string);
			bool draw();


	};

	/* Pure Drawable is an implementation of Drawable that doesnt have any entity that represents it in the game logic.
	 * For exammple, explosions when a bullet hits an object.  
	 */
	class PureDrawable : public Drawable{
		protected:
			int width,height;
			int x,y;

			bool loadMedia();
		public:
			//x, y, width, height, path, format, renderer,frameNumber,frameDelay
			PureDrawable(int,int,int,int,string,SDL_PixelFormat*,SDL_Renderer*,int, int);
			~PureDrawable();
			bool draw();

	};

	
	/* An explosion is a special kind of pure drawable because after the animation is over, must end is existence.
	*/
	class ExplosionDrawable : public PureDrawable{
		private:
			bool animationOver;
		public:
			//x,y,width,height,string,format,renderer
			ExplosionDrawable(int,int,int,int,string,SDL_PixelFormat*,SDL_Renderer*,int,int);
			bool draw();

	};

	/* Since there are three kind of explosions in the 1978 game, we create these 3 singleton classes to represent them.
	*/
	class TypeOneExplosionDrawable : public ExplosionDrawable{
		public:
			//x,y,width,height,format,renderer
			TypeOneExplosionDrawable(int,int,int,int,SDL_PixelFormat*,SDL_Renderer*);
	};

	class TypeTwoExplosionDrawable : public ExplosionDrawable{
		public:
			//x,y,width,height,format,renderer
			TypeTwoExplosionDrawable(int,int,int,int,SDL_PixelFormat*,SDL_Renderer*);
	};


	class TypeThreeExplosionDrawable : public ExplosionDrawable{
		public:
			//x,y,width,height,format,renderer
			TypeThreeExplosionDrawable(int,int,int,int,SDL_PixelFormat*,SDL_Renderer*);
	};


	/*	The logic behind an audio source is similar, but is simplier.
	*/
	class AudioSource {
		private:
			Mix_Chunk* sound;
			string path;

			void loadMedia();

		public:
			AudioSource(string path);
			~AudioSource();
			void play();
			void free();

	};

	/* Classic Space Battle View is the class that take care of showing a classic space battle. It has access to the Model, the game logic, to gain information
	*  on what has changed from last frame and to be updated accordingly.
	*/
	class ClassicSpaceBattleView{
		private:
			bool basicInit();
			bool spaceBattleInit(bool);
			bool audioInit(bool);
			void createShields();
			void initializeSingleShield(int);
			void createHudElements();
			void close();
			/**private methods to divide the different entities to be drawn**/
			void renderEnemies();
			void renderPlayer();
			void renderEntities();
			void renderShields();
			void renderBullets();
			void renderExplosions();
			void renderHUD();
			void renderPauseElements();
			void audioUpdate();
			void addExplosion(int,int);
			string generateScoreString();

			string generateEnemyBulletSuffix();

		protected:
			vector<std::shared_ptr<DrawableObject>> enemies;
			vector<std::shared_ptr<DrawableObject>> entities;
			vector<std::shared_ptr<DrawableObject>> bullets;
			vector<vector<std::pair<std::shared_ptr<DrawableObject>, std::shared_ptr<DrawableObject>>>> shields;
			vector< std::shared_ptr<Drawable>> fixedDrawableElements;
			vector< std::shared_ptr<Drawable>> pauseDrawableElements;
			vector< std::shared_ptr<PureDrawable>> lifesShips;
			vector< std::shared_ptr<DrawableText>> changingText;
			queue<ExplosionDrawable*> explosions;
			// vector<DrawableText*> changingText;
			DrawableObject *player;
			ClassicSpaceBattle* model;


			//---SOUND----//
			queue<std::shared_ptr<AudioSource>> mainMusic;
			AudioSource* playerShipExplosionSFX;
			AudioSource* enemyShipExplosionSFX;
			AudioSource* projectileFiredSFX;
			int framesSinceLastAudio;
			int currentFrameTreshold;
			int lifesLastFrame;


			int lastScore;
			int lifes;

			TTF_Font* hudFont = NULL;
			SDL_Window* window = NULL;
			SDL_Renderer* renderer = NULL;
			SDL_Surface* screenSurface = NULL;


		public:
			ClassicSpaceBattleView(ClassicSpaceBattle*);
			~ClassicSpaceBattleView();
			void addNewPlayerBullet();
			void update();
			bool changeModelAndRestart(ClassicSpaceBattle*);
			


	};
}