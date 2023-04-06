/**
  \brief lib que inicializa y fabrica los mapas a partir de matrices (ver mapas.c)
  \author Agostini, Luca R1092
  \version 0.00
*/
//---- Includes ------//
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "Data_1.h"
//-------------------//

int inicializar_lvl(struct level_data *level)
{
  struct stat stat1;
  int i = 0,fd,j;
  int lvl_actual[B_TOTAL];
  char *level_cadena_data;
  
  level->time = 60;
  level->time_ant = 61;
  
  level->background = cargar_imagen( "background.bmp" ); 
  if(level->background == NULL)
  {
    printf("error al cargar background\n");
    return FAIL;
  }
 
  while (i < JAIL_DIM)
  {
    level->jail_img[i]=cargar_imagen( "bloque.bmp" );
    if(level->jail_img[i] == NULL)
    {
      printf("error al cargar bloque imagen (de jail) n° %i",i);
      return FAIL;
    }
    
    level->jail_img[i]->w = JAIL_BLOQUE_ANCHO;
    level->jail_img[i]->h = JAIL_BLOQUE_LARGO;
    level->jail_rect[i].w = JAIL_BLOQUE_ANCHO;
    level->jail_rect[i].h = JAIL_BLOQUE_LARGO;
    
    i++;
  }
  
  i = 0;
  while(i < B_TOTAL)
  {
    level->bloque_imagen[i]=cargar_imagen( "bloque.bmp" );
    if(level->bloque_imagen[i] == NULL)
    {
      printf("error al cargar bloque imagen n° %i",i);
      return FAIL;
    }
    
    level->bloque_imagen[i]->w = B_W;
    level->bloque_imagen[i]->h = B_H;
    level->bloque_rec[i].w = B_W;
    level->bloque_rec[i].h = B_H;
    i++;
  }
  
 // level_1(lvl_actual);
  if(level->level_num == 1)
    fd = open("level_1",O_RDONLY);
  else if(level->level_num == 2)
    fd = open("level_2",O_RDONLY);
  else if(level->level_num == 3)
    fd = open("level_3",O_RDONLY);
  else if(level->level_num == 4)
    fd = open("level_4",O_RDONLY);
  
  
  if(fd < 0)
  {
    printf("Error al cargar el nivel\nDetalles: File descriptor: %i\n",fd);
    return FAIL;
  }
  if(fstat(fd,&stat1) != 0)  
  {
    printf("Falla al cargar nivel ( tamaño de archivo invalido )\n");
    return FAIL;
  }
  
  level_cadena_data = (char *)malloc(stat1.st_size);
    
  if(level_cadena_data == NULL)
  {
    printf("Error al cargar el nivel ( direccion de memoria invalida )\n");
    return FAIL;
  }
  
  read(fd, level_cadena_data,stat1.st_size);
  
  close(fd);
  
  cadena_a_mat(level_cadena_data,lvl_actual);
  
  level_factory(level, lvl_actual ) ; 
  
  return CHECK_OK;
}
  
void cadena_a_mat(char *level_data_dir,int *lvl_actual_dir)
{
  int i = 0,j=0;
  
  for(i = 0; i < B_TOTAL; i++)
  {
    while(*(level_data_dir+j) == ',' || *(level_data_dir+j) == '\n' || *(level_data_dir+j) == '\r' 
      || *(level_data_dir+j) == ' ')
      j++;
    
    *(lvl_actual_dir+i) = atoi(level_data_dir+j);
    
    j++;
  }
  return;
}

/**
 * \fn level_factory
  \brief recive como parametros una matriz de numeros, y basandose en esos numeros crea el mapa correspondiente
*/
void level_factory(struct level_data *lev, int map_data[LEVEL_ALTO*LEVEL_ANCHO] ) 
{ 
    int i,pos_vert =15 ,pos_horiz = 0;
    
    //-- Generica para todos los mapas--
    int jail_matriz[JAIL_DIM]=
    {
      1,2,1,2,1,1,2,1,2,1,
      2,1,0,0,0,0,0,0,1,2,
      1,0,0,0,0,0,0,0,0,1,
      2,0,0,0,0,0,0,0,0,2,
      1,0,0,0,0,0,0,0,0,2,
      2,0,0,0,0,0,0,0,0,1,
      1,0,0,0,0,0,0,0,0,2,
      2,0,0,0,0,0,0,0,0,1,
      2,1,0,0,0,0,0,0,1,2,
      1,2,1,2,1,2,1,1,2,1
    };
    
    //------------- COLORES ------------
    Uint32 Rojo = SDL_MapRGB( lev->background->format, 240, 10, 10);
    Uint32 Verde = SDL_MapRGB( lev->background->format, 10, 240, 10);
    Uint32 Azul = SDL_MapRGB( lev->background->format, 10, 10, 240);
    
    Uint32 JAIL_COLOR_1 = SDL_MapRGB( lev->background->format, 80, 80, 80);
    Uint32 JAIL_COLOR_2 = SDL_MapRGB( lev->background->format, 150, 150, 150);
    
    
    //mas adelante voy a precisar este dato para las coliciones
    for( i = 0; i < B_TOTAL; i++)
      lev->mat_data[i] = map_data[i];
    
    for( i = 0; i < JAIL_DIM; i++)
      lev->jail_mat_data[i] = jail_matriz[i];
    //-----------------------------------------------
      
    // Genero nivel
    for(i = 0; i < (B_TOTAL)+1 ;i++)
    {

	if(map_data[i] == RED_BLOQUE)
	{
	  SDL_FillRect( lev->bloque_imagen[i], 0 , Rojo); 
	}
	else if(map_data[i] == GREEN_BLOQUE)
	{
	  SDL_FillRect( lev->bloque_imagen[i], 0 , Verde); 
	}
	else if(map_data[i] == BLUE_BLOQUE)
	{
	  SDL_FillRect( lev->bloque_imagen[i], 0 , Azul); 
	}
	pos_horiz += B_W;
	
	if( i%LEVEL_ANCHO == 0 )
	{
	  pos_vert+= B_H;
	  pos_horiz = 0;
	}
	lev->bloque_rec[i].x = (pos_horiz);
	lev->bloque_rec[i].y = (pos_vert);
	
    }
    
    //Genero Jail
    pos_vert = 350 ,pos_horiz = 500;
    for(i = 0; i < JAIL_DIM; i++)
    {
	
	if(jail_matriz[i] == JAIL_COL_1)
	{
	  SDL_FillRect( lev->jail_img[i], 0 , JAIL_COLOR_1); 
	}
	else if(jail_matriz[i] == JAIL_COL_2)
	{
	  SDL_FillRect( lev->jail_img[i], 0 , JAIL_COLOR_2); 
	}
      
	pos_horiz += JAIL_BLOQUE_ANCHO;
	if( i%10 == 0 )
	{
	  pos_vert += JAIL_BLOQUE_LARGO;
	  pos_horiz = 500;
	}
	lev->jail_rect[i].x = (pos_horiz);
	lev->jail_rect[i].y = (pos_vert);

    }
    
    return;
} 


