#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include <array>

namespace ZLevel {
	struct TilePos : public sf::Vector2i {
		/// \brief This is a cached value. It should be accurate, but may not be if the TilePos is manually overriden
		uint16_t layer;

		TilePos( int x, int y, int z ) : sf::Vector2i( x, y ), layer(z) {

		}
	};

	class Tile {
		/// \brief Cached tile position
		TilePos pos;
		sf::Sprite drawable;

		void preRender() {

		}

	public: 
		TilePos getTilePos() {
			return this->pos;
		}

		void render( ZLevel::Window& window ) {
			preRender();
			window.draw( this->drawable );
		}
		void render( ZLevel::Window* window ) {
			preRender();
			window->draw( this->drawable );
		}
	};

	class Window : public sf::RenderWindow {

		sf::View camera;
		
		Window( sf::VideoMode bounds, const std::string title ) : sf::RenderWindow( bounds, title ) {

		}

		virtual void onResize() {
			// TODO: Calculate view
		}
	};

	class Game {
		std::array<std::map<TilePos, Tile>, 32u> loaded_tiles; // Z-Layer, Position : Tile
		ZLevel::Window *window;

	public:
		void renderTiles() {
		}	
	};
}