#include <iostream>
#include <fstream>


#include <vector>
#include <SFML/Graphics.hpp>

int main() {
	

	while(!engine.GetWindow()->IsDone()) { // While Engine Window is Open
		engine.HandleInput(); // Handle the PLayer's Inputs
		engine.Update(); // Update Game Objects
		engine.Render(); // Render
	}
}