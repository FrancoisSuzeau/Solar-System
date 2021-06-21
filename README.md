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

The initial position of the view matrix (camera) is on the ````150, 150, 150```` coordinates. You can move your sight with your keyboord and your mouse. Here is the list of all the move command following this shem : QWERTY/AZERTY.
+ Q/Z : move forward
+ S : 	move backward
+ A/Q : move to the left
+ D : move to the right
+ LCTR : move up
+ LSHIFT : move down
+ Left button mouse (maintain) : orient camera (up, down, right, left)
+ ESCAPE : Quit the program

Make sure that the executable file is in the ````bin```` directory.

## More in coming ...

At the end, I will try to render planets and moons proceduraly. For now these objects are only textured with static view. I will also implements a clicking interactive window when you clik on a planet to show his orbital informations and others.

For the moment I am working on this following aspect :
+ Implements atmosphere effects (like red shadowing on the frontier of the dark side of a planets)
+ Implements distance light interaction (the more an object is distant of the sun, the less it receive light)

With this feature, I will follow with distant objects behaviour. OpenGL let you to have the possibility to fixe perspective aspect. When you move backward, after a while, the object will disappear and his name will appear. With that I will make sur that his name is always orientate according to the camera.


After all of that, I will implements the most consequent part for me : celestial mechanics (I have allready begin researches).

Many of these ideas came to me while I was coding, so I hope more come too.