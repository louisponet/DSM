#version 410
layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_colour;
layout(location = 2) in vec3 vertex_normal;
layout(location = 3) in mat4 model_mat;
layout(location = 7) in float mat_specular_intensity;
layout(location = 8) in float mat_specular_power;
layout(location = 9) in unsigned int sph_index;

uniform mat4 transformMatrix;
uniform vec3 eye_world_pos0;
uniform unsigned int selected_index;
out vec3 normal0;
out vec3 colour;
out vec3 world_pos;
out float specular_intensity;
out float specular_power;
out vec3 eye_world_pos;

void main () {
if (selected_index == sph_index){
    colour = vertex_colour+vec3(1.0f-vertex_colour.x/6.0f,1.0f-vertex_colour.y/6.0f,1.0f-vertex_colour.z/6.0f);
}
else{
    colour = vertex_colour;
}
normal0 = (model_mat*vec4(vertex_normal,0.0f)).xyz;
world_pos = (model_mat*vec4(vertex_position,1.0f)).xyz;
eye_world_pos = eye_world_pos0;
specular_intensity = mat_specular_intensity;
specular_power = mat_specular_power;
gl_Position = transformMatrix*vec4(vertex_position,1.0f);
}