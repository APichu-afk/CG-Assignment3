#include "GBuffer.h"

void GBuffer::Init(unsigned width, unsigned height)
{
	//stores width and height
	_windowWidth = width;
	_windowHeight = height;

	//adds colour targets to our GBuffer
	_gBuffer.AddColorTarget(GL_RGBA8);	//Albedo Buffer, needs all channels
	_gBuffer.AddColorTarget(GL_RGB8);	//Normals Buffer, does not need alpha
	_gBuffer.AddColorTarget(GL_RGB8);	//Specular Buffer, Technically only needs 1 channel

	//Important note, you can obtain the positional data using the depth buffer (there's a calculation that you can do).
	//But here, we're going to use POSTION buffer
	_gBuffer.AddColorTarget(GL_RGB32F);

	//add a depth buffer
	_gBuffer.AddDepthTarget();

	//Initializes our framebuffer
	_gBuffer.Init(width, height);

	//Initializes pass through shader
	_passThrough = Shader::Create();
	_passThrough->LoadShaderPartFromFile("shaders/passthrough_vert.glsl", GL_VERTEX_SHADER);
	_passThrough->LoadShaderPartFromFile("shaders/passthrough_frag.glsl", GL_FRAGMENT_SHADER);
	_passThrough->Link();
}

void GBuffer::Bind()
{
	_gBuffer.Bind();
}

void GBuffer::BindLighting()
{
	_gBuffer.BindColorAsTexture(Target::ALBEDO, 0);
	_gBuffer.BindColorAsTexture(Target::NORMAL, 1);
	_gBuffer.BindColorAsTexture(Target::SPECULAR, 2);
	_gBuffer.BindColorAsTexture(Target::POSITION, 3);
}

void GBuffer::Clear()
{
	_gBuffer.Clear();
}

void GBuffer::Unbind()
{
	_gBuffer.Unbind();
}

void GBuffer::UnbindLighting()
{
	_gBuffer.UnbindTexture(0);
	_gBuffer.UnbindTexture(1);
	_gBuffer.UnbindTexture(2);
	_gBuffer.UnbindTexture(3);
}

void GBuffer::DrawBuffersToScreen()
{
	//Binds passthrouggh shader
	_passThrough->Bind();

	//Set viewport to top left
	glViewport(0, _windowHeight / 2.f, _windowWidth / 2.f, _windowHeight / 2.f);
	_gBuffer.BindColorAsTexture(Target::ALBEDO, 0);
	_gBuffer.DrawFullscreenQuad();
	_gBuffer.UnbindTexture(0);
	
	//Set viewport to top right
	glViewport(_windowWidth / 2.f, _windowHeight / 2.f, _windowWidth / 2.f, _windowHeight / 2.f);
	_gBuffer.BindColorAsTexture(Target::NORMAL, 0);
	_gBuffer.DrawFullscreenQuad();
	_gBuffer.UnbindTexture(0);
	
	//Set viewport to bot left
	glViewport(0, 0, _windowWidth / 2.f, _windowHeight / 2.f);
	_gBuffer.BindColorAsTexture(Target::SPECULAR, 0);
	_gBuffer.DrawFullscreenQuad();
	_gBuffer.UnbindTexture(0);
	
	//Set viewport to bot right
	glViewport(_windowWidth / 2.f, 0, _windowWidth / 2.f, _windowHeight / 2.f);
	_gBuffer.BindColorAsTexture(Target::POSITION, 0);
	_gBuffer.DrawFullscreenQuad();
	_gBuffer.UnbindTexture(0);

	//Unbimd our passthrough shader
	_passThrough->UnBind();
}

void GBuffer::DrawBuffersToScreenSeperate(bool position, bool normal, bool material, bool lightaccum)
{
	//Binds passthrouggh shader
	_passThrough->Bind();

	//Set viewport to top left
	//glViewport(0, _windowHeight / 2.f, _windowWidth / 2.f, _windowHeight / 2.f);
	if (material) {
		_gBuffer.BindColorAsTexture(Target::ALBEDO, 0);
		_gBuffer.DrawFullscreenQuad();
		_gBuffer.UnbindTexture(0);
	}

	//Set viewport to top right
	//glViewport(_windowWidth / 2.f, _windowHeight / 2.f, _windowWidth / 2.f, _windowHeight / 2.f);
	else if (normal) {
		_gBuffer.BindColorAsTexture(Target::NORMAL, 0);
		_gBuffer.DrawFullscreenQuad();
		_gBuffer.UnbindTexture(0);
	}

	//Set viewport to bot left
	//glViewport(0, 0, _windowWidth / 2.f, _windowHeight / 2.f);
	else if (lightaccum) {
		_gBuffer.BindColorAsTexture(Target::SPECULAR, 0);
		_gBuffer.DrawFullscreenQuad();
		_gBuffer.UnbindTexture(0);
	}

	//Set viewport to bot right
	//glViewport(_windowWidth / 2.f, 0, _windowWidth / 2.f, _windowHeight / 2.f);
	else if (position) {
		_gBuffer.BindColorAsTexture(Target::POSITION, 0);
		_gBuffer.DrawFullscreenQuad();
		_gBuffer.UnbindTexture(0);
	}

	//Unbimd our passthrough shader
	_passThrough->UnBind();
}

void GBuffer::Reshape(unsigned width, unsigned height)
{
	//Stores new width and height
	_windowWidth = width;
	_windowHeight = height;

	//Reshapes the framebuffer
	_gBuffer.Reshape(width, height);
}
