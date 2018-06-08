attribute	vec4	attr_position;
attribute	vec4	attr_color;
attribute	vec2	attr_textureCoord;
uniform	        mat4	unif_mvp;
varying		vec4	vary_color;
varying		vec2	vary_textureCoord;
void main()
{
	vary_color = attr_color;
	vary_textureCoord = attr_textureCoord;
	gl_Position = unif_mvp * attr_position;
}