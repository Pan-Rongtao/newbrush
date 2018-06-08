#pragma once
#define shader_primitive_frag "\
precision  lowp float; \
uniform	vec4 _color;\
void main()\
{\
	gl_FragColor = _color;\
}"
