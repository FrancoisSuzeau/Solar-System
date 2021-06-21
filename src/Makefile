# ================== Rappel ======================
# $@ partie gauche de la dépendance (ou cible)
# $< est la premiere dependance
# $^ la liste des dépendances
# @$ pour desactiver l'echo des lignes de commandes en cas d'erreur

CFLAGS=-Wall -m32
LD_SDL_MINGW32=-L./../lib -I./../include -m32 -lmingw32 -lSDL2main -lSDL2
LD_SDLIMAGE_MINGW32=-L./../lib -I./../include -m32 -lmingw32 -lSDL2_image
LD_SDLMIXER_MINGW32=-L./../lib -I./../include -m32 -lmingw32 -lSDL2_mixer
LD_SDLTTF_MINGW32=-L./../lib -I./../include -m32 -lmingw32 -lSDL2_ttf
LD_GLEW_MINGW32=-L./../lib -I./../include -m32 -lmingw32 -lglew32 -lopengl32 -lglu32 -lgdi32 
EXEC=../bin/SS_Project(C++)
CC=g++

#génération de la liste des fichiers objets
# SRC contient liste des fichier sources du projet 
# on pourrait utiliser une construction automatique a l'aide du joker *.c et la commande wildcard mais il faudra gerer les dépendances vis a vis des .h
# SRC=$(wildcard *.c)
SRC=Main.cpp OpenGlSketch/OpenGlSketch.cpp Shader/Shader.cpp Input/Input.cpp Texture/Texture.cpp Audio/Audio.cpp Camera/Camera.cpp CelestialBody/Geometry/Sphere.cpp CelestialBody/Planete/AtmoPlanete.cpp CelestialBody/Planete/SimplePlanete.cpp CelestialBody/Geometry/Disk.cpp CelestialBody/Ring/Ring.cpp CelestialBody/Planete/PlaneteRing.cpp Text/Text.cpp CelestialBody/Skybox/Skybox.cpp CelestialBody/Star/Star.cpp CelestialBody/System/PlanetarySystem.cpp CelestialBody/System/SolarSystem.cpp

OBJET=$(SRC:.cpp=.o)

all:${EXEC}

${EXEC}: ${OBJET}
	@${CC}  -o $@ $^ ${LD_SDL_MINGW32} ${LD_SDLIMAGE_MINGW32} ${LD_SDLMIXER_MINGW32} ${LD_SDLTTF_MINGW32} ${LD_GLEW_MINGW32} ${CFLAGS}

# au cas ou .h est modifié

main.o: OpenGlSketch/OpenGlSketch.h 
OpenGlSketch.o: OpenGlSketch/OpenGlSketch.h Input/Input.h Audio/Audio.h Camera/Camera.h CelestialBody/Skybox/Skybox.h CelestialBody/System/SystemCreator.h CelestialBody/System/SolarSystemCreator.h
Shader.o: Shader/Shader.h
Input.o: Input/Input.h
Texture.o: Texture/Texture.h
Audio.o: Audio/Audio.h
Sphere.o: CelestialBody/Geometry/Sphere.h CelestialBody/CelestialBody.h
AtmoPlanete.o: CelestialBody/Planete/AtmoPlanete.h CelestialBody/Planete/SimplePlanete.h
SimplePlanete.o: CelestialBody/Planete/SimplePlanete.h CelestialBody/Geometry/Sphere.h Texture/Texture.h Text/Text.h
Camera.o: Camera/Camera.h
Disk.o: CelestialBody/Geometry/Disk.h CelestialBody/CelestialBody.h
Ring.o: CelestialBody/Ring/Ring.h CelestialBody/Geometry/Disk.h Texture/Texture.h
PlaneteRing.o: CelestialBody/Planete/PlaneteRing.h CelestialBody/Planete/SimplePlanete.h CelestialBody/Ring/Ring.h
Text.o: Text/Text.h Texture/Texture.h Shader/Shader.h
Skybox.o: CelestialBody/Skybox/Skybox.h Shader/Shader.h
Star.o: CelestialBody/Star/Star.h CelestialBody/Geometry/Sphere.h Texture/Texture.h Text/Text.h
PlanetarySystem.o: CelestialBody/System/PlanetarySystem.h CelestialBody/Planete/AtmoPlanete.h CelestialBody/Planete/PlaneteRing.h CelestialBody/Planete/SimplePlanete.h CelestialBody/System/System.h
SolarSystem.o: CelestialBody/System/SolarSystem/h CelestialBody/System/PlanetarySystem.h CelestialBody/Planete/AtmoPlanete.h CelestialBody/Planete/PlaneteRing.h CelestialBody/Planete/SimplePlanete.h CelestialBody/System/System.h CelestialBody/Star/Star.h
SystemCreator.h: CelestialBody/System/System.h
PlanetarySystemCreator.h: CelestialBody/System/SystemCreator.h CelestialBody/System/PlanetarySystem.h
SolarSystemCreator.h: CelestialBody/System/SystemCreator.h CelestialBody/System/SolarSystem.h
CelestialBody.h: Shader/Shader.h

%.o:%.cpp
	@$(CC) -o $@ -c $< ${LD_SDL_MINGW32} ${LD_SDLIMAGE_MINGW32} ${LD_SDLMIXER_MINGW32} ${LD_SDLTTF_MINGW32} ${LD_GLEW_MINGW32} ${CFLAGS}

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