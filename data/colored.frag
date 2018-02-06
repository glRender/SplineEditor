#version 130
out vec4 color;   
in vec3 keyring_position; 
in vec3 keyring_color;

void main(void)
{
    color = vec4(keyring_color, 1.0);
}
