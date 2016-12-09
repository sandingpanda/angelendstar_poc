#ifndef AE_PHYSICS_ENGINE
#define AE_PHYSICS_ENGINE

//C++
#include <math.h>
#include <stdint.h>

//SYSTEM
#include "Map.h"
#include "EntityList.h"

class PhysicsEngine {
public:
	PhysicsEngine();
	~PhysicsEngine();

	//scrolling values
	int scroll_speed_x, scroll_speed_y = 0;
	int scroll_dir_x, scroll_dir_y = 0;

	//pointer to current map
	Map* current_map;

	void setEntityList(EntityList* $entity_list);

	void moveAllEntities();

	//map walk lookup
	void getEntityCorners(Entity* $entity, uint32_t $x, uint32_t $y);

	//entity movement/reaction calls
	void moveEntity(Entity* $entity);
	void fallCorner(Entity* $entity);

private:
	static const int _MAX_GRAVITY = 32;

	uint32_t _entity_count = 0;
	EntityList* _entity_list;
};


#endif