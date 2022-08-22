# Algo1-9511-Ejercicios-Obligatorios
Repositorio personal - Guido E. Rodriguez #108723
Si este repositorio te es útil, te agradeceria si le das una estrellita. Un abrazo. 😉

## Herramientas necesarias
- gcc 
- Algún programa que permita visualizar imagenes en formato pbm, ppm, bmp
	- (Recomendación 1) Image Viewer (eog) 
	- (Recomendación 2) Imagemagick (Conversor de formatos de archivo de imágenes)
	- (Recomendación 3) Gimp

### Instalación de imagemagick
```bash
sudo apt-get install imagemagick
```

## Ejercicio Obligatorio 1

Este ejercicio corresponde al primer ejercicio obligatorio de cátedra Algoritmos y programación 1 - 95.11 - Essaya.  
El mismo consta en un primer acercamiento a las técnicas de Raytraicing mediante el trazado de una esfera en un lienzo de resolución VGA a partir de la colisión de rayos con la misma.
En este caso es utilizada solamente la componente ambiental del modelo de Phong.

### Compilando el ejercicio

``` c 
gcc main.c -Wall -pedantic -std=c99 -o main -lm && ./main > imagen.pbm && convert imagen.pbm imagen.png
 ```
### Resultado

<p align="center" width="500">
   <img align="center" width="300" src="Ejercicio_1/imagen.png" />
</p>

### Documentación
[Ejercicio Obligatorio 1](https://ejercicio-obligatorio-1.netlify.app/index.html)

## Ejercicio Obligatorio 2

Este ejercicio corresponde al segundo ejercicio obligatorio de cátedra Algoritmos y programación 1 - 95.11 - Essaya.  
El mismo consta en un segundo acercamiento a las técnicas de Raytraicing para el transporte de luz mediante el modelo de iluminación de Phong. En la imagen serán trazadas 6 esferas en un lienzo de resolución VGA con su correspondiente intensidad a partir de la colisión de rayos con las mismas.
En este caso es utilizada la componente ambiental y difusa del modelo de Phong.

### Compilando el ejercicio

``` c 
gcc main.c -Wall -pedantic -std=c99 -o main -lm && ./main > imagen.pgm && convert imagen.pgm imagen.png
 ```
 
### Resultado

<p align="center" width="500">
   <img align="center" width="300" src="Ejercicio_2/imagen.png" />
</p>


### Documentación
[Ejercicio Obligatorio 2](https://ejercicio-obligatorio-2.netlify.app/index.html)

## Ejercicio Obligatorio 3

Este ejercicio corresponde al tercer ejercicio obligatorio de cátedra Algoritmos y programación 1 - 95.11 - Essaya.
El mismo consta en un tercer acercamiento a las técnicas de Raytraicing para el transporte de luz mediante el modelo de iluminación de Phong. En este caso se añade elementos al modelo tales como el color del material y la luz, coeficientes de reflexión ambiental y difusa.
En la imagen serán trazadas 23 esferas en un lienzo de resolución VGA con su correspondiente intensidad de color a partir de la colisión de rayos de luz de diferentes colores con las mismas.

### Compilando el ejercicio

``` c 
gcc main.c -Wall -pedantic -std=c99 -o main -lm && ./main > imagen.ppm && convert imagen.ppm imagen.png
 ```
 
### Resultado

<p align="center" width="500">
   <img align="center" width="300" src="Ejercicio_3/imagen.png" />
</p>

### Documentación
[Ejercicio Obligatorio 3](https://ejercicio-obligatorio-3.netlify.app/index.html)

## Ejercicio Obligatorio 4

Este ejercicio corresponde al cuarto ejercicio obligatorio de cátedra Algoritmos y programación 1 - 95.11 - Essaya.
En este caso se hace hincapié en la modularización de programas, TDA (ADT), CLA y uso de la herramienta Makefile

### Diagrama de arquitectura del programa

<p align="center" width="500">
    <img align="center" width="500" src="Ejercicio_4/diagrama_de_arquitectura.png" />
</p>


### Compilación y ejecución

Compilando...

```bash
make
```

Ejecutando...

**Opción PPM**

```bash
./main 640 480 imagen.ppm
```

**Opción BMP**

```bash
./main 640 480 imagen.bmp
```

### Resultado

<p align="center" width="500">
   <img align="center" width="300" src="Ejercicio_4/imagen.png" />
</p>

### Documentación
[Ejercicio Obligatorio 4](https://ejercicio-obligatorio-4.netlify.app/index.html)

