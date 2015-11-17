SOURCE=Animation.cpp Entity.cpp FPS.cpp  Game.cpp Render.cpp Stopwatch.cpp Surface.cpp Window.cpp main.cpp util.cpp
MYPROGRAM=0x58
MYINCLUDES=--std=c++11
MYLIBRARIES=-lSDL -lSDLmain -lSDL_gfx -lSDL_ttf
CC=g++

all: $(MYPROGRAM)

$(MYPROGRAM): $(SOURCE)

	$(CC) $(SOURCE) -o$(MYPROGRAM) $(MYLIBRARIES) $(MYINCLUDES)

clean:

	rm -f $(MYPROGRAM)
