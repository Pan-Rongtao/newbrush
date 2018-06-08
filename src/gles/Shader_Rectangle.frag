#pragma once

#define Shader_Rectangle_Frag "\
precision	lowp	float;\
uniform		float	BlendIntensity;\
varying		vec4	var_color;\
void main()\
{\
	gl_FragColor = var_color;\
	gl_FragColor.rgb = gl_FragColor.rgb * BlendIntensity;\
	gl_FragColor.a = gl_FragColor.a * BlendIntensity;\
}\
"