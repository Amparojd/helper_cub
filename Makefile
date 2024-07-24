# Nombre del ejecutable
NAME = basic_helper

# Directorios
MLX_DIR = ./minilibx-linux

# Archivos fuente
SRCS = main.c

# Archivos objeto
OBJS = $(SRCS:.c=.o)

# Compilador y flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(MLX_DIR)

# Librerías
LIBS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

# Regla por defecto
all: $(NAME)

# Regla para crear el ejecutable
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

# Regla para compilar archivos .c en archivos .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpiar archivos objeto
clean:
	rm -f $(OBJS)

# Limpiar todo
fclean: clean
	rm -f $(NAME)

# Recompilar desde cero
re: fclean all

# Compilar MiniLibX
$(MLX_DIR)/libmlx.a:
	make -C $(MLX_DIR)

.PHONY: all clean fclean re
