// ALL NORMALS MUST BE NORMALIZED BEFORE BEING SENT TO THE FRAGMENT SHADER
// Nevermind. Interpolation between the vertex and fragment shaders could skew normals anyway. Normalize twice to be safe
#version 330 core

in vec3 _position;
in vec3 _color;
in vec3 _normal;

uniform float shadeNormals = 0.0f;
uniform float shadeLight = 0.0f;
uniform vec3 attVals = vec3(1.0f, 0.1f, 0.01f);

uniform float ambientLightFactor = 1.0f;

uniform vec3 lightPosition;
uniform vec3 eyePosition;

out vec4 color;

void main()
{
	vec4 c = vec4(_color, 1);
	vec3 normal = normalize(_normal);
	vec3 lightVector = lightPosition - _position;
	float distance = length(lightVector);
	lightVector = normalize(lightVector);
	float attenuation = attVals.x + attVals.y * distance + attVals.z * distance * distance;

	float dot1 = dot(lightVector, normal);
	float diffuseLight = max(dot1, 0.0f);
	diffuseLight = diffuseLight / attenuation;

	vec3 eyeVector = normalize(eyePosition - _position);
	vec3 reflectedVector = reflect(-lightVector, normal);
	float dot2 = dot(reflectedVector, eyeVector);
	dot2 = pow(dot2, 100);
	float specularity = max(dot2, 0.0f);
	specularity = specularity / attenuation;

	vec4 av = vec4(ambientLightFactor, ambientLightFactor, ambientLightFactor, 1);
	vec4 dv = vec4(diffuseLight, diffuseLight, diffuseLight, 1);
	vec4 sv = vec4(specularity, specularity, specularity, 1);

	float totalLight = diffuseLight;
	float brightness = clamp(totalLight, 0.0f, 1.0f);

	if(shadeNormals > 0.5f)
	{					// To avoid black areas
		color = (av + dv + sv) * vec4(abs(_normal), 1);
	}
	else
	{
		if(shadeLight < 0.5f)
		{
			// Thinmatrix's
			color = dv * c + sv; 
			// Thinmatric's with ambient light
			//color = (av + dv) * c + sv; 
			// Jamie's
			color = (av + dv + sv);
			// Difference seems to be Thinmatrix's light is white and Jamie's is the color of the surface
		}
		else
		{
			color = (av + dv + sv) * c;
		}
	}
}