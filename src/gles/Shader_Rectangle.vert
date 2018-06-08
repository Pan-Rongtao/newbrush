#pragma once

#define Shader_Rectangle_Vert "\
precision	lowp	float;\
attribute	vec4	att_position;\
attribute	vec4	att_color;\
attribute	vec2	att_texcoord;\
uniform		mat4	unf_mat;\
varying		vec4	var_color;\
varying		vec2	var_texcoord;\
void main()\
{\
	var_color = att_color;\
	var_texcoord = att_texcoord;\
	gl_Position = unf_mat * att_position;\
}\
"