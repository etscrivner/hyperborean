# Hyperborean

Simple C++ game engine using SDL2 for graphics and Lua for scripting.

# Building

## Linux/Unix/MacOS

Given that you have the standard C/C++ buildtools installed locally, you merely
need to do:

```shell
make
```

You can then run the program using:

```shell
./build/hyperborean
```

## Windows

You'll need a copy of MinGW installed with g++ >= 6.1.0. I recommend
[Nuwen MinGW](https://nuwen.net/mingw.html). Once you've successfully
done this you run the following command to build:

```shell
make.exe
```

Notice that this version of Hyperborean is dynamically linked, so
you'll need to distribute all of the DLL files in `.\build` along with
the executable.