# Project OpenGL

##  Setup 
Follow the instructions in the <a href="./SETUP.md">Setup file</a>.

## Overview
This project is a small project that i am making to learn OpenGL. The goal
is too reintroduce some of the game engines features to learn how they realy work on the inside.

## Compiling
In this project I have setup a lot things, even when i want to compile the program, the command to run is :
``` bash

g++ src/*.cpp include/glad/glad.c -o bin/prog.exe -std=c++11 -Wall -lGL -lGLU -lglut -lGLEW -lglfw -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor

``` 

Because I always forget all of this commands, i wrote a little shell script that as the resposibility to compile the program.