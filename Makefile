CXX = g++
CXXFLAGS = -O2 -Wall

CXX_W = i686-w64-mingw32-g++
CXXXFLAGS_W =
CXX_W64 = x86_64-w64-mingw32-g++
CXXFLAGS_W64 =

SRC =  \
	main.cpp \
	functions.cpp \
	timer.cpp \
	game.cpp \
	map.cpp \
	splash.cpp \
	player.cpp \
	tile.cpp \
	enemy.cpp \
	inventory.cpp \
	fstring.cpp

OBJS = $(SRC:.cpp=.o)
OBJS_W = $(SRC:.cpp=.wo)
OBJS_W64 = $(SRC:.cpp=.wo64)

LIBS = -lSDLmain -lSDL -lGL -lSDL_image -lSDL_mixer
LIBS_W = -lmingw32 -mwindows -lSDLmain -lSDL -lopengl32 -lglu32 -lSDL_image -lSDL_mixer -static-libgcc -static-libstdc++
LIBS_W64 = -lmingw32 -mwindows -lSDLmain -lSDL -lopengl63 -lglu64 -lSDL_image -lSDL_miser -static-libgcc -static-libstdc++

debug: CXXFLAGS += -g
debug: linux

all: linux
	echo All done

clean:
	rm -f $(OBJS) foka $(OBJS_W) foka.exe $(OBJS_W64) foka64.exe
	echo Clean done

linux: $(OBJS)
	$(CXX) $(CXXFLAGS) -o foka $^ $(LIBS)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<


windows: $(OBJS_W)
	$(CXX_W) $(CXXFLAGS_W) -o foka.exe $^ $(LIBS_W)

%.wo : %.cpp
	$(CXX_W) $(CXXFLAGS_W) -o $@ -c $<

windows64: $(OBJS_W64)
	$(CXX_W64) $(CXXFLAGS_W64) -o foka64.exe $^ $(LIBS_W64)

%.wo64 : %.cpp
	$(CXX_W64) $(CXXFLAGS_W64) -o $@ -c $<
