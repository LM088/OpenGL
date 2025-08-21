# CMake Demo 

CMake is an automation took to build makefiles. Obviously, we only have a couple files here but as the number of files keep increasing, building everything using makefiles is going to be tedious. You could also use the same cmakelists.txt file to generate build files for other build systems like ninja and visual studio.  

CMake uses out-of-source builds, so make sure your CMakeLists.txt file is in the source directory but the actually builds themselves must be in a separate directory within the source dir. named builds. 

Cd into builds/ and run the command 
```
cmake .. 
```
That will create the required makefiles, after which you can use "make" command to build the executable. 
