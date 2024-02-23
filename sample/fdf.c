# include "fdf.h"

int	is_key(int key)
{
	return (key == 24 || key == 69 || key == 27 || key == 78 \
	|| key == 91 || key == 28 || key == 84 || key == 19 ||\
	key == 126 || key == 125 || key == 123 || key == 124 ||\
	key == 49 || key == 87 || key == 23  || key == 86 ||\
	key == 21 || key == 88 || key == 22);
}

void	do_key(int key, fdf **data)
{
	if (key == 24 || key == 69)
		data[0][0].scale += 3;
	if (key == 27 || key == 78)
		data[0][0].scale -= 3;
	if (key == 91 || key == 28)
		data[0][0].z_scale += 1;
	if (key == 84 || key == 19)
		data[0][0].z_scale -= 1;
	if (key == 126)
		data[0][0].shift_y -= 10;
	if (key == 125)
		data[0][0].shift_y += 10;
	if (key == 123)
		data[0][0].shift_x -= 10;
	if (key == 124)
		data[0][0].shift_x += 10;
	if (key == 49 || key == 87 || key == 23)
	{	
		data[0][0].is_isometric =  1;
		if (data[0][0].is_isometric)
			data[0][0].is_isometric = 0;
	}	
	if (key == 86 || key == 21)
		data[0][0].angle += 0.05;
	if (key == 88 || key == 22)
		data[0][0].angle -= 0.05;
}

int	check_win_size(int key, fdf **data)
{
	if ((key == 0 && data[0][0].win_y <= 500) ||\
	(key == 6 && data[0][0].win_x <= 500))
		return (1);
	if ((key == 1 && data[0][0].win_y > 1000) ||\
	(key == 7 && data[0][0].win_x > 2000))
		return (1);
	return (0);
}

void	full_screen(fdf **data)
{
	static int	old_x;
	static int	old_y;

	if (data[0][0].win_x != 2560)
	{
		old_x = data[0][0].win_x;
		old_y = data[0][0].win_y;
	}
	if (data[0][0].win_x == 2560)
		data[0][0].win_x = old_x;
	else
		data[0][0].win_x = 2560;
	if (data[0][0].win_y == 1400)
		data[0][0].win_y = old_y;
	else
		data[0][0].win_y = 1400;
}

void	change_window_size(int key, fdf **data)
{
	if (check_win_size(key, data))
		return ;
	if (key == 6)
		data[0][0].win_x -= 100;
	if (key == 7)
		data[0][0].win_x += 100;
	if (key == 0)
		data[0][0].win_y -= 100;
	if (key == 1)
		data[0][0].win_y += 100;
	if (key == 3)
		full_screen(data);
}

void	new_window(int key, fdf **data)
{
	change_window_size(key, data);
	mlx_destroy_window(data[0][0].mlx_ptr, data[0][0].win_ptr);
	data[0][0].mlx_ptr = mlx_init();
	data[0][0].win_ptr = mlx_new_window(data[0][0].mlx_ptr, \
	data[0][0].win_x, data[0][0].win_y, "FDF");
	data[0][0].shift_x = data[0][0].win_x / 3;
	data[0][0].shift_y = data[0][0].win_y / 3;
	draw(data);
	mlx_key_hook(data[0][0].win_ptr, deal_key, data);
	mlx_loop(data[0][0].mlx_ptr);
}

int	deal_key(int key, fdf **data)
{
	ft_printf("%d\n", key);
	if (is_key(key))
	{
		mlx_clear_window(data[0][0].mlx_ptr, data[0][0].win_ptr);
		do_key(key, data);
		print_data(data[0][0]);
		draw(data);
	}
	if (key == 6 || key == 7 || key == 0 || key == 1 || key == 3)
		new_window(key, data);
	if (key == '5')
	{
		mlx_destroy_window(data[0][0].mlx_ptr, data[0][0].win_ptr);
		free(data);
		exit(0);
	}
	return (0);
}

void	set_default(fdf *data)
{
	data->scale = 20;
	data->z_scale = 1;
	data->is_isometric = 1;
	data->angle = 0.523599;
	data->win_x = 1000;
	data->win_y = 500;
	data->shift_x = data->win_x / 3;
	data->shift_y = data->win_y / 3;
	data->mlx_ptr = mlx_init();
	data->win_ptr =\
	mlx_new_window(data->mlx_ptr, data->win_x, data->win_y, "FDF");
}


int main(int argc, char *argv[])
{
	if (argc == 2)
	{
		fdf **data;

		data = read_file(argv[1]);
		set_default(&data[0][0]);
		draw(data);
		mlx_key_hook(data[0][0].win_ptr, deal_key, data);
		mlx_loop(data[0][0].mlx_ptr);
	}
	else
		ft_error("Error: usage{ ./fdf map.fdf}");
	return (0);
}
