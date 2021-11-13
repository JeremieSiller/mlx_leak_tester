# mlx_leak_tester

A small add-on for the mlx-library which lets you know if you destroyed all images and windows

## Table of contents
1. [About](#about)
2. [How to use](#howtouse)
3. [Leaks](#leaks)
4. [Protection](#protection)
5. [MLX](#mlx)


## About

This project uses the mlx-library and made some adjustments to it. The mlx-library is used in the 42-core-curriculum
and because 42 uses mac-os it is pretty hard to properly test for leaks in mlx. Therefore I added some leak testing to 
the library.

**how it works:**

The project is techincally not checking for leaks its more or less counting all mlx-create calls and subtracts the
amount of destroy calls. 
Instead of calling the real mlx-functions it will call a function wich will put all pointers in to a list and
then calls the real function you actually wanted to call. For destroying it will call a function which will remove
the pointer from the list and then calls the real mlx-destroy function.
At exit it will loop through the list and prints all pointers that are still left and therefore have not been freed/destroyed.

## How to use

To use the library just compile it as if it was the real mlx-libray which means include mlx.h...
```c
#include "mlx/mlx.h" //addjust the path if you are using a different directory-structure
```
compile with the framework flags...:
```bash
cc -YOURFLAGS -framework OpenGL -framework AppKit -lmlx // addjust -lmlx if you are using a different directory-structure
```
if you are already using mlx you can just copy the mlx-folder out of this repository and use it the same was as the real mlx

## Leaks

For leaks the programm will show you all undestroyed images and windows when your programm exits (not if it gets signaled).
Be aware: not all leaks are gonna fail you if you submit your project. It won't harm your project if you fix them. 
Also if it doesnt print anything at exit it doesn't mean your project doesn't have leaks. This library only checks for mlx-leaks,
meaning malloc or similar functions are not getting tracked.
Always check leaks for yourself and dont rely on this tool.

## Protection

This is a second feature this library supports. You can check if your protection guards work properly.
To use it compile the library like this:
```bash
export PROTECTION_VALUE=X; make --directory=PATHTOMLX
```
replace X with the number of the protection you want to check 0 being the first.
What does this mean? :
if you compile with a PROTECTION_VALUE >= 0 it means that the library is gonna return NULL on the
PROTECTION_VALUE-th call of a mlx-create function.

## MLX
This project is an adjustment to the mlx-library you can find it here:
https://github.com/42Paris/minilibx-linux
