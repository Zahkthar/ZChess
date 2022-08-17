# Windows only Makefile :

CXX = gcc
CXXFLAGS = -Wall -Wextra -g# Mettre -O1 ou -O2 à la place de -g pour la version prod
HEADERS_LOCALISATION = include

LDFLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image# -mwindows pour supprimer l'affichage de la console
LIB_LOCALISATION = lib

EXEC = ZChess

SRC = main.c game.c utils.c MainMenuState.c OptionMenuState.c GameState.c
OBJ = $(SRC:.c=.o)

all: ZChess

ZChess: $(OBJ)
	$(CXX) -L $(LIB_LOCALISATION) $(addprefix obj\, $(OBJ)) -o bin\$(EXEC) $(LDFLAGS)

%.o: src\%.c
	$(CXX) $(CXXFLAGS) -I $(HEADERS_LOCALISATION) -c $< -o obj\$@

.PHONY: clean mrproper

clean:
	del /f /q obj\*.o

mrproper: clean
	del /f /q bin\$(EXEC).exe