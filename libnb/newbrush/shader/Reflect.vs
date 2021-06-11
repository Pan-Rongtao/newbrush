R"(
attribute vec3 position;
attribute vec2 uv;
attribute vec3 normal;
uniform mat4 u_modelMatrix;
uniform mat4 u_viewProjectionMatrix;
varying vec2 v_uv;
varying vec3 v_normal;
varying vec3 v_fragPos;

void main()
{
	v_fragPos = vec3(u_modelMatrix * vec4(position, 1.0));
	v_normal = mat3(u_modelMatrix) * normal;
	v_uv = uv;
	gl_Position = u_viewProjectionMatrix * u_modelMatrix * vec4(position, 1.0);
}
)"