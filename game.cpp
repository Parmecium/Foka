#include "main.h"
#include "splash.h"
#include "player.h"
#include "tile.h"
#include "game.h"

Game::Game(void)
{
    //this->width = 1060;
    //this->height = 880;
    this->width = 500;
    this->height = 500;
    this->caption = "Foka";
    this->isRunning = true;
    this->fps = 10;
    this->player = new Player(25, 25);
    this->player2 = new Player(75, 25);
    this->music = NULL;
}

Game::~Game(void)
{
    int i;

    delete this->player;
    for(i = 0; i < this->tile.size(); i++)
    {
        delete this->tile[i];
    }

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
    glClearColor(0.08, 0, 0, 1);

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
    this->loadMap();
    std::cout << "map is loaded" << std::endl;

    // Initialize texture
    this->player->loadTexture("foka");
    this->player2->loadTexture("foka");
    std::cout << "texture is initialize" << std::endl;
}

void Game::splash(void)
{
    Splash *splash = new Splash(this->width, this->height);
    splash->show();
    delete splash;
}

void Game::loadMap(void)
{
    int i;

    // Test walls
    this->tile.push_back(new Tile(100, 100, 50, 100, TILE_WALL_RIGHT));
    this->tile.push_back(new Tile(150, 200, 50, 100, TILE_WALL_LEFT));

    // Wall sides
    for(i = 0; i < this->width; i += 100)
    {
        this->tile.push_back(new Tile(0, i, 24, 100, TILE_WALL_RIGHT));
        this->tile.push_back(new Tile(this->width - 24, i, 25, 100, TILE_WALL_LEFT));
    }
    // Wall down and up
    for(i = 0; i < this->height; i+= 100)
    {
        this->tile.push_back(new Tile(i, 0, 100, 24, TILE_WALL_UP));
    }

    // Load textures for tiles
    for(i = 0; i < this->tile.size(); i++)
        this->tile[i]->loadTexture();
}

void Game::render(void)
{
    int i;

    this->player->render();
    this->player2->render();
    for(i = 0; i < this->tile.size(); i++)
    {
        this->tile[i]->render();
    }
}

void Game::logic(void)
{
    int i;

    player->move();
    player->collision(this->width, this->height);
    player2->move();
    player2->collision(this->width, this->height);
    for(i = 0; i < this->tile.size(); i++)
    {
        //player->collision(tile[i]);
        this->tile[i]->collision(player);
        this->tile[i]->collision(player2);
    }
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
                        player->changeMoveState(PLAYER_MOVE_ADD, PLAYER_MOVE_DOWN);
                        break;
                    case SDLK_RIGHT:
                        player->changeMoveState(PLAYER_MOVE_ADD, PLAYER_MOVE_RIGHT);
                        break;
                    case SDLK_UP:
                        player->changeMoveState(PLAYER_MOVE_ADD, PLAYER_MOVE_UP);
                        break;
                    case SDLK_LEFT:
                        player->changeMoveState(PLAYER_MOVE_ADD, PLAYER_MOVE_LEFT);
                        break;
                    case SDLK_s:
                        player2->changeMoveState(PLAYER_MOVE_ADD, PLAYER_MOVE_DOWN);
                        break;
                    case SDLK_d:
                        player2->changeMoveState(PLAYER_MOVE_ADD, PLAYER_MOVE_RIGHT);
                        break;
                    case SDLK_w:
                        player2->changeMoveState(PLAYER_MOVE_ADD, PLAYER_MOVE_UP);
                        break;
                    case SDLK_a:
                        player2->changeMoveState(PLAYER_MOVE_ADD, PLAYER_MOVE_LEFT);
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
                        player->changeMoveState(PLAYER_MOVE_DELETE, PLAYER_MOVE_DOWN);
                        break;
                    case SDLK_RIGHT:
                        player->changeMoveState(PLAYER_MOVE_DELETE, PLAYER_MOVE_RIGHT);
                        break;
                    case SDLK_UP:
                        player->changeMoveState(PLAYER_MOVE_DELETE, PLAYER_MOVE_UP);
                        break;
                    case SDLK_LEFT:
                        player->changeMoveState(PLAYER_MOVE_DELETE, PLAYER_MOVE_LEFT);
                        break;
                    case SDLK_s:
                        player2->changeMoveState(PLAYER_MOVE_DELETE, PLAYER_MOVE_DOWN);
                        break;
                    case SDLK_d:
                        player2->changeMoveState(PLAYER_MOVE_DELETE, PLAYER_MOVE_RIGHT);
                        break;
                    case SDLK_w:
                        player2->changeMoveState(PLAYER_MOVE_DELETE, PLAYER_MOVE_UP);
                        break;
                    case SDLK_a:
                        player2->changeMoveState(PLAYER_MOVE_DELETE, PLAYER_MOVE_LEFT);
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

    // Main loop
    std::cout << "Main loop is started\n";
    while(isRunning)
    {
        // Handle events
        this->events(event);

        // Logic
        this->logic();

        // Render
        glClear(GL_COLOR_BUFFER_BIT);
        glPushMatrix();
        glOrtho(0, this->width, 0, this->height, -1, 1);    // Set the matrix
        // Begin render
        this->render();
        // End render
        glPopMatrix();
        SDL_GL_SwapBuffers();
        SDL_Delay(fps);
    }
    std::cout << "Main loop end\n";
}
