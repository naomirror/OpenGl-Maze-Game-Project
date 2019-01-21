// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <glm/gtc/matrix_transform.hpp>
// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>
#include <iostream>
#include <vector>
#include "View.hpp"

int H = 500; // Height of window
int W = 500; // Width of window

int main(void)
{


	//initialise myview
	View* myview = new View(W, H);
	
	//initialise the scene and if succesful go into the control loop to wait for user input
	if (myview->initialise() != -1) {
        myview->update();
    }	else {
		std::cout << "ERROR: The game has not been initialised correctly" << std::endl;
		return 0;
	}
	
	return 0;
}

