
#include "fdf.h"
#include <stdio.h>

void	ft_error(char *s)
{
	ft_printf("%s\n", s);
	exit(1);
}

void	get_data_from_map(char *line, fdf **data, int y)
{
	char	**map_data;
	int	x;

	map_data = ft_split(line , ' ');
	x = 0;
	while (map_data[x])
	{
		data[y][x].z = ft_atoi(map_data[x]);
		data[y][x].x = x;
		data[y][x].y = y;
		data[y][x].is_last = 0;
		free(map_data[x++]);
	}
	free(map_data);
	free(line);
	data[y][--x].is_last = 1;
}

fdf	**map_memory(char *file_name)
{
	fdf	**new;
	int	x;
	int	y;
	int	fd;
	char	*line;

	if ((fd = open(file_name, O_RDONLY, 0)) <= 0)
		ft_error("NOT EXIST FILE!");
	line = get_next_line(fd);
	x = deli_count(line, ' ');
	free(line);
	y = 0;
	while ((line = get_next_line(fd)) > 0)
	{
		y++;
		free(line);
	}
	free(line);
	new = (fdf **)malloc(sizeof(fdf *) * (++y + 1));
	while (y > 0)
		new[--y] = (fdf *)malloc(sizeof(fdf) * (x + 1));
	close(fd);
	return (new);
}

fdf	**read_file(char *file_name)
{
	int	fd;
	int	y;
	char	*line;
	fdf	**data;

	data = map_memory(file_name);
	fd = open(file_name, O_RDONLY, 0);
	y = 0;
	while ((line = get_next_line(fd)) > 0)
		get_data_from_map(line, data, y++);
	free(line);
	data[y] = NULL;
	close(fd);
	return (data);
}
