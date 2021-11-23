all: compile link

compile:
	g++ -I src/include -c main.cpp
link:
	g++ main.o -o main -L src/lib -l sfml-network -l sfml-system