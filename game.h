#ifndef GAME_H
#define GAME_H

class Game
{
    private:
        int width;
        int height;
        std::string caption;
        bool isRunning;
        int fps;
        SDL_Event event;
        Timer *timer;
        Map *map;
        Menu *mainMenu;

        void events(SDL_Event event);
        void init(void);
        void splash(void);
        //void loadMap(void);
        //void render(void);
        //void logic(void);
        void resize(int width, int height);

    public:
        Game(void);
        ~Game(void);
        void mainLoop(void);
};

#endif  // GAME_H
