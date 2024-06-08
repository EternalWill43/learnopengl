#version 330 core
out vec4 FragColor;
in vec3 ourColor;
in vec4 pos;
void main()
{
  FragColor = vec4(pos.r + 0.5f, pos.g + 0.5f, pos.b + 0.5f , 1.0f);
};