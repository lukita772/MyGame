//-----INCLUDES------//
#include "Data_1.h"
#include <time.h>
#include <stdio.h>
//------------------//
/**
 * \fn dibujar_mapa
  \brief funcion que recive los datos del mapa y los dibuja en pantalla
  \author Agostini, Luca R1092
  \version 0.00
*/
void dibujar_mapa( struct level_data *level,SDL_Surface* destination ) 
{
    int i=0;
    SDL_BlitSurface( level->background , NULL, destination, &(level->bloque_rec[22]) ); 
    
    // Bliteo map
    while(i < (B_TOTAL))
    {
      SDL_BlitSurface( level->bloque_imagen[i] , NULL, destination, &(level->bloque_rec[i]) ); 
      i++;
    }
    
    // Blitteo jail
    i = 0;
    while(i< (JAIL_DIM))
    {
      SDL_BlitSurface( level->jail_img[i] , NULL, destination, &(level->jail_rect[i]) );
      i++;
    }
    return;
} 
/**
 * \fn dibujar_entidad
  \brief funcion que dibuja todas las entidades animadas en la pantalla
  \author Agostini, Luca R1092
  \version 0.00
*/
void dibujar_entidad( struct enemy_data *e,struct char_data *p, SDL_Surface* destination,struct level_data *lvl ) 
{ 
  int i,j;
  
  for(j = 0; j < BICHITOS_CANT_MAX;j++)
  {
   
    //bliteo bombas
    for( i= 0; i < CANTIDAD_BOMBAS_MAX;i++)
    {
      //printf("estado bomba %i: (%i)\n",i,e->enemy_bomb[i].estado);
      if((e+j)->enemy_bomb[i].estado == BOMB_ON)
      {
	//printf("entreee\n");
	SDL_BlitSurface((e+j)->enemy_bomb[i].bomba_sprite, NULL, destination, &((e+j)->enemy_bomb[i].bomba_rect));
      }
    }
    //blitteo bichito
    SDL_BlitSurface( (e+j)->sprite, &((e+j)->frame[enemy_movimiento((e+j),lvl)]), destination, &((e+j)->enemy_rect) );
    
  }
    //bliteo mi pj
    SDL_BlitSurface( p->sprite, &(p->frame[p->frame_actual[4]]), destination, &(p->char_rect) ); 
    
    //bliteo proyectil (si esta activado)
    if(p->proyectil_estado == proyectil_ON)
      SDL_BlitSurface( p->proyectil, NULL, destination, &(p->proyectil_rec) ); 
}

/**
 * \fn muestra_datos_juego
  \brief funcion que actualiza los labels del juego
  \author Agostini, Luca R1092
*/
void muestra_datos_juego(struct char_data *p,struct label_data *l,SDL_Surface *pantalla,struct level_data *lev)
{
  char datos_cadena[30];
  
  sprintf(datos_cadena,"- %i -",lev->level_num);
  l->Level_data = TTF_RenderText_Solid( l->fondo, datos_cadena, l->textColor);
  
  sprintf(datos_cadena,"%i pts",p->score);
  l->score_data = TTF_RenderText_Solid( l->fondo, datos_cadena, l->textColor);
  
  sprintf(datos_cadena,"(%i,%i)",p->char_rect.x,p->char_rect.y);
  l->Pos_data = TTF_RenderText_Solid( l->fondo, datos_cadena, l->textColor);

  sprintf(datos_cadena,".: %i :.",p->player_vidas);
  l->Vidas_data = TTF_RenderText_Solid( l->fondo, datos_cadena, l->textColor);
  
  if(lev->time > 10)
  {
    sprintf(datos_cadena,"Tiempo: %i seg.",time_fn(lev));
    l->time = TTF_RenderText_Solid( l->fondo, datos_cadena, l->textColor);
  }
  else
  {
    sprintf(datos_cadena,"Tiempo: %i seg. (HURRY UP!!)",time_fn(lev));
    l->time = TTF_RenderText_Solid( l->fondo, datos_cadena, l->textColor);
  }
  SDL_BlitSurface( l->time , NULL, pantalla, &(l->rec_time) );
  
  SDL_BlitSurface( l->Level_nom , NULL, pantalla, &(l->rec[0]) );
  SDL_BlitSurface( l->Level_data , NULL, pantalla, &(l->rec[1]) );
  SDL_BlitSurface( l->score_nom , NULL, pantalla, &(l->rec[2]) );
  SDL_BlitSurface( l->score_data , NULL, pantalla, &(l->rec[3]) );
  SDL_BlitSurface( l->Pos_nom, NULL, pantalla, &(l->rec[4]) );
  SDL_BlitSurface( l->Pos_data , NULL, pantalla, &(l->rec[5]) );
  SDL_BlitSurface( l->Vidas_nom , NULL, pantalla, &(l->rec[6]) );
  SDL_BlitSurface( l->Vidas_data , NULL, pantalla, &(l->rec[7]) );
  SDL_BlitSurface( l->Luk , NULL, pantalla, &(l->rec[8]) );
  
  return;
}

/**
 * \fn refresco_pantalla
  \brief funcion que actualiza los datos continuamente 
  \author Agostini, Luca R1092
  \version 0.00
*/
void refresco_pantalla(struct enemy_data *e,struct char_data *p,struct level_data *l,SDL_Surface *pantalla,struct label_data *labels)
{ 
  dibujar_mapa( l, pantalla );
  dibujar_entidad( e,p, pantalla,l );
  muestra_datos_juego(p,labels,pantalla,l);  
  
  SDL_Flip( pantalla );             //refrescar
  SDL_FillRect( pantalla, 0 ,0);    //borrar restos de imagenes anteriores
  return;
}
 
