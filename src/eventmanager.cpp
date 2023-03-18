#include "include/eventmanager.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

void Arcade::Bind::UpdateState() {
    this->last_state = this->state;
    if(!this->isMouseButton) {
        this->state = sf::Keyboard::isKeyPressed( this->code );
    }else {
        this->state = sf::Mouse::isButtonPressed( this->m_code );
    }
}

bool Arcade::BindManager::GetState( std::string key ) {
    std::map<std::string, Arcade::Bind*>::iterator it = this->binds.find( key );
    if(it != this->binds.end()) {
        return this->binds[key]->state;
    }
    return false;
}
void Arcade::BindManager::SetState( std::string key, bool n_value ) {
    std::map<std::string, Arcade::Bind*>::iterator it = this->binds.find( key );
    if(it != this->binds.end()) {
        this->binds[key]->state = n_value;
    }
}
void Arcade::BindManager::UpdateBinds() {
    for(std::pair<std::string, Bind*> bind : this->binds) {
        bind.second->UpdateState();
    }
}

bool Arcade::BindManager::CreateBind( std::string name, sf::Keyboard::Key code ) {
    if(this->binds.find( name ) != this->binds.end()) { return false; } // Bind with this name already exists | return failure

    this->binds[name] = new Arcade::Bind( code );

    return true; // Assume Sucess

}
bool Arcade::BindManager::CreateBind( std::string name, sf::Mouse::Button code ) {
    if(this->binds.find( name ) != this->binds.end()) { return false; } // Bind with this name already exists | return failure

    this->binds[name] = new Arcade::Bind( code );

    return true; // Assume Sucess

}

bool Arcade::BindManager::RemoveBind( std::string name ) {
    if(this->binds.find(name) == this->binds.end()) { return false; } // Bind with this name does not exist | return failure

    this->binds.erase(name);

    return true; // Assume Sucess
}

void Arcade::BindManager::PrintBinds() {
    for( std::pair<std::string, Arcade::Bind*> bind : this->binds ) {
        std::cout << bind.first << '\t' << bind.second->state << std::endl;
    }
}

bool Arcade::BindManager::StartPress( std::string key ) {
    std::map<std::string, Arcade::Bind*>::iterator it = this->binds.find( key );
    if(it != this->binds.end()) {
        return (this->binds[key]->state && !this->binds[key]->last_state); // This Frame is pressed, but not last frame
    }
    return false; // Return false if we can't find the bind
}

bool Arcade::BindManager::EndPress( std::string key ) {
    std::map<std::string, Arcade::Bind*>::iterator it = this->binds.find( key );
    if(it != this->binds.end()) {
        return (!this->binds[key]->state && this->binds[key]->last_state); // This Frame is not pressed, but last frame was pressed
    }
    return false; // Return false if we can't find the bind
}

void Arcade::Mouse::Update( const sf::Window *window, const sf::Event &event ) {
    if(event.type == sf::Event::MouseWheelScrolled) {
        this->wheel_delta = event.mouseWheelScroll.delta;
        sf::Vector2i _pos = this->position;
        this->position = sf::Vector2i(event.mouseWheelScroll.x, event.mouseWheelScroll.y);
        this->motion = position - _pos;
    }
}

float Arcade::Mouse::GetWheelDelta() {
    return this->wheel_delta;
}

void Arcade::Mouse::Clear() {
    this->motion = sf::Vector2i(0, 0);
    this->wheel_delta = 0;
}