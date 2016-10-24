#version 410 
layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_colour;
layout(location = 2) in vec3 vertex_normal;
layout(location = 3) in mat4 model_mat;
layout(location = 7) in float mat_specular_intensity;
layout(location = 8) in float mat_specular_power;
layout(location = 9) in unsigned int sph_index;

uniform mat4 transformMatrix;

void main () {
gl_Position = transformMatrix*model_mat*vec4(vertex_position,1.0);
}