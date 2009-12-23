#ifndef INC_WEAPONERY_H
#define INC_WEAPONERY_H

#include <map>

#include "game/weapons/weapon.h"
#include "game/ammotype.h"

namespace SI {
	class Ship;

	/**
	 * A Weaponery. This is a weapon depot.
	*/
	class Weaponery {
	public:
		virtual ~Weaponery();

		void addAmmo(std::string, AmmoType*);
		void addWeapon(std::string, VWeapon*);
		void clear();

		VWeapon* getWeapon(std::string id, Ship* ship);

		/**
		 * Returns an ammo type.
		 *
		 * @param id The ID of the ammo.
		 *
		 * @return A ammotype of type T*.
		*/
		template<typename T>
		T* getAmmoType(std::string id) {
			return dynamic_cast<T*>(fAmmo[id]);
		}
	private:
		/**
		 * A map of all ammo.
		*/
		std::map<std::string, AmmoType*> fAmmo;
		
		/**
		 * A map of all weapons.
		*/
		std::map<std::string, VWeapon*> fWeapons;
	};
}

#endif // INC_WEAPONERY_H
