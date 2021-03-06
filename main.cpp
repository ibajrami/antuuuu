#include <SDL2/SDL.h>
#include <iostream>

#include "Grille.h"
#include "Ant.h"
#include "Miel.h"


const int PIXEL_SIZE = 6;


int main(int argc, char* argv[]) {

    if(argc <= 1){
        std::cout<<"Arguments missing: WIDTH |  HEIGHT" <<std::endl;
    }

    const int SCREEN_WIDTH = atoi(argv[1]);
    const int SCREEN_HEIGHT = atoi(argv[2]);
    std::cout<< "SCREEN_WIDTH : " << SCREEN_WIDTH << std::endl;
    std::cout<< "SCREEN_HEIGHT: " << SCREEN_HEIGHT << std::endl;



    //Render window
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Surface* screenSurface = NULL;



    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("Init error ! SDL_Error: %s\n", SDL_GetError());
    } else {
        Uint32 startime = SDL_GetTicks();
        SDL_Event event;
        window = SDL_CreateWindow("ANTS ANTS PARTY !",
                                    SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED,
                                    SCREEN_WIDTH,
                                    SCREEN_HEIGHT,
                                    SDL_WINDOW_SHOWN
                                    );

        renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED| SDL_RENDERER_PRESENTVSYNC);
        SDL_SetRenderDrawColor(renderer,0x00,0x00,0x00,0x00);
        SDL_SetRenderDrawBlendMode(renderer,SDL_BLENDMODE_ADD);

        if (window == NULL) {
            printf("Window could not be created! SDL_Error:%s\n", SDL_GetError());
        } else {

            screenSurface = SDL_GetWindowSurface(window);


            Grille grille(renderer);

            int colonyX = 90;
            int colonyY = 90;

            Miel* miel = new Miel(&grille,10,10);
            int antNumber = 100;
            Ant*family[antNumber];
            for(int i=0;i<antNumber;i++){
                family[i] = new Ant(&grille,renderer);
                family[i]->setPosX(colonyX);
                family[i]->setPosY(colonyY);
            }

//            Ant* albert = new Ant(&grille,renderer);
//            albert->setPosX(colonyX);
//            albert->setPosY(colonyY);

//            Ant* albertine = new Ant(&grille,renderer);
//            albertine->setPosX(colonyX);
//            albertine->setPosY(colonyY);





            bool run = true;
            //Uint32 startTime = SDL_GetTicks();


            do{
                SDL_SetRenderDrawColor(renderer,0x00,0x00,0x00,0x00);
                SDL_RenderClear(renderer);

                while(SDL_PollEvent(&event) != 0){

                    if(event.type == SDL_QUIT){
                        run = false;
                    }else if(event.type == SDL_KEYDOWN){

                        switch(event.key.keysym.sym){
                            case SDLK_ESCAPE:
                            run = false;break;
                        }

                    }
                }


                grille.draw();
                grille.lowerPheromonLevel();
                grille.getCase(colonyX,colonyY)->setPheromoneTravelLevel(255);
                grille.getCase(colonyX+1,colonyY)->setPheromoneTravelLevel(255);
                grille.getCase(colonyX+2,colonyY)->setPheromoneTravelLevel(255);
                grille.getCase(colonyX,colonyY+1)->setPheromoneTravelLevel(255);
                grille.getCase(colonyX,colonyY+2)->setPheromoneTravelLevel(255);
                grille.getCase(colonyX+1,colonyY+1)->setPheromoneTravelLevel(255);
                grille.getCase(colonyX+2,colonyY+2)->setPheromoneTravelLevel(255);
                grille.getCase(colonyX+1,colonyY+2)->setPheromoneTravelLevel(255);
                grille.getCase(colonyX+2,colonyY+1)->setPheromoneTravelLevel(255);


                miel->update();

//                albert->move();
//                albertine->move();
                for(int i=0;i<antNumber;i++){
                    family[i]->move();
                }

                miel->draw(renderer);
                //colony
                SDL_SetRenderDrawColor( renderer, 0x00, 0xFF, 0x00, 0xFF );
                SDL_Rect fillColonyRect = { colonyX*6, colonyY*6 ,24, 24};
                SDL_RenderFillRect( renderer, &fillColonyRect );

                SDL_RenderPresent(renderer);
                //SDL_Delay(50);

            }while(run);
        }

    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
