R"(
attribute vec3 position;
attribute vec2 uv;
attribute vec3 normal;
attribute vec4 boneIndexs;
attribute vec4 boneWeights;
uniform mat4 u_modelMatrix;
uniform mat4 u_viewProjectionMatrix;
uniform mat4 u_rootMatrix;
uniform bool u_hasBones;
uniform mat4 u_bonesMatrixs[60];	//有些驱动无法支持到100
varying vec2 v_uv;
varying vec3 v_normal;
varying vec3 v_fragPos;

void main()
{
	mat4 _mat = mat4(1.0);
	if(u_hasBones)
	{
		_mat = u_bonesMatrixs[int(boneIndexs[0])] * boneWeights[0];
		_mat += u_bonesMatrixs[int(boneIndexs[1])] * boneWeights[1];
		_mat += u_bonesMatrixs[int(boneIndexs[2])] * boneWeights[2];
		_mat += u_bonesMatrixs[int(boneIndexs[3])] * boneWeights[3];
	}
	else
	{
		_mat = u_modelMatrix;
	}
	_mat = u_rootMatrix * _mat;
	v_uv = uv;
	v_fragPos = vec3(_mat * vec4(position, 1.0));
	v_normal = mat3(_mat) * normal;
	gl_Position = u_viewProjectionMatrix * _mat * vec4(position, 1.0);
}
)"