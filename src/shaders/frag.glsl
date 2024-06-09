#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float flip;

void main()
{
    vec2 coord = vec2((flip != 0.0 ? 1.0f - TexCoord.x : TexCoord.x), TexCoord.y);
    //FragColor = mix(texture(texture1, TexCoord), texture(texture2, coord), 0.2);
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
}