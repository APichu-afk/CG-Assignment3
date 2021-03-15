#include "BlurEffect.h"

void BlurEffect::Init(unsigned width, unsigned height)
{
    int index = int(_buffers.size());
    _buffers.push_back(new Framebuffer());
    _buffers[index]->AddColorTarget(GL_RGBA8);
    _buffers[index]->AddDepthTarget();
    _buffers[index]->Init(width, height);
    index++;
    _buffers.push_back(new Framebuffer());
    _buffers[index]->AddColorTarget(GL_RGBA8);
    _buffers[index]->Init(unsigned(width / m_downscale), unsigned(height / m_downscale));
    index++;
    _buffers.push_back(new Framebuffer());
    _buffers[index]->AddColorTarget(GL_RGBA8);
    _buffers[index]->Init(unsigned(width / m_downscale), unsigned(height / m_downscale));
    index++;
    _buffers.push_back(new Framebuffer());
    _buffers[index]->AddColorTarget(GL_RGBA8);
    _buffers[index]->Init(width, height);

    //Loads the shaders
    index = int(_shaders.size());
    _shaders.push_back(Shader::Create());
    _shaders[index]->LoadShaderPartFromFile("shaders/passthrough_vert.glsl", GL_VERTEX_SHADER);
    _shaders[index]->LoadShaderPartFromFile("shaders/passthrough_frag.glsl", GL_FRAGMENT_SHADER);
    _shaders[index]->Link();
    index++;
    _shaders.push_back(Shader::Create());
    _shaders[index]->LoadShaderPartFromFile("shaders/passthrough_vert.glsl", GL_VERTEX_SHADER);
    _shaders[index]->LoadShaderPartFromFile("shaders/Post/Bloom_frag.glsl", GL_FRAGMENT_SHADER);
    _shaders[index]->Link();
    index++;
    _shaders.push_back(Shader::Create());
    _shaders[index]->LoadShaderPartFromFile("shaders/passthrough_vert.glsl", GL_VERTEX_SHADER);
    _shaders[index]->LoadShaderPartFromFile("shaders/Post/BlurH_frag.glsl", GL_FRAGMENT_SHADER);
    _shaders[index]->Link();
    index++;
    index = int(_shaders.size());
    _shaders.push_back(Shader::Create());
    _shaders[index]->LoadShaderPartFromFile("shaders/passthrough_vert.glsl", GL_VERTEX_SHADER);
    _shaders[index]->LoadShaderPartFromFile("shaders/Post/BlurV_frag.glsl", GL_FRAGMENT_SHADER);
    _shaders[index]->Link();
    index++;
    _shaders.push_back(Shader::Create());
    _shaders[index]->LoadShaderPartFromFile("shaders/passthrough_vert.glsl", GL_VERTEX_SHADER);
    _shaders[index]->LoadShaderPartFromFile("shaders/Post/Composite_frag.glsl", GL_FRAGMENT_SHADER);
    _shaders[index]->Link();
    index++;

    direction = glm::vec2(1.0f / width, 1.0f / height);
}

void BlurEffect::ApplyEffect(PostEffect* buffer)
{
    //Draws previous buffer to first render target
    BindShader(0);

    buffer->BindColorAsTexture(0, 0, 0);

    _buffers[0]->RenderToFSQ();

    buffer->UnbindTexture(0);

    UnbindShader();


    //Performs high pass on the first render target
    BindShader(1);
    _shaders[1]->SetUniform("u_threshold", m_threshold);

    BindColorAsTexture(0, 0, 0);

    _buffers[1]->RenderToFSQ();

    UnbindTexture(0);

    UnbindShader();


    //Computes blur, vertical and horizontal
    for (unsigned i = 0; i < m_passes; i++)
    {
        //Horizontal pass
        BindShader(2);
        _shaders[2]->SetUniform("u_direction", direction.x);

        BindColorAsTexture(1, 0, 0);

        _buffers[2]->RenderToFSQ();

        UnbindTexture(0);

        UnbindShader();

        //Vertical pass
        BindShader(3);
        _shaders[3]->SetUniform("u_direction", direction.y);

        BindColorAsTexture(2, 0, 0);

        _buffers[1]->RenderToFSQ();

        UnbindTexture(0);

        UnbindShader();
    }


    //Composite the scene and the bloom
    BindShader(4);

    buffer->BindColorAsTexture(0, 0, 0);
    BindColorAsTexture(1, 0, 1);

    _buffers[0]->RenderToFSQ();

    UnbindTexture(1);
    UnbindTexture(0);

    UnbindShader();
}

float BlurEffect::GetDownscale() const
{
    return m_downscale;
}

float BlurEffect::GetThreshold() const
{
    return m_threshold;
}

unsigned BlurEffect::GetPasses() const
{
    return m_passes;
}

void BlurEffect::SetDownscale(float downscale)
{
    m_downscale = downscale;
}

void BlurEffect::SetThreshold(float threshold)
{
    m_threshold = threshold;
}

void BlurEffect::SetPasses(unsigned passes)
{
    m_passes = passes;
}