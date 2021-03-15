#version 420

layout(binding = 0) uniform sampler2D uTex;
uniform float u_direction;

out vec4 fragColor;

in vec2 TexCoords;

void main() 
{
	fragColor = vec4(0.0, 0.0, 0.0, 0.0);

	fragColor += texture(uTex, vec2(TexCoords.x, TexCoords.y - 4.0 * u_direction)) * 0.06;
	fragColor += texture(uTex, vec2(TexCoords.x, TexCoords.y - 3.0 * u_direction)) * 0.09;
	fragColor += texture(uTex, vec2(TexCoords.x, TexCoords.y - 2.0 * u_direction)) * 0.12;
	fragColor += texture(uTex, vec2(TexCoords.x, TexCoords.y - 		 u_direction)) * 0.15;
	fragColor += texture(uTex, vec2(TexCoords.x, TexCoords.y				   )) * 0.16;
	fragColor += texture(uTex, vec2(TexCoords.x, TexCoords.y +		 u_direction)) * 0.15;
	fragColor += texture(uTex, vec2(TexCoords.x, TexCoords.y + 2.0 * u_direction)) * 0.12;
	fragColor += texture(uTex, vec2(TexCoords.x, TexCoords.y + 3.0 * u_direction)) * 0.09;
	fragColor += texture(uTex, vec2(TexCoords.x, TexCoords.y + 4.0 * u_direction)) * 0.06;
}