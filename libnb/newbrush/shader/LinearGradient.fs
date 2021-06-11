R"(
precision mediump float;
uniform vec4 u_colors[10];
uniform float u_offsets[10];
uniform vec2 u_resolution;
uniform int u_gradientCount;
uniform bool u_horizontal;

void main()
{
	float _n = u_horizontal ? gl_FragCoord.x / u_resolution.x : gl_FragCoord.y / u_resolution.y;
	vec4 _color = mix(u_colors[0], u_colors[1], smoothstep(u_offsets[0], u_offsets[1], _n));
	for(int i = 2; i < u_gradientCount; ++i)
		_color = mix(_color, u_colors[i], smoothstep(u_offsets[i-1], u_offsets[i], _n));
	gl_FragColor = _color;
}
)"