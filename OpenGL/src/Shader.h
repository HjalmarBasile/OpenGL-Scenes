#pragma once

#include <string>
#include <unordered_map>
#include <glad/glad.h>

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

static constexpr const char* VERTEX_BASIC_SHADER_PATH = "res/shaders/basic.vert";
static constexpr const char* FRAGMENT_BASIC_SHADER_PATH = "res/shaders/basic.frag";

static constexpr const char* VERTEX_POS_COL_SHADER_PATH = "res/shaders/pos_col.vert";
static constexpr const char* FRAGMENT_COL_IN_SHADER_PATH = "res/shaders/col_in.frag";

static constexpr const char* VERTEX_BASIC_MVP_SHADER_PATH = "res/shaders/basic_mvp.vert";
static constexpr const char* FRAGMENT_BASIC_LAMP_SHADER_PATH = "res/shaders/basic_lamp.frag";

static constexpr const char* VERTEX_POS_NORM_UMVP_SHADER_PATH = "res/shaders/pos_norm_umvp.vert";
static constexpr const char* FRAGMENT_BASIC_LIGHTED_SHADER_PATH = "res/shaders/basic_lighted.frag";

static constexpr const char* VERTEX_GOURAUD_SHADER_PATH = "res/shaders/gouraud.vert";
static constexpr const char* FRAGMENT_GOURAUD_SHADER_PATH = "res/shaders/gouraud.frag";

static constexpr const char* VERTEX_TEXTURE_2D_SHADER_PATH = "res/shaders/texture2D.vert";
static constexpr const char* VERTEX_TEXTURE_2D_POS_3D_SHADER_PATH = "res/shaders/texture2D_pos3D.vert";
static constexpr const char* FRAGMENT_TEXTURE_2D_SHADER_PATH = "res/shaders/texture2D.frag";

static constexpr const char* VERTEX_POS_COL_UV_SHADER_PATH = "res/shaders/pos_col_uv.vert";
static constexpr const char* FRAGMENT_POS_COL_UV_SHADER_PATH = "res/shaders/pos_col_uv.frag";

static constexpr const char* UNIFORM_COLOR = "u_Color";
static constexpr const char* UNIFORM_MODEL = "u_Model";
static constexpr const char* UNIFORM_VIEW = "u_View";
static constexpr const char* UNIFORM_PROJ = "u_Proj";
static constexpr const char* UNIFORM_MODEL_VIEW = "u_ModelView";
static constexpr const char* UNIFORM_MVP = "u_MVP";
static constexpr const char* UNIFORM_LIGHT_POSITION = "u_LightPosition";
static constexpr const char* UNIFORM_LIGHT_COLOR = "u_LightColor";
static constexpr const char* UNIFORM_OBJECT_COLOR = "u_ObjectColor";
static constexpr const char* UNIFORM_AMBIENT_COLOR = "u_AmbientColor";
static constexpr const char* UNIFORM_AMBIENT_STRENGHT = "u_AmbientStrenght";
static constexpr const char* UNIFORM_DIFFUSE_STRENGHT = "u_DiffuseStrenght";
static constexpr const char* UNIFORM_SPECULAR_STRENGHT = "u_SpecularStrenght";
static constexpr const char* UNIFORM_SPECULAR_SHININESS = "u_SpecularShininess";
static constexpr const char* UNIFORM_TEXTURE = "u_Texture";
static constexpr const char* UNIFORM_TEXTURE1 = "u_Texture1";
static constexpr const char* UNIFORM_TEXTURE2 = "u_Texture2";
static constexpr const char* UNIFORM_MIX_LAMBDA = "u_MixLambda";

typedef void (APIENTRYP GLGetObjectivHandler)(GLuint object, GLenum pname, GLint* params);
typedef void (APIENTRYP GLGetObjectInfoLogHandler)(GLuint object, GLsizei maxLength, GLsizei* length, GLchar* infoLog);
typedef void (APIENTRYP GLDeleteObjectHandler)(GLuint object);

class Shader
{
private:
	unsigned int m_RendererID;
	std::unordered_map<std::string, GLint> m_UniformLocationCache;
public:
	Shader(const std::string& vertfilepath, const std::string& fragfilepath);
	~Shader();

	void Use() const;
	static void Unuse();

	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform3f(const std::string& name, float v0, float v1, float v2);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniformMatrix4fv(const std::string& name, const glm::mat4& matrix);
private:
	GLint GetUniformLocation(const std::string& name);

	static const char* GetShaderName(GLenum shaderType);
	static const std::string GetErrorMessage(GLenum GL_STATUS, GLenum shaderType);

	static GLboolean GLValidateObjectStatus(GLuint object, GLenum GL_STATUS, GLenum shaderType,
		GLGetObjectivHandler GLGetObjectiv, GLGetObjectInfoLogHandler GLGetObjectInfoLog, GLDeleteObjectHandler GLDeleteObject);

	static std::string ParseShader(const std::string& filepath);
	static GLuint CompileShader(GLenum shaderType, const std::string& source);
	static GLuint CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
};
