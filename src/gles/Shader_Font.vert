#pragma once
#define shader_font_vert "\
precision  lowp float;\
uniform    mat4 _MVP;\
attribute  vec3 _position;\
attribute  vec3 _uv;\
attribute  vec4 _color;\
varying    vec3 _outUV;\
varying    vec4 _outColor;\
void main()\
{\
   vec4    pos =   vec4(_position.x,_position.y,_position.z,1);\
   gl_Position =   _MVP * pos;\
   _outUV      =   _uv;\
   _outColor   =   _color;\
}"
