CXX = g++
CXXFLAGS = -O2 -Wall

CXX_W = i686-w64-mingw32-g++
CXXXFLAGS_W =

SRC =  \
	main.cpp \
	functions.cpp \
	timer.cpp \
	game.cpp \
	map.cpp \
	splash.cpp \
	player.cpp \
	tile.cpp \
	enemy.cpp

OBJS = $(SRC:.cpp=.o)
OBJS_W = $(SRC:.cpp=.wo)

LIBS = -lSDLmain -lSDL -lGL -lSDL_image -lSDL_mixer
LIBS_W = -lmingw32 -mwindows -lSDLmain -lSDL -lopengl32 -lglu32 -lSDL_image -lSDL_mixer

debug: CXXFLAGS += -g
debug: linux

all: linux
	echo All done

clean:
	rm -f $(OBJS) foka $(OBJS_W) foka.exe
	echo Clean done

linux: $(OBJS)
	$(CXX) $(CXXFLAGS) -o foka $^ $(LIBS)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<


windows: $(OBJS_W)
	$(CXX_W) $(CXXFLAGS_W) -o foka.exe $^ $(LIBS_W) -static-libgcc -static-libstdc++

%.wo : %.cpp
	$(CXX_W) $(CXXFLAGS_W) -o $@ -c $<
