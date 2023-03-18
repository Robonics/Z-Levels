#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <array>
#include <cstddef>
#include <memory>

#include "arcade_engine.hpp"

namespace Arcade {

	class EngineWrapper;

	struct AnimData {
		std::vector<sf::IntRect> frames;
		int frame;
		float frame_time;
		sf::Clock time_since_frame;

		public:
			AnimData();
			AnimData( const AnimData &c );
			AnimData( std::vector<sf::IntRect> frames, float frametime );
			sf::IntRect Rect();
	};

	class Animation {
		std::shared_ptr<sf::Texture> spritesheet; // Refers to an engine texture
		std::map< std::string, AnimData> animsheet;
		std::string cur_animation_name;

		public:
			Animation();
			Animation( const Animation &c );
			Animation( std::shared_ptr<sf::Texture> texture, std::map< std::string, AnimData> anims );
			
			std::shared_ptr<sf::Texture> getSpriteSheet();
			sf::IntRect getTextureRect();
			bool setAnimation( const std::string name );
			std::string getAnimation();
			bool Exists( const std::string name );
	};

    class Entity : sf::Sprite {
        sf::Vector2f world_pos;
        Arcade::Animation animations;
        // std::string ref_name;

		Arcade::EngineWrapper *engine; // We store a reference to the engine, this doesn't need to be a smart ptr because the engine should always exist

    public:
		virtual void render();
		virtual void update( unsigned int ent_index );

		Entity( Arcade::EngineWrapper *engine, Arcade::Animation anim ) : Sprite(), animations(anim), engine(engine) {
			this->world_pos = sf::Vector2f(0.0f, 0.0f);
			this->setTexture( *(this->animations.getSpriteSheet()) );
		}
		Entity( Arcade::EngineWrapper *engine, Arcade::Animation anim, sf::Vector2f pos ) : animations(anim), world_pos(pos), engine(engine) {
			this->setTexture( *(this->animations.getSpriteSheet()) );
		}

		Arcade::Animation* GetAnimations();
    };

}