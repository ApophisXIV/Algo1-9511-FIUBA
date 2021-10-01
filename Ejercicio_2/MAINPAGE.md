## Ejercicio Obligatorio 2

Este ejercicio corresponde al segundo ejercicio obligatorio de cátedra Algoritmos y programación 1 - 95.11 - Essaya.  
El mismo consta en un primer acercamiento a las técnicas de Raytraicing para el transporte de luz mediante el modelo de iluminación de Phong. En este caso serán trazadas 6 esferas en un lienzo de resolución VGA con su correspondiente intensidad a partir de la colisión de rayos con las mismas.

### Esquema de situación

                                        ......
                                      ..........
                                     ............
                                    ...n Esferas..
                                    ..............
                                    ..X...........
                                    o/............
                                   y/.............
                                  a/ ............
                         240     R/   ..........
        ┌─────────────────┬──────/──────────┐
        │\                │     ##########  │
        │ |               │    ########### /│ --> Escala de grises
        │ \               │   /########## / │
        │  |              │  /  ######## /  │
        │  \              │ /     ##### /   │
        │   |             │/           /    │
    -320├───\── ──────────┼─────────────────┤320
        │    |           /│          /      │
        │    \          / │         /       │
        │     |        /  │        /        │
        │     \       /   │       /         │
        │      |      |   │      /          │
        │      \      |   │     /           │
        └───────|─────|───┴────/────────────┘
         \      \     | -240  /            /
          \      |    |      /           /
           \     \    |     /          /
            \    ┌──────────┐        /
             \   │          │      /
              \  │  Camara  │    /
               \ │          │  /
                \└──────────┘/

### Compilando el ejercicio

Para poder ejecutar el siguiente comando es necesario tener instalado Gimp y GCC

``` c 
gcc main.c -Wall -pedantic -std=c99 -o main -lm && ./main > imagen.pgm && gimp imagen.pgm
 ```

Esto va a producir una imagen de tamaño VGA en formato pgm que será abierta en gimp.

### Datos personales

- **Alumno:** Guido E. Rodriguez  
- **Número de padrón:** 108723  
- **Contacto:** guerodrigue@fi.uba.ar  
- **Fecha de entrega:** 2021-09-27
- **Copyright** Copyright (c) 2021