/**
 * \name main.c
  \brief nucleo del programa
  \author Agostini, Luca R1092
  \version 0.00
*/
//--------------
//-- Includes --
//--------------
#include <stdio.h>
#include <string.h>
#include "Data_1.h"

#define LVL_NOMBRE_LONG 50

int main (int argc, char *argv[])
{ 
  SDL_Surface *pantalla;
  SDL_Event event;
  
  struct char_data player_1;
  struct level_data level_1;
  struct label_data label_1;
  
  struct enemy_data enemy_1[BICHITOS_CANT_MAX];
  
  int aux = 1,i,j,TECLA_ESTADO,CHECK_ESTADO,SCREEN_ESTADO = FULL_ON;
  char level_label[LVL_NOMBRE_LONG];
  
  if(inicializar(enemy_1,&player_1,&level_1, &pantalla,&label_1) == FAIL)
    return FAIL;

  do {
	while (SDL_PollEvent( &event )) 
	{
	 
		switch (event.type) 
		{	
			case SDL_KEYDOWN: //si detecta un evento en el teclado
			  
				if(event.key.keysym.sym == ARRIBA_BOTON)
				  TECLA_ESTADO = ARRIBA;
				
				else if(event.key.keysym.sym == ABAJO_BOTON)
				  TECLA_ESTADO = ABAJO;
				
				else if(event.key.keysym.sym == IZQ_BOTON)
				  TECLA_ESTADO = IZQ;
				
				else if(event.key.keysym.sym == DER_BOTON)
				  TECLA_ESTADO = DER;
				
				else if(event.key.keysym.sym == POW_BOTON)
				  disparar_proyectil(&player_1);
				
				else if(event.key.keysym.sym == SCREEN_SWITCH_BOTON)
				{
				  if(SCREEN_ESTADO == FULL_OFF)
				  {
				    SCREEN_ESTADO = FULL_ON;
				    pantalla = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_FULLSCREEN );
				  }
				  else
				  {
				    SCREEN_ESTADO = FULL_OFF;
				    pantalla = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
				  }
				  SDL_Flip(pantalla);
				}
				
				else if(event.key.keysym.sym == LEVEL_UP_BOTON)
				{	//para test de nivel(lvl up)
				  for(i = 0; i < BICHITOS_CANT_MAX; i++)
				    enemy_1[i].enemy_estado = EN_JAIL;
	
				}
				
				else if(event.key.keysym.sym == EXIT_BOTON)
				  aux = 0;
				
				break;
					
			case SDL_QUIT:
				aux = 0;
				break;
			default:
			  TECLA_ESTADO = -1;
				break;
		}		
	}
	
	if(TECLA_ESTADO == ARRIBA)
	  char_actualizar_data(&player_1,ARRIBA,&level_1);
				
	else if(TECLA_ESTADO == ABAJO)
	  char_actualizar_data(&player_1,ABAJO,&level_1);
				
	else if(TECLA_ESTADO == IZQ)
	  char_actualizar_data(&player_1,IZQ,&level_1);
				
	else if(TECLA_ESTADO == DER)
	  char_actualizar_data(&player_1,DER,&level_1);
		
	refresco_pantalla(enemy_1,&player_1,&level_1,pantalla,&label_1);
	CHECK_ESTADO = check_game(&player_1,enemy_1,&level_1);
	
	
	if(CHECK_ESTADO == GAME_OVER)
	  aux = 0;
	else if(CHECK_ESTADO == LEVEL_UP)
	{
	   //--------- Level : n (mensaje)-------//
	   sprintf(level_label,"- Level: %i -",level_1.level_num);
	   (label_1.Level_titulo) = TTF_RenderText_Solid( label_1.fondo, level_label, label_1.textColor);
	   SDL_BlitSurface( label_1.Level_titulo , NULL, pantalla, &(label_1.rec_titulo));
	   SDL_Flip(pantalla);
	   SDL_Delay(2500);
	
	}
	else if(CHECK_ESTADO == LVL_MAX)
	{
	    label_1.rec_titulo.x = 20;
	    sprintf(level_label,"-¡¡Ganaste!!, Gracias por jugar!!-",level_1.level_num);
	    (label_1.Level_titulo) = TTF_RenderText_Solid( label_1.fondo, level_label, label_1.textColor);
	    SDL_BlitSurface( label_1.Level_titulo , NULL, pantalla, &(label_1.rec_titulo));
	    SDL_Flip(pantalla);
	    SDL_Delay(2500);
	    label_1.rec_titulo.x = 200;
	    label_1.rec_titulo.y -= 50;
	    aux = 0;
	}

   } while (aux == 1);
  
  //--------- game over (mensaje) ------//
  sprintf(level_label,"- Game Over ! -",level_1.level_num);
  (label_1.Level_titulo) = TTF_RenderText_Solid( label_1.fondo, level_label, label_1.textColor);
  SDL_BlitSurface( label_1.Level_titulo , NULL, pantalla, &(label_1.rec_titulo));
  SDL_Flip(pantalla);
  SDL_Delay(2000);
	  
  //-- Libero las imagenes --
  
  SDL_FreeSurface(player_1.sprite);
  SDL_FreeSurface(player_1.proyectil);
  SDL_FreeSurface(label_1.Level_data);
  SDL_FreeSurface(label_1.Level_nom);
  SDL_FreeSurface(label_1.score_nom);
  SDL_FreeSurface(label_1.score_data);
  SDL_FreeSurface(label_1.Pos_nom);
  SDL_FreeSurface(label_1.Pos_data);
  SDL_FreeSurface(label_1.Vidas_nom);
  SDL_FreeSurface(label_1.Vidas_data);
  SDL_FreeSurface(label_1.Level_titulo);
  SDL_FreeSurface(label_1.time);
  SDL_FreeSurface(label_1.Luk);
  SDL_FreeSurface(level_1.background);
  
  for(i = 0; i < BICHITOS_CANT_MAX; i++)
  {
    SDL_FreeSurface(enemy_1[i].sprite);
    
    for(j = 0; j < CANTIDAD_BOMBAS_MAX; j++) 
      SDL_FreeSurface(enemy_1[i].enemy_bomb[j].bomba_sprite);
  }
  
  for(i = 0;i < B_TOTAL; i++)
    SDL_FreeSurface(level_1.bloque_imagen[i]);

  for(i = 0 ; i < JAIL_DIM; i++)
    SDL_FreeSurface(level_1.jail_img[i]);
  
  //Cierro la fuente
  TTF_CloseFont(label_1.fondo);
  
  SDL_FreeSurface(pantalla); 
  
  //-- Cierro todo --
  TTF_Quit();
  SDL_Quit();
  
  return GAME_OVER;
}