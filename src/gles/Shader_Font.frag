#pragma once
#define shader_font_frag "\
precision  lowp float;\
uniform    sampler2D   _texture;\
varying    vec4        _outColor;\
varying    vec3        _outUV;\
void main()\
{\
   vec4   color   =   texture2D(_texture,vec2(_outUV.x,_outUV.y));\
  	if( _outUV.z > 0.0 )\
  	{\
		gl_FragColor    =   color.w * _outColor;\
	}\
 	else \
 	{\
       gl_FragColor    =   color * _outColor;\
    }\
}"
