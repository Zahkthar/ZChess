CXX = gcc
CXXFLAGS = -Wall -Wextra -g # Mettre -O1 ou -O2 à la place de -g pour la version prod
HEADERS_LOCALISATION = include

LDFLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image # -mwindows pour supprimer l'affichage de la console
LIB_LOCALISATION = lib

EXEC = ZChess

all : release

release : main.o game.o utils.o MainMenuState.o OptionMenuState.o GameState.o
	$(CXX) -L $(LIB_LOCALISATION) obj\main.o obj\game.o obj\utils.o obj\MainMenuState.o obj\OptionMenuState.o obj\GameState.o -o bin\$(EXEC) $(LDFLAGS)

main.o : src\main.c
	$(CXX) $(CXXFLAGS) -I $(HEADERS_LOCALISATION) -c src\main.c -o obj\main.o

game.o : src\game.c
	$(CXX) $(CXXFLAGS) -I $(HEADERS_LOCALISATION) -c src\game.c -o obj\game.o

utils.o : src\utils.c
	$(CXX) $(CXXFLAGS) -I $(HEADERS_LOCALISATION) -c src\utils.c -o obj\utils.o

MainMenuState.o : src\MainMenuState.c
	$(CXX) $(CXXFLAGS) -I $(HEADERS_LOCALISATION) -c src\MainMenuState.c -o obj\MainMenuState.o

OptionMenuState.o : src\OptionMenuState.c
	$(CXX) $(CXXFLAGS) -I $(HEADERS_LOCALISATION) -c src\OptionMenuState.c -o obj\OptionMenuState.o

GameState.o : src\GameState.c
	$(CXX) $(CXXFLAGS) -I $(HEADERS_LOCALISATION) -c src\GameState.c -o obj\GameState.o