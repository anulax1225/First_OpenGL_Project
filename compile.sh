if [ -d ./bin ]; then
	echo Deleting existing bin folder
	rm -d -r ./bin	
	echo Creating bin folder
	mkdir ./bin
else 
	echo Creating bin folder	
	mkdir ./bin
fi
echo Compiling GLFW program 
g++ src/*.cpp include/glad/glad.c -o bin/prog.exe -std=c++11 -Wall -lGL -lGLU -lglut -lGLEW -lglfw -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor
echo Compilation Success