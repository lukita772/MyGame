# A linux based game developed in my first year of university

## Requirements
- SDL Libraries
- TTL fonts
- GCC Compiler
- Linux-based SO

## To install SDL libraries
Execute the next command line:
```bash
$ git clone https://github.com/libsdl-org/SDL.git -b SDL2
cd SDL
mkdir build
cd build
../configure
make
sudo make install

```

## To compile
Execute the next command line:
```bash
$ gcc main.c dibujar_funciones.c  level_funciones.c enemy_funciones.c inicializar.c coliciones.c char_funciones.c check_juego.c -lSDL  -lSDL_ttf -oprueba

```

![Screenshot from 2023-04-07 18-43-16](https://user-images.githubusercontent.com/117228370/230682612-c1312b0b-6136-4e8e-99a4-3497e82ab550.png)

