#include "Cube.h"

Cube::Cube()
{
	/* Generate vertex array object */
	m_VAO = std::make_unique<VertexArray>();

	/* Create and bind vertex buffer */
	m_VertexBuffer = std::make_unique<VertexBuffer>(s_Positions, POSITIONS_SIZE * sizeof(float));

	/* Define a vertex buffer layout */
	VertexBufferLayout layout;
	layout.Push<float>(VERTEX_SIZE);
	layout.Push<float>(UV_SIZE);

	/* m_VAO is defined by the pair (m_VertexBuffer, layout) */
	m_VAO->AddBuffer(*m_VertexBuffer, layout);
}

Cube::~Cube() {}

void Cube::Draw()
{
	GLCheckErrorCall(glDrawArrays(GL_TRIANGLES, 0, CUBE_VERTICES));
}

void Cube::SetMVP(glm::mat4 MVP)
{
	m_Shader->SetUniformMatrix4fv(UNIFORM_MVP, MVP);
}

const float Cube::s_Positions[] = {
	/* vertices */			/* UV coordinates */
	-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,	0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,	1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,	1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,	1.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,	1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,	1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,	1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,	0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,	1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,	1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,	1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,	1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,	0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,	0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,	0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,	1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,	1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,	1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,	1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,	1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,	0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,	0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,	1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,	1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,	1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,	0.0f, 1.0f
};

TexturedCube::TexturedCube(const char * texturePath)
{
	/* Create shader program */
	m_Shader = std::make_unique<Shader>(VERTEX_TEXTURE_2D_POS_3D_SHADER_PATH, FRAGMENT_TEXTURE_2D_SHADER_PATH);
	m_Shader->Use();

	/* Load texture to memory */
	m_Texture2D = std::make_unique<Texture>(texturePath);
	const unsigned int slot = 0;
	m_Texture2D->Bind(slot);
	m_Shader->SetUniform1i(UNIFORM_TEXTURE, slot);
}

TexturedCube::~TexturedCube()
{
	this->Unbind();
}

void TexturedCube::Bind()
{
	m_VAO->Bind();
	m_Shader->Use();
	m_Texture2D->Bind(0);
}

void TexturedCube::Unbind()
{
	m_VAO->Unbind();
	m_VertexBuffer->Unbind();
	m_Shader->Unuse();
	m_Texture2D->Unbind();
}

LampCube::LampCube()
{
	m_Shader = std::make_unique<Shader>(VERTEX_BASIC_MVP_SHADER_PATH, FRAGMENT_BASIC_LAMP_SHADER_PATH);
	m_Shader->Use();
}

LampCube::~LampCube()
{
	this->Unbind();
}

void LampCube::Bind()
{
	m_VAO->Bind();
	m_Shader->Use();
}

void LampCube::Unbind()
{
	m_VAO->Unbind();
	m_VertexBuffer->Unbind();
	m_Shader->Unuse();
}

void LampCube::SetLightColor(glm::vec3 lightColor)
{
	m_Shader->SetUniform3f(UNIFORM_LIGHT_COLOR, lightColor.r, lightColor.g, lightColor.b);
}

LightedCube::LightedCube()
{
	m_Shader = std::make_unique<Shader>(VERTEX_BASIC_MVP_SHADER_PATH, FRAGMENT_BASIC_LIGHTED_SHADER_PATH);
	m_Shader->Use();
}

LightedCube::~LightedCube()
{
	this->Unbind();
}

void LightedCube::Bind()
{
	m_VAO->Bind();
	m_Shader->Use();
}

void LightedCube::Unbind()
{
	m_VAO->Unbind();
	m_VertexBuffer->Unbind();
	m_Shader->Unuse();
}

void LightedCube::SetObjectColor(glm::vec3 objectColor)
{
	m_Shader->SetUniform3f(UNIFORM_OBJECT_COLOR, objectColor.r, objectColor.g, objectColor.b);
}

void LightedCube::SetLightColor(glm::vec3 lightColor)
{
	m_Shader->SetUniform3f(UNIFORM_LIGHT_COLOR, lightColor.r, lightColor.g, lightColor.b);
}
