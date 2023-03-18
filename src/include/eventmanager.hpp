#pragma once

#include <map>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <functional>

namespace Arcade {

    struct Bind {
        sf::Keyboard::Key code;
        sf::Mouse::Button m_code;
        bool isMouseButton = false;
        bool state = false;
        bool last_state = false;
        Bind( sf::Keyboard::Key code ) : code( code ) {}
        Bind( sf::Mouse::Button code) : m_code( code ) { this->isMouseButton = true; }
        void UpdateState();
    };

    class Mouse {
        sf::Vector2i position;
        sf::Vector2i motion;
        float wheel_delta;

        public:
            void Update( const sf::Window *window, const sf::Event &event );
            void Clear();
            void SetPos( const sf::Window *window, sf::Vector2i pos );
            float GetWheelDelta();

            Mouse() : position(0, 0), motion(0, 0) {}
    };

    class BindManager {
        std::map<std::string, Bind*> binds;
        public:
            bool GetState( std::string key );
            bool StartPress( std::string key );
            bool EndPress( std::string key );
            void SetState( std::string key, bool n_value );
            void UpdateBinds();
            bool CreateBind( std::string name, sf::Keyboard::Key code );
            bool CreateBind( std::string name, sf::Mouse::Button code );
            bool RemoveBind( std::string name );

            void PrintBinds();
    };

}