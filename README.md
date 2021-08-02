# Solar System
Author : François SUZEAU, 
bachelor's degree graduaded in computer science.

## Introduction
This project is a Solar System simulation written in C++ using the OpenGL 3.3 and SDL2 librairy.
I would like to make it the most accurate as possible using celestial mechanics theory.
This program works with a front C++ application to load textures files, calculate  all the vertices of the objects and their orbit, and to capture keyboard/mouse events.
The back end is the opengGL context that compile shader program written in GLSL and use it to represent object in the 3D world as well.

I try to make it usable directly after the download of the source files but I suggest to re-compile it before. For that a Makefile for windows is available in the parent directory (I am still learning how to configure the build aspect of a project). For now it is only usable on Windows but I strongly consider to make it usable on Linux and Mac system.

## How to use
At the launch, all the textures, audio, font files are loaded. You can follow this load on the terminal command if you had launch the program with it.
After a while the Solar System appears with all planets and moons (note that Mercury is on the other side of the Sun to test lights effects)
For now, planets and moons are only rotating, I haven't merge the celestial mechanics on the main branch yet.

The initial position of the view matrix (camera) is on the ````100, 100, 100```` coordinates. You can move your sight with your keyboord and your mouse. Here is the list of all the move command following this shem : QWERTY/AZERTY.
+ Q/Z : move forward
+ S : 	move backward
+ A/Q : move to the left
+ D : move to the right
+ LCTR : move up
+ LSHIFT : move down
+ Left button mouse (maintain) : orient camera (up, down, right, left)
+ UP : increase the volume of the music
+ DOWN : decrease the volume
+ LEFT : decrease the camera velocity
+ RIGHT : increase the camera velocity
+ ESCAPE : Quit the program

Make sure that the executable file is in the ````bin```` directory.

## ====================== Added features ======================

### 29/06/2021

+ Distance light interaction (the more an object is distant of the sun, the less it receive light) : for now set to 0.35 for linear therm and 0.44 for quadratic therm (stand by)
+ Add a factory method for system (planetary system and solar system) and another factory method for planetes. This update comes with the following features
+ Add a load screen with title and a loading bar which fills up when an object is loaded
+ Fix some bugs and memory leaks
+ Now linkable object files (*.o) will be ignored by git

### 20/07/2021
+ Distant objects behaviour : OpenGL let you to have the possibility to fixe perspective aspect. When you move backward, after a while, the object disappear and his name appear. Also, these name are oriented with the camera position

+ Atmosphere effect : Venus, Earth, Mars, Jupiter and Saturn have transparent and colored atmosphere all arround their surface. It is simply a disk moving in relation with the camera position. These atmosphere are not shadowed because of the impossibility to make a framebuffer work well.


### 21/07/2021
+ Sound : Add a playist feature, now six track are playing one after the other. (Had to initialize pointer to struct Mix_music to NULL -> drop a warning)

### 02/08/2021
+ Framebuffer : Use it to make an HDR mode (For now I cannot make a bloom effect on the light -> skybox not displaying and blur effect not working)
+ Overlay : a simple overlay displaying some information using the framebuffer API
    - Music : Name of the track, compositor and (the record studio or the orchestra)
    - Navigation information : The x, y, z coordinates and the navigation speed based on the light speed multiply by the camera speed (from 0 to 1). The coordinates are not refreshed all the frame due to a certain time calculation and impacting the fluidity, but they are refreshed when the radius length from the origin coordinates of the world to the camera is changing by 10 + (camera speed * 10)
    - Date : the day, the month and the hour recovered on the system running this application

+ Overlay : Now the application adapts with the screen size (recover the screen parameter with a system call function)


## More in coming ...

At the end, I will try to render planets and moons proceduraly. For now these objects are only textured with static view. I will also implements a clicking interactive window when you clik on a planet to show his orbital informations and others.

For the moment I am working on this following aspect :
+ Implements atmosphere effects (like red shadowing on the frontier of the dark side of a planets, bloom and blur effect) : impossible due to a not working framebuffer

+ After all of that, I will implements the most consequent part for me : celestial mechanics (I have allready begin researches).

+ With the celestial mechanics build I will change the apparent size of the planet scaling them with the distance to the sun.

+ By clicking on the planet, we will have the possibility to read information of this body

+ Add a setting configuration

Many of these ideas came to me while I am coding, so I hope more come too.