#include "sound.h"
#include <iostream>
#include <chrono>
#include <thread>

void SoundEffect::add(std::string name) {
	Sounds_t temp;
	sounds.push_back(temp);
	auto index = sounds.size() - 1;
	sounds[index].name = name;
	std::string filename = "c:/Temp/";
	filename.append(name);
	filename.append(".wav");
	std::cout << "filename: " << filename << std::endl;
	if (!sounds[index].buffer.loadFromFile(filename))
		std::cout << "EERRRRROR" << std::endl;
	else
		std::cout << "OK" << std::endl;
	sounds[index].sound.setBuffer(sounds[index].buffer);
}

void SoundEffect::play(std::string name) {
	std::vector<Sounds_t>::iterator it;
	for (it = sounds.begin(); it != sounds.end(); it++) {
		if (it->name == name) {
			it->sound.play();
		}
	}
}

void SoundEffect::stop(std::string name) {
	std::vector<Sounds_t>::iterator it;
	for (it = sounds.begin(); it != sounds.end(); it++) {
		if (it->name == name) {
			it->sound.stop();
		}
	}
}
