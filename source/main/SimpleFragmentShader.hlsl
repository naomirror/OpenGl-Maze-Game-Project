#version 330 core

//in vec3 fragmentColor;
// Ouput data
out vec3 color;

void main() {
    
    // Output color = color specified in the vertex shader,
    
    // interpolated between all 3 surrounding vertices
    vec3 LightColor = vec3(1,1,1);
    float LightPower =0.5;
    vec3 ambient = LightPower * LightColor;
    vec3 result = ambient * vec3(0.0,1.0,0.0);
    color = result;
    //color =vec3(1.0,0.0,0.0);
}


