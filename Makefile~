all: linux windows


linux: main.o functions.o game.o player.o splash.o tile.o
	g++ -o foka main.o functions.o game.o player.o splash.o tile.o -lSDLmain -lSDL -lGL -lSDL_image -lSDL_mixer

main.o: main.cpp
	g++ -c -o main.o main.cpp

functions.o: functions.cpp
	g++ -c -o functions.o functions.cpp

game.o: game.cpp
	g++ -c -o game.o game.cpp

player.o: player.cpp
	g++ -c -o player.o player.cpp

splash.o: splash.cpp
	g++ -c -o splash.o splash.cpp

tile.o: tile.cpp
	g++ -c -o tile.o tile.cpp


windows: mainW.o functionsW.o gameW.o playerW.o splashW.o tileW.o
	i686-w64-mingw32-g++ -o parmecium.exe mainW.o functionsW.o gameW.o playerW.o splashW.o tileW.o -static-libgcc -static-libstdc++ -lmingw32 -lSDLmain -lSDL -lopengl32 -lglu32 -lSDL_image

mainW.o: main.cpp
	i686-w64-mingw32-g++ -c -o mainW.o main.cpp

functionsW.o: functions.cpp
	i686-w64-mingw32-g++ -c- o functionsW.o functions.cpp

gameW.o: game.cpp
	i686-w64-mingw32-g++ -c -o gameW.o game.cpp

playerW.o: player.cpp
	i686-w64-mingw32-g++ -c -o playerW.o player.cpp

splashW.o: splash.cpp
	i686-w64-mingw32-g++ -c -o splashW.o splash.cpp

tileW.o: tile.cpp
	i686-w64-mingw32-g++ -c -o tileW.o tile.cpp


clean:
	rm -rf *.o foka foka.exe
