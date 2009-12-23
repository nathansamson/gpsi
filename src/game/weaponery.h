#ifndef INC_WEAPONERY_H
#define INC_WEAPONERY_H

#include <map>

#include "game/weapons/weapon.h"
#include "game/ammotype.h"

namespace SI {
	class Ship;

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
		*/
		template<typename T>
		T* getAmmoType(std::string id) {
			return dynamic_cast<T*>(fAmmo[id]);
		}
	private:
		std::map<std::string, AmmoType*> fAmmo;
		std::map<std::string, VWeapon*> fWeapons;
	};
}

#endif // INC_WEAPONERY_H
