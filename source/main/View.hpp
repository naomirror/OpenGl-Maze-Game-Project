#pragma once
// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>
#include <vector>

// Include GLM
#include <glm/glm.hpp>
using namespace glm;
#include "common/objloader.hpp"
#include "common/vboindexer.hpp"
#include <glm/gtx/transform.hpp>
#include "common/shader.hpp"
#include "common/controls.hpp"
#include "common/text2D.hpp"

class View {
private:
    
    GLFWwindow* window;
    
    GLuint programID;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> vertices1;
    std::vector<glm::vec3> vertices2;
    GLuint VertexArray1;
    GLuint vertexArray2;
    GLuint vertexbufferMaze;
    GLuint vertexbufferPlayer;
    GLuint vertexbufferCol;
    
    //screen size
    int width;
    int height;
  
    
    
    
    
public:
    View(int widtht, int heightt);
    ~View();
    int initialise();
    void update();

    
};

