# Algo1-9511-Ejercicios-Obligatorios
 Personal Repository - Guido E. Rodriguez #108723

## Ejercicio Obligatorio 1

Este ejercicio corresponde al primer ejercicio obligatorio de cátedra Algoritmos y programación 1 - 95.11 - Essaya.  
El mismo consta en un primer acercamiento a las técnicas de Raytraicing mediante el trazado de una esfera en un lienzo de resolución VGA a partir de la colisión de rayos con la misma.

### Esquema de situación

                                        ......
                                      ..........
                                     ............
                                    .....Esfera...
                                    ..............
                                    ..X...........
                                    o/............
                                   y/.............
                                  a/ ............
                         240     R/   ..........
        ┌─────────────────┬──────/──────────┐
        │\                │     ##########  │
        │ |               │    ########### /│
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
gcc main.c -Wall -pedantic -std=c99 -o main -lm && ./main > imagen.pbm && gimp imagen.pbm
 ```

Esto va a producir una imagen de tamaño VGA en formato pbm que será abierta en gimp.