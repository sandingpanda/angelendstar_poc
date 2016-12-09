#ifndef AE_SFX_LIBRARY
#define AE_SFX_LIBRARY

#include "AudioPlayer.h"

enum class SFXSample { SHOOT_ONE, SHOOT_TWO, EXPLOSION, BLAST, BLADE};

class SFXLibrary
{
public:
	SFXLibrary();
	~SFXLibrary();

	static void loadSamples();
	static void playSFX(SFXSample $sample);
	
	static AudioPlayer* AUDIO_PLAYER;
	
private:
	static const char* PATH_SHOOT_ONE;
	static const char* PATH_SHOOT_TWO;
	static const char* PATH_EXPLOSION;
	static const char* PATH_BLAST;
	static const char* PATH_BLADE;

	static int _index_list[5];
};

#endif