# Install dependencies :

* g++ the C++ compileur
``` bash

	sudo apt install g++

```
 
* cmake and xorg-dev to build GLFW
``` bash

	sudo apt install build-essential cmake xorg-dev

```

* Adds other dependencies
```bash 

	sudo apt-get install libx11-dev libglu1-mesa-dev freeglut3-dev libglew2.2 libglew-dev libglu1-mesa libgl1-mesa-glx libgl1-mesa-dev libglfw3-dev libglfw3

```

# Installing GLFW :

Install source package for OpenGL from glfw.org/download.html
Go to the GLFW folder and write commandes :
```bash

	cmake -G "Unix Makefiles"
	make
	sudo make install  
```

# Install GLAD :
Install glad zip from the website (check local files at the end of the page)
https://glad.dav1d.de/
Add glad to your project directory

