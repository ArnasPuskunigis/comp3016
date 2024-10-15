#include "Brick.h"

void Brick::TakeDamage() {

	if (health >= 1) {
		health--;
		if (health == 0) {
			destroyed = true;
		}
	}
};