//
// BetterCarryingEachOther 2016.03.11
// key state control module
//

#include "key.h"

bool Key::keyStatePend[256] = {false};
bool Key::keyStateAccept[256] = {false};

void Key::keyPressed(unsigned char key, int x, int y) {
	keyStatePend[key] = true;
}

void Key::keyReleased(unsigned char key, int x, int y) {
	keyStatePend[key] = false;
}

bool Key::keyCheckPressed(unsigned char key) {
	return keyStatePend[key] && !keyStateAccept[key];
}

bool Key::keyCheckReleased(unsigned char key) {
	return !keyStatePend[key] && keyStateAccept[key];
}

bool Key::keyCheckOn(unsigned char key) {
	return keyStatePend[key];
}

void Key::keyUpdate() {
	for (int i = 0; i < 256; i++) {
		if (keyStatePend[i])
			keyStateAccept[i] = true;
		else
			keyStateAccept[i] = false;
	}
}