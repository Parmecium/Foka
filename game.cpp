#include "main.h"
#include "functions.h"
#include "timer.h"
#include "splash.h"
#include "player.h"
#include "tile.h"
#include "map.h"
#include "game.h"

Game::Game(void)
{
    this->width = 860;
    this->height = 630;
    //this->width = 1060;
    //this->height = 880;
    this->caption = "Foka";
    this->isRunning = true;
    this->fps = 10;
    this->music = NULL;
    this->map = new Map(9000, 9000, this->width, this->height);
}

Game::~Game(void)
{
    delete this->map;

    // Free
    SDL_Quit();
}

void Game::init(void)
{
    // initialize SDL
    SDL_Init(SDL_INIT_EVERYTHING);

    // Get OpenGL memory usage
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // Caption of the window
    SDL_WM_SetCaption(this->caption.c_str(), NULL);

    // Size of window
    SDL_SetVideoMode(this->width, this->height, 32, SDL_OPENGL);

    // Specific the clear color
    //glClearColor(0, 0, 0, 1);   // Black color
    glClearColor(0.06, 0.06, 0.06, 1);

    // What portion of the screen we will display
    glViewport(0, 0, this->width, this->height);

    // Shadermodel
    glShadeModel(GL_SMOOTH);

    // 2D rendering
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Disable depth checking
    glDisable(GL_DEPTH_TEST);

    // Enable texture
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    std::cout << "OpenGL is initialize" << std::endl;

    // Load map
    //this->loadMap();
    std::cout << "Map is loaded" << std::endl;

    // Initialize texture
}

void Game::splash(void)
{
    Splash *splash = new Splash(this->width, this->height);
    splash->show();
    delete splash;
}

void Game::events(SDL_Event event)
{
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
            isRunning = false;
        //if(event.type = SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE)
            //isRunning = false;

        switch(event.type)
        {
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_DOWN:
                        map->getPlayer()->changeMoveState(PLAYER_MOVE_ADD, PLAYER_MOVE_DOWN);
                        break;
                    case SDLK_RIGHT:
                        map->getPlayer()->changeMoveState(PLAYER_MOVE_ADD, PLAYER_MOVE_RIGHT);
                        break;
                    case SDLK_UP:
                        map->getPlayer()->changeMoveState(PLAYER_MOVE_ADD, PLAYER_MOVE_UP);
                        break;
                    case SDLK_LEFT:
                        map->getPlayer()->changeMoveState(PLAYER_MOVE_ADD, PLAYER_MOVE_LEFT);
                        break;
                    case SDLK_s:
                        map->getPlayer2()->changeMoveState(PLAYER_MOVE_ADD, PLAYER_MOVE_DOWN);
                        break;
                    case SDLK_d:
                        map->getPlayer2()->changeMoveState(PLAYER_MOVE_ADD, PLAYER_MOVE_RIGHT);
                        break;
                    case SDLK_w:
                        map->getPlayer2()->changeMoveState(PLAYER_MOVE_ADD, PLAYER_MOVE_UP);
                        break;
                    case SDLK_a:
                        map->getPlayer2()->changeMoveState(PLAYER_MOVE_ADD, PLAYER_MOVE_LEFT);
                        break;
                    case SDLK_ESCAPE:
                        isRunning = false;
                        break;
                }
                break;
            case SDL_KEYUP:
                switch(event.key.keysym.sym)
                {
                    case SDLK_DOWN:
                        map->getPlayer()->changeMoveState(PLAYER_MOVE_DELETE, PLAYER_MOVE_DOWN);
                        break;
                    case SDLK_RIGHT:
                        map->getPlayer()->changeMoveState(PLAYER_MOVE_DELETE, PLAYER_MOVE_RIGHT);
                        break;
                    case SDLK_UP:
                        map->getPlayer()->changeMoveState(PLAYER_MOVE_DELETE, PLAYER_MOVE_UP);
                        break;
                    case SDLK_LEFT:
                        map->getPlayer()->changeMoveState(PLAYER_MOVE_DELETE, PLAYER_MOVE_LEFT);
                        break;
                    case SDLK_s:
                        map->getPlayer2()->changeMoveState(PLAYER_MOVE_DELETE, PLAYER_MOVE_DOWN);
                        break;
                    case SDLK_d:
                        map->getPlayer2()->changeMoveState(PLAYER_MOVE_DELETE, PLAYER_MOVE_RIGHT);
                        break;
                    case SDLK_w:
                        map->getPlayer2()->changeMoveState(PLAYER_MOVE_DELETE, PLAYER_MOVE_UP);
                        break;
                    case SDLK_a:
                        map->getPlayer2()->changeMoveState(PLAYER_MOVE_DELETE, PLAYER_MOVE_LEFT);
                        break;
                }
                break;
        }
    }
}

void Game::mainLoop(void)
{
    // Initialization
    this->init();

    // Splash screen
    this->splash();

    // Initialize texture
    this->map->loadTexture();

    // Main loop
    std::cout << "Main loop is started\n";
    while(isRunning)
    {
        // Handle events
        this->events(event);

        // Logic
        this->map->logic();

        // Render
        glClear(GL_COLOR_BUFFER_BIT);
        glPushMatrix();
        glOrtho(0, this->width, 0, this->height, -1, 1);    // Set the matrix
        // Begin render
        this->map->render();
        // End render
        glPopMatrix();
        SDL_GL_SwapBuffers();
        SDL_Delay(fps);
    }
    std::cout << "Main loop end\n";
}
