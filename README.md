# TurboVis
A turbomachine visualisation tool, made for the TU Delft AE4206 Turbomachinery course.
Enables real-time exploration and experimentation of load-coefficient based turbomachine design.

![Screenshot of TurboVis](screenshot.png)

## Installation
### Windows
Download the Windows binary and extract it to a directory on your computer together with the *turbovis.ini* file.
The provided file is a 32-bit executable that should run on both x64 and x86 systems.

### Ubuntu (x64)
Move the binary executable and the *turbovis.ini* file to a directory on your computer. Depending on your desktop, you might be able to doubleclick the program to run it. Otherwise, you can always run the program as *./TurboVis*.

If you place the program (along with the ini) in */usr/bin/*, you will be able to call it from anywhere using a simple *TurboVis*.

In case you experience problems with permissions, be sure to check if the program is set to allow execution, and if not change it using *chmod +X TurboVis*.

### OSX
Unfortunately I don't have a Mac to build the software on myself readily available, so releases for OSX might be a little slower. If you want though, you can build it yourself!
#### Building on OSX
1. [Install Homebrew (if you don't have it already). This should be as simple as copy-pasting a terminal command from https://brew.sh/](https://brew.sh/).
2. Install CMake with `brew install cmake`
3. Verify cmake has been correctly installed by running `cmake`.
4. Clone this repository to `/some/path/`, 
5. `mkdir /some/path/build/`
6. In `/some/path/build/`, run the command `cmake ..` to generate build files
7. Build the program with `build`. This should create an executable that can either be run by double-clicking, or by running `./name_of_executable`



### Other platforms
For other platforms, full source code is available, and it should build on most systems.
As the program runs on an **OpenGL** backend, building requires your system to have dev opengl headers available. For debian-based systems you can for example use *freeglut3-dev*, but windows and apple should have these preinstalled. All other dependencies are already present in the source code.
Building is straightforward using [CMake](https://cmake.org/), and then compiling it using your favourite compiler.

# Known Issues
## Windows: Freezing after a couple of seconds
This is an issue caused by the OpenGL implementations of some newer graphics cards. Try running the program in Windows 8 compatibility mode with full screen optimisations turned off.

## Libraries used

* [Dear IMGui](https://github.com/ocornut/imgui)
* [implot](https://github.com/epezent/implot)
* [GLFW](https://www.glfw.org/)
