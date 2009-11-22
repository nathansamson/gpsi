#ifndef INC_GAMEENTITY_H
#define INC_GAMEENTITY_H

namespace SI {

	/**
	 * The basic of all game entities.
	*/
	class VGameEntity {
	public:
		virtual void visualize();
		virtual void update(unsigned int) = 0;
	protected:
		void move(Vector2);
	private:
		Vector2 fLocation;
	}
}

#endif // INC_GAMEENTTITY_H