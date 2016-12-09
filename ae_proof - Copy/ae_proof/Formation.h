#ifndef AE_MAP_FORMATION
#define AE_MAP_FORMATION

#include <stdint.h>
#include <array>

class Formation
{
public:
	Formation();
	~Formation();

	int scroll_type = 0;
	bool active = false;
	static const uint32_t MAX_ENEMIES = 16;

	std::array<std::string, MAX_ENEMIES> enemies;
};

#endif