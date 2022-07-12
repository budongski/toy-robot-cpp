#pragma once
#include <framework/gridmath.h>
#include <framework/receiver.h>

namespace toyrobot
{
	class Toy /*: public toyrobot::Receiver */
	{
	public:
		explicit Toy();
		Toy(int id, const toyrobot::Transform4D& transform) 
			: mTransform(transform)
		{
		}
		~Toy() {}

		toyrobot::Transform4D mTransform;
	};

}