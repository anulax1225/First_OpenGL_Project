echo ----------------------------------------------
echo \| Building OpenGL Project
echo ----------------------------------------------
if [ -d ./bin ]; then
	echo [build]Deleting existing bin folder
	rm -d -r ./bin	
	echo [build]Creating bin folder
	mkdir ./bin
	echo [build]Copying the assets folder
	cp -r assets bin/assets
else 
	echo [build]Creating bin folder	
	mkdir ./bin
	echo [build]Copying the assets folder
	cp -r assets bin/assets
fi
echo ----------------------------------------------
echo ----------------------------------------------
echo [compile]Compiling GLFW program 
g++ src/*.cpp lib/stb_image/stb_image.cpp lib/glad/glad.c -o bin/prog.exe -std=c++11 -Wall -lGL -lGLU -lglut -lGLEW -lglfw -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor
echo [compile]Compilation Success
echo ----------------------------------------------