#include "View.hpp"

View::View(int widtht, int heightt) {
    width = widtht;
    height = heightt;
   
}
View::~View() {
    
}

int View::initialise() {
    
    // Initialise GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        getchar();
        return -1;
    }
    
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    

    
    // Open a window and create its OpenGL context
    window = glfwCreateWindow(width, height, "My Game", NULL, NULL);
    if (window == NULL) {
        fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
        getchar();
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
     glewExperimental = true;  // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return -1;
    }
    
    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    
    // Set the mouse at the center of the screen
    
    glfwPollEvents();
    //we set the cursor at the centre so that it always start on our origin (0,0,0)
    glfwSetCursorPos(window, width / 2, height / 2);
    
    
    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    

    
    std::vector<glm::vec2> uvs; // Won't be used at the moment.
    
    std::vector<glm::vec3> normals; // Won't be used at the moment.
    
    bool res = loadOBJ("cube.obj", vertices, uvs, normals);
    
    
    
    
    
    
    glGenBuffers(1, &vertexbuffer);
    
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    
    //glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
    
    
    programID = LoadShaders("SimpleVertexShader.hlsl", "SimpleFragmentShader.hlsl");
    

    return 1;
}

void View::update() {
    
    do{
        // Clear the screen. It's not mentioned before Tutorial 02, but it can cause flickering, so it's there nonetheless.
        glClear( GL_COLOR_BUFFER_BIT );
        
        glUseProgram(programID);
        
        // Draw nothing, see you in tutorial 2 !
        glEnableVertexAttribArray(0);
        
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        
        glVertexAttribPointer(
                              
                              0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                              
                              3,                  // size
                              
                              GL_FLOAT,           // type
                              
                              GL_FALSE,           // normalized?
                              
                              0,                  // stride
                              
                              (void*)0            // array buffer offset
                              
                              );
        
        
        
        // Draw the triangles
        
        glDrawArrays(GL_TRIANGLES, 0, vertices.size() * sizeof(glm::vec3));
        
        
        
        glDisableVertexAttribArray(0);
        
        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
          glfwWindowShouldClose(window) == 0 );
    
    // Close OpenGL window and terminate GLFW
    glfwTerminate();
    
}

