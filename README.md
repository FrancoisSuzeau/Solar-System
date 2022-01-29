# Solar System
Author : François SUZEAU, 
bachelor's degree graduaded in computer science.

## Introduction
This project is a Solar System simulation written in C++ using the OpenGL 3.3 and SDL2 librairy.
I would like to make it the most accurate as possible using celestial mechanics theory.
This program works with a back C++ application to load textures files, calculate  all the vertices of the objects and their orbit, and to capture keyboard/mouse events.
The front is the opengGL context that compile shader program written in GLSL and use it to represent object in the 3D world as well.

I try to make it usable directly after the download of the source files but I suggest to re-compile it before. For that a Makefile for windows is available in the parent directory. You have the possibility to build the project for a release or debug version with : ``DEBUG=0`` or ``DEBUG=1`` option when you call the make feature of your compilator. For now it is only usable on Windows but I strongly consider to make it usable on Linux and Mac system.

For developpment i use this configuration :
+ Intel(R) Xeon(R) CPU E5-2678 v3 2.50GHz
+ 12 Go RAM
+ Nvidia GeForce GTX 1080 (DirectX 12 FL 12.1)

But I can run the simulation on my laptop with good performance :
+ Intel(R) Core(TM) I5-10210U CPU 1.60GHz
+ 8 Go RAM
+ Intel(R) UHD Graphics (DirectX 12 FL 12.1)

## How to use
At the launch, all the textures, audio, font files are loaded and config file. You can follow this load on the terminal command if you had launch the program with it.
After a while the Solar System appears with all planets and moons.
For now, planets and moons are only rotating, I haven't create orbital mechanics yet

The initial position of the ship is on the ``0, 9000, 0`` coordinates. You can move the position with the keyboard, the ship orientation with the left button of the mouse and the camera position with the right button. Here is the list of all the move command following this shem : QWERTY/AZERTY.
+ W/Z : move forward
+ S : 	move backward
+ A/Q : move to the left
+ D : move to the right
+ Q/A : set speed to minimum
+ E : set speed to maximum
+ LCTR : move up
+ LSHIFT : move down
+ Left button mouse (maintain) : orient ship (up, down, right, left)
+ Right button mouse (maintain) : orient camera (all around the ship)
+ ESCAPE : Display the settings menu
+ Mouse Wheel : Change the navigation speed by 10% the speed of the light
+ SPACE : Display body information

Make sure that the executable file is in the ````build/debug```` ````or build/release```` directory.
You will see a ````config.save```` file in the same directory where configuration are saved. You can change them before launch but make sure you respect the value that are available.
It is possible now to change musique option but you have to pause the simulation to display the mouse.

## Possible issues
+ The program require OpenGL version 4.0 or more. It is possible that the program doesn't run if you don't have this version. You can check your version with this tool : https://www.realtech-vr.com/home/glview


## ====================== Added features ======================

### 29/06/2021

+ Distance light interaction (the more an object is distant of the sun, the less it receive light) : for now set to 0.35 for linear therm and 0.44 for quadratic therm (stand by)
+ Add a factory method for system (planetary system and solar system) and another factory method for planetes. This update comes with the following features
+ Add a load screen with title and a loading bar which fills up when an object is loaded
+ Fix some bugs and memory leaks
+ Now linkable object files (*.o) will be ignored by git

### 20/07/2021 (change atmosphere effect the 27/09/2021)
+ Distant objects behaviour : OpenGL let you to have the possibility to fixe perspective aspect. When you move backward, after a while, the object disappear and his name appear. Also, these name are oriented with the camera position

+ Atmosphere effect : Venus, Earth, Mars, have transparent and colored atmosphere all arround their surface.

### 21/07/2021
+ Sound : Add a playist feature, now six track are playing one after the other. (Had to initialize pointer to struct Mix_music to NULL -> drop a warning)

### 02/08/2021
+ Framebuffer : Use it to make an HDR mode
+ Overlay : a simple overlay displaying some information using the framebuffer API
    - Music : Name of the track, compositor and (the record studio or the orchestra)
    - Navigation information : the navigation speed based on the light speed multiply by the camera speed (from 0 to 200).
    - Date : the day, the month and the hour recovered on the system running this application

+ Overlay : Now the application adapts with the screen size (recover the screen parameter with a system call function)

### 04/08/2021
+ Settings frame : a simple frame where we can choose settings (hdr, exposure, speed navigation, music, music volume and if overlay is display or not)

### 14/09/2021
+ We can now have a little window showing planete information (for now it is only displaying the name of the body)
+ Use the mouse wheel to change speed navigation

### 17/09/2021
+ Add a setting option : Can choose to show name of body or not
+ Optimization : one shader per object type displayed (one for text, one for overlay/setting/information frame, one per body type, one for atmosphere)
+ Optimization : font are only loaded by SDL once and then Opengl use the SDL_Surface pointer to build the opengl object
+ Optimization : Pointer test at each allocation/use and pointer released

### 27/09/2021
+ Scalling the simulation with Earth as scale (multiply by 30)
+ Name disapear dynamiquely with view sized of the body
+ Moon have now their name displaying
+ Speed navigation : with a percent of light speed as unit
+ Setting : add option to show planete information or not
+ Correcting cross machine errors : adapte GLSL script to OpenGL version installed on the host machine (Windows)

### 29/07/2021
+ Adding particule effect when moving into scene
+ Fix a bug on settings feature but have to perform design

### 30/09/2021
+ Perform design on settings display

### 15/10/2021
+ adding the Assimp library to load model (.obj file)
+ Create a asteroid field display

### 30/10/2021
+ Changing navigation by a third person camera with ship as moveable
+ undisplay particule (for now, to adapt it to new navigation)

### 08/11/2021
+ Implement an asteroid field with Model Instanced Object (3500 because of low performance pc)

### 18/11/2021
+ Adding normal map for all object exept for Sun, Spaceship, and Mars/Earth Cloud (making Rings so smooth)
+ Testing parallax method but create bug so for now it is only available for Rings

### 20/11/2021
+ Refactoring the settings class on Text members (use vector)
+ Tracking all textures, VAOs, VBOs, IBOs, frambuffers, renderBuffers bind by OpenGL are unbind and correctly deleted

### 23/11/2021
+ Bloomed the Sun, and planete's atmosphere (Venus, Earth, Mars, Jupiter, Saturn, Uranus, Neptune)
+ Adding gradient atenuation of how the atmosphere turn black when on the hidden face of a planete (not facing the sun) making a nice red/violet smooth sunrise for Earth and other color for other planetes
+ Changing how HDR effect work and values of light and ambient strenght in shaders

### 28/11/2021
Big refactoring session
+ Extract class : Renderdata used to pass many parameters
+ Now there is a planete renderer and texture are stick to ONE sphere
+ No more factory method for planete make easy to modify without taking care witch type of planete this is

### 04/12/2021
Changing the way of how the navigation is done
+ This not the ship that moving anymore but object around him

### 11/01/2022
Integrating Dear ImGui for User interface
+ Overlay : music, Navigation and application information
+ Settings : Three TabMenu (Navigation options, HUD, Performance)
+ Settings display : now using escape
+ Can change music track, volume, mute options (soon radio channel) directly with overlay
+ Settings : Asteroid count influence performance so you can choose the amount

### 18/01/2022
+ Now overlay navigation display solar radiation and gravitational influence by body (if near to a planete then display his gravitational influcence and his possible moon's influence)
+ Create a config file management and a button for saving preferences for performance and HUD tab menu
+ Body's information : integrating DearImgui and change display key

### 20/01/2022
+ Can now chose the skin of the ship

### 29/01/2022
+ Implement ship maneuverability
+ Implement speed reducing when approching a body

## More in coming ...
At the end, I will try to render planets and moons proceduraly. For now these objects are only textured with static view. I will also implements a clicking interactive window when you clik on a planet to show his orbital informations and others.

For the moment I am working on this following aspect :
+ Overlay and Audio : create radio with his own kind of music
+ After all of that, I will implements the most consequent part for me : celestial mechanics (I have allready begin researches).
+ Change particule movement by ship movement not by camera movement
+ bug correction on skybox (see the borders)
+ Implement hit box to prevent to pass through body (have to extract method to calculate radius coming from body position)
+ Make a Linux version : Have to think twice because I have to change screen adaptation of the overlay

Many of these ideas came to me while I am coding, so I hope more come too.