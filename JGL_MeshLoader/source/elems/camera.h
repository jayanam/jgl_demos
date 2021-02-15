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
      mNear = near;
      mFar = far;
      mFOV = fov;
			mPerspective = glm::perspective(fov, aspect, near, far);
		}

    void set_aspect(float aspect)
    {
      mPerspective = glm::perspective(mFOV, aspect, mNear, mFar);
    }

		void set_offset(const glm::vec3& offset)
		{
			mPosition += offset;
		}

		glm::mat4 get_perspective() const
		{
			return mPerspective;
		}

    glm::mat4 get_view_projection() const
    {
      return mPerspective * get_view();
    }

		glm::mat4 get_view() const
		{
      return glm::lookAt(mPosition, mPosition + mFront, mUp);
		}

	private:
		glm::mat4 mPerspective;
		glm::vec3 mPosition;
		glm::vec3 mUp;
    glm::vec3 mFront;
    float mFOV;
    float mNear;
    float mFar;
	};
}

