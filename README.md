# Project OpenGL

##  Setup 
Follow the instructions in the <a href="./SETUP.md#prerequiste">Setup file</a>.

## Overview
This project is a small project that i am making to learn OpenGL. The goal
is too reintroduce some of the game engines features to learn how they realy work on the inside.

In this project I have setup a lot things, even when i want to compile the program. 
``` bash

g++ src/*.cpp include/glad/glad.c -o bin/prog.exe -std=c++11 -Wall -lGL -lGLU -lglut -lGLEW -lglfw -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor

``` 

All those funny flags are for GLFW so that the compiler adds the dependencies.
But because I always forget all of this commands, i wrote a little shell script that as the resposibility to compile the program.
See in <a href="./SETUP.md#compiling">Setup file</a>