echo ----------------------------------------------
echo \| Building OpenGL Project
echo ----------------------------------------------
if [ -d ./bin ]; then
	echo [build]Deleting existing bin folder
	rm -d -r ./bin	
	echo [build]Creating bin folder
	mkdir ./bin
	echo [build]Copying assets folder
	cp -r assets bin/assets
else 
	echo [build]Creating bin folder	
	mkdir ./bin
	echo [build]Copying assets folder
	cp -r assets bin/assets
fi
echo ----------------------------------------------
echo ----------------------------------------------
echo [compile]Compiling GLFW program 
if [ "$1" = "--Debug" ]; then
	echo [compile]Compiling to Debug mode
	g++ -g src/*.cpp src/io/*.cpp lib/stb_image/stb_image.cpp lib/glad/glad.c -o bin/prog.exe -std=c++11 -Wall -lGL -lGLU -lglut -lGLEW -lglfw -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor
else
	echo [compile]Compiling to Realease mode
	g++ src/*.cpp src/io/*.cpp lib/stb_image/stb_image.cpp lib/glad/glad.c -o bin/prog.exe -std=c++11 -Wall -lGL -lGLU -lglut -lGLEW -lglfw -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor
fi
if [ $? -eq 0 ]; then
	echo [compile]Compilation Success
else 
	echo [compile]Error will compiling
fi
echo ----------------------------------------------
