build:
	g++ main.cpp --std=c++17 -o main

run:build
	./main > image.ppm