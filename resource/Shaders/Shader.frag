uniform  sampler2D  sampler;
uniform  float	    unif_blendIntensity;
uniform	 bool	    unif_colorMode = true;
varying   vec4	    vary_color;
varying   vec2	    vary_textureCoord;

uniform   sampler2D unif_sampler;

void main()
{
	if(unif_colorMode)
		gl_FragColor = vary_color;
	else
		gl_FragColor = texture2D(unif_sampler, vary_textureCoord);
}