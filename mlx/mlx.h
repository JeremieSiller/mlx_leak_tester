#ifndef MLX_H
#define MLX_H

#include "mlx_leaks.h"
# define mlx_init() _mlx_init_()
# define mlx_new_window(a, b, c, d) _mlx_new_window_(a, b, c, d)
# define mlx_new_image(a, b, c) _mlx_new_image_(a, b, c)
# define mlx_xpm_to_image(a, b, c ,d) _mlx_xpm_to_image_(a, b, c ,d)
# define mlx_xpm_file_to_image(a, b, c ,d) _mlx_xpm_file_to_image_(a, b, c ,d)
// # define mlx_png_file_to_image(a, b, c, d) _mlx_png_file_to_image_(a, b, c, d)
# define mlx_destroy_window(a, b) _mlx_destroy_window_(a, b)
# define mlx_destroy_image(a, b) _mlx_destroy_image_(a, b)
#endif
