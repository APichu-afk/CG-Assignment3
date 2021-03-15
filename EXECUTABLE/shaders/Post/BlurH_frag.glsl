#version 420

layout(binding = 0) uniform sampler2D uTex;
uniform float u_direction;

out vec4 fragColor;

in vec2 TexCoords;

void main() 
{
	fragColor = vec4(0.0, 0.0, 0.0, 0.0);

	fragColor += texture(uTex, vec2(TexCoords.x - 4.0 * u_direction, TexCoords.y)) * 0.06;
	fragColor += texture(uTex, vec2(TexCoords.x - 3.0 * u_direction, TexCoords.y)) * 0.09;
	fragColor += texture(uTex, vec2(TexCoords.x - 2.0 * u_direction, TexCoords.y)) * 0.12;
	fragColor += texture(uTex, vec2(TexCoords.x - 		u_direction, TexCoords.y)) * 0.15;
	fragColor += texture(uTex, vec2(TexCoords.x, 					TexCoords.y)) * 0.16;
	fragColor += texture(uTex, vec2(TexCoords.x +		u_direction, TexCoords.y)) * 0.15;
	fragColor += texture(uTex, vec2(TexCoords.x + 2.0 * u_direction, TexCoords.y)) * 0.12;
	fragColor += texture(uTex, vec2(TexCoords.x + 3.0 * u_direction, TexCoords.y)) * 0.09;
	fragColor += texture(uTex, vec2(TexCoords.x + 4.0 * u_direction, TexCoords.y)) * 0.06;
}