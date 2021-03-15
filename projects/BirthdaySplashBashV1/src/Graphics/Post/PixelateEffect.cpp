#include "Graphics/Post/PixelateEffect.h"

void PixelateEffect::Init(unsigned width, unsigned height)
{
	//Load the buffers
	int index = int(_buffers.size());
	_buffers.push_back(new Framebuffer());
	_buffers[index]->AddColorTarget(GL_RGBA8);
	_buffers[index]->Init(width, height);

	//Load the shaders
	index = int(_shaders.size());
	_shaders.push_back(Shader::Create());
	_shaders[index]->LoadShaderPartFromFile("shaders/passthrough_vert.glsl", GL_VERTEX_SHADER);
	_shaders[index]->LoadShaderPartFromFile("shaders/Post/Pixelate_frag.glsl", GL_FRAGMENT_SHADER);
	_shaders[index]->Link();

	m_windowSize = glm::vec2(float(width), float(height));
}

void PixelateEffect::ApplyEffect(PostEffect* buffer)
{
	BindShader(0);
	_shaders[0]->SetUniform("uWindowSize", m_windowSize);
	_shaders[0]->SetUniform("uPixelSize", m_pixelSize);

	buffer->BindColorAsTexture(0, 0, 0);

	_buffers[0]->RenderToFSQ();

	buffer->UnbindTexture(0);

	UnbindShader();
}

glm::vec2 PixelateEffect::GetWindowSize() const
{
	return m_windowSize;
}

float PixelateEffect::GetPixelSize() const
{
	return m_pixelSize;
}

void PixelateEffect::SetPixelSize(float size)
{
	m_pixelSize = size;
}
