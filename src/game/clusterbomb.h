#ifndef INC_CLUSTERBOMB_H
#define INC_CLUSTERBOMB_H

#include "game/ammotype.h"
#include "game/bullet.h"
#include "game/gameentity.h"

namespace SI {
	class ClusterBombType: public AmmoType {
	public:
		Vector2 fSpeed;
		BulletType* fBulletType;
		int fBullets;
		int fMaxTicksAlive;
	};
	
	class ClusterBomb: public VGameEntity {
	public:
		ClusterBomb(Vector2, int, EntityGroup*, ClusterBombType*, IGameEntityFactory*);
		
		virtual std::vector<VGameEntity*> update(int);
		virtual double getImpact();
		virtual void collide(VGameEntity*);
	private:
		ClusterBombType* fClusterBombType;
		int fTicksAlive;
		bool fExploded;
	};
}

#endif // INC_CLUSTERBOMB_H
