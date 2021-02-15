#include "pch.h"
#include "shader_util.h"

namespace nshaders
{


	unsigned int ShaderUtil::get_compiled_shader(unsigned int shader_type, const std::string& shader_source)
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

			fprintf(stderr, "Compilation error in shader: %s\n", strInfoLog);
			delete[] strInfoLog;
		}

		return shader_id;
	}

	bool ShaderUtil::load(const std::string& vertexshader_file, const std::string& fragmentshader_file)
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

	void ShaderUtil::use()
	{
		glUseProgram(mProgramId);
	}

  void ShaderUtil::update(const nelems::Camera* camera)
  {
    GLint modelLoc = glGetUniformLocation(mProgramId, "model");
    GLint viewLoc = glGetUniformLocation(mProgramId, "view");
    GLint projLoc = glGetUniformLocation(mProgramId, "projection");

    glm::mat4 model{ 1.0f };

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera->get_view()));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera->get_perspective()));
  }

	void ShaderUtil::unload()
	{
		glDeleteProgram(mProgramId);
	}

  void ShaderUtil::set_vec4(const glm::vec4& vec4, const std::string& name)
  {
    GLint myLoc = glGetUniformLocation(get_program_id(), name.c_str());
    glProgramUniform4fv(get_program_id(), myLoc, 1, glm::value_ptr(vec4));
  }
}

