R"(
precision mediump float;
varying vec4 v_color;
varying vec2 v_uv;
varying float v_texIndex;
varying float v_opacity;
uniform sampler2D u_samplers[16];	//android中最高支持16

void main()
{
	int _index = int(v_texIndex);
	gl_FragColor = texture2D(u_samplers[_index], v_uv) * v_color;
	gl_FragColor.a = gl_FragColor.a * v_opacity;
}
)"