#ifndef GAMESTATE_INCLUDED
#define GAMESTATE_INCLUDED

#include <SDL.h>
enum GameStates
{
    STATE_NULL,
    STATE_INTRO,
    STATE_TITLE,
    STATE_GREEN_OVERWORLD,
    STATE_RED_ROOM,
    STATE_BLUE_ROOM,
    STATE_EXIT,
};

class GameState
{
    public:
    virtual void handle_events() = 0;
    virtual void logic() = 0;
    virtual void render() = 0;
    virtual ~GameState(){};
};

class Intro : public GameState
{
    private:
    SDL_Surface *background;

    SDL_Surface *message;
	
//std::stack<GameState*> states;
	
    public:
    Intro();
    ~Intro();

    void handle_events();
    void logic();
    void render();
};

class Title : public GameState
{
    private:
    SDL_Surface *background;

    SDL_Surface *message;

    public:
    Title();
    ~Title();

    void handle_events();
    void logic();
    void render();
};

class OverWorld : public GameState
{
    private:
    const static int LEVEL_WIDTH = 1280;
    const static int LEVEL_HEIGHT = 960;

    SDL_Surface *background;


    public:
    OverWorld( int prevState );

    ~OverWorld();

    void handle_events();
    void logic();
    void render();
};


#endif