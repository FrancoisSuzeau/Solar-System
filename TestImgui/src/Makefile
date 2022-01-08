# ================== Rappel ======================
# $@ partie gauche de la dépendance (ou cible)
# $< est la premiere dependance
# $^ la liste des dépendances
# @$ pour desactiver l'echo des lignes de commandes en cas d'erreur

CFLAGS=-Wall -m64
LD_SDL_MINGW32=-L./../lib -I./../include -m64 -lmingw32 -lSDL2main -lSDL2
LD_SDLIMAGE_MINGW32=-L./../lib -I./../include -m64 -lmingw32 -lSDL2_image
LD_SDLMIXER_MINGW32=-L./../lib -I./../include -m64 -lmingw32 -lSDL2_mixer
LD_SDLTTF_MINGW32=-L./../lib -I./../include -m64 -lmingw32 -lSDL2_ttf
LD_GLEW_MINGW32=-L./../lib -I./../include -m64 -lmingw32 -lglew32 -lopengl32 -lglu32 -lgdi32
LD_ASSIMP_MINGW32=-L./../lib -I./../include -m64 -lmingw32 -lassimp
EXEC=../bin/testImgui
CC=g++

#génération de la liste des fichiers objets
# SRC contient liste des fichier sources du projet 
# on pourrait utiliser une construction automatique a l'aide du joker *.c et la commande wildcard mais il faudra gerer les dépendances vis a vis des .h
# SRC=$(wildcard *.c)
SRC=Main.cpp imgui/imgui_demo.cpp imgui/imgui_draw.cpp imgui/imgui_impl_opengl3.cpp imgui/imgui_impl_sdl.cpp imgui/imgui_tables.cpp imgui/imgui_widgets.cpp imgui/imgui.cpp

OBJET=$(SRC:.cpp=.o)

all:${EXEC}

${EXEC}: ${OBJET}
	@${CC}  -o $@ $^ ${LD_SDL_MINGW32} ${LD_SDLIMAGE_MINGW32} ${LD_SDLMIXER_MINGW32} ${LD_SDLTTF_MINGW32} ${LD_GLEW_MINGW32} ${LD_ASSIMP_MINGW32} ${CFLAGS}

# au cas ou .h est modifié

main.o:

%.o:%.cpp
	@$(CC) -o $@ -c $< ${LD_SDL_MINGW32} ${LD_SDLIMAGE_MINGW32} ${LD_SDLMIXER_MINGW32} ${LD_SDLTTF_MINGW32} ${LD_GLEW_MINGW32} ${LD_ASSIMP_MINGW32} ${CFLAGS}

#La partie en commentaire représente ce que la ligne au dessus fait
#function.o: function.c
#	@${CC} -o function.o -c function.c ${CFLAGS}

#main.o:main.c headers.h
#	@${CC} -o main.o -c main.c ${CFLAGS}


# Sur unix seulement
#.PHONY: clean mrpoper

#clean:
#	@rm -rf *.o

#mrpoper: clean
#	@rm -rf $(EXEC)

# Sur windows seulement
.PHONY: clean mrpoper

clean:
	del ${OBJET}

mrpoper: clean
	del $(EXEC)