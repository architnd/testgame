#include <iostream>
#include <list>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
using namespace std;

class Car
{
private:
   int speed_;
   SDL_Renderer *renderer_;
   SDL_Surface *imageSurface_;
   SDL_Texture *texture_;
   SDL_Rect destRect_;

public:
   Car(SDL_Renderer *renderer)
   {
      //cout << "I am a Constructor\n";
      speed_ = 0;
      renderer_ = renderer;
      imageSurface_ = IMG_Load("Car2.png");
      texture_ = SDL_CreateTextureFromSurface(renderer_, imageSurface_);
      destRect_.x = 100; // Initial X-coordinate
      destRect_.y = 100; // Initial Y-coordinate
      destRect_.w = 100; //imageSurface_->w; // Width
      destRect_.h = 100; //imageSurface_->h; // Height
   }
   ~Car()
   {
      //cout << "I am a Destructor\n";
   }
   void Start()
   {
      //cout << "Start\n";
   }
   void Stop()
   {
      //cout << "Stop\n";
      speed_ = 0;
   }
   void Break()
   {
      //cout << "Break\n";
      if (speed_ > 0)
      {
         speed_ = speed_ - 5;
         destRect_.x -= 1;
      }
   }
   void Accelerate()
   {
      // cout << "Accelerate\n";
      speed_ = speed_ + 5;
      destRect_.x += 1;
   }
   void Show()
   {
      SDL_RenderClear(renderer_);
      SDL_RenderCopy(renderer_, texture_, NULL, &destRect_);
      SDL_RenderPresent(renderer_);
   }
};

int main()
{
   SDL_Init(SDL_INIT_VIDEO);
   SDL_Window *window = SDL_CreateWindow("My Car Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, 0);

   SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
   Car c1(renderer);
   c1.Show();
   SDL_Event event;
   while (1)
   {
      SDL_PollEvent(&event);
      if (event.type == SDL_QUIT)
      {
         break;
      }
      else if (event.type == SDL_KEYDOWN)
      {
         if (event.key.keysym.sym == SDLK_UP)
         {
         }
         else if (event.key.keysym.sym == SDLK_DOWN)
         {
         }
         else if (event.key.keysym.sym == SDLK_LEFT)
         {
            c1.Break();
         }
         else if (event.key.keysym.sym == SDLK_RIGHT)
         {
            c1.Accelerate();
         }
      }
      c1.Show();
   }
   SDL_DestroyRenderer(renderer);
   SDL_DestroyWindow(window);
   SDL_Quit();
   return 0;
}
