R"(
precision mediump float;
struct Material
{
	vec3 ambientColor;
	vec3 diffuseColor;
	vec3 specularColor;
	vec3 emissionColor;
	float shininess;
	sampler2D diffuseSampler;
	sampler2D specularSampler;
	sampler2D emissionSampler;
};
struct Light
{
	vec3 position;
	vec3 ambientColor;
	vec3 diffuseColor;
	vec3 specularColor;
};
varying vec2 v_uv;
varying vec3 v_normal;
varying vec3 v_fragPos;
uniform vec3 u_cameraPosition;
uniform Material u_material;
uniform Light u_light;
uniform bool u_hasTexture;
uniform float u_opacity;

void main()
{
	vec3 _ambient, _diffuse, _specular;
	float _alpha = 0.0;
	if(!u_hasTexture)
	{
		_ambient = u_material.ambientColor;
		_diffuse = u_material.diffuseColor;
		_specular = u_material.specularColor;
		_alpha = u_opacity;
	}
	else
	{
		vec4 _diffuseRgba = texture2D(u_material.diffuseSampler, v_uv);
		_ambient = _diffuse = _diffuseRgba.rgb;
		_specular = texture2D(u_material.specularSampler, v_uv).rgb;
		_alpha = _diffuseRgba.a;
	}
	//ambient
	_ambient = u_light.ambientColor * _ambient;
	//diffuse
	vec3 _norm = normalize(v_normal);
	vec3 _lightDir = normalize(u_light.position - v_fragPos);
	float _diff = max(dot(_norm, _lightDir), 0.0);
	_diffuse = u_light.diffuseColor * _diff * _diffuse;
	//specular
	vec3 _viewDir = normalize(-u_cameraPosition + v_fragPos);
	vec3 _reflectDir = reflect(-_lightDir, _norm);
	float _spec = pow(max(dot(_viewDir, _reflectDir), 0.0), u_material.shininess);
	_specular = u_light.specularColor * _spec * _specular;
	//emissive
	vec3 _emission = u_material.emissionColor * texture2D(u_material.emissionSampler, v_uv).rgb;
	vec3 _color = _ambient + _diffuse /*+ _specular*/ + _emission;
	gl_FragColor = vec4(_color, 1.0);
}
)"