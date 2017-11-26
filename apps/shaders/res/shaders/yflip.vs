#version 410 core

layout(location = 0) in vec3 a_loc;
layout(location = 1) in vec4 a_color;

out vec4 v_color;

void main() {
  gl_Position = vec4(a_loc.x, -a_loc.y, a_loc.z, 1.0);
  v_color = a_color;
}
