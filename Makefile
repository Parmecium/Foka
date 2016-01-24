CXX = g++
CXXFLAGS = -O2 -Wall

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

LIBS = -lSDLmain -lSDL -lGL -lSDL_image -lSDL_mixer

debug: CXXFLAGS += -g
debug: linux

all: linux
	echo All done

clean:
	rm -f $(OBJS) foka
	echo Clean done

linux: $(OBJS)
	$(CXX) $(CXXFLAGS) -o foka $^ $(LIBS)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<
