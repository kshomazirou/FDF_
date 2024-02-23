#ifndef FDF_H
# define FDF_H

# include "src/printf/libft/libft.h"
# include "src/printf/ft_printf.h"
# include "src/get_next_line/get_next_line.h"
# include "minilibx_macos/mlx.h"
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct
{
	float	x;
	float	y;
	float	z;
	int	is_last;

	int	zoom;
	int	color;
	int	shift_x;
	int	shift_y;
	int	z_scale;
	int	scale;
	double	angle;
	int	is_isometric;	
	int	win_x;
	int	win_y;

	void	*mlx_ptr;
	void	*win_ptr;
}	fdf;

fdf	**read_file(char *file_name);
void	bresenham(fdf a, fdf b, fdf *data);
void	draw(fdf **data);
void	print_data(fdf data);
int	deal_key(int key, fdf **data);
void	set_param(fdf *a, fdf *b, fdf *data);
void	new_window(int key, fdf **data);
void	isometric(fdf *data, double angle);
void	ft_error(char *s);

#endif
