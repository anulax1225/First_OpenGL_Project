# Project OpenGL

## Software
* C++ : version 12.

### Libreries
* GLFW : Moderne version of OpenGL.
* GLAD : Function and variable manager.
* GLM : Math lib for matrix vec multiplication and matrix matrix multiplication.
* STB_IMAGE : Image loader for OpenGL.

##  Setup 
Follow the instructions in the <a href="./SETUP.md#prerequiste">Setup file</a>.

## Overview
This project is a small project that i am making to learn OpenGL. The insperation comes from a <a href="https://www.youtube.com/watch?v=_POT8K638VY&list=PLysLvOneEETPlOI_PI4mJnocqIpr2cSHS&pp=iAQB">youtube playlist</a> to learn OpenGL. The goal is too reintroduce some of the game engines features to learn how they realy work on the inside. I want to learn more on mesh rendering, lighting, physiques, GPU shaders and memory management etc. so this project sims a good way to do it.

In this project I have setup a lot things, even when i want to compile the program. 
``` bash

g++ src/*.cpp include/glad/glad.c -o bin/prog.exe -std=c++11 -Wall -lGL -lGLU -lglut -lGLEW -lglfw -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor

``` 

All those funny flags are for GLFW so that the compiler adds the dependencies.
But because I always forget all of this commands, i wrote a little shell script that as the resposibility to compile the program.
See in <a href="./SETUP.md#compiling">Setup file</a>

## Steps 
1. Initilizing a GLFW window and setup of the libreries.
1. Drawing first triangle using the vertices with vertex and fragment shader (VBO).
1. Drawing a triangle with a EBO.
1. Adding color to data input.
1. Creating a Shader class to don't repeat code.

## Theory 

### Triangles

### Graphiques pipline

### Shader program

### GPU Memory access

### Texture 

### Camera
