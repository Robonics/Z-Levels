#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>

namespace ZLevel {
	struct Animation {
		sf::IntRect bounds;
		float timing;

		Animation( sf::IntRect bounds, float timing ) : bounds(bounds), timing(timing) {}
	};
	class Animatable {
		sf::Texture spritesheet;
		std::map<std::string, Animation> animations;
	};
}