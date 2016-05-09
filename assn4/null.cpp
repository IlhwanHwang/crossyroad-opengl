//
// BetterCarryingEachOther 2016.04.29
// null objects
//

#include "null.h"
#include "view.h"

NullLimiter::NullLimiter(float y) {
	locate(y);
}

void NullLimiter::update() {
	if (View::getY() > pos.y + View::getZfar()) {
		expire();
		return;
	}

	Object::update();
}