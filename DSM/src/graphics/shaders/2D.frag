#version 410
in vec3 colour;
out vec4 frag_colour;
in vec3 normal0;

struct point_light {
    vec3 colour;
    float amb_intensity;
    float diff_intensity;
    vec3 position;
};

uniform point_light gpoint_light;
void main () {
vec4 ambient_colour = vec4(gpoint_light.colour * 0.6f,1.0f);
vec3 light_position = normalize(vec3(0.0f,1.0f,0.0f));
vec3 normal = normalize(normal0);
float diffuse_factor = dot(normal,light_position);
vec4 diffuse_colour = vec4(0.0f,0.0f,0.0f,0.0f);

if (diffuse_factor>0.0f){
	diffuse_colour = vec4(gpoint_light.colour,1.0f) * gpoint_light.diff_intensity*diffuse_factor;
}

frag_colour = vec4(colour,1.0f)*(ambient_colour+diffuse_colour);
}