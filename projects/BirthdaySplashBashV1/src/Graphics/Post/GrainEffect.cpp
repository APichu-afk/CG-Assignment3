#include "Graphics/Post/GrainEffect.h"
#include "Gameplay/Timing.h"

void GrainEffect::Init(unsigned width, unsigned height)
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
	_shaders[index]->LoadShaderPartFromFile("shaders/Post/Grain_frag.glsl", GL_FRAGMENT_SHADER);
	_shaders[index]->Link();

	m_windowSize = glm::vec2(float(width), float(height));
}

void GrainEffect::ApplyEffect(PostEffect* buffer)
{
	m_time = Timing::Instance().DeltaTime;

	BindShader(0);
	_shaders[0]->SetUniform("uWindowSize", m_windowSize);
	_shaders[0]->SetUniform("uStrength", m_strength);
	_shaders[0]->SetUniform("uTime", m_time);

	buffer->BindColorAsTexture(0, 0, 0);

	_buffers[0]->RenderToFSQ();

	buffer->UnbindTexture(0);

	UnbindShader();
}

glm::vec2 GrainEffect::GetWindowSize() const
{
	return m_windowSize;
}

float GrainEffect::GetStrength() const
{
	return m_strength;
}

float GrainEffect::GetTime() const
{
	return m_time;
}

void GrainEffect::SetStrength(float strength)
{
	m_strength = strength;
}

