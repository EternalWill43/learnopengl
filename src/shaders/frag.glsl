#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float flip;
uniform float opacity;

void main()
{
    vec2 coord = vec2((flip != 0.0 ? 1.0f - TexCoord.x : TexCoord.x), TexCoord.y);
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, coord), opacity);
   // FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
}