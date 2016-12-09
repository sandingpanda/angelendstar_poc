#include "EntityList.h"

EntityList::EntityList()
{
	for (int $i = 0; $i < MAX_ENTITIES; $i++) {
		_entities[$i] = NULL;
	}
}

EntityList::~EntityList()
{
	for (int $i = 0; $i < MAX_ENTITIES; $i++) {
		_entities[$i] = NULL;
	}
}

//add/remove functions
void EntityList::addEntity(Entity* $new_entity)
{
	if ($new_entity == NULL) {
		printf("EntityList.addEntity-> ERROR: INVALID ENTITY");
	}

	int $i;

	for ($i = 0; $i < MAX_ENTITIES; $i++) {
		if (_entities[$i] == NULL) {
			_entities[$i] = $new_entity;
			_entities[$i]->active = true;
			break;
		}
	}
}

void EntityList::freeEntity(Entity* $entity)
{
	for (int $i = 0; $i < MAX_ENTITIES; $i++) {
		if (_entities[$i] == $entity) {
			_entities[$i] = NULL;
		}
	}
}

void EntityList::setGraphics(Graphics* $graphics)
{
	if ($graphics != NULL) {
		_graphics = $graphics;
	}
	else
	{
		printf("EntityList.setGraphics-> ERROR: INVALID GRAPHICS OBJECT");
	}
}

//iterative entity functions
void EntityList::allEntitiesThink()
{
	for (int $i = 0; $i < MAX_ENTITIES; $i++) {
		if (_entities[$i] != NULL) {
			if (_entities[$i]->active) {
				_entities[$i]->think(_entities[$i]);
			}

			if (_entities[$i]->dead) {
				if (_entities[$i]->type == EntityType::ENEMY) {
					score = score + _entities[$i]->score_value;
					update_score = true;
				}

				_entities[$i]->active = false;
				_entities[$i]->die();
				_entities[$i] = NULL;
			}
		}
	}
}

void EntityList::allEntitiesDraw()
{
	for (int $i = 0; $i < MAX_ENTITIES; $i++) {
		if (_entities[$i] != NULL) {
			if (_entities[$i]->active) {
				Entity* $entity = _entities[$i];
				Sprite* $sprite = $entity->sprite;

				if ($sprite->visible) {
					if ($entity->show_bounds) {
						_graphics->renderBasicRect(&$entity->bound_rect);
					}
					_graphics->renderTexture($sprite->sprite_texture, $sprite->setFrame($entity->current_frame), $entity->x - $entity->sprite_x, $entity->y - $entity->sprite_y);
				}
			}
		}
	}
}

Entity* EntityList::allEntitiesHit(Entity* $entity)
{
	for (int $i = 0; $i < MAX_ENTITIES; $i++) {
		if (_entities[$i] != NULL) {
			if (_entities[$i]->active) {
				if (_entities[$i] != $entity) {
					if (GameRect::intersects(&$entity->bound_rect, &_entities[$i]->bound_rect)) {
						return _entities[$i];
					}
				}
			}
		}
	}
	return NULL;
}

Entity* EntityList::forEachEntity(int $index)
{
	return _entities[$index];
}
