#if 1
#include <iostream>
#include <list>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

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

public:
    Car(SDL_Renderer *renderer)
    {
        speed_ = 0;
        renderer_ = renderer;
        imageSurface_ = IMG_Load("Car.png");
        texture_ = SDL_CreateTextureFromSurface(renderer_, imageSurface_);
        destRect_.x = 100; // Initial X-coordinate
        destRect_.y = 260; // Initial Y-coordinate
        destRect_.w = 100; //imageSurface_->w; // Width
        destRect_.h = 100; //imageSurface_->h; // Height
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
        SDL_RenderCopy(renderer_, texture_, NULL, &destRect_);
        SDL_RenderPresent(renderer_);
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
        if (speed_ > 0)
        {
            speed_ = speed_ - 5;
        }
        destRect_.x -= 4;
    }
    void Accelerate() override
    {
        speed_ = speed_ + 5;
        destRect_.x += 4;
    }
};
#endif
#if 1
// Menu constants
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define MENU_WIDTH 200
#define MENU_HEIGHT 300
#define MENU_PADDING 20

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
    window = SDL_CreateWindow("SDL Menu", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, /*SCREEN_WIDTH*/ 800, /*SCREEN_HEIGHT*/ 600, SDL_WINDOW_SHOWN);
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
    font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf", 24);
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
                        //SDL_Init(SDL_INIT_VIDEO);
                        //SDL_Window *window = SDL_CreateWindow("My Car Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_FULLSCREEN);
                        //SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
                        SDL_Surface *image = SDL_LoadBMP("image.bmp");
                        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
                        //Car c1(renderer);
                        Formula1 c1(renderer);
                        //c1.Show();
                        while (1)
                        {
                            SDL_RenderCopy(renderer, texture, NULL, NULL);
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
                                c1.Show();
                            }  
                        }

                        SDL_DestroyTexture(texture);
                        SDL_FreeSurface(image);
                        //SDL_DestroyRenderer(renderer);
                        //SDL_DestroyWindow(window);

                        break;
                    }
                }
            }
        }
    }

    // Cleanup
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
#endif