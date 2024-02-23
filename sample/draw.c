#include "fdf.h"
# define MAX(a, b) (a > b ? a : b)

float mod(float i)
{
    return ((i < 0) ? -i : i);
}

void isometric(fdf *data, double angle)//here role is check!
{
	data->x = (data->x - data->y) * cos(angle);
	data->y = (data->x + data->y) * sin(angle) - data->z;
}

void	zoom(fdf *a, fdf *b, fdf *data)
{
	a->x *= data->scale;
	a->y *= data->scale;
	b->x *= data->scale;
	b->y *= data->scale;
	a->z *= data->z_scale;
	b->z *= data->z_scale;
}

void	set_param(fdf *a, fdf *b, fdf *data)
{
	zoom(a, b, data);
	if (data->is_isometric)
	{
		isometric(a, data->angle);
		isometric(b, data->angle);
	}
	a->x += data->shift_x;
	a->y += data->shift_y;
	b->x += data->shift_x;
	b->y += data->shift_y;
}

void	print_data(fdf data)
{
	char	*menu;
	
	menu = "up, down, left, right: move picture";
	mlx_string_put(data.mlx_ptr, data.win_ptr, 10, 5, 0x03fc35, menu);
	menu = "5, space: 3d/2d mode; +, -: zoom";
	mlx_string_put(data.mlx_ptr, data.win_ptr, 10, 20, 0x03fc35, menu);
	menu = "8, 2: z-scale; 4, 6:rotation";
	mlx_string_put(data.mlx_ptr, data.win_ptr, 10, 35, 0x03fc35, menu);
	menu = "f: full screen mode";
	mlx_string_put(data.mlx_ptr, data.win_ptr, 10, 50, 0x03fc35, menu);

}

void	color_judge(int *color, fdf a, fdf b)
{
	if (b.z || a.z)
		*color = 0xfc0345;
	else
		*color = 0xBBFAFF;
	if (b.z != a.z)
		*color = 0xfc031c;
}

void	bresenham(fdf a, fdf b, fdf *data)
{
	float	x_step;
	float	y_step;
	float	max;
	int	color;

	set_param(&a, &b, data);
	x_step = b.x - a.x;
	y_step = b.y - a.y;
	max = MAX(mod(x_step), mod(y_step));
	x_step /= max;
	y_step /= max;
	color_judge(&color, a, b);
	while ((int)(a.x - b.x) || (int)(a.y - b.y))
	{
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, a.x, a.y, color);
		a.x += x_step;
		a.y += y_step;
		if (a.x > data->win_x || a.y > data->win_y || a.y < 0 || a.x < 0)
			break ;
	}
}

void draw(fdf **data)
{
    int	x;
    int	y;

	print_data(data[0][0]);//here is check!
	y = 0;
	while (data[y])
	{
		x = 0;
		while (1)
		{
			if (data[y + 1])
				bresenham(data[y][x], data[y + 1][x], &data[0][0]);
			if (!data[y][x].is_last)
				bresenham(data[y][x], data[y][x + 1], &data[0][0]);
			if (data[y][x].is_last)
				break ;
			x++;
		}
		y++;
	}
}

