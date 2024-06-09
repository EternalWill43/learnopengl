#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float flip;

void main()
{
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, vec2(flip - TexCoord.x, TexCoord.y)), 0.2);
}