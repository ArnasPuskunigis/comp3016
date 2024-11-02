#include "Brick.h"
#include <iostream>

//Reduce brick health. if reaches 0 then the brick should not be active
void Brick::TakeDamage() {

	if (health >= 1) {
		health--;
		if (health == 0) {
			destroyed = true;
		}
	}
};