/**
  \file data_1.h
  \brief lib que contiene datos principales del juego
  \author Agostini, Luca R1092
  \version 0.00
*/
// -----Includes------ //
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

//---- DEFINES: General ----//
#define GAME_OVER -1
#define CHECK_OK 1
#define FAIL -2
#define MOVE_OK 7
#define MOVE_NO -7
#define ARCHIVO_NAME_RG 30
#define LEVEL_UP 55
#define LVL_MAX 4
#define FULL_ON 1
#define FULL_OFF -1
//------ CTRL -------//
#define ARRIBA_BOTON 'w'
#define ABAJO_BOTON 's'
#define DER_BOTON 'd'
#define IZQ_BOTON 'a'
#define POW_BOTON 'p'
#define SCREEN_SWITCH_BOTON '2'
#define LEVEL_UP_BOTON '1'
#define EXIT_BOTON '0'
//----------------------
//-- Pantalla: Data --
//----------------------
#define SCREEN_WIDTH		(650)	//!< Ancho de la ventana.
#define SCREEN_HEIGHT		(520)	//!< Alto de la ventana.
#define SCREEN_BPP		(16)	//!< Bit per pixel.
//----------- Mapas data ----------------//
#define B_W 25   //!< Ancho del bloque.
#define B_H 25  //!< Largo del bloque.

#define RED_BLOQUE 1   
#define GREEN_BLOQUE 2
#define BLUE_BLOQUE 3
#define NULO_BLOQUE 0

#define LEVEL_ANCHO 20       //!cantidad de bloques a lo ancho
#define LEVEL_ALTO 25        //!cantidad de bloques a lo largo

#define B_TOTAL LEVEL_ALTO*LEVEL_ANCHO   //!< Cant. total de bloques.

//--------- bichitos defines------------//
#define BICHITOS_CANT_MAX 5
#define scorpion_ancho 32       //!ancho de frame
#define scorpion_largo 32       //!largo de frame
#define CANT_FRAMES_BICHITO 15
#define DER 0
#define IZQ 1
#define ABAJO 2
#define ARRIBA 3
//bombas
#define PLANTAR_BOMB 5
#define CANTIDAD_BOMBAS_MAX 1
#define BOMB_ON 17
#define BOMB_OFF 0

#define FRAME_ENEMY_RG 4
//--------- mi personaje defines -------------//
#define CANT_FRAMES_PJ 15
#define pj_ancho 32          //!ancho de frame
#define pj_largo 32         //!largo de frame
#define CHAR_SPEED 3     //!Velocidad de desplazamiento del pj

#define proyectil_ON 5
#define proyectil_OFF -5  
#define proyectil_VEL 4   //!Velocidad de desplazamiento del proyectil

#define NOMBRE_LONG 30
#define FRAME_PJ_RG 5

//------- labels defines ---------//
#define LABEL_NUM 9         //!Cant. de labels

//-------- Jail: data
#define JAIL_DIM 100
#define JAIL_COL_1 1
#define JAIL_COL_2 2
#define JAIL_BLOQUE_ANCHO 15
#define JAIL_BLOQUE_LARGO 15

#define EN_JAIL 9
#define EN_JUEGO 8

//---------------- STRUCTS ---------------------//
struct char_data
{
   SDL_Surface *sprite; 
   SDL_Surface *proyectil;
   
   SDL_Rect proyectil_rec;
   SDL_Rect char_rect;
   SDL_Rect origen;
   
   int player_vidas;
   int score;
   int proyectil_estado;
   int proyectil_direccion;
   char name[NOMBRE_LONG];  
   SDL_Rect frame[CANT_FRAMES_PJ];  // cantidad de frames
   int frame_actual[FRAME_PJ_RG];   // cada pos. guarda el ultimo frame que se le setio respecto de cada movimiento correspondiente (de 0 a 3) ,el cuarto tiene el ultimo frame conocido
};

struct label_data
{
  SDL_Surface *time;
  SDL_Rect rec_time;
  
  SDL_Surface *Level_titulo;
  SDL_Rect rec_titulo;
  
  SDL_Surface *Level_nom;
  SDL_Surface *Level_data;
  SDL_Surface *score_nom;
  SDL_Surface *score_data;
  SDL_Surface *Pos_nom;
  SDL_Surface *Pos_data;
  SDL_Surface *Vidas_nom;
  SDL_Surface *Vidas_data;
  SDL_Surface *Luk;
  SDL_Rect rec[LABEL_NUM];
  
  TTF_Font *fondo;
  SDL_Color textColor;
};

struct level_data
{
  SDL_Surface *background;
  SDL_Surface *bloque_imagen[B_TOTAL];
  SDL_Rect bloque_rec[B_TOTAL];
  SDL_Color textColor;
  
  int mat_data[B_TOTAL]; // tiene los parametros de los colores de los bloques(
  int level_num;
  unsigned int time;
  unsigned int time_ant;
  unsigned int semilla; 
  
  //------ Pequeño box donde van los bichitos que mueren ----//
  int jail_dim[JAIL_DIM];
  SDL_Surface *jail_img[JAIL_DIM];
  SDL_Rect jail_rect[JAIL_DIM];
  int jail_mat_data[JAIL_DIM];
};
struct bomba
{
  int estado; //puesta o no puesta
  SDL_Surface *bomba_sprite;
  SDL_Rect bomba_rect;
  
};
struct enemy_data
{
    SDL_Surface *sprite;
    SDL_Rect enemy_rect;
    SDL_Rect frame[CANT_FRAMES_BICHITO];
    int frame_actual[FRAME_ENEMY_RG]; 
 
    int bombas_plantadas;
    struct bomba enemy_bomb[CANTIDAD_BOMBAS_MAX]; 
    int enemy_estado;
    int enemy_velocidad;
    int opcion;
};


/**
  \brief prototipos
  \author Agostini, Luca R1092
  \version 0.00
*/
//---------------level_funciones.c--------------//
int inicializar_lvl(struct level_data *level);
void level_factory(struct level_data *lev, int map_data[B_TOTAL] );
void cadena_a_mat(char *level_data_dir,int *lvl_actual_dir);

//---------------mapas.c--------------//
void level_1(int *matriz_dir);
void level_2(int *matriz_dir);
void level_3(int *matriz_dir);

//-------- dibujar_funciones.c -----------------//
void dibujar_entidad( struct enemy_data *e,struct char_data *p, SDL_Surface* destination,struct level_data *lvl );
void dibujar_mapa( struct level_data *level,SDL_Surface* destination ); 
void refresco_pantalla(struct enemy_data *e,struct char_data *p,struct level_data *l,SDL_Surface *pantalla,struct label_data *labels);
void muestra_datos_juego(struct char_data *p,struct label_data *l,SDL_Surface *pantalla,struct level_data *lev);

//--------------enemy_funciones.c----------------//
int enemy_movimiento(struct enemy_data *bichito1,struct level_data *lev);
void plantar_bomb(struct enemy_data *bichito1);
void enemy_ataque(struct enemy_data *bichito1);

//------------ inicializar.c------------//
int inicializar(struct enemy_data *e,struct char_data *p,struct level_data *l,SDL_Surface **pantalla,struct label_data *labels);
int init_labels(struct label_data *labels);
int init_pj(struct char_data *p);
int init_enemy(struct enemy_data *e);
SDL_Surface *cargar_imagen(char filename[ARCHIVO_NAME_RG]);

//------------ coliciones.c ---------------//
int check_colicion_pj_bichitos(struct enemy_data *e, struct char_data *p);
int check_colicion(struct char_data *p,struct level_data *l);
int check_enemy_colicion(struct enemy_data *e,struct level_data *l);
void colicion_proyectil(struct char_data *p,struct level_data *l,struct enemy_data *e);

//------------ char_funciones.c ------------------//
void char_actualizar_data(struct char_data *mi_pj,int movimiento,struct level_data *level);
void disparar_proyectil(struct char_data *mi_char);
void actualizar_proyectil(struct char_data *mi_char);


//-------------check_juego.c----------//
int check_game(struct char_data *p,struct enemy_data *e,struct level_data *level);
unsigned int time_fn(struct level_data *lev);



