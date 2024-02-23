FRAMEWORKS=-framework CoreFoundation -framework AppKit -framework OpenGL
FLAGS=-Werror -Wextra -Wall
NAME=fdf

SRC = src/printf/ft_printf.c \
	src/printf/ft_change_base.c \
	src/printf/ft_hexer.c \
	src/printf/ft_inter.c \
	src/printf/ft_pointer.c \
	src/printf/ft_putputstr_fd.c \
	src/printf/ft_putstr_count.c \
	src/printf/ft_tolower.c \
	src/printf/ft_putputchar_fd.c \
	src/printf/ft_uber_count.c \
	src/printf/ft_operator.c \
	src/printf/libft/ft_itoa.c \
	src/printf/libft/ft_putchar_fd.c \
	src/printf/libft/ft_putstr_fd.c \
	src/printf/libft/ft_strdup.c \
	src/printf/libft/ft_tolower.c \
	src/get_next_line/get_next_line.c \
	src/get_next_line/get_next_line_utils.c \
	fdf.c \
	draw.c \
	read_file.c \

INCLUDES = src/printf/libft/libft.a \
		minilibx_macos/libmlx.a \
		$(FRAMEWORKS)

$(NAME):
	@make -C src/printf/libft/ all
	@make -C src/printf/ all
	@make -C minilibx_macos/ all
	cc $(SRC) -o $(NAME) $(FLAGS) $(INCLUDES)

all: $(NAME)

clean:
	@make -C src/printf/libft clean
	@make -C src/printf/ clean
	@make -C minilibx_macos/ clean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re 
