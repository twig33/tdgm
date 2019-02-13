//эм хз как пользоваться графикменежером поетому пока некомпилится
#include "gamestate.h"
#include "graphics.h"
#include <stack>
#include <SDL.h>

SDL_Event event;
int stateID = STATE_NULL;
int nextState = STATE_NULL;	
GameState *currentState = NULL;
void set_next_state( int newState );

Intro::Intro()
{
    //background = loadFromPath( "introbg.png" );

   // message = TTF_RenderText_Solid( font, "...", textColor );
}

Intro::~Intro()
{
    SDL_FreeSurface( background );
    SDL_FreeSurface( message );
}

void Intro::handle_events()
{
    while( SDL_PollEvent( &event ) )
    {
        if( event.type == SDL_QUIT )
        {
            set_next_state( STATE_EXIT );
        }
        else if( ( event.type == SDL_KEYDOWN ) && ( event.key.keysym.sym == SDLK_RETURN ) )
        {
            set_next_state( STATE_TITLE );
        }
    }
}

void Intro::logic()
{
	
}

void Intro::render()
{
    //apply_surface( 0, 0, background, screen );

    //apply_surface( ( SCREEN_WIDTH - message->w ) / 2, ( SCREEN_HEIGHT - message->h ) / 2, message, screen );
}

Title::Title()
{
    //background = loadFromPath( "titlebg.png" );

 //   message = TTF_RenderText_Solid( font, "еуые", textColor );
}

Title::~Title()
{
    SDL_FreeSurface( background );
    SDL_FreeSurface( message );
}

void Title::handle_events()
{
    while( SDL_PollEvent( &event ) )
    {
        if( event.type == SDL_QUIT )
        {
            set_next_state( STATE_EXIT );
        }
        else if( ( event.type == SDL_KEYDOWN ) && ( event.key.keysym.sym == SDLK_RETURN ) )
        {
            set_next_state( STATE_GREEN_OVERWORLD );
        }
    }
}

void Title::logic()
{
	//сдл полл евент иф ентер поменять стейт или типо того 
}

void Title::render()
{
    //apply_surface( 0, 0, background, screen );

    //apply_surface( ( SCREEN_WIDTH - message->w ) / 2, ( SCREEN_HEIGHT - message->h ) / 2, message, screen );
}

OverWorld::OverWorld( int prevState )
{
    //background = loadFromPath( "greenoverworld.png" );

    }


OverWorld::~OverWorld()
{
    SDL_FreeSurface( background );
}

void OverWorld::handle_events()
{
    while( SDL_PollEvent( &event ) )
    {
			//проверка инпута от игрока

        if( event.type == SDL_QUIT )
        {
            set_next_state( STATE_EXIT );
        }
    }
}

void OverWorld::logic()
{
    //мувмент тд
}

void OverWorld::render()
{
    //сет камера и рендер
}

void change_state()				//заменить както стаком
{
    
    if( nextState != STATE_NULL )
    {
        if( nextState != STATE_EXIT )
        {
            delete currentState;
        }

        switch( nextState )
        {
            case STATE_TITLE:
                currentState = new Title();
                break;

            case STATE_GREEN_OVERWORLD:
                currentState = new OverWorld( stateID );
                break;
        }

        stateID = nextState;
        nextState = STATE_NULL;
    }
}

void set_next_state( int newState )
{
    //If the user doesn't want to exit
    if( nextState != STATE_EXIT )
    {
        //Set the next state
        nextState = newState;
    }
}

