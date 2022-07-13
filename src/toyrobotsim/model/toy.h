#pragma once
#include <framework/gridmath.h>
#include <framework/receiver.h>

namespace toyrobot
{
	class Toy
	{
	public:
		Toy(int id, const toyrobot::Transform4D& transform) 
			: mTransform(transform)
		{
		}
		virtual ~Toy() = default;

		toyrobot::Transform4D mTransform;
	};

}