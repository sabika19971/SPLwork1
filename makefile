# Please implement your Makefile rules and targets below.
all: clean link
link: compile
		g++ -o bin/main bin/main.o bin/Auxiliary.o

compile: src/main.cpp src/Auxiliary.cpp include
		g++ -g -c -Wall -Weffc++ -std=c++11 -o bin/main.o src/main.cpp 
		g++ -g -c -Wall -Weffc++ -std=c++11 -o bin/Auxiliary.o src/Auxiliary.cpp
clean: 
		rm -rf bin/*
		
# Customize this file to define how to build your project.