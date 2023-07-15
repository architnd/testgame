#include <iostream>
#include <list>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>
#include <unistd.h>
//#include <SDL_rotozoom.h>

using namespace std;

struct ICar
{
    virtual ~ICar() = default;
    virtual void Start() = 0;
    virtual void Stop() = 0;
    virtual void Break() = 0;
    virtual void Accelerate() = 0;
    virtual void Show() = 0;
    virtual void ChangeCar(int i) = 0;
};

class Car : virtual public ICar
{
protected:
    int i;
    int speed_;
    SDL_Renderer *renderer_;
    SDL_Surface *imageSurface_;
    SDL_Texture *texture_;
    SDL_Rect destRect_;
    double angle_;

public:
    Car(SDL_Renderer *renderer)
    {
        speed_ = 0;
        renderer_ = renderer;
        imageSurface_ = IMG_Load("Car3.png");
        texture_ = SDL_CreateTextureFromSurface(renderer_, imageSurface_);
        destRect_.x = 885; // Initial X-coordinate
        destRect_.y = 540; // Initial Y-coordinate
        destRect_.w = 150; //imageSurface_->w; // Width
        destRect_.h = 150; //imageSurface_->h; // Height
        angle_ = 0.0;
    }
    ~Car() override = default;
    void Start() override
    {
    }
    void Stop() override
    {
        speed_ = 0;
    }
    void Break() override
    {
        if (speed_ > 0)
        {
            speed_ = speed_ - 5;
        }
        destRect_.x -= 2;
    }
    void Accelerate() override
    {
        speed_ = speed_ + 5;
        destRect_.x += 2;
    }
    void Show() override
    {
        //SDL_RenderClear(renderer_);
        SDL_RenderCopyEx(renderer_, texture_, NULL, &destRect_, angle_, NULL, SDL_FLIP_NONE);
        SDL_RenderPresent(renderer_);
    }
    void TurnRight()
    {
        angle_ = 20.0;
        if (destRect_.x < 1115)
        {
            //double d = 90.0;
            destRect_.x += 8;
        }
    }
    void TurnLeft()
    {
        angle_ = 340.0;
        if (destRect_.x > 655)
        {
            //double d = 90.0;
            destRect_.x -= 8;
        }
    }
    void ChangeCar(int i) override
    {
        if (i == 1)
        {
            imageSurface_ = IMG_Load("Car.png");
            texture_ = SDL_CreateTextureFromSurface(renderer_, imageSurface_);
        }
        else if (i == 2)
        {
            imageSurface_ = IMG_Load("Car2.png");
            texture_ = SDL_CreateTextureFromSurface(renderer_, imageSurface_);
        }
        else if (i == 3)
        {
            imageSurface_ = IMG_Load("Car3.png");
            texture_ = SDL_CreateTextureFromSurface(renderer_, imageSurface_);
        }
    }
};

class Formula1 : virtual public Car
{
public:
    Formula1(SDL_Renderer *renderer)
        : Car(renderer)
    {
    }
    ~Formula1() override = default;
    void Break() override
    {
        angle_ = 0.0;
        //if (speed_ > 0)
        //{
        //    speed_ = speed_ - 5;
        //}
        //destRect_.y += 8;
    }
    void Accelerate() override
    {
        angle_ = 0.0;
        //speed_ = speed_ + 5;
        //destRect_.y -= 8;
        //destRect_.x += cos(3.14)*4;
    }
};
// Menu constants
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define MENU_WIDTH 1200
#define MENU_HEIGHT 900
#define MENU_PADDING 100

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
TTF_Font *font = NULL;

// Menu options
const char *menuOptions[] = {
    "New Game",
    "Load Game",
    "Options",
    "Exit"};
int selectedOption = 0;

// Function to render text
SDL_Texture *renderText(const char *text, SDL_Color color)
{
    SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

// Function to draw the menu
void drawMenu()
{
    SDL_Color textColor = {255, 255, 255, 255};
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    int numOptions = sizeof(menuOptions) / sizeof(menuOptions[0]);
    int totalHeight = (TTF_FontHeight(font) + MENU_PADDING) * numOptions;
    int startY = (SCREEN_HEIGHT - totalHeight) / 2;

    for (int i = 0; i < numOptions; i++)
    {
        if (i == selectedOption)
        {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        }
        else
        {
            SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
        }

        SDL_Rect optionRect = {(SCREEN_WIDTH - MENU_WIDTH) / 2, startY + i * (TTF_FontHeight(font) + MENU_PADDING), MENU_WIDTH, TTF_FontHeight(font) + MENU_PADDING};
        SDL_RenderFillRect(renderer, &optionRect);

        SDL_Texture *optionTexture = renderText(menuOptions[i], textColor);
        int textWidth, textHeight;
        SDL_QueryTexture(optionTexture, NULL, NULL, &textWidth, &textHeight);

        SDL_Rect textRect = {optionRect.x + (optionRect.w - textWidth) / 2, optionRect.y + (optionRect.h - textHeight) / 2, textWidth, textHeight};
        SDL_RenderCopy(renderer, optionTexture, NULL, &textRect);
        SDL_DestroyTexture(optionTexture);
    }

    SDL_RenderPresent(renderer);
}
class Road
{
    SDL_Surface *image;
    SDL_Texture *texture;
    SDL_Rect destRect;

public:
    Road()
    {
        image = IMG_Load("road3.png");
        texture = SDL_CreateTextureFromSurface(renderer, image);
        destRect.x = 0;     // Initial X-coordinat
        destRect.y = -1000; // Initial Y-coordinate
        destRect.w = 1920;  //imageSurface_->w; // Width
        destRect.h = 3000;  //imageSurface_->h; // Height
    }
    void ShowRoad()
    {
        SDL_RenderCopyEx(renderer, texture, NULL, &destRect /*NULL*/, 0.0, NULL, SDL_FLIP_NONE);
        //SDL_RenderPresent(renderer);
        //SDL_DestroyTexture(texture);
        //SDL_FreeSurface(image);
    }
    void Accelerate1()
    {
        if (destRect.y != -10)
        {
            destRect.y += 10;
        }
        else if (destRect.y = -10)
        {
            destRect.y -= 1090;
        }
    }
    void Break1()
    {
        if (destRect.y != -1910)
        {
            destRect.y -= 10;
        }
        else if (destRect.y = -1910)
        {
            destRect.y += 1070;
        }
    }
    void timer()
    {
            Accelerate1();
            sleep(1);
    }
};

int main(int argc, char *argv[])
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL initialization failed. SDL Error: %s\n", SDL_GetError());
        return 1;
    }

    // Initialize SDL TTF
    if (TTF_Init() < 0)
    {
        printf("SDL TTF initialization failed. TTF Error: %s\n", TTF_GetError());
        return 1;
    }

    // Create window
    window = SDL_CreateWindow("SDL Menu", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, /*SCREEN_WIDTH*/ 1920, /*SCREEN_HEIGHT*/ 1080, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (window == NULL)
    {
        printf("Window creation failed. SDL Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        printf("Renderer creation failed. SDL Error: %s\n", SDL_GetError());
        return 1;
    }

    // Load font
    font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf", 42);
    if (font == NULL)
    {
        printf("Font loading failed. TTF Error: %s\n", TTF_GetError());
        return 1;
    }

    // Main loop
    SDL_Event event;
    int quit = 0;
    while (!quit)
    {
        drawMenu();
        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                quit = 1;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_UP:
                    selectedOption--;
                    if (selectedOption < 0)
                    {
                        selectedOption = sizeof(menuOptions) / sizeof(menuOptions[0]) - 1;
                    }
                    break;
                case SDLK_DOWN:
                    selectedOption++;
                    if (selectedOption >= sizeof(menuOptions) / sizeof(menuOptions[0]))
                    {
                        selectedOption = 0;
                    }
                    break;
                case SDLK_RETURN:
                case SDLK_RETURN2:
                case SDLK_KP_ENTER:
                    if (selectedOption == 0)
                    {
                        Road road;
                        //SDL_Init(SDL_INIT_VIDEO);
                        //SDL_Window *window = SDL_CreateWindow("My Car Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_FULLSCREEN);
                        //SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
                        //Car c1(renderer);
                        Formula1 c1(renderer);
                        //c1.Show();
                        while (1)
                        {
                            road.ShowRoad();
                            road.Accelerate1();
                            //SDL_RenderCopyEx(renderer, texture, NULL, /*&destRect*/ NULL, 0.0, NULL, SDL_FLIP_NONE);
                            //SDL_RenderCopy(renderer, texture, NULL, NULL);
                            //SDL_RenderPresent(renderer);
                            c1.Show();
                            if (SDL_PollEvent(&event))
                            {
                                if (event.type == SDL_QUIT)
                                {
                                    break;
                                }
                                else if (event.type == SDL_KEYDOWN)
                                {
                                    if (event.key.keysym.sym == SDLK_UP)
                                    {
                                        //c1.Accelerate();
                                        //road.Accelerate1();
                                        //road.timer();
                                    }
                                    else if (event.key.keysym.sym == SDLK_DOWN)
                                    {
                                        c1.Break();
                                        road.Break1();
                                    }
                                    else if (event.key.keysym.sym == SDLK_LEFT)
                                    {
                                        c1.TurnLeft();
                                    }
                                    else if (event.key.keysym.sym == SDLK_RIGHT)
                                    {
                                        c1.TurnRight();
                                    }
                                    else if (event.key.keysym.sym == SDLK_1)
                                    {
                                        c1.ChangeCar(1);
                                    }
                                    else if (event.key.keysym.sym == SDLK_2)
                                    {
                                        c1.ChangeCar(2);
                                    }
                                    else if (event.key.keysym.sym == SDLK_3)
                                    {
                                        c1.ChangeCar(3);
                                    }
                                    else if (event.key.keysym.sym == SDLK_ESCAPE)
                                    {
                                        break;
                                    }
                                }
                                //c1.Show();
                            }
                        }

                        //SDL_DestroyTexture(texture);
                        //SDL_FreeSurface(image);
                        //SDL_DestroyRenderer(renderer);
                        //SDL_DestroyWindow(window);

                        break;
                    }
                    else if (selectedOption == 3)
                    {
                        goto exit;
                    }
                }
            }
        }
    }
exit:
    // Cleanup
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
