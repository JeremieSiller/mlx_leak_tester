// leaks.c
// Copyright (c) jsiller (jsiller@student.42heilbronn.de)
// This file is part of mlx_leak_tester (based on mlx by Ecole 42),
// forked at 12th of November 2021
// See LICENSE file for more details about the conditions this file is released under.
// file added by jsiller, not in original mlx

#include "mlx_leaks.h"
#include <stdlib.h>\
#include <string.h>

typedef struct s_leaks {
	char			*what;
	void			*addr;
	struct s_leaks	*next;
	struct s_leaks	*prev;
} t_leaks;

static t_leaks	*head;
static int		not_need;
static int		protect;

static void	remove_node(void *addr)
{
	t_leaks	*lst = head;
	t_leaks *tmp;

	if (lst && lst->addr == addr)
	{
		head = lst->next;
		free(lst);
		return ;
	}
	while (lst && lst->addr != addr)
	{
		tmp = lst;
		lst = lst->next;
	}
	if (lst == 0)
	{
		not_need++;
		return ;
	}
	tmp->next = lst->next;
	free(lst);
}

static int	add_node(void *addr, char *what)
{
	t_leaks	*node = calloc(sizeof(t_leaks), 1);
	t_leaks	*lst = head;

	if (!node)
		return 1;
	node->addr = addr;
	node->what = what;
	if (!lst)
	{
		head = node;
		return 0;
	}
	while (lst && lst->next)
	{
		lst = lst->next;
	}
	node->prev = lst;
	lst->next = node;
	return (0);
}

static void	showLeaks(void)
{
	t_leaks *rot = head;

	while (rot)
	{
		if (!strcmp("mlx_ptr", rot->what))
		{
			printf("\033[33m[KO]\033[0;37m: \033[0;36m%s\033[0;37m at:\033[0;36m%p \033[0;37mhas not been destroyed\n\tthe standard mlx library does not a function to fix this leak\n\tbut you can use the mlx_destory function out of this library\n", rot->what, rot->addr);
		}
		else
		{
			printf("\033[0;31m[KO]\033[0;37m: \033[0;36m%s\033[0;37m at:\033[0;36m%p \033[0;37mhas not been destroyed\n", rot->what, rot->addr);
		}
		remove_node(rot->addr);
		rot = rot->next;
	}
	if (not_need > 0)
		printf("[WARNING]: you have destroyed %i uninitialized mlx_pointer(s)\n", not_need);
}

void	*_mlx_init_(void)
{
	void *addr;
	head = 0;
	not_need = 0;
	protect = 0;
	atexit(&showLeaks);
	if (protect == PROTECT_VALUE)
		return (NULL);
	protect++;
	addr = mlx_init();
	if (!addr)
		return (NULL);
	if (add_node(addr, "mlx_ptr"))
		return (NULL);
	return (addr);
}

void	*_mlx_new_window_(void *mlx_ptr, int size_x, int size_y, char *title)
{
	void	*addr;

	if (protect == PROTECT_VALUE)
		return (NULL);
	addr = mlx_new_window(mlx_ptr, size_x, size_y, title);
	if (!addr)
		return (addr);
	protect++;
	if (add_node(addr, "window"))
		return (NULL);
	return (addr);
}

void	*_mlx_new_image_(void *mlx_ptr,int width,int height)
{
	void	*addr;

	if (protect == PROTECT_VALUE)
		return (NULL);
	addr = mlx_new_image(mlx_ptr, width, height);
	if (!addr)
		return (addr);
	protect++;
	if (add_node(addr, "image"))
		return (NULL);
	return (addr);
}

void	*_mlx_xpm_to_image_(void *mlx_ptr, char **xpm_data,
			  int *width, int *height)
{
	void	*addr;

	if (protect == PROTECT_VALUE)
		return (NULL);
	addr = mlx_xpm_to_image(mlx_ptr, xpm_data, width, height);
	if (!addr)
		return (addr);
	protect++;
	if (add_node(addr, "xpm_image"))
		return (NULL);
	return (addr);
}

void	*_mlx_xpm_file_to_image_(void *mlx_ptr, char *filename,
			       int *width, int *height)
{
	void	*addr;

	if (protect == PROTECT_VALUE)
		return (NULL);
	addr = mlx_xpm_file_to_image(mlx_ptr, filename, width, height);
	if (!addr)
		return (addr);
	protect++;
	if (add_node(addr, "xpm_image"))
		return (NULL);
	return (addr);
}

// void	*_mlx_png_file_to_image_(void *mlx_ptr, char *file, int *width, int *height)
// {
// 	void	*addr;

// 	addr = mlx_png_file_to_image(mlx_ptr, file, width, height);
// 	if (!addr)
// 		return (addr);
// 	if (add_node(addr, "xpm_image"))
// 		return (NULL);
// 	return (addr);
// }

int	_mlx_destroy_image_(void *mlx_ptr, void *img_ptr)
{
	remove_node(img_ptr);
	return (mlx_destroy_image(mlx_ptr, img_ptr));
}

int	_mlx_destroy_window_(void *mlx_ptr, void *win_ptr)
{
	remove_node(win_ptr);
	return(mlx_destroy_window(mlx_ptr, win_ptr));
}

void	_mlx_destroy_(void *mlx_ptr)
{
	remove_node(mlx_ptr);
}
