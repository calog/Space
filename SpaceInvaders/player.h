#pragma once

enum estados { muerto, vivo };

typedef struct player {
	double x;
	double y;
	int w;
	int h;
	int lives;
	bool state;
}player_t;