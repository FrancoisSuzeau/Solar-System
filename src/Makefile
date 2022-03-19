# ================== Reminder ======================
# $@ left side of rule (target)
# $< dependency of the target
# $^ list all dependencies
# @$ Deactivate echo

DEBUG ?= 1
ifeq ($(DEBUG), 1)
	CFLAGS = -Wextra -m64 -g
else
	CFLAGS = -Wextra -m64 -DNDEBUG
endif

LD_SDL_MINGW32=-L./../lib -I./../include -m64 -lmingw32 -lSDL2main -lSDL2
LD_SDLIMAGE_MINGW32=-L./../lib -I./../include -m64 -lmingw32 -lSDL2_image
LD_SDLMIXER_MINGW32=-L./../lib -I./../include -m64 -lmingw32 -lSDL2_mixer
LD_SDLTTF_MINGW32=-L./../lib -I./../include -m64 -lmingw32 -lSDL2_ttf
LD_GLEW_MINGW32=-L./../lib -I./../include -m64 -lmingw32 -lglew32 -lopengl32 -lglu32 -lgdi32
LD_ASSIMP_MINGW32=-L./../lib -I./../include -m64 -lmingw32 -lassimp

ifeq ($(DEBUG), 1)
	EXEC=..\build\debug\SolarSystem
else
	EXEC=..\build\release\SolarSystem
endif

CC=g++

# Generate source files list
SRC=Main.cpp ContextManager.cpp
SRC+=Loader\Loader.cpp
SRC+=ErrorHandler\ErrorHandler.cpp
SRC+=InOut\Input\Input.cpp InOut\Audio\Audio.cpp
SRC+=Objects\Object.cpp Objects\BasicObjects\Square.cpp Objects\BasicObjects\Sphere.cpp Objects\Spaceship\Spaceship.cpp
SRC+=Renderers\BasicRenderers\SquareRenderer.cpp Renderers\BasicRenderers\SphereRenderer.cpp
SRC+=Shader\Shader.cpp
SRC+=Skybox\Skybox.cpp
SRC+=Model\Mesh.cpp Model\Model.cpp
SRC+=Application\Camera\Camera.cpp
SRC+=Objects\TexturedObjects\Star\Star.cpp
SRC+=Renderers\TexturedRenderers\StarRenderer\StarRenderer.cpp
SRC+=Application\Texture\Texture.cpp
SRC+=Application\Application.cpp Application\DataManager.cpp Application\Settings\Settings.cpp Application\Overlay\Overlay.cpp
SRC+=..\lib\imgui\imgui_demo.cpp ..\lib\imgui\imgui_draw.cpp ..\lib\imgui\imgui_impl_opengl3.cpp ..\lib\imgui\imgui_impl_sdl.cpp ..\lib\imgui\imgui_tables.cpp ..\lib\imgui\imgui_widgets.cpp ..\lib\imgui\imgui.cpp

OBJET=$(SRC:.cpp=.o)
DEP=$(SRC:.cpp=.d)

all:${EXEC}
ifeq ($(DEBUG), 1)
	@echo "GENERATING IN DEBUG MODE -> DONE"
else
	@echo "GENERATING IN RELEASE MODE -> DONE"
endif

# Comile target with modules
${EXEC}: ${OBJET}
	@${CC}  -o $@ $^ ${LD_SDL_MINGW32} ${LD_SDLIMAGE_MINGW32} ${LD_SDLMIXER_MINGW32} ${LD_SDLTTF_MINGW32} ${LD_GLEW_MINGW32} ${LD_ASSIMP_MINGW32} ${CFLAGS}

# include all .d files
-include $(DEP)

# Compile all modules
%.o:%.cpp
	@echo Compiling : $<
	@$(CC) -o $@ -c $< ${LD_SDL_MINGW32} ${LD_SDLIMAGE_MINGW32} ${LD_SDLMIXER_MINGW32} ${LD_SDLTTF_MINGW32} ${LD_GLEW_MINGW32} ${LD_ASSIMP_MINGW32} ${CFLAGS}

# Config all dependencies (header files)
%.d:%.cpp
	@$(CC) -MM -MD -o $@ $< ${LD_SDL_MINGW32} ${LD_SDLIMAGE_MINGW32} ${LD_SDLMIXER_MINGW32} ${LD_SDLTTF_MINGW32} ${LD_GLEW_MINGW32} ${LD_ASSIMP_MINGW32} ${CFLAGS}



# Window only
.PHONY: clean mrpoper

clean:
	del $(OBJET) $(DEP)

mrpoper: clean
	del $(EXEC).exe