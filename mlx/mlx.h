// mlx.h
// Copyright (c) jsiller (jsiller@student.42heilbronn.de)
// This file is part of mlx_leak_tester (based on mlx by Ecole 42),
// forked at 12th of November 2021
// See LICENSE file for more details about the conditions this file is released under.
// original file from mlx

#ifndef MLX_H
#define MLX_H

#include "mlx_leaks.h"
# define mlx_init() _mlx_init_()
# define mlx_new_window(mlx_ptr, size_x, size_y, title) _mlx_new_window_(mlx_ptr, size_x, size_y, title)
# define mlx_new_image(mlx_ptr, width, height) _mlx_new_image_(mlx_ptr, width, height)
# define mlx_xpm_to_image(mlx_ptr, xpm_data, width , heigth) _mlx_xpm_to_image_(mlx_ptr, xpm_data, width ,heigth)
# define mlx_xpm_file_to_image(mlx_ptr, filename, width ,heigth) _mlx_xpm_file_to_image_(mlx_ptr, filename, width ,heigth)
// # define mlx_png_file_to_image(a, b, c, d) _mlx_png_file_to_image_(a, b, c, d)
# define mlx_destroy_window(mlx_ptr, win_ptr) _mlx_destroy_window_(mlx_ptr, win_ptr)
# define mlx_destroy_image(mlx_ptr, img_ptr) _mlx_destroy_image_(mlx_ptr, img_ptr)
# define mlx_destroy(mlx_ptr) _mlx_destroy_(mlx_ptr);
#endif
