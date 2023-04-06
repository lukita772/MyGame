
//-----INCLUDES------//
#include "Data_1.h"
#include <time.h>
#include <stdio.h>
//------------------//

/**
 * \fn check_colicion
  \brief funcion que busca continuamente coliciones, si se detectan, retornara un "MOVE_NO" , lo que significara
  que el objeto no tiene permiso de moverse
  \author Agostini, Luca R1092
*/
int check_colicion(struct char_data *p,struct level_data *l)
{
  int i;
  
  // Colicion char-bloques
  for(i=0;i < B_TOTAL ; i++)
  {
    //solamente compruebo si hay coliciones con los bloques de color
    if(l->mat_data[i] != NULO_BLOQUE)
    {
      //si las coordenadas del pj estan dentro del rango de las coordenadas de un bloque de color
       if((p->char_rect.x >= l->bloque_rec[i].x - B_W) && (p->char_rect.x <=  (l->bloque_rec[i].x+ B_W))
	&&(p->char_rect.y >= l->bloque_rec[i].y - B_H) && (p->char_rect.y <= (l->bloque_rec[i].y + B_H)))  
	  return MOVE_NO; //da la orden de no mover el pj

    }
  }  
  
  return MOVE_OK; //si se chequio todo y no se detectaron coliciones en un punto, el movimiento es permitido
}
/**
 * \fn check_enemy_colicion
  \brief funcion que busca continuamente coliciones, si se detectan, retornara un "MOVE_NO" , lo que significara
  que el objeto no tiene permiso de moverse (sistema enemigo-mapa)
  \author Agostini, Luca R1092
*/
int check_enemy_colicion(struct enemy_data *e,struct level_data *l)
{
  int i,j;
  
  for(j = 0 ; j < BICHITOS_CANT_MAX; j ++)
  {
    
    for(i=0;i < B_TOTAL ; i++)
    {
      //solamente compruebo si hay coliciones con los bloques de color
      if(l->mat_data[i] != NULO_BLOQUE)
      {
	//si las coordenadas del bichito estan dentro del rango de las coordenadas de un bloque de color
	if(((e+j)->enemy_rect.x >= l->bloque_rec[i].x - B_W) && ((e+j)->enemy_rect.x <=  (l->bloque_rec[i].x+ B_W))
	  &&((e+j)->enemy_rect.y >= l->bloque_rec[i].y - B_H) && ((e+j)->enemy_rect.y <= (l->bloque_rec[i].y + B_H)))  
	    return MOVE_NO; //da la orden de no mover el bichito

      }
    }
    
    for(i=0;i < JAIL_DIM ; i++)
    {
      //solamente compruebo si hay coliciones con los bloques de color
      if(l->jail_mat_data[i] != NULO_BLOQUE)
      {
	//si las coordenadas del bichito estan dentro del rango de las coordenadas de un bloque de color
	if(((e+j)->enemy_rect.x >= l->jail_rect[i].x - JAIL_BLOQUE_ANCHO) && ((e+j)->enemy_rect.x <=  (l->jail_rect[i].x+ JAIL_BLOQUE_ANCHO))
	  &&((e+j)->enemy_rect.y >= l->jail_rect[i].y - JAIL_BLOQUE_LARGO) && ((e+j)->enemy_rect.y <= (l->jail_rect[i].y + JAIL_BLOQUE_LARGO)))  
	    return MOVE_NO; //da la orden de no mover el bichito

      }
    } 
  }
  
  return MOVE_OK; //si se chequio todo y no se detectaron coliciones en un punto, el movimiento es permitido
}
/**
 * \fn check_colicion_pj_bichitos
  \brief funcion que busca continuamente coliciones, si se detectan, retornara un "MOVE_NO" , lo que significara
  que el objeto no tiene permiso de moverse (sistema enemigo-personaje, bomba-personaje)
  \author Agostini, Luca R1092
*/
int check_colicion_pj_bichitos(struct enemy_data *e, struct char_data *p)
{
  int i;
  // Colicion pj - bichitos
  for(i = 0 ; i < BICHITOS_CANT_MAX; i++)
  {
    
      if(((e+i)->enemy_rect.x >= p->char_rect.x - pj_ancho) && ((e+i)->enemy_rect.x <=  (p->char_rect.x+ pj_ancho))
	  &&((e+i)->enemy_rect.y >= p->char_rect.y - pj_largo) && ((e+i)->enemy_rect.y <= (p->char_rect.y + pj_largo)))  
      {//comienza if
      
	  p->char_rect = p->origen;
	
	  p->player_vidas --; //descontar una vida
      
      }//termina if
    
  }
  // Colicion pj- bombas
  for(i = 0; i < (CANTIDAD_BOMBAS_MAX*BICHITOS_CANT_MAX); i++) //porque cada bichito tiene un max de bombs
  {
    //si existe colicion
    if(((e+i)->enemy_bomb->bomba_rect.x >= p->char_rect.x - pj_ancho) && ((e+i)->enemy_bomb->bomba_rect.x  <=  (p->char_rect.x+ pj_ancho))
	  &&((e+i)->enemy_bomb->bomba_rect.y  >= p->char_rect.y - pj_largo) && ((e+i)->enemy_bomb->bomba_rect.y <= (p->char_rect.y + pj_largo)))  
    {
      
	(e+i)->enemy_bomb->estado = BOMB_OFF;
	//la aislo
	(e+i)->enemy_bomb->bomba_rect.x = 600;
	(e+i)->enemy_bomb->bomba_rect.y = 600;
	
	p->char_rect = p->origen;
	
	p->player_vidas --; //descontar una vida
      
    }
  }
 
  return CHECK_OK;
}

void colicion_proyectil(struct char_data *p,struct level_data *l,struct enemy_data *e)
{
  int i;
  if(p->proyectil_estado == proyectil_ON) //si el proyectil fue disparado
  {
    
    for(i=0;i < B_TOTAL ; i++)
    {
      //solamente compruebo si hay coliciones con los bloques de color
      if(l->mat_data[i] != NULO_BLOQUE)
      {
	//si las coordenadas del pj estan dentro del rango de las coordenadas de un bloque de color
	if((p->proyectil_rec.x >= l->bloque_rec[i].x - B_W) && (p->proyectil_rec.x <=  (l->bloque_rec[i].x+ B_W))
	  &&(p->proyectil_rec.y >= l->bloque_rec[i].y - B_H) && (p->proyectil_rec.y <= (l->bloque_rec[i].y + B_H)))  
	    p->proyectil_estado = proyectil_OFF;
      
      }
    }
  
    for(i = 0; i < BICHITOS_CANT_MAX; i++)
    {
      if((e+i)->enemy_estado != EN_JAIL)
      {
	//verifico si existe colicion entre el proyectil y un bichito
	if(((e+i)->enemy_rect.x >= p->proyectil_rec.x - pj_ancho) && ((e+i)->enemy_rect.x <=  (p->proyectil_rec.x+ pj_ancho))&&((e+i)->enemy_rect.y >= p->proyectil_rec.y - pj_largo) && ((e+i)->enemy_rect.y <= (p->proyectil_rec.y + pj_largo)))
	{
	  p->proyectil_estado = proyectil_OFF;
	  p->score += 15;
	  //--- lo mando a jail
	  (e+i)->enemy_rect.x = (l->jail_rect[0].x + 30);
	  (e+i)->enemy_rect.y = (l->jail_rect[0].y + 30);
	  (e+i)->enemy_estado = EN_JAIL;
	}
      }
    }
   
  }
  
  return ;
}