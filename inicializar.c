//------Includes------//
#include "Data_1.h"
#include <stdlib.h>
#include <time.h>
//-------------------//
/**
 * \fn inicializar
  \brief funcion que inicializa variables por defecto en primera instancia
  \author Agostini, Luca R1092
  \version 0.00
*/
int inicializar(struct enemy_data *e,struct char_data *p,struct level_data *l,SDL_Surface **pantalla,struct label_data *labels)
{
  int semilla = time(NULL);
  srand(semilla);
  
  if(*pantalla == NULL) // si la pantalla aun no fue creada
  {
    //----------- Inicializar subsistemas SDL y fondos---------------// 
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ) 
    {   
      printf("error al inicializar sdl systems\n");
      return FAIL; 
    }
    if(TTF_Init() == -1)
    {
      printf("error al inicializar tff\n");
      return FAIL;
    }
    *pantalla = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_FULLSCREEN );
    if(*pantalla == NULL)
    {
      printf("error al inicializar pantalla\n");
      return FAIL;
    }
    SDL_WM_SetCaption( "Proyecto Info1 R1092: Agostini, Luca v.1.0", NULL );
    
    l->level_num = 1; // inicio en el nivel 1
  }
  
  
  if(init_labels(labels) == FAIL)//Cargar fondos
    return FAIL;
  
  if(init_enemy(e) == FAIL)//cargar enemigos
    return FAIL;
  
  if(init_pj(p) == FAIL) //Cargar datos de jugador
    return FAIL;
  
  if(inicializar_lvl(l)== FAIL) //Cargar map
    return FAIL;
  
  
  //----------------- Presentacion ------------ 
  (labels->Level_titulo) = TTF_RenderText_Solid( labels->fondo, "-Proyecto Info 1:Agostini Luca R1092 v1.0-", labels->textColor);
  SDL_BlitSurface( labels->Level_titulo , NULL, *pantalla, &(labels->rec_titulo));
  SDL_Flip(*pantalla);
  SDL_Delay(2000);
  
  labels->rec_titulo.x += 210;
  labels->rec_titulo.y += 40;
  
  (labels->Level_titulo) = TTF_RenderText_Solid( labels->fondo, "- Enjoy !! -", labels->textColor);
  SDL_BlitSurface( labels->Level_titulo , NULL, *pantalla, &(labels->rec_titulo));
  SDL_Flip(*pantalla);
  SDL_Delay(2000);
  
  labels->rec_titulo.y += 40;
  
  (labels->Level_titulo) = TTF_RenderText_Solid( labels->fondo, "- Level: 1 -", labels->textColor);
  SDL_BlitSurface( labels->Level_titulo , NULL, *pantalla, &(labels->rec_titulo));
  SDL_Flip(*pantalla);
  SDL_Delay(2500);
  //----------------------------
  
  return CHECK_OK;
}
/**
 * \fn cargar_imagen
  \brief funcion que recive la ruta de acceso de un .bmp y lo adapta al programa
  \author Agostini, Luca R1092
  \version 0.00
*/
SDL_Surface *cargar_imagen(char filename[ARCHIVO_NAME_RG]) 
{ 
    SDL_Surface* loadedImage = NULL;  // la imagen recivida
    SDL_Surface* imagen_optima = NULL; // la nueva imagen optimizada
    
    loadedImage = SDL_LoadBMP(filename);
    
    if( loadedImage != NULL ) 
    { 
      imagen_optima = SDL_DisplayFormat( loadedImage );   //moldea la imagen al formato q preciso
      
      if( imagen_optima != NULL )
      { 
	//Map the color key (aux 0x061, 0x44, 0x2b) 
	Uint32 colorkey = SDL_MapRGB( imagen_optima->format, 0, 0, 0); //retorna un pixel 
	//transparento el fondo d la imagen pasandole el color del pixel (colorkey)
	SDL_SetColorKey( imagen_optima, SDL_SRCCOLORKEY, colorkey );  
      }
      else
      {
	printf("Error al adaptar imagen\n");
	return 0;
      }
      //Free the old image 
      SDL_FreeSurface( loadedImage ); 
    }
    else
      printf("Error al inicializar imagen\n");
    
    return imagen_optima; 
}
/**
 * \fn init_labels
  \brief 
  \author Agostini, Luca R1092
*/
int init_labels(struct label_data *labels)
{
    int i,altura_lab = 90;
  
    //init rec de titulo del lvl
    labels->rec_titulo.x = 5;
    labels->rec_titulo.y = 200;
    //------------------------
    
    labels->fondo = TTF_OpenFont("fondo1.ttf",15);
  
    if(labels->fondo == NULL)
    {
      printf("error de font\n");
      return FAIL;
    }
    SDL_Color col = { 255, 0, 100 };
    SDL_Color col2 = { 255, 255, 255 };
  
    labels->textColor = col;
  
    for(i = 0; i < LABEL_NUM; i++)
    {
      labels->rec[i].x = 510;
      labels->rec[i].y = altura_lab;
      altura_lab += 30;
    }
    
    labels->rec_time.x = 2;
    labels->rec_time.y = 10;
    
    //------------- Cargar labels -------------------//
    
    (labels->Level_nom) = TTF_RenderText_Solid( labels->fondo, "Level: ", labels->textColor);
    (labels->score_nom) = TTF_RenderText_Solid( labels->fondo, "Score: ", labels->textColor);
    (labels->Pos_nom) = TTF_RenderText_Solid( labels->fondo, "Posicion: ", labels->textColor);
    (labels->Vidas_nom) = TTF_RenderText_Solid( labels->fondo, "Vidas: ", labels->textColor);
    (labels->Luk) = TTF_RenderText_Solid( labels->fondo, "Luk corp.", labels->textColor);
   
    labels->textColor = col2; //reseteo el color
     
}
/**
 * \fn init_pj
  \brief inicializa y carga los datos de la estructura char_data
  \author Agostini, Luca R1092
  \version 0.00
*/
int init_pj(struct char_data *p)
{
  int i,largo,ancho; //ancho y largo definen desde donde situar el escaneo de frames
  
  p->sprite = cargar_imagen( "char_4.bmp" );  //guardo la imagen optimizada
  if((p->sprite) == NULL)
  {
    printf("error al cargar la imagen del personaje\n");
    return FAIL;
  }
  
  p->proyectil = cargar_imagen("bala.bmp");
  if((p->proyectil) == NULL)
  {
    printf("error al cargar la imagen del personaje\n");
    return FAIL;
  }
  
  
  p->proyectil_estado = proyectil_OFF;
  p->score = 0;
  
  p->origen.x = 400;   //Posicion de origen
  p->origen.y = 400;
  
  p->char_rect = p->origen; // Posicion en funcion del tiempo
  
  largo = 2;
  ancho = 1;
  
  for(i = 0 ; i< FRAME_PJ_RG; i++)
    p->frame_actual[i] = 0; //este dato me dira en que frame quede respecto de una posicion
  
  //init de frames 
  for(i = 0 ; i < CANT_FRAMES_PJ; i++)
  {
    p->frame[i].w = pj_ancho;
    p->frame[i].h = pj_largo;
    
    p->frame[i].x = ancho;
    p->frame[i].y = largo;
    ancho += pj_ancho;
    
    if((i+1)%4 == 0)
    {
      largo += pj_largo;
      p->frame[i].y = largo;
      ancho = 0;
    }
  }
  //inicializacion de frames
  p->frame_actual[DER] = 13;
  p->frame_actual[IZQ] = 5;
  p->frame_actual[ABAJO] = 1;
  p->frame_actual[ARRIBA] = 9;
  p->frame_actual[4] = 0;
  
  p->player_vidas = 3;
  
  return CHECK_OK;
}
/**
 * \fn init_enemy
  \brief inicializa y carga los datos de la estructura enemy_data
  \author Agostini, Luca R1092
  \version 0.00
*/
int init_enemy(struct enemy_data *e)
{
  int i,j,largo,ancho; //ancho y largo definen desde donde situar el escaneo de frames
  SDL_Rect origen;
  origen.x = 100;
  origen.y = 100;
 
  for(i = 0; i < (BICHITOS_CANT_MAX); i++)
  {
    (e+i)->sprite = cargar_imagen("Skelpion.bmp");
    if(((e+i)->sprite) == NULL)
    {
      printf("error al cargar la imagen del bichito\n");
      return FAIL;
    }
    
    largo = 2;
    ancho = 1;
  
    for(j = 0; j < (CANTIDAD_BOMBAS_MAX); j++)
    {
      (e+i)->enemy_bomb[j].bomba_sprite = cargar_imagen("bomb.bmp");
      
      if(((e+i)->enemy_bomb[j].bomba_sprite) == NULL)
      {
	printf("error al cargar la imagen de las bomba n° %i\n",j);
	return FAIL;
      }
      (e+i)->enemy_bomb[j].estado = BOMB_OFF; //todas las bombas empiezan desactivadas
    }
    
    
    
    for(j = 0; j < FRAME_ENEMY_RG;j++)
      (e+i)->frame_actual[i] = 0; //este dato me dira en que frame quede respecto de una posicion
   
     //init de frames 
    for(j = 0 ; j < CANT_FRAMES_BICHITO; j++)
    {
  
      (e+i)->frame[j].w = scorpion_ancho;
      (e+i)->frame[j].h = scorpion_largo;
    
      (e+i)->frame[j].x = ancho;
      (e+i)->frame[j].y = largo;
      ancho += scorpion_ancho;
   
      if((j+1)%4 == 0)	
      {
	largo += scorpion_largo;
	(e+i)->frame[j].y = largo;
	ancho = 0;
      }
    }
    
    //setear posicion
    (e+i)->enemy_rect = origen;
    
    origen.x += 50;
    
    //setear velocidad
    (e+i)->enemy_velocidad = 1;
    //inicializacion de frames
    (e+i)->frame_actual[DER] = 13;
    (e+i)->frame_actual[IZQ] = 5;
    (e+i)->frame_actual[ABAJO] = 1;
    (e+i)->frame_actual[ARRIBA] = 9;
  
    (e+i)->bombas_plantadas = 0;
    
    
    //setear estado de los enemigos
    (e+i)->enemy_estado = EN_JUEGO;
    }
    
  
  return CHECK_OK;
}