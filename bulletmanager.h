#include "bullet.h"
#include <vector>


#ifndef BULLET_MANAGER_H
#define BULLET_MANAGER_H
class BulletManager{
	private:
		std::vector<Bullet*> bullets;
	public:
		BulletManager();
		~BulletManager();
		BulletManager(const BulletManager&) = delete;
		BulletManager& operator=(const BulletManager&) = delete;
	public:
		void shoot(Bullet*);
		void update();
		void renderAllBullets();
};
#endif
