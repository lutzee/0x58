SOURCE=Animation.cpp Entity.cpp FPS.cpp  Game.cpp Render.cpp Stopwatch.cpp Surface.cpp Window.cpp main.cpp util.cpp
MYPROGRAM=0x58
MYINCLUDES=-Wunreachable-code -Wunused -g
MYLIBRARIES=-lSDL -lSDLmain -lSDL_gfx
CC=g++

all: $(MYPROGRAM)

$(MYPROGRAM): $(SOURCE)

	$(CC) $(SOURCE) -o$(MYPROGRAM) $(MYLIBRARIES) $(MYINCLUDES)

clean:

	rm -f $(MYPROGRAM)
