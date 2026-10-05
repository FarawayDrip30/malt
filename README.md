# malt
## oscillation (v0.1.0)
### whuh?

malt is a game engine written in pure C (except for stb_image.h, according to github, but one day I will fix that...) that uses OpenGL to make 2D games.  

it is designed and currently half-implemented to have several backends for graphics, audio etc to allow for building to multiple platforms, and will have modularity so you only include what you want in your final binary.  

it also has a cool logo:  
![cool logo](https://raw.githubusercontent.com/FarawayDrip30/malt/main/res/img/toothygrin.jpg)  

### usin'

malt is just kinda for me right now and has no documentation. to use it, you will need to download and build the portaudio binary and put libportaudio-2.dll in the same folder as the .exe created, and modify the makefile by changing the IFLAGS to all the folders that your header files are for glfw, glad, cglm and portaudio. here is the filestructure needed from your listed include folder:  
-=-=-=-=-=-=-=-=-=-=-=-=  
include  
|-cglm  
&emsp;|-(everything in cglm. too much stuff to list.)  
|-glad  
&emsp;|-glad.h  
|-GLFW  
&emsp;|-glfw3.h  
&emsp;|-glfw3native.h  
|-KHR (i don't know if you need this one but i must've gotten it for some reason.)  
&emsp;|-khrplatform.h  
|-portaudio  
&emsp;|-pa_win_waveformat.h (might work without?)  
&emsp;|-pa_win_wmme.h (might work without?)  
&emsp;|-portaudio.h  
-=-=-=-=-=-=-=-=-=-=-=-=  
  
you can build it and change the makefile to use whatever compiler you want, but i used w64devkit from [mingw](https://www.mingw-w64.org/downloads/) to use GCC.  
set the CC variable in the makefile to your compiler path or whatever compiler you're using and run "make" (using GNU make). It should create a file called "malt.exe".  

to write custom code, you will have to modify the c files. if you're making new c files, you'll have to add the "path-to-c-file.o" to the OBJ line in the makefile.  

### libraries used
[glfw](https://www.glfw.org/)  
[glad](https://glad.dav1d.de/)  
[cglm](https://github.com/recp/cglm)  
[stb_image.h](https://github.com/nothings/stb/blob/master/stb_image.h)  
[portaudio](https://portaudio.com/)  