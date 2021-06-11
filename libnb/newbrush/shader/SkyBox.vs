R"(
attribute vec4 position;
uniform mat4 u_modelMatrix;
uniform mat4 u_viewProjectionMatrix;
varying vec3 v_uv;

void main()
{
	v_uv = position.xyz;
	gl_Position = (u_viewProjectionMatrix * u_modelMatrix * position).xyww;
}
)"