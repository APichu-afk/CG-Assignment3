#version 420

layout (location = 0) in vec2 inUV;

struct DirectionalLight
{
	//Light direction (defaults to down, to the left, and a little forward)
	vec4 _lightDirection;

	//Generic Light controls
	vec4 _lightCol;

	//Ambience controls
	vec4 _ambientCol;
	float _ambientPow;
	
	//Power controls
	float _lightAmbientPow;
	float _lightSpecularPow;
	
	float _shadowBias;
};

layout (std140, binding = 0) uniform u_Lights
{
	DirectionalLight Ambience;
};

layout (binding = 0) uniform sampler2D s_albedoTex;
layout (binding = 4) uniform sampler2D s_lightAccumTex;
layout (binding = 5) uniform sampler2D s_skybox;

out vec4 frag_color;

void main()
{
	//Albedo
	vec4 textureColor = texture(s_albedoTex, inUV);
	//Lights
	vec4 lightAccum = texture(s_lightAccumTex, inUV);
	//skybox
	vec4 skybox = texture(s_skybox, inUV);

	//Ambient calculation
	vec3 ambient = Ambience._lightAmbientPow * Ambience._ambientCol.rgb;

	//The result of all lighting
	vec3 result = (ambient + lightAccum.rgb) * textureColor.rgb;

	//Add the skybox
	result = result + skybox.rgb;

	//The light accumulation
	frag_color = vec4(result, 1.0);
}