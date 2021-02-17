#pragma once

#include "elems/camera.h"
#include "elems/light.h"

namespace nshaders
{

	// Utitlity class to load, compile and attach a vertex- and fragment shader to a program
	class Shader
	{

	private:
		unsigned int mProgramId;

		unsigned int get_compiled_shader(unsigned int shader_type, const std::string& shader_source);

	public:
		Shader() = default;

		// Load a vertex and a fragment shader from file
		bool load(const std::string& vertexshader_file, const std::string& fragmentshader_file);

		// Use the program
		void use();

    void update_camera(const nelems::Camera* camera);

    void update_light(const nelems::Light* light);

		// Delete the program
		void unload();

    unsigned int get_program_id() { return mProgramId; }

    void set_vec4(const glm::vec4& vec4, const std::string& name);



	};
}

