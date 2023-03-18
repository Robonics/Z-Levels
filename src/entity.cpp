#include "include/entity.hpp"
#include <string>
#include <algorithm>
#include "include/arcade_const.hpp"

#include <iostream>

#include <map>

using Arcade::Entity;
using Arcade::Animation;
using Arcade::AnimData;

AnimData::AnimData() : frame(0), frame_time(1) {
	this->time_since_frame.restart();
}

AnimData::AnimData( std::vector<sf::IntRect> frames, float frametime ) : frames(frames), frame_time(frametime), frame(0) {
	this->time_since_frame.restart();
}
AnimData::AnimData( const AnimData &c ) {
	this->frames = c.frames;
	this->frame_time = c.frame_time;
	this->time_since_frame.restart();
	this->frame = 0;
}

sf::IntRect AnimData::Rect() {
	// Calculate if we should advance frames
	if(this->time_since_frame.getElapsedTime().asSeconds() >= this->frame_time) {
		this->frame++;
		this->time_since_frame.restart();
	}
	if(this->frame >= this->frames.size()) {
		this->frame = 0;
	}
	return this->frames[this->frame];

}

Animation::Animation() : cur_animation_name("default") {}

Animation::Animation( const Animation &c ) {
	this->spritesheet = c.spritesheet;
	this->animsheet = c.animsheet;
}
Animation::Animation( std::shared_ptr<sf::Texture> texture, std::map< std::string, AnimData> anims ) : spritesheet(texture), animsheet(anims) {}


bool Animation::Exists( const std::string anim ) {
    return this->animsheet.find( anim ) != this->animsheet.end();
}

bool Animation::setAnimation( const std::string anim ) {
	if(this->animsheet.find( anim ) != this->animsheet.end()) {
		this->cur_animation_name = anim;
		return true;
	}
	return false;
}

std::shared_ptr<sf::Texture> Arcade::Animation::getSpriteSheet() {
	return this->spritesheet;
}

sf::IntRect Arcade::Animation::getTextureRect() {
	if(this->animsheet.find( this->cur_animation_name ) != this->animsheet.end()) {
		return this->animsheet[this->cur_animation_name].Rect();
	}
	return sf::IntRect( 0, 0, 10, 10 ); // Return a default if we cannot find the animation
}

void Arcade::Entity::render() {
	this->setPosition( this->world_pos );
	this->setTextureRect(this->animations.getTextureRect());
	this->engine->GetWindow()->Draw( *this );
}

void Arcade::Entity::update( unsigned int ent_index ) {
	// Do Nothing for the default entity class
}

Arcade::Animation* Arcade::Entity::GetAnimations() {
	return &(this->animations);
}

// bool Arcade::Animation::AppendToSpritesheet( const std::string file_path, std::string key, Arcade::AnimData anim ) { // Append a new animation onto a spritesheet
//     sf::Image n_text;
//     if(!n_text.loadFromFile( file_path )) return false; // Failed to append
//     sf::Vector2u n_size = n_text.getSize();
//     sf::Vector2u o_size = this->spritesheet.getSize();

//     sf::Image f_text;
//     f_text.create( std::max( n_size.x, o_size.x ), n_size.y + o_size.y, sf::Color(0, 0, 0, 0)); // Use the largest size between the old and new textures to create the final image's width, the hieght is just the sum

//     f_text.copy( this->spritesheet.copyToImage(), 0, 0, sf::IntRect(0, 0, 0, 0), true ); // Copy the old spritesheet to the top left corner
//     f_text.copy(n_text, 0, o_size.y + 1, sf::IntRect(0, 0, 0, 0), true); // Copy the new one below that

//     if(!this->spritesheet.loadFromImage( f_text )) return false; // Reload the texture with the final image | If failed return false
//     this->animationsheet[key] = anim;

//     return true; // Appended Successfully
// }

// FIXME: Append causes compilation errors