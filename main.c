#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "./minilibx-linux/mlx.h"

#define WIN_WIDTH  800
#define WIN_HEIGHT 600
#define UI_CLR     0x000000

typedef struct s_window {
    void *mlx;
    void *win;
    char *nam;
    int ui_visible;
} t_window;

void draw_rectangle(t_window *data, int x, int y, int width, int height, int border_color, int fill_color) {
    int i;

    // Dibujar borde izquierdo y derecho
    i = 0;
    while (i <= height) {
        mlx_pixel_put(data->mlx, data->win, x, y + i, border_color); // Borde izquierdo
        mlx_pixel_put(data->mlx, data->win, x + width, y + i, border_color); // Borde derecho
        i++;
    }

    // Dibujar borde superior e inferior
    i = 0;
    while (i <= width) {
        mlx_pixel_put(data->mlx, data->win, x + i, y, border_color); // Borde superior
        mlx_pixel_put(data->mlx, data->win, x + i, y + height, border_color); // Borde inferior
        i++;
    }

    // Rellenar el rectángulo con color de relleno
    for (i = 1; i < width; i++) {
        int j = 1;
        while (j < height) {
            mlx_pixel_put(data->mlx, data->win, x + i, y + j, fill_color);
            j++;
        }
    }
}

void user_interface_texts(t_window *data) {
    if (data->ui_visible == 0) {
        int rect_width = 600;   // Ancho del fondo
        int rect_height = 400;  // Alto del fondo
        int rect_x = (WIN_WIDTH - rect_width) / 2;   // Posición x del borde izquierdo del fondo (centrado)
        int rect_y = (WIN_HEIGHT - rect_height) / 2; // Posición y del borde superior del fondo (centrado)
        int text_size = 24;     // Tamaño del texto
        int text_padding = 20;  // Espacio interior entre el borde y el texto
        int text_color = UI_CLR;  // Color del texto
        int border_color = 0xCCCCCC;  // Color del borde
        int background_color = 0xFF0000;  // Color de fondo rojo

        // Dibujar el fondo rojo con bordes
        draw_rectangle(data, rect_x, rect_y, rect_width, rect_height, border_color, background_color);

        // Obtener la longitud del texto más largo para centrar correctamente
        int longest_text_length = 0;
        int current_text_length = 0;

        current_text_length = strlen("Controls Keys");
        if (current_text_length > longest_text_length) {
            longest_text_length = current_text_length;
        }

        current_text_length = strlen("Move = ^ v < >");
        if (current_text_length > longest_text_length) {
            longest_text_length = current_text_length;
        }

        // Calcular la posición x para centrar el texto
        int text_center_x = rect_x + (rect_width - longest_text_length * text_size) / 2;

        // Dibujar texto dentro del fondo
        mlx_string_put(data->mlx, data->win, text_center_x, rect_y + text_padding, text_color, "Controls Keys");
        mlx_string_put(data->mlx, data->win, text_center_x, rect_y + text_padding + 40, text_color, "Move = ^ v < >");
        mlx_string_put(data->mlx, data->win, text_center_x, rect_y + text_padding + 80, text_color, "Iter = W and Q");
        mlx_string_put(data->mlx, data->win, text_center_x, rect_y + text_padding + 120, text_color, "Zoom = - and +");
        mlx_string_put(data->mlx, data->win, text_center_x, rect_y + text_padding + 160, text_color, "Rot8 = R and T");
        mlx_string_put(data->mlx, data->win, text_center_x, rect_y + text_padding + 200, text_color, "Mouse = M or S");
        mlx_string_put(data->mlx, data->win, text_center_x, rect_y + text_padding + 240, text_color, "Color = SHIFT");
        mlx_string_put(data->mlx, data->win, text_center_x, rect_y + text_padding + 280, text_color, "Reset = CLEAR");
        mlx_string_put(data->mlx, data->win, text_center_x + 150, rect_y + rect_height - 55, text_color, data->nam);
    }
}


// Función para manejar eventos de teclado
int handle_key_press(int keycode, t_window *data) {
    if (keycode == 65307) { // Tecla Esc
        mlx_destroy_window(data->mlx, data->win);
        exit(0);
    }
    if (keycode == 104) { // Tecla 'H'
        data->ui_visible = !data->ui_visible;
        mlx_clear_window(data->mlx, data->win);
        user_interface_texts(data);
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
    data.nam = strdup("Example Name"); // Inicializa el nombre

    if (!data.mlx || !data.win || !data.nam) {
        return (1);
    }

    user_interface_texts(&data);
    mlx_hook(data.win, 2, 1L << 0, handle_key_press, &data); // Registrar función para manejar eventos de teclado
    mlx_hook(data.win, 17, 0, handle_window_close, &data);   // Registrar función para manejar cierre de ventana
    mlx_loop(data.mlx);

    free(data.nam);
    return (0);
}
