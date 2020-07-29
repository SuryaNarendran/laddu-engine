#version 330

in vec4 vPosition;
in vec3 vNormal;
out vec4 vColor;

out vec3 fN, fE, fL;

uniform mat4 model_view;
uniform mat4 projection;
uniform mat4 transform;
uniform vec4 lightPosition;



void main()
{


	vec4 lightPos = lightPosition; 

	vec4 mvPosition = model_view*transform*vPosition;
	
	fN = vNormal;
	fE = (mvPosition).xyz;
	fL = lightPos.xyz;

	if(lightPosition.w != 0.0){
		fL -= fE;
	}

	gl_Position = projection*mvPosition;
}
