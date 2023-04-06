// Includes
#include "Data_1.h"

/**
 * \fn char_actualizar_data
  \brief funcion que actualiza los datos del personaje
  \author Agostini, Luca R1092
*/
void char_actualizar_data(struct char_data *mi_pj,int movimiento,struct level_data *level)
{
    if(movimiento == DER)
    {
      mi_pj->char_rect.x += CHAR_SPEED;
      
      if(check_colicion(mi_pj,level) == MOVE_OK) //si el movimiento es autorizado
      {
	if(mi_pj->frame_actual[DER] >= 14)
	  mi_pj->frame_actual[DER] = 10;
    
	mi_pj->frame_actual[DER] += 1;
    
	mi_pj->frame_actual[FRAME_PJ_RG-1] = mi_pj->frame_actual[DER];
      }
      else
	mi_pj->char_rect.x -= 10;
      
      return;
    }
    else if(movimiento == IZQ)
    {
      mi_pj->char_rect.x -= CHAR_SPEED;
      
      if(check_colicion(mi_pj,level) == MOVE_OK) //si el movimiento es autorizado
      {
	if(mi_pj->frame_actual[IZQ] >= 6)
	  mi_pj->frame_actual[IZQ] = 3;
    
	mi_pj->frame_actual[IZQ] += 1;
	mi_pj->frame_actual[FRAME_PJ_RG-1] = mi_pj->frame_actual[IZQ];
      }
      else
	mi_pj->char_rect.x += 10;
      
	return;
    }
    else if(movimiento == ABAJO)
    {
      mi_pj->char_rect.y += CHAR_SPEED;
    
      if(check_colicion(mi_pj,level) == MOVE_OK) //si el movimiento es autorizado
      {
	if(mi_pj->frame_actual[ABAJO] >= 2)
	  mi_pj->frame_actual[ABAJO] = -1;
    
	mi_pj->frame_actual[ABAJO] += 1;
	mi_pj->frame_actual[FRAME_PJ_RG-1] = mi_pj->frame_actual[ABAJO];
      }
      else
	mi_pj->char_rect.y -= 10;
      
      return;
    }
    else if(movimiento == ARRIBA)
    {
      mi_pj->char_rect.y -= CHAR_SPEED;
    
      if(check_colicion(mi_pj,level) == MOVE_OK) //si el movimiento es autorizado
      {
	if(mi_pj->frame_actual[ARRIBA] >= 10)
	  mi_pj->frame_actual[ARRIBA] = 7;
    
	mi_pj->frame_actual[ARRIBA] += 1;
	mi_pj->frame_actual[FRAME_PJ_RG-1] = mi_pj->frame_actual[ARRIBA];
      }
      else
	mi_pj->char_rect.y +=10;
	
      return ;
    }

}

void disparar_proyectil(struct char_data *mi_char)
{
  if(mi_char->proyectil_estado == proyectil_OFF) //si el proyectil no fue disparado
  {
      if(mi_char->frame_actual[FRAME_PJ_RG-1] >= 0 && mi_char->frame_actual[FRAME_PJ_RG-1] <= 3)
	mi_char->proyectil_direccion = ABAJO;
      else if(mi_char->frame_actual[FRAME_PJ_RG-1] >= 4 && mi_char->frame_actual[FRAME_PJ_RG-1] <= 7)
	mi_char->proyectil_direccion = IZQ;
      else if(mi_char->frame_actual[FRAME_PJ_RG-1] >= 8 && mi_char->frame_actual[FRAME_PJ_RG-1] <= 11)
	mi_char->proyectil_direccion = ARRIBA;
      else if(mi_char->frame_actual[FRAME_PJ_RG-1] >= 12 && mi_char->frame_actual[FRAME_PJ_RG-1] <= 15)
	mi_char->proyectil_direccion = DER;
    
      
      mi_char->proyectil_rec.y = mi_char->char_rect.y; //desde la posicion actual de mi pj
      mi_char->proyectil_rec.x = mi_char->char_rect.x;
      mi_char->proyectil_estado = proyectil_ON;   //activo el proyectil
  }
  return;
}

void actualizar_proyectil(struct char_data *mi_char)
{
  if(mi_char->proyectil_estado == proyectil_ON) //si el proyectil fue disparado
  {
    if(mi_char->proyectil_direccion == ABAJO)
      mi_char->proyectil_rec.y = mi_char->proyectil_rec.y +proyectil_VEL;
    else if(mi_char->proyectil_direccion == IZQ)
      mi_char->proyectil_rec.x = mi_char->proyectil_rec.x -proyectil_VEL;
    else if(mi_char->proyectil_direccion == ARRIBA)
      mi_char->proyectil_rec.y = mi_char->proyectil_rec.y -proyectil_VEL;
    else if(mi_char->proyectil_direccion == DER)
      mi_char->proyectil_rec.x = mi_char->proyectil_rec.x +proyectil_VEL;
        
  }
  return;
}