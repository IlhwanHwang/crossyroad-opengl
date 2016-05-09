//
// BetterCarryingEachOther 2016.03.11
// key state control module
//

#pragma once

class Key {
private:
	static bool keyStatePend[256];
	static bool keyStateAccept[256];
public:
	static void keyPressed(unsigned char key, int x, int y);
	static void keyReleased(unsigned char key, int x, int y);
	static bool keyCheckPressed(unsigned char key);
	static bool keyCheckReleased(unsigned char key);
	static bool keyCheckOn(unsigned char key);
	static void keyUpdate();
};