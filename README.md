# USING MYSQL IN C++ [FOR WINDOWS ONLY]
Using MYSQL in C++ using MYSQL-CPP-CONN package (vcpkg package manager)

## How to run

### Prerequisites
1. [Mingw (C/C++ compiler and debugger)](https://www.mingw-w64.org/)
2. [Visual Studio C++ tools](https://visualstudio.microsoft.com/downloads/)
3. [CMake](https://cmake.org/download/)
4. [vcpkg](https://vcpkg.io)

Clone this repo
```bash
git clone <this repo>.git
```

Add the [mingw, cmake and vcpkg] into path **[skip this part if mingw, vcpkg and cmake are in path already]**
if you are using Clion add the following into the path
```
C:\Program Files\JetBrains\CLion 2024.1.2\bin\mingw
C:\Program Files\JetBrains\CLion 2024.1.2\bin\cmake\win\x64\bin
C:\Users\User\.vcpkg-clion\vcpkg
```

Replace **User** with your PC **username**

Install packages

```bash
vcpkg install
```

Configure Cmake
```bash
cmake ---preset="default"
```
Build
```bash
cmake --build build
```
Run the application
```bash
./build/Debug/HelloWorld.exe
```

you can find more info about vcpkg at [vcpkg.io](https://vcpkg.io)