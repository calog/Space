/*Standart*/
#include <stdio.h>
#include <stdlib.h>

/*Allegro*/
#include <allegro5/allegro5.h>
#include <allegro5/allegro_color.h> // NO OLVIDAR AGREGAR EN EL LINKER DEL PROYECTO
#include <allegro5/allegro_primitives.h> // NO OLVIDAR AGREGAR EN EL LINKER DEL PROYECTO
#include <allegro5/events.h>
#include <allegro5/allegro_image.h>
#include <allegro5/keyboard.h>
#include <allegro5/keycodes.h>

/*Structs*/
#include "player.h"

#define D_WIDTH		800
#define D_HEIGHT	600

int main(void)
{
	ALLEGRO_DISPLAY* display = NULL;
	if (!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}

	if (!al_init_primitives_addon()) {
		fprintf(stderr, "failed to initialize primitives!\n");
		return -1;
	}

	display = al_create_display(D_WIDTH, D_HEIGHT);

	if (!display) {
		al_shutdown_primitives_addon();
		fprintf(stderr, "failed to create display!\n");
		return -1;
	}

	if (!al_init_image_addon()) 
	{
		al_shutdown_image_addon();
		fprintf(stderr, "failed to load image addon!\n");
		return -1;
	}

	/*Player*/
	player_t p;
	p.x = 20;
	p.y = 20;
	p.state = 1;


	al_clear_to_color(al_color_name("black"));
	al_flip_display();
	ALLEGRO_BITMAP* playerTexture = al_load_bitmap("player.jpg");
	

	/*Allegro events*/
	ALLEGRO_EVENT ev;
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	al_register_event_source(queue, al_get_display_event_source(display)); //registra display (ej: que se cierre)
	//al_register_event_source(queue, al_get_keyboard_event_source());//registra teclado

	do {
		al_get_next_event(queue, &ev);

		switch (ev.type) {

		case ALLEGRO_EVENT_KEY_DOWN:
			if (ev.keyboard.keycode == ALLEGRO_KEY_LEFT) {
				al_draw_bitmap(playerTexture, p.x - 10, p.y, 0);
				//al_draw_circle(p.x - 10, p.y, 5, al_map_rgb(0, 0, 0), 1);
				p.x = p.x - 10;
			}
			else if (ev.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
				al_draw_bitmap(playerTexture, p.x + 10, p.y,0);
				//al_draw_circle(p.x + 10, p.y, 5, al_map_rgb(0, 0, 0), 1);
				p.x = p.x + 10;
			}
		}

		al_clear_to_color(al_map_rgb(255, 255, 255));
		al_flip_display();

	} while (ev.type != ALLEGRO_EVENT_DISPLAY_CLOSE);

	return 0;
}

