#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include "input.h"
#include "element.h"
#include "shader/shader_util.h"

namespace nelems
{
	class Camera : public Element
	{
	public:

		Camera(const glm::vec3& position, float fov, float aspect, float near, float far)
		{
			mPosition = position;
			mAspect = aspect;
      mNear = near;
      mFar = far;
      mFOV = fov;

			set_aspect(mAspect);

			update_view_matrix();
		}

		void update(nshaders::Shader* shader) override
		{
			glm::mat4 model{ 1.0f };
			shader->set_mat4(model, "model");
			shader->set_mat4(mViewMatrix, "view");
			shader->set_mat4(get_projection(), "projection");
			shader->set_vec3(mPosition, "camPos");
		}

    void set_aspect(float aspect)
    {
      mProjection = glm::perspective(mFOV, aspect, mNear, mFar);
    }

		void set_distance(float offset)
		{
			mDistance += offset;
			update_view_matrix();
		}

		const glm::mat4& get_projection() const
		{
			return mProjection;
		}

    glm::mat4 get_view_projection() const
    {
      return mProjection * get_view_matrix();
    }

		glm::vec3 get_up() const
		{
			return glm::rotate(get_direction(), cUp);
		}

		glm::vec3 get_right() const
		{
			return glm::rotate(get_direction(), cRight);
		}

		glm::vec3 get_forward() const
		{
			return glm::rotate(get_direction(), cForward);
		}

		glm::quat get_direction() const
		{
			return glm::quat(glm::vec3(-mPitch, -mYaw, 0.0f));
		}

		glm::mat4 get_view_matrix() const
		{
			return mViewMatrix;
		}

		void on_mouse_wheel(double delta)
		{
			set_distance(delta * 0.5);

			update_view_matrix();
		}

		void reset()
		{
			mFocus = { 0.0f, 0.0f, 0.0f };
			//mDistance = 5.0f;
			update_view_matrix();
		}

		void on_mouse_move(double x, double y, EInputButton button)
		{
			glm::vec2 pos2d{ x, y };

			if (button == EInputButton::Right)
			{
				glm::vec2 delta = (pos2d - mCurrentPos2d) * 0.004f;

				float sign = get_up().y < 0 ? -1.0f : 1.0f;
				mYaw += sign * delta.x * cRotationSpeed;
				mPitch += delta.y * cRotationSpeed;

				update_view_matrix();
			}	
			else if (button == EInputButton::Middle)
			{
				// TODO: Adjust pan speed for distance
				glm::vec2 delta = (pos2d - mCurrentPos2d) * 0.003f;

				mFocus += -get_right() * delta.x * mDistance;
				mFocus += get_up() * delta.y * mDistance;

				update_view_matrix();
			}

			mCurrentPos2d = pos2d;
		}

		void update_view_matrix()
		{
			mPosition =  mFocus - get_forward() * mDistance;

			glm::quat orientation = get_direction();
			mViewMatrix = glm::translate(glm::mat4(1.0f), mPosition) * glm::toMat4(orientation);
			mViewMatrix = glm::inverse(mViewMatrix);
		}

	private:
		glm::mat4 mViewMatrix;
		glm::mat4 mProjection = glm::mat4{ 1.0f };
		glm::vec3 mPosition = { 0.0f, 0.0f, 0.0f };

		glm::vec3 mFocus = { 0.0f, 0.0f, 0.0f };

		float mDistance = 5.0f;
		float mAspect;
    float mFOV;
    float mNear;
    float mFar;

		float mPitch = 0.0f;
		float mYaw = 0.0f;

		glm::vec2 mCurrentPos2d = { 0.0f, 0.0f };

		const glm::vec3 cRight = { 1.0f, 0.0f, 0.0f };
		const glm::vec3 cUp = { 0.0f, 1.0f, 0.0f };
		const glm::vec3 cForward = { 0.0f, 0.0f, -1.0f };

		const float cRotationSpeed = 2.0f;

	};
}

