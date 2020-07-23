#version 330

in vec4 vPosition;
in vec3 vNormal;
out vec4 vColor;

out vec3 fN, fE, fL;

uniform mat4 model_view;
uniform mat4 projection;
vec4 LightPosition = vec4(10, 10.0, 10.0, 1.0);



void main()
{

	float theta = 45 * 0.0174533;//degree to radians
	vec4 lightPos = LightPosition; 
	lightPos.x = cos(theta)*LightPosition.x - sin(theta)*LightPosition.z;
	lightPos.z = sin(theta)*LightPosition.x + cos(theta)*LightPosition.z;
	
	fN = vNormal;
	fE = (model_view*vPosition).xyz;
	fL = lightPos.xyz;

	if(LightPosition.w != 0.0){
		fL = lightPos.xyz - vPosition.xyz;
	}

	gl_Position = projection*model_view*vPosition;
}
