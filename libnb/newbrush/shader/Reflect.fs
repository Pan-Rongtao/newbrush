R"(
precision mediump float;
struct Material
{
	vec3 ambientColor;
	vec3 diffuseColor;
	vec3 specularColor;
	vec3 cubemapColor;
	sampler2D diffuseSampler;
	samplerCube cubeSampler;
};
varying vec2 v_uv;
varying vec3 v_normal;
varying vec3 v_fragPos;
uniform vec3 u_cameraPosition;
uniform Material u_material;
uniform bool u_hasTexture;
uniform bool u_hasCubemap;
	
void main()
{
	vec4 _color = u_hasTexture ?  texture2D(u_material.diffuseSampler, v_uv).rgba : vec4(u_material.diffuseColor, 1.0);
	vec3 _colorRgb = _color.rgb;
	if(u_hasCubemap)
	{
		_colorRgb *= u_material.ambientColor;
		_colorRgb += u_material.specularColor;
		vec3 I = normalize(v_fragPos - u_cameraPosition);
		vec3 R = reflect(I, normalize(v_normal));
		_colorRgb += textureCube(u_material.cubeSampler, R).rgb * u_material.cubemapColor;
	}
	gl_FragColor = vec4(_colorRgb, _color.a);
}
)"