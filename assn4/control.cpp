//
// BetterCarryingEachOther 2016.05.16
// control module
//

#include "control.h"
#include "key.h"

bool Control::day = true;
bool Control::ssao = true;

void Control::update() {
	if (Key::keyCheckPressed('2'))
		day = !day;

	if (Key::keyCheckPressed('3'))
		ssao = !ssao;
}