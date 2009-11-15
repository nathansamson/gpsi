#include "guiframework/widgets/widget.h"

namespace sdlframework {
	VWidget::VWidget() {
	}

	VWidget::VWidget(SDLWindow* window) : fWindow(window), fFill(false) {

	}

	void VWidget::setFill(bool fill) {
		fFill = true;
	}

	void VWidget::mouseMotion(SDL_MouseMotionEvent) {
	}
}