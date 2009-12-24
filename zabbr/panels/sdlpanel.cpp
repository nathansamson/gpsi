#include "panels/sdlpanel.h"

namespace Zabbr {

	/**
	 * Constructor.
	 *
	 * The Panel is now in the foreground.
	 *
	 * @param window The window of the Panel.
	*/
	VSDLPanel::VSDLPanel(SDLWindow* window) : fParentPanel(NULL),
	                fWindow(window), fIsBackground(false) {
	}
	
	/**
	 * Destructor.
	*/
	VSDLPanel::~VSDLPanel() {
	}
	
	/**
	 * Function called by the SDLWindow to draw the Panel.
	*/
	void VSDLPanel::draw() {
	}

	/**
	 * Function called by the SDLWindow when a key is pressed.
	 *
	 * @param evnt The SDL Keyboard event.
	*/
	void VSDLPanel::keyPress(SDL_KeyboardEvent evnt) {
	}
	
	/**
	 * Function called by the SDLWindow when a key is released.
	 *
	 * @param evnt The SDL Keyboard event.
	*/
	void VSDLPanel::keyRelease(SDL_KeyboardEvent evnt) {
	}

	/**
	 * Function called by the SDLWindow when a mouse motion event is generated.
	 *
	 * @param evnt The SDL Mouse Motion event.
	*/
	void VSDLPanel::mouseMotion(SDL_MouseMotionEvent evnt) {
	}

	/**
	 * Function called by the SDLWindow when a mouse button event is generated.
	 *
	 * @param evnt The SDL Mouse Button event.
	*/
	void VSDLPanel::mouseButton(SDL_MouseButtonEvent evnt) {
	}
	
	/**
	 * Function called by the SDLWindow if the window should be closed.
	*/
	void VSDLPanel::quit() {
	}
	
	/**
	 * Function called by the when the user requests a quit.
	*/
	void VSDLPanel::requestQuit() {
		fQuitRequestEvent();
	}
	
	/**
	 * Connect to the QuitRequest Event.
	*/
	void VSDLPanel::connectRequestQuit(ICallback0* cb) {
		fQuitRequestEvent.connect(cb);
	}

	/**
	 * Gives control back to the parent Panel. This Panel will be closed.
	*/
	void VSDLPanel::openParentPanel() {
		if (this->fParentPanel) 
			this->fParentPanel->foreground();
		fWindow->openParentPanel(this->fParentPanel);
	}

	/**
	 * Gives Panel to the specified Panel.
	 *
	 * @param c The new active Panel. The parent of Panel will be this Panel.
	*/
	void VSDLPanel::openPanel(VSDLPanel* c) {
		c->fParentPanel = this;
		background();
		c->foreground();
		fWindow->openPanel(c);
	}

	/**
	 * Moves the Panel to the background.
	*/
	void VSDLPanel::background() {
		fIsBackground = true;
	}

	/**
	 * Moves the Panel back to the foreground.
	*/
	void VSDLPanel::foreground() {
		fIsBackground = false;
	}
}
