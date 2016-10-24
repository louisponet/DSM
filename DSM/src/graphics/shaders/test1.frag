#version 410
in vec3 colour;
in vec3 normal0;
in vec3 world_pos;
in float specular_intensity;
in float specular_power;
in vec3 eye_world_pos;
out vec4 color;

struct point_light {
    vec3 colour;
    float amb_intensity;
    float diff_intensity;
    vec3 position;
};

uniform point_light gpoint_light;
void main () {

vec4 ambient_colour = vec4(gpoint_light.colour * gpoint_light.amb_intensity,1.0f);
vec3 light_position = normalize(gpoint_light.position - world_pos);
vec3 normal = normalize(normal0);

float diffuse_factor = dot(normal,light_position);


vec4 diffuse_colour = vec4(0.0f,0.0f,0.0f,0.0f);
vec4 specular_colour = vec4(0.0f,0.0f,0.0f,0.0f);

if (diffuse_factor>0.0f){
    diffuse_colour = vec4(gpoint_light.colour,1.0f) * gpoint_light.diff_intensity*diffuse_factor;
    vec3 vertex_to_eye = normalize(eye_world_pos-world_pos);
    vec3 light_reflect = normalize(reflect(-gpoint_light.position,normal));
    float specular_factor = dot(vertex_to_eye, light_reflect);
    if(specular_factor>0) {
        specular_factor = pow(specular_factor,specular_power);
        specular_colour = vec4(gpoint_light.colour*specular_intensity*specular_factor,1.0f);
    }
}
 color = vec4(1.0,0.0,1.0,1.0);
}