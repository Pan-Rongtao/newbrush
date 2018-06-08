#pragma once
#define shader_image_frag "\
precision highp float;\
uniform		float		BlendIntensity;\
uniform		sampler2D	sampler;\
varying		vec2		v_Texcoord;\
void main(void)\
{\
	gl_FragColor = texture2D(sampler, v_Texcoord);\
	gl_FragColor.rgb = gl_FragColor.rgb * BlendIntensity;\
	gl_FragColor.a = gl_FragColor.a * BlendIntensity;\
}"
