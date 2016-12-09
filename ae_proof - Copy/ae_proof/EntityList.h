#ifndef AE_ENTITY_LIST
#define AE_ENTITY_LIST

#include "Entity.h"
#include "Graphics.h"

class EntityList
{
public:
	EntityList();
	~EntityList();

	//add/remove functions
	void addEntity(Entity* $entity);
	void freeEntity(Entity* $entity);

	void setGraphics(Graphics* $graphics);

	//iterative functions
	void allEntitiesThink();
	void allEntitiesDraw();
	Entity* allEntitiesHit(Entity* $entity);
	Entity* forEachEntity(int $index);

	static const int MAX_ENTITIES = 256;

	int score;
	bool update_score;

private:
	Entity* _entities[MAX_ENTITIES];

	Graphics* _graphics;
};

#endif