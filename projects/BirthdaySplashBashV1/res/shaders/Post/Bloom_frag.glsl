#version 420

layout(binding = 0) uniform sampler2D uTex;
uniform float u_threshold;

out vec4 fragColor;

in vec2 TexCoords;

void main() 
{
	vec4 color = texture(uTex, TexCoords);
	
	float luminance = (color.r + color.g + color.b) / 3.0;
	
	if (luminance > u_threshold) 
	{
		fragColor = color;
	}
	else
	{
		fragColor = vec4(0.0, 0.0, 0.0, 1.0);
	}
}