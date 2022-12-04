#include <SFML/Audio.hpp>
#include <string.h>

class SoundEffect {
private:
	struct Sounds_t {
		std::string name;
		sf::SoundBuffer buffer;
		sf::Sound sound;
	};
	std::vector<Sounds_t> sounds;
public:
	int error;
	void add(std::string);
	void play(std::string);
	void stop(std::string);
};