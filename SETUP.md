# Prerequiste

* g++ the C++ compileur :
``` bash

	sudo apt install g++

```
 
* cmake and xorg-dev to build GLFW :
``` bash

	sudo apt install build-essential cmake xorg-dev

```

* Adds other dependencies :
```bash 

	sudo apt-get install libx11-dev libglu1-mesa-dev freeglut3-dev libglew2.2 libglew-dev libglu1-mesa libgl1-mesa-glx libgl1-mesa-dev libglfw3-dev libglfw3

```

# Installing GLFW 
1. Install source package for OpenGL from <a href="https://glfw.org/download.html">GLFW</a>.
1. Unzip it and put it in a dependencie folder.
1. Then go in the GLFW folder and write the commandes :
```bash

	cmake -G "Unix Makefiles"
	make
	sudo make install  

```

# Install GLAD 
1. Install <a href="https://glad.dav1d.de/">GLAD zip file</a> from the website (check local files at the end of the page).
1. Unzip it and search for the glad folder inside.
1. Add it to your project directory in the include folder.

# Install GLM
1. Install <a href="https://github.com/g-truc/glm/tags">GLM zip file</a> from the github repo, take the latest tag.
1. Unzip it and search for the glm folder inside.
1. Add it to your project directory in the include folder.

# Install STB_IMAGE
1. Download <a href="https://raw.githubusercontent.com/nothings/stb/master/stb_image.h">raw stb_image.h file</a> from the github repo.
1. Add it to the include folder. 

# Compiling
To complie your best program you need to run the command :
``` bash
	
	./compile.sh

```

If you get an error of permition, run the command :
``` bash

	chmod +x compile.sh

```

