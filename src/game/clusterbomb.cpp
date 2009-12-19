#include "game/clusterbomb.h"
#include "game/gameentityfactory.h"

namespace SI {
	ClusterBomb::ClusterBomb(Vector2 pos, int dir, EntityGroup* group,
	                         ClusterBombType* type, IGameEntityFactory* fac):
	    VGameEntity(pos, dir, type->fBoundingShapeDesc, group, fac),
	    fClusterBombType(type), fTicksAlive(0), fExploded(false) {
	}
	
	std::vector<VGameEntity*> ClusterBomb::update(int ticks) {
		fTicksAlive += ticks;
		if (fTicksAlive > fClusterBombType->fMaxTicksAlive) {
			fExploded = true;
		}
		move(ticks * fClusterBombType->fSpeed);
		if (fExploded) {
			// return something
			std::vector<VGameEntity*> bullets;
			for (int i = 0; i < fClusterBombType->fBullets; i++) {
				int rotated = 0;
				
				rotated = (i+1)*1.0/(fClusterBombType->fBullets+1) * 180 - 90;
				bullets.push_back(fEntityFactory->createBullet(getPosition(), rotated, getGroup(), fClusterBombType->fBulletType));
			}
			die();
			return bullets;
		} else {
			return std::vector<VGameEntity*>();
		}
	}
	
	double ClusterBomb::getImpact() {
		return 0.0;
	}
	
	void ClusterBomb::collide(VGameEntity* other) {
		fExploded = true;
	}
}
