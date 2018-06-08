#pragma once
#define  shader_image_vert "\
attribute vec4 my_Vertex;\
attribute vec2 my_Texcoord;\
uniform   mat4 my_TransformMatrix;\
varying   vec2 v_Texcoord;\
void main()\
{\
	v_Texcoord  = my_Texcoord;\
	gl_Position = my_TransformMatrix * my_Vertex;\
}"
