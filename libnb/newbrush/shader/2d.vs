R"(
attribute vec4 position;
attribute vec4 color;
attribute vec2 uv;
attribute float texIndex;
attribute float opacity;
uniform mat4 u_viewProjectionMatrix;
varying vec4 v_color;
varying vec2 v_uv;
varying float v_texIndex;
varying float v_opacity;

void main()
{
	v_color = color;
	v_uv = uv;
	v_texIndex = texIndex;
	v_opacity = opacity;
	gl_Position = u_viewProjectionMatrix * position;
}
)"