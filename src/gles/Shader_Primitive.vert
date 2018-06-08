#pragma once

#define shader_primitive_vert "\
precision  lowp float;\
uniform    mat4 _MVP;\
attribute  vec3 _position;\
void main()\
{\
   vec4    pos =   vec4(_position.x,_position.y,_position.z,1);\
   gl_Position =   _MVP * pos;\
}"
