R"(
attribute vec3 position;
uniform mat4 u_modelMatrix;
uniform mat4 u_viewProjectionMatrix;

void main()
{
	gl_Position = u_viewProjectionMatrix * u_modelMatrix * vec4(position, 1.0);
}
)"