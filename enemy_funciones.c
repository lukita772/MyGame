//-------Includes---------//
#include "Data_1.h"
#include <time.h>
#include <stdio.h>
//------------------------//
int enemy_movimiento(struct enemy_data *bichito1,struct level_data *lev)
{
  unsigned int tiempo_real = time(NULL);
  
  if(tiempo_real != lev->time_ant) //se cumple al pasar un segundo 
    bichito1->opcion = rand()%5;
  
  
  
  switch(bichito1->opcion) // le paso valores aleatorios correspondientes a movimientos de la entidad
  {
    case DER:
      
      bichito1->enemy_rect.x += bichito1->enemy_velocidad;             //lo desplazo en x a la imagen en el map
      
      if(check_enemy_colicion(bichito1, lev) == MOVE_OK)
      {
	if(bichito1->frame_actual[DER] >= 14)    //si llego al ultimo cuadro
	{
	  bichito1->frame_actual[DER] = 11;     //reseteo el frame
	}
	bichito1->frame_actual[DER] +=1;     // lo llevo al proximo frame
      }
      else
	bichito1->enemy_rect.x -= bichito1->enemy_velocidad;  
      
      return bichito1->frame_actual[DER];  //retorno el numero de cuadro correspondiente
      
    case IZQ:
      
      bichito1->enemy_rect.x -= bichito1->enemy_velocidad;
      
      if(check_enemy_colicion(bichito1, lev) == MOVE_OK)
      {
	if(bichito1->frame_actual[IZQ] >= 6)
	{
	  bichito1->frame_actual[IZQ] = 3;   //reseteo el frame
	}
	bichito1->frame_actual[IZQ] +=1;
      }
      else 
	bichito1->enemy_rect.x += bichito1->enemy_velocidad;
      
      return bichito1->frame_actual[IZQ];
      
    case ABAJO:
      
      bichito1->enemy_rect.y += bichito1->enemy_velocidad;
      
      if(check_enemy_colicion(bichito1, lev) == MOVE_OK)
      {
	if(bichito1->frame_actual[ABAJO] >= 2)
	{
	  bichito1->frame_actual[ABAJO] = -1; //reseteo el frame
	}
	bichito1->frame_actual[ABAJO] +=1;
      }
      else
	bichito1->enemy_rect.y -= bichito1->enemy_velocidad;
      
      return bichito1->frame_actual[ABAJO];
      
    case ARRIBA:
      
      bichito1->enemy_rect.y -= bichito1->enemy_velocidad;
      if(check_enemy_colicion(bichito1, lev) == MOVE_OK)
      {
	if(bichito1->frame_actual[ARRIBA] >= 10)
	{
	  bichito1->frame_actual[ARRIBA] = 7;    //reseteo el frame
	}
	bichito1->frame_actual[ARRIBA] +=1;
      }
      else
	bichito1->enemy_rect.y +=bichito1->enemy_velocidad;
      
      return bichito1->frame_actual[ARRIBA];

    default:
      // se queda quieto en el lugar
      break;
  }
  return 0; //devuelve el frame 0
}

void enemy_ataque(struct enemy_data *bichito1)
{    
  unsigned int op;
  
  //printf("semilla : %i \n",semilla);
  
  if(bichito1->enemy_bomb[bichito1->bombas_plantadas].estado == BOMB_OFF)
  {
	  if(bichito1->bombas_plantadas <= CANTIDAD_BOMBAS_MAX)
	  {
	    //srand(semilla);
	    op = rand()%100;
	    
	    //printf("random:  %i  \n",op);
	    switch(op) // le paso valores aleatorios correspondientes a movimientos de la entidad
	    {
	      case PLANTAR_BOMB:
		//plantar una bomba
		plantar_bomb(bichito1);
		return;
	      default:
		//no hacer nada
		return;
	    }
	  }
    }
    else
      return;
}

void plantar_bomb(struct enemy_data *bichito1)
{	
	    //la bomba actual tendra las coordenadas del enemigo al plantarlas
	    bichito1->enemy_bomb[bichito1->bombas_plantadas].bomba_rect.x = bichito1->enemy_rect.x; 
	    bichito1->enemy_bomb[bichito1->bombas_plantadas].bomba_rect.y = bichito1->enemy_rect.y; 
	    // activo la bomba correspondiente basandome en la cant d bombas plantadas
	    bichito1->enemy_bomb[bichito1->bombas_plantadas].estado = BOMB_ON; 
	
	    bichito1->bombas_plantadas = (bichito1->bombas_plantadas)+1 ;
	   //printf("PLANTE!!\n");
  
  return;
}
