premake5 gmake
make
if [ -z ${exec} ]; then
	./bin/linux-x86_64-Debug/first_proj/first_proj
fi