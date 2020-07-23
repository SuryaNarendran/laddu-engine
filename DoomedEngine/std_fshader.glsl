#version 330

in vec3 fN, fE, fL;

out vec4  fColor;

vec4 AmbientProduct = vec4(0.50, 0.0, 0.0, 1.0);
vec4 DiffuseProduct = vec4(0.50, 0.50, 0.0, 1.0);
vec4 SpecularProduct = vec4(0.5,0.5,0.75,1.0);

float Shininess = 1;

void main()
{
	vec3 N = normalize(fN);
	vec3 E = normalize(fE);
	vec3 L = normalize(fL);

	vec3 H = normalize(L + E);

	vec4 ambient = AmbientProduct;

	float Ks = max(dot(H, N), 0.0);
	Ks = pow(Ks, Shininess);
	float Kd = max( dot(L, N), 0.0 );

	vec4 specular = Ks*SpecularProduct;
    vec4  diffuse = Kd*DiffuseProduct;

	fColor = ambient + diffuse + specular;
	fColor.a = 1.0;
}
