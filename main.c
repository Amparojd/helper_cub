#include <stdlib.h>
#include <stdio.h>
#include "./minilibx-linux/mlx.h"

#define WIN_WIDTH  1200
#define WIN_HEIGHT 800

typedef struct s_window {
    void *mlx;
    void *win;
    void *img;
    int   img_width;
    int   img_height;
    int   ui_visible;
} t_window;

void user_interface_image(t_window *data) {
    if (data->ui_visible) {
        mlx_put_image_to_window(data->mlx, data->win, data->img, (WIN_WIDTH - data->img_width) / 2, (WIN_HEIGHT - data->img_height) / 2);
    }
}

// Función para manejar eventos de teclado
int handle_key_press(int keycode, t_window *data) {
    if (keycode == 65307) { // Tecla Esc
        mlx_destroy_window(data->mlx, data->win);
        exit(0);
    }
    if (keycode == 104) { // Tecla 'h'
        data->ui_visible = !data->ui_visible;
        mlx_clear_window(data->mlx, data->win);
        user_interface_image(data);
    }
    return 0;
}

// Función para manejar el cierre de la ventana
int handle_window_close(t_window *data) {
    printf("Se cerró la ventana\n");
    mlx_destroy_window(data->mlx, data->win);
    exit(0);
}

int main(void) {
    t_window data;

    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, WIN_WIDTH, WIN_HEIGHT, "basic_helper");
    data.img = mlx_xpm_file_to_image(data.mlx, "helper.xpm", &data.img_width, &data.img_height);
    data.ui_visible = 1; // Inicializa la visibilidad de la UI como visible

    if (!data.mlx || !data.win || !data.img) {
        return (1);
    }

    user_interface_image(&data);
    mlx_hook(data.win, 2, 1L << 0, handle_key_press, &data); // Registrar función para manejar eventos de teclado
    mlx_hook(data.win, 17, 0, handle_window_close, &data);   // Registrar función para manejar cierre de ventana
    mlx_loop(data.mlx);

    return (0);
}
