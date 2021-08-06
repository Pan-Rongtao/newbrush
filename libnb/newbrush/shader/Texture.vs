R"(
attribute vec4 position;
attribute vec2 uv;
uniform mat4 u_modelMatrix;
uniform mat4 u_viewProjectionMatrix;
varying vec2 v_uv;

void main()
{
	v_uv = uv;//normalize(position.xy);
	gl_Position = u_viewProjectionMatrix * u_modelMatrix * position;
}
)"