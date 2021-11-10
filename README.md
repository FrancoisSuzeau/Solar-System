# Solar System
Author : François SUZEAU, 
bachelor's degree graduaded in computer science.

## Introduction
This project is a Solar System simulation written in C++ using the OpenGL 3.3 and SDL2 librairy.
I would like to make it the most accurate as possible using celestial mechanics theory.
This program works with a back C++ application to load textures files, calculate  all the vertices of the objects and their orbit, and to capture keyboard/mouse events.
The front is the opengGL context that compile shader program written in GLSL and use it to represent object in the 3D world as well.

I try to make it usable directly after the download of the source files but I suggest to re-compile it before. For that a Makefile for windows is available in the parent directory (I am still learning how to configure the build aspect of a project). For now it is only usable on Windows but I strongly consider to make it usable on Linux and Mac system.

## How to use
At the launch, all the textures, audio, font files are loaded. You can follow this load on the terminal command if you had launch the program with it.
After a while the Solar System appears with all planets and moons.
For now, planets and moons are only rotating, I haven't create orbital mechanics yet

The initial position of the ship is on the ````1, 9000, 1```` coordinates. You can move the position with the keyboard, the ship orientation with the left button of the mouse and the camera position with the right button. Here is the list of all the move command following this shem : QWERTY/AZERTY.
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
+ UP : increase the volume of the music (deprecated)
+ DOWN : decrease the volume (deprecated)
+ ESCAPE : Quit the program
+ P : Display the settings menu
+ Mouse Wheel : Change the navigation speed by 10% the speed of the light
+ I : Display body information 

Make sure that the executable file is in the ````bin```` directory.

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
+ Framebuffer : Use it to make an HDR mode (For now I cannot make a bloom effect on the light -> skybox not displaying and blur effect not working)
+ Overlay : a simple overlay displaying some information using the framebuffer API
    - Music : Name of the track, compositor and (the record studio or the orchestra)
    - Navigation information : the navigation speed based on the light speed multiply by the camera speed (from 0 to 200).
    - Date : the day, the month and the hour recovered on the system running this application

+ Overlay : Now the application adapts with the screen size (recover the screen parameter with a system call function)

### 04/08/2021
+ Settings frame : a simple frame where we can choose settings (hdr, exposure, speed navigation, music, music volume and if overlay is display or not)
+ Cliking on a setting button : It adatps on the screen dimension

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

## More in coming ...
At the end, I will try to render planets and moons proceduraly. For now these objects are only textured with static view. I will also implements a clicking interactive window when you clik on a planet to show his orbital informations and others.

For the moment I am working on this following aspect :
+ Implements atmosphere effects (like red shadowing on the frontier of the dark side of a planets, bloom and blur effect) : impossible due to a not working framebuffer

+ Overlay : Display the sphere influence when approching a body or interplanetary travel

+ After all of that, I will implements the most consequent part for me : celestial mechanics (I have allready begin researches).

+ Change particule class to a move effect by the ship orientation

+ Create an asteroid field class with Opengl Instanced Object to optimize the render

+ Big refactoring phase

+ Implement hit box to prevent to pass through body (have to extract method to calculate radius coming from body position)

+ rescaling object due to a high value error of floating point. Value of translation are too high so error are high to

+ Make a Linux version : Have to think twice because I have to change screen adaptation of the overlay

Many of these ideas came to me while I am coding, so I hope more come too.