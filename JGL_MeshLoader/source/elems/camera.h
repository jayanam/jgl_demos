#pragma once

namespace nelems
{
	class Camera
	{
	public:
		Camera(const glm::vec3& position, float fov, float aspect, float near, float far)
		{
			mPosition = position;
			mUp = glm::vec3(0.0f, 1.0f, 0.0f);
      mFront = glm::vec3(0.0f, 0.0f, 1.0f);
			mPerspective = glm::perspective(fov, aspect, near, far);
		}

		inline glm::mat4 get_perspective() const
		{
			return mPerspective;
		}

		inline glm::mat4 get_view() const
		{
      return glm::lookAt(mPosition, mPosition + mFront, mUp);
		}

	private:
		glm::mat4 mPerspective;
		glm::vec3 mPosition;
		glm::vec3 mUp;
    glm::vec3 mFront;
	};
}

