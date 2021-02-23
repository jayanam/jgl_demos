#include "pch.h"
#include "shader_util.h"

namespace nshaders
{
	unsigned int Shader::get_compiled_shader(unsigned int shader_type, const std::string& shader_source)
	{
		unsigned int shader_id = glCreateShader(shader_type);

		const char* c_source = shader_source.c_str();
		glShaderSource(shader_id, 1, &c_source, nullptr);
		glCompileShader(shader_id);

		GLint result;
		glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);

		if (result == GL_FALSE)
		{
			int length;
			glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &length);

			GLchar* strInfoLog = new GLchar[length + 1];
			glGetShaderInfoLog(shader_id, length, &length, strInfoLog);

			fprintf(stderr, "Compile error in shader: %s\n", strInfoLog);
			delete[] strInfoLog;
		}

		return shader_id;
	}

	bool Shader::load(const std::string& vertexshader_file, const std::string& fragmentshader_file)
	{
		std::ifstream is_vs(vertexshader_file);
		const std::string f_vs((std::istreambuf_iterator<char>(is_vs)), std::istreambuf_iterator<char>());

		std::ifstream is_fs(fragmentshader_file);
		const std::string f_fs((std::istreambuf_iterator<char>(is_fs)), std::istreambuf_iterator<char>());

		mProgramId = glCreateProgram();

		unsigned int vs = get_compiled_shader(GL_VERTEX_SHADER, f_vs);
		unsigned int fs = get_compiled_shader(GL_FRAGMENT_SHADER, f_fs);

		glAttachShader(mProgramId, vs);
		glAttachShader(mProgramId, fs);

		glLinkProgram(mProgramId);
		glValidateProgram(mProgramId);

		glDeleteShader(vs);
		glDeleteShader(fs);

		return true;
	}

	void Shader::use()
	{
		glUseProgram(mProgramId);
	}

	void Shader::unload()
	{
		glDeleteProgram(mProgramId);
	}

	void Shader::set_mat4(const glm::mat4& mat4, const std::string& name)
	{
		GLint myLoc = glGetUniformLocation(get_program_id(), name.c_str());
		glUniformMatrix4fv(myLoc, 1, GL_FALSE, glm::value_ptr(mat4));
	}

	void Shader::set_i1(int v, const std::string& name)
	{
		GLint myLoc = glGetUniformLocation(get_program_id(), name.c_str());
		glUniform1i(myLoc, v);
	}

	void Shader::set_f1(float v, const std::string& name)
	{
		GLint myLoc = glGetUniformLocation(get_program_id(), name.c_str());
		glUniform1f(myLoc, v);
	}

	void Shader::set_f3(float a, float b, float c, const std::string& name)
	{
		GLint myLoc = glGetUniformLocation(get_program_id(), name.c_str());
		glUniform3f(myLoc, a, b, c);
	}

	void Shader::set_vec3(const glm::vec3& vec3, const std::string& name)
	{
		GLint myLoc = glGetUniformLocation(get_program_id(), name.c_str());
		glProgramUniform3fv(get_program_id(), myLoc, 1, glm::value_ptr(vec3));
	}

  void Shader::set_vec4(const glm::vec4& vec4, const std::string& name)
  {
    GLint myLoc = glGetUniformLocation(get_program_id(), name.c_str());
    glProgramUniform4fv(get_program_id(), myLoc, 1, glm::value_ptr(vec4));
  }
}

