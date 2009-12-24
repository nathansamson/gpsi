#ifndef INC_CLUSTERBOMB_H
#define INC_CLUSTERBOMB_H

#include "game/ammotype.h"
#include "game/bullet.h"
#include "game/projectile.h"

namespace SI {
	/**
	 * A cluster bomb type.
	*/
	class ClusterBombType: public AmmoType {
	public:
		/**
		 * The speed of the bomb.
		*/
		Vector2 fSpeed;
		
		/**
		 * The type of the bullets.
		*/
		BulletType* fBulletType;
		
		/**
		 * The number of bullets in the bomb.
		*/
		int fBullets;
		
		/**
		 * The time the bomb will be alive (before it explodes)
		*/
		int fMaxTicksAlive;
	};
	
	/**
	 * A cluster bomb projectile.
	*/
	class ClusterBomb: public IProjectile {
	public:
		ClusterBomb(Vector2, int, EntityGroup*, ClusterBombType*, IGameEntityFactory*);
		
		virtual std::vector<VGameEntity*> update(int);
		virtual double getImpact();
		virtual void collide(VGameEntity*);
	private:
		/**
		 * The type of the cluster bomb.
		*/
		ClusterBombType* fClusterBombType;
		
		/**
		 * The time the bomb is alive.
		*/
		int fTicksAlive;
		
		/**
		 * Flag to see if the bomb is exploded.
		*/
		bool fExploded;
	};
}

#endif // INC_CLUSTERBOMB_H
