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

Install source package for OpenGL from <a href="https://glfw.org/download.html">GLFW</a>.
Unzip it and put it in a dependencie folder.
Then go in the GLFW folder and write the commandes :
```bash

	cmake -G "Unix Makefiles"
	make
	sudo make install  

```

# Install GLAD 
Install <a href="https://glad.dav1d.de/">glad</a> from the website (check local files at the end of the page)
Add glad to your project directory in the include folder.

# Compileting
To complie your best program you need to run the command :
``` bash
	
	./compile.sh

```

If you get an error of permition, run the command :
``` bash

	chmod +x compile.sh

```