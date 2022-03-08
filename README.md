# mlx_leak_tester

A small add-on for the mlx-library which lets you know if you destroyed all images and windows

## Table of contents
1. [About](#about)
2. [MLX](#mlx)
3. [How to use](#howtouse)
4. [Leaks](#leaks)
5. [Protection](#protection)


## About

This project uses the mlx-library with some adjustments. The mlx-library is used in the 42-core-curriculum
and because 42 uses Mac-OS it is pretty hard to properly test for leaks when using mlx. This add-on is gonna help
you to test for leaks.

**how it works:**

The project is technically not checking for leaks, its more or less counting all mlx-create calls and subtracts the
amount of destroy calls. 
Instead of calling the real mlx-functions it will call a function wich will save all allocated pointers in a list. Aftewards 
it calls the real function you actually wanted to call and returns it's value. When destroying the image/window it will call a function which will remove
the pointer from the list.
At exit it will loop through the list and print all pointers that are still left and therefore have not been freed/destroyed.

## MLX

This project is an adjustment to the mlx-library you can find it here:
https://github.com/42Paris/minilibx-linux


## How to use

To use the library just compile it as if it was the real mlx-libray which means include mlx.h...
```c
#include "mlx/mlx.h" //adjust the path if you are using a different directory-structure
```
compile with the framework flags...:
```bash
cc -YOURFLAGS -framework OpenGL -framework AppKit -lmlx //adjust -lmlx if you are using a different directory-structure
```
if you are already using mlx you can just rename this repository to however you called the actual mlx repo (e.g mlx). Fully recompile your project aftewards:
```bash
make re
```

## Leaks

For leaks the programm will show you all undestroyed images and windows when your programm exits (not if it gets signaled).
Be aware: not all leaks are gonna fail you if you submit your project but it won't harm your project if you fix them. 
Also if it doesnt print anything at exit, it doesn't mean your project doesn't have leaks. This library only checks for mlx-leaks,
meaning malloc or similar functions are not getting tracked.
Always check leaks for yourself and dont rely on this tool.

**mlx_init:**

the mlx_init function allocates memory in a struct, but there is not function to properly free everything mlx_init allocated. If you tried fixing this by
simply freeing the mlx_ptr, you probably realized that there are still leaks. That is the case because the mlx_ptr is a pointer to a struct which contains a pointer to an allocated image. 
This library contains a mlx_destroy function to fix this leak. If you don't wanna submit your project with this library, you can copy following code into your mlx_library:

copy the prototype in mlx.h:
```c
void	mlx_destroy(void *mlx_ptr);
```
copy the function in mlx_init_loop.m:
```c
void	mlx_destroy(void *mlx_ptr)
{
	mlx_ptr_t	*ptr;

	ptr = mlx_ptr;
	mlx_destroy_image(ptr, ptr->font);
	free(ptr);
}
```

## Protection

This is a second feature this library supports. You can check if your protection guards work properly.
To use it compile the library like this:
```bash
export PROTECTION_VALUE=X; make --directory=PATHTOMLX
```
replace X with the number of the protection you want to check (0 being the first).
What does this mean?
If you compile with a PROTECTION_VALUE >= 0 it means that the library is gonna return NULL on the
X-th call of a mlx-create function.
If your code contains something like this:
```c
void	*mlx;

mlx = mlx_init();
mlx_loop(mlx);
```
it will probabaly segfault (if mlx_init returns NULL), because you did not properly protect the mlx_init-function.
A proper protection guard would look like this:
```c
void	*mlx;

mlx = mlx_init();
if (!mlx)
{
	//free everything
	//write an error message
	exit(1); //or any other code that is not 0
}
mlx_loop(mlx);
```
