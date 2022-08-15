build:
	g++ main.cpp --std=c++17 -O3 -o main

run:build
	./main > image.ppm
	pnmtojpeg image.ppm > image.jpeg