#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>

void dessin(char * filename, SDL_Renderer * ren);
SDL_Texture* loadTexture(char * filename, SDL_Renderer *ren);

const int WIDTH  = 640;
const int HEIGHT = 480;
 
int main(int argc, char** argv){

  	SDL_Window *win = 0;
	SDL_Renderer *ren = 0;
 
	/* Initialisation de la SDL. Si ça se passe mal, on quitte */
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0){
      	fprintf(stderr,"Erreur initialisation\n");
      	return -1;
  	}

	/* Création de la fenêtre et du renderer */
  	SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &win, &ren); // SDL_WINDOW_SHOWN|SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC,&win,&ren);
 
  	if (!win || !ren){
		fprintf(stderr,"Erreur à la création des fenêtres\n");
		SDL_Quit();
		return -1;
	}

  	/* Affichage du fond noir */
  	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
  	SDL_RenderClear(ren);
  	SDL_RenderPresent(ren);

  	SDL_Delay(2000);
  	dessin("arch.bmp",ren);
  	SDL_Delay(2000);
  	dessin("a.bmp",ren);
  	SDL_Delay(2000);
	SDL_RenderClear(ren);
	dessin("b.bmp",ren);
  	SDL_Delay(2000);
 
  	SDL_DestroyRenderer(ren);
  	SDL_DestroyWindow(win);
  	SDL_Quit();
  	return 0;
}

SDL_Texture* loadTexture(char * filename, SDL_Renderer *ren){
    SDL_Texture *texture = 0;
    SDL_Surface *loadedImage = 0;
    loadedImage = SDL_LoadBMP(filename);
    
    if (!loadedImage){
        fprintf(stderr,"Erreur chargement image : %s\n",SDL_GetError());
        return 0;
    }
 
    texture = SDL_CreateTextureFromSurface(ren, loadedImage);
    SDL_FreeSurface(loadedImage);

    if (texture == 0){
        fprintf(stderr,"Erreur creation texture : %s\n",SDL_GetError());
      	return 0;
   	}
    return texture;
}

void dessin(char * filename, SDL_Renderer * ren){
	SDL_Texture * tex = 0;
  	SDL_Rect dst;
 
  	tex = loadTexture(filename,ren);
  	if (tex == 0) return;
 
  	// Récupération de la taille de la texture 
  	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
 
  	// Centrage
  	dst.x = (WIDTH - dst.w)/2;
  	dst.y = (HEIGHT- dst.h)/2;
 
  	// Affichage
  	SDL_RenderCopy(ren, tex, NULL, &dst);
  	SDL_RenderPresent(ren);
}
