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
    window = glfwCreateWindow(width, height, "Maze Game", NULL, NULL);
    if (window == NULL) {
        fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
        getchar();
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);//escape key capture
    
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); //hide cursor and enable movement
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
    
    //bool res = loadOBJ("mazetris.obj", vertices, uvs, normals);
    bool res =loadOBJ("leftWall.obj",vertices, uvs, normals);
    bool res0 =loadOBJ("rightWall.obj",vertices, uvs, normals);
    bool res1 =loadOBJ("inner1Wall.obj",vertices, uvs, normals);
    bool res2 =loadOBJ("inner2Wall.obj",vertices, uvs, normals);
    bool res3 =loadOBJ("inner3Wall.obj",vertices, uvs, normals);
    bool res4 =loadOBJ("backWall.obj",vertices, uvs, normals);
    bool res5 =loadOBJ("frontWall.obj",vertices, uvs, normals);
    bool res6 =loadOBJ("floor.obj",vertices, uvs, normals);
    bool res7 =loadOBJ("player.obj",vertices1,uvs,normals);
    bool res8 =loadOBJ("t1.obj",vertices2, uvs, normals);
    bool res9 =loadOBJ("t2.obj",vertices2, uvs, normals);
    bool res10 =loadOBJ("t3.obj",vertices2, uvs, normals);
    glGenBuffers(1, &vertexbufferMaze);
    
    glBindBuffer(GL_ARRAY_BUFFER, vertexbufferMaze);
    
    //glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
    
    glGenBuffers(1, &vertexbufferPlayer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbufferPlayer);
    glBufferData(GL_ARRAY_BUFFER, vertices1.size() * sizeof(glm::vec3), &vertices1[0], GL_STATIC_DRAW);
    
    glGenBuffers(1, &vertexbufferCol);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbufferCol);
    glBufferData(GL_ARRAY_BUFFER, vertices2.size() * sizeof(glm::vec3), &vertices2[0], GL_STATIC_DRAW);    programID = LoadShaders("SimpleVertexShader.hlsl", "SimpleFragmentShader.hlsl");
    
    

    return 1;
}

glm::mat4 getMVPMatrix(glm::mat4 ProjectionMatrix, glm::mat4 ViewMatrix, glm::mat4 ModelMatrix) {
    
    
    
    
    
    
    
    glm::mat4 Projection = ProjectionMatrix;
    
    //glm::perspective(
                                             //glm::radians(90.0f),
                                            // 4.0f/ 3.0f,
                                             //0.1f,
                                            // 1000.0f
                                            // );
    
    
    
    glm::mat4 View = ViewMatrix;
    //(mat4) glm::lookAt(
                             //    glm::vec3(0,100,-40), // Camera is at (4,3,-3), in
                               //  World Space
                               //  glm::vec3(0, 0, 0), // and looks at the origin
                                 //glm::vec3(0, 1, 0) // Head is up (set to 0,-1,0 to
                                // look upside-down
    //);
    
    
    glm::mat4 Model = ModelMatrix;
    
    //glm::mat4(100.0f); // keep an identity matrix so the geometry stays where it was placed originally
    
    
    
    
    
    
    
    // Our ModelViewProjection : multiplication of our 3 matrices
    
    
    
    glm::mat4 mvp = Projection * View * Model; // Remember, matrix multiplication is the other way around
    
    
    
    return mvp;
    
    
    
    
    
    
    
}

void View::update() {
    GLuint MatrixID1 = glGetUniformLocation(programID, "MVP");
    do{
        // Clear the screen. It's not mentioned before Tutorial 02, but it can cause flickering, so it's there nonetheless.
        glClear( GL_COLOR_BUFFER_BIT );
        glUseProgram(programID);
        computeMatricesFromInputs(window, width, height);
        glm::mat4 mvp1 = getMVPMatrix(getProjectionMatrix(), getViewMatrix(), glm::mat4(1.0f));
        
        glUniformMatrix4fv(MatrixID1, 1, GL_FALSE, &mvp1[0][0]);
        

       
        // Draw nothing, see you in tutorial 2 !
        glEnableVertexAttribArray(0);
        
        glBindBuffer(GL_ARRAY_BUFFER, vertexbufferMaze);
        
        glVertexAttribPointer(
                              
                              0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                              
                              3,                  // size
                              
                              GL_FLOAT,           // type
                              
                              GL_FALSE,           // normalized?
                              
                              0,                  // stride
                              
                              (void*)0            // array buffer offset
                              
                              );
        
        
        
        // Draw the triangles
        std::cout << vertices.size() << std::endl;
        //glDrawArrays(GL_TRIANGLES, 0, vertices.size() * sizeof(glm::vec3));
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawArrays(GL_TRIANGLES, 0, vertices.size() );
        
        glDisableVertexAttribArray(0);
        
        glEnableVertexAttribArray(0);
        
        glBindBuffer(GL_ARRAY_BUFFER, vertexbufferCol);
        
        glVertexAttribPointer(
                              
                              0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                              
                              3,                  // size
                              
                              GL_FLOAT,           // type
                              
                              GL_FALSE,           // normalized?
                              
                              0,                  // stride
                              
                              (void*)0            // array buffer offset
                              
                              );
        
        
        
        // Draw the triangles
        std::cout << vertices.size() << std::endl;
        //glDrawArrays(GL_TRIANGLES, 0, vertices.size() * sizeof(glm::vec3));
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawArrays(GL_TRIANGLES, 0, vertices2.size() );
        
        glDisableVertexAttribArray(0);

        glm::mat4 mvp2 = getMVPMatrix(
                                      
                                      getProjectionMatrix(),
                                      
                                      getViewMatrix(),
                                      
                                      getModelMatrix());
                                                
        glUniformMatrix4fv(MatrixID1, 1, GL_FALSE, &mvp2[0][0]);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbufferPlayer);
        
        glVertexAttribPointer(
                              
                              0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                              
                              3,                  // size
                              
                              GL_FLOAT,           // type
                              
                              GL_FALSE,           // normalized?
                              
                              0,                  // stride
                              
                              (void*)0            // array buffer offset
                              
                              );
        glDrawArrays(GL_TRIANGLES, 0, vertices1.size());
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

