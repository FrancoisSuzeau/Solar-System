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
SRC=Main.cpp OpenGlSketch/OpenGlSketch.cpp Shader/Shader.cpp Input/Input.cpp Texture/Texture.cpp Audio/Audio.cpp Camera/Camera.cpp CelestialBody/Geometry/Sphere.cpp CelestialBody/Planete/AtmoPlanete.cpp CelestialBody/Planete/SimplePlanete.cpp CelestialBody/Geometry/Disk.cpp CelestialBody/Ring/Ring.cpp CelestialBody/Planete/PlaneteRing.cpp Text/Text.cpp CelestialBody/Skybox/Skybox.cpp CelestialBody/Star/Star.cpp CelestialBody/System/PlanetarySystem.cpp CelestialBody/System/SolarSystem.cpp StartScreen/StartScreen.cpp CelestialBody/Geometry/Square.cpp Atmosphere/Atmosphere.cpp Atmosphere/StarAtmosphere.cpp Overlay/MusicOverlay.cpp #CelestialBody/Geometry/Disk2.cpp

OBJET=$(SRC:.cpp=.o)

all:${EXEC}

${EXEC}: ${OBJET}
	@${CC}  -o $@ $^ ${LD_SDL_MINGW32} ${LD_SDLIMAGE_MINGW32} ${LD_SDLMIXER_MINGW32} ${LD_SDLTTF_MINGW32} ${LD_GLEW_MINGW32} ${CFLAGS}

# au cas ou .h est modifié

main.o: OpenGlSketch/OpenGlSketch.hpp 
OpenGlSketch.o: OpenGlSketch/OpenGlSketch.hpp Input/Input.hpp Audio/Audio.hpp Camera/Camera.hpp CelestialBody/System/SystemCreator.hpp CelestialBody/System/SolarSystemCreator.hpp StartScreen/StartScreen.hpp CelestialBody/Geometry/Square.cpp CelestialBody/Geometry/Square.hpp Shader/Shader.hpp Overlay/MusicOverlay.hpp
Shader.o: Shader/Shader.hpp
Input.o: Input/Input.hpp
Texture.o: Texture/Texture.hpp
Audio.o: Audio/Audio.hpp
Sphere.o: CelestialBody/Geometry/Sphere.hpp CelestialBody/CelestialBody.hpp
AtmoPlanete.o: CelestialBody/Planete/SimplePlanete.hpp
SimplePlanete.o: CelestialBody/Planete/SimplePlanete.hpp CelestialBody/Geometry/Sphere.hpp Texture/Texture.hpp Text/Text.hpp Atmosphere/Atmosphere.hpp
Camera.o: Camera/Camera.hpp
Disk.o: CelestialBody/Geometry/Disk.hpp CelestialBody/CelestialBody.hpp
Square.o: CelestialBody/Geometry/Square.hpp Shader/Shader.hpp
Ring.o: CelestialBody/Ring/Ring.hpp CelestialBody/Geometry/Disk.hpp Texture/Texture.hpp
PlaneteRing.o: CelestialBody/Planete/PlaneteRing.hpp CelestialBody/Planete/SimplePlanete.hpp CelestialBody/Ring/Ring.hpp
Text.o: Text/Text.hpp Texture/Texture.hpp Shader/Shader.hpp
Skybox.o: CelestialBody/Skybox/Skybox.hpp Shader/Shader.hpp
Star.o: CelestialBody/Star/Star.hpp CelestialBody/Geometry/Sphere.hpp Texture/Texture.hpp Text/Text.hpp Atmosphere/StarAtmosphere.hpp
PlanetarySystem.o: CelestialBody/System/PlanetarySystem.hpp CelestialBody/System/System.hpp CelestialBody/Planete/PlaneteCreator.hpp CelestialBody/Planete/SimplePlaneteCreator.hpp CelestialBody/Planete/AtmoPlaneteCreator.hpp CelestialBody/Planete/PlaneteRingCreator.hpp Atmosphere/Atmosphere.hpp
SolarSystem.o: CelestialBody/System/SolarSystem/hpp CelestialBody/System/PlanetarySystem.hpp CelestialBody/Planete/PlaneteCreator.hpp CelestialBody/Planete/SimplePlaneteCreator.hpp CelestialBody/Planete/AtmoPlaneteCreator.hpp CelestialBody/Planete/PlaneteRingCreator.hpp CelestialBody/System/System.hpp CelestialBody/Star/Star.hpp CelestialBody/Skybox/Skybox.hpp
StartScreen/StartScreen.o: StartScreen/StartScreen.hpp Text/Text.hpp
Atmosphere.o: Atmosphere/Atmosphere.hpp CelestialBody/CelestialBody.hpp CelestialBody/Geometry/Disk.hpp
StarAtmosphere.o: Atmosphere/StarAtmosphere.hpp CelestialBody/CelestialBody.hpp CelestialBody/Geometry/Disk.hpp
#Disk2.o: CelestialBody/Geometry/Disk2.hpp CelestialBody/CelestialBody.hpp
MusicOverlay.o: Overlay/MusicOverlay.hpp Texture/Texture.cpp CelestialBody/Geometry/Disk.cpp

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