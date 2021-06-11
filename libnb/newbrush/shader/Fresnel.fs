R"(
precision highp float;

varying vec3 v_fragPos;
varying vec3 v_normal;
uniform vec3 u_cameraPosition;

void main(void) {
    vec3 color = vec3(1., 1., 1.);
	//vec3 _viewDir = normalize(-vec3(0.0,0.0,-10.0) + v_fragPos);
	vec3 cameraPos = vec3(0.0,0.0,-10.0);//u_cameraPosition;
    vec3 viewDirectionW = normalize(-cameraPos + v_fragPos);

    // Fresnel
	float fresnelTerm = dot(viewDirectionW, v_normal);
	fresnelTerm = clamp(1.0 - fresnelTerm, 0., 1.);

    gl_FragColor = vec4(color * fresnelTerm, 1.);
}

)"