
#include "Data_1.h"

/**
 * \fn check_game
  \brief proximo a dibujar las entidades en la pantalla , basadas en los parametros previamente inicializados en el metodo inicializar, Esta funcion chequea continuamente los cambios producidos en el juego , y en base a los cambios, realiza nuevas acciones
  \author Agostini, Luca R1092
*/
int check_game(struct char_data *p,struct enemy_data *e,struct level_data *level)
{
  int i,aux,j;
  
	i = 0;
	while((e+i)->enemy_estado == EN_JAIL) 
	{
	      //si todos los bichitos estan en jail
	      if(i == (BICHITOS_CANT_MAX -1))
	      {
		level->level_num ++;
		
		if( level->level_num > LVL_MAX) //si es el nivel maximo , directamente retornar
		  return LVL_MAX;
		
		inicializar_lvl(level);
		p->char_rect = p->origen;
		
		for(j = 0; j < BICHITOS_CANT_MAX; j++)
		{
		  (e+j)->enemy_velocidad += 1;
		  (e+j)->enemy_estado = EN_JUEGO;
		  (e+j)->enemy_rect.x = 50+(50*j);
		  (e+j)->enemy_rect.y = 110;
		 
		}
	
		return LEVEL_UP;
	      }
	      i++;
	}
	  
	actualizar_proyectil(p);
	colicion_proyectil(p,level,e); //chequea si el proyectil coliciona con el entorno
	check_colicion_pj_bichitos(e,p);
	
	for(i = 0; i < BICHITOS_CANT_MAX ; i++)
	  enemy_ataque((e+i));
	
	//chequear que no haya perdido
	if(p->player_vidas == 0)
	  return GAME_OVER;
	else if(level->time == 0)
	  return GAME_OVER;
	
	// Cada 15 seg un bichito vuelve de jail
	if((level->time)%15 == 0)
	{
	  aux = 1;
	  i= 0;
	  while((aux == 1) && (i < BICHITOS_CANT_MAX)) 
	  {
	    if(((e+i)->enemy_estado) == EN_JAIL) //Busco bichitos en jail
	    {
	      (e+i)->enemy_rect.x = 150;         //los devuelvo a la partida
	      (e+i)->enemy_rect.y = 150;
	      (e+i)->enemy_estado = EN_JUEGO;
	      
	      aux = 0;           //condicion de corte(en cuanto encuentra el primer bichito sale del while
	    }
	    i++;
	  } 
	}
	
	return CHECK_OK;
}



/**
 * \fn time_fn
  \brief devuelve el tiempo transcurrido de juego en segundos 
  \author Agostini, Luca R1092
*/
unsigned int time_fn(struct level_data *lev)
{
  unsigned int tiempo_real;
  
  tiempo_real = time(NULL);
  
  if(tiempo_real != lev->time_ant)
  {
    lev->time_ant =  tiempo_real;
    lev->time --; 
  }
  
  return lev->time;
}