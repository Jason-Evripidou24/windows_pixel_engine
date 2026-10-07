# Windows Pixel Engine

This project is a 3d software renderer that uses zero external dependencies (excluding a single stb_image.h header file). It is written entirely in C++.
</br>

It was created to implement the transformation and rendering pipeline of a modern 3D graphics engine from the ground up, without relying on graphics APIs such as OpenGL or DirectX.
</br>

The renderer is responsible for the complete process of transforming 3D geometry into pixels on the screen. This includes model, view and projection transformations, clipping, perspective division, rasterisation, depth testing, colour interpolation, texture sampling, and final presentation to an operating system specific frame (currently only for Windows).
</br>

Currently this project only supports 64-bit Windows operating systems (specifically Windows 10 and 11).
</br>

The most up to date revision of the project can be found at "/revision_02/rev_03". All previous revisions are also included in this repository in case that anybody wishes to see the progression.
</br>
</br>


## Building the Application

An included build.bat file is included for each project revision. This utilises the Microsoft Visual Studio compiler and thus it must be installed on your machine.
</br>

The build script automatically configures the Visual Studio development environment, compiles the source files, and links the resulting executable.
</br>

The application can be built from the command line using:
</br>

<code>build.bat</code>
</br>

The build script also supports cleaning the build output:
</br>

<code>build.bat clean</code>
</br>

The output executable file can be found at "/build/app.exe".
</br>

The project does not use CMake or another external build system. It is compiled directly using the Microsoft Visual C++ compiler provided by Visual Studio.
</br>
</br>