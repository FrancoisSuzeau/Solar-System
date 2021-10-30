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
EXEC=../bin/SS_Project(C++)
CC=g++

#génération de la liste des fichiers objets
# SRC contient liste des fichier sources du projet 
# on pourrait utiliser une construction automatique a l'aide du joker *.c et la commande wildcard mais il faudra gerer les dépendances vis a vis des .h
# SRC=$(wildcard *.c)
SRC=Main.cpp OpenGlSketch/OpenGlSketch.cpp Shader/Shader.cpp Input/Input.cpp Texture/Texture.cpp Audio/Audio.cpp Camera/Camera.cpp CelestialBody/Geometry/Sphere.cpp CelestialBody/Planete/AtmoPlanete.cpp CelestialBody/Planete/SimplePlanete.cpp CelestialBody/Geometry/Disk.cpp CelestialBody/Ring/Ring.cpp CelestialBody/Planete/PlaneteRing.cpp Text/Text.cpp CelestialBody/Skybox/Skybox.cpp CelestialBody/Star/Star.cpp CelestialBody/System/PlanetarySystem.cpp CelestialBody/System/SolarSystem.cpp StartScreen/StartScreen.cpp CelestialBody/Geometry/Square.cpp Atmosphere/Atmosphere.cpp Overlay/Overlay.cpp Settings/Settings.cpp PlaneteInformation/PlaneteInformation.cpp Particule/Particule.cpp Model/Mesh.cpp Model/Model.cpp Spaceship/Spaceship.cpp CelestialBody/AsteroidField/AsteroidField.cpp

OBJET=$(SRC:.cpp=.o)

all:${EXEC}

${EXEC}: ${OBJET}
	@${CC}  -o $@ $^ ${LD_SDL_MINGW32} ${LD_SDLIMAGE_MINGW32} ${LD_SDLMIXER_MINGW32} ${LD_SDLTTF_MINGW32} ${LD_GLEW_MINGW32} ${LD_ASSIMP_MINGW32} ${CFLAGS}

# au cas ou .h est modifié

main.o: OpenGlSketch/OpenGlSketch.hpp 
OpenGlSketch.o: OpenGlSketch/OpenGlSketch.hpp Input/Input.hpp Audio/Audio.hpp Camera/Camera.hpp CelestialBody/System/SystemCreator.hpp CelestialBody/System/SolarSystemCreator.hpp StartScreen/StartScreen.hpp CelestialBody/Geometry/Square.hpp Shader/Shader.hpp Overlay/Overlay.hpp Settings/Settings.hpp Particule/Particule.hpp Spaceship/Spaceship.hpp
Shader.o: Shader/Shader.hpp
Input.o: Input/Input.hpp
Texture.o: Texture/Texture.hpp
Audio.o: Audio/Audio.hpp
Sphere.o: CelestialBody/Geometry/Sphere.hpp CelestialBody/CelestialBody.hpp Shader/Shader.hpp
AtmoPlanete.o: CelestialBody/Planete/SimplePlanete.hpp Shader/Shader.hpp
SimplePlanete.o: CelestialBody/Planete/SimplePlanete.hpp CelestialBody/Geometry/Sphere.hpp Texture/Texture.hpp Text/Text.hpp Atmosphere/Atmosphere.hpp PlaneteInformation/PlaneteInformation.hpp Shader/Shader.hpp
Camera.o: Camera/Camera.hpp Input/Input.hpp Spaceship/Spaceship.hpp
Disk.o: CelestialBody/Geometry/Disk.hpp CelestialBody/CelestialBody.hpp Shader/Shader.hpp
Square.o: CelestialBody/Geometry/Square.hpp Shader/Shader.hpp
Ring.o: CelestialBody/Ring/Ring.hpp CelestialBody/Geometry/Disk.hpp Texture/Texture.hpp Shader/Shader.hpp
PlaneteRing.o: CelestialBody/Planete/PlaneteRing.hpp CelestialBody/Planete/SimplePlanete.hpp CelestialBody/Ring/Ring.hpp Shader/Shader.hpp
Text.o: Text/Text.hpp Texture/Texture.hpp Shader/Shader.hpp
Skybox.o: CelestialBody/Skybox/Skybox.hpp Shader/Shader.hpp
Star.o: CelestialBody/Star/Star.hpp CelestialBody/Geometry/Sphere.hpp Texture/Texture.hpp Atmosphere/Atmosphere.hpp
PlanetarySystem.o: CelestialBody/System/PlanetarySystem.hpp CelestialBody/System/System.hpp CelestialBody/Planete/PlaneteCreator.hpp CelestialBody/Planete/SimplePlaneteCreator.hpp CelestialBody/Planete/AtmoPlaneteCreator.hpp CelestialBody/Planete/PlaneteRingCreator.hpp Atmosphere/Atmosphere.hpp Text/Text.hpp Shader/Shader.hpp PlaneteInformation/PlaneteInformation.hpp
SolarSystem.o: CelestialBody/System/SolarSystem.hpp CelestialBody/System/PlanetarySystem.hpp CelestialBody/Planete/PlaneteCreator.hpp CelestialBody/Planete/SimplePlaneteCreator.hpp CelestialBody/Planete/AtmoPlaneteCreator.hpp CelestialBody/Planete/PlaneteRingCreator.hpp CelestialBody/System/System.hpp CelestialBody/Star/Star.hpp CelestialBody/Skybox/Skybox.hpp Shader/Shader.hpp PlaneteInformation/PlaneteInformation.hpp CelestialBody/AsteroidField/AsteroidField.hpp
StartScreen/StartScreen.o: StartScreen/StartScreen.hpp Text/Text.hpp Shader/Shader.hpp
Atmosphere.o: Atmosphere/Atmosphere.hpp CelestialBody/Geometry/Sphere.hpp Shader/Shader.hpp
Overlay.o: Overlay/Overlay.hpp CelestialBody/Geometry/Square.hpp Text/Text.hpp Shader/Shader.hpp
Settings.o: Settings/Settings.hpp CelestialBody/Geometry/Square.hpp Text/Text.hpp Shader/Shader.hpp Input/Input.hpp
PlaneteInformation.o: PlaneteInformation/PlaneteInformation.hpp CelestialBody/Geometry/Square.hpp Text/Text.hpp Shader/Shader.hpp
Particule.o: Particule/Particule.hpp Shader/Shader.hpp CelestialBody/Geometry/Sphere.hpp Input/Input.hpp Spaceship/Spaceship.hpp
Mesh.o: Model/Mesh.hpp Shader/Shader.hpp
Model.o: Model/Model.hpp Model/Mesh.hpp Shader/Shader.hpp
Spaceship.o : Spaceship/Spaceship.hpp Model/Model.hpp Shader/Shader.hpp Input/Input.hpp
AsteroidField.o: CelestialBody/AsteroidField.hpp Model/Model.hpp Shader/Shader.hpp

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