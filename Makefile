build:
	g++ main.cpp --std=c++17 -O3 -o main

run:build
	./main 400 100 50 > image.ppm
	pnmtojpeg image.ppm > image.jpeg