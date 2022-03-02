/*
**
** mlx_opengl.h 
**
** public include, use it after mlx.h
** designed only for minilibx_macos
**
*/

// Copyright (c) jsiller (jsiller@student.42heilbronn.de)
// This file is part of mlx_leak_tester (based on mlx by Ecole 42),
// forked at 12th of November 2021
// See LICENSE file for more details about the conditions this file is released under.
// original file from mlx

void    *mlx_new_opengl_window(void *mlx_ptr, int size_x, int size_y, char *title);

/* create an opengl window. put_image & pixel_put & string_put do not work there. */

int	mlx_opengl_swap_buffers(void *win_ptr);

/* the created window is double buffered. Use this funct to swap buffers */
/* this funct will call glFlush(). Don't call it. */

int	mlx_opengl_window_set_context(void *win_ptr);

/* in case multiple opengl windows are present, change opengl active context */
