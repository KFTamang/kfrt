build:
	g++ main.cpp --std=c++17 -O3 -o main

run:build
	./main 400 100 50 > image.ppm
	pnmtojpeg image.ppm > image.jpeg

profile:
	g++ -pg main.cpp -O3 -g -o main_for_profile
	./main_for_profile 90 10 10 > profile.ppm
	pnmtojpeg profile.ppm > profile.jpeg
	gprof main_for_profile > profile_result.txt