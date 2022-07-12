#pragma once

#include <string>
#include <array>

namespace toyrobot
{
	struct Cell
	{
		int x;
		int y;
	};

	using Rotation = std::string;
	using RotationIndex = short int;

	template<typename MovePolicy>
	struct Transform
	{
		Transform() : cell(Cell{ 0, 0 }) , heading(0)
		{
		}

		Transform(int x, int y, const Rotation& face)
			: cell(Cell{ x,y })
			, heading(MovePolicy::rotationToIndex(face))
		{
		}

		Transform(int x, int y, RotationIndex face)
			: cell(Cell{ x,y })
			, heading(face)
		{
		}

		Transform(int x, int y)
			: cell(Cell{ x, y })
			, heading(0)
		{
		}

		Transform(const std::string& face)
			: cell(Cell{ 0, 0 })
			, heading(MovePolicy::rotationToIndex(face))
		{
		}

		void right() 
		{
			heading = (++heading) % MovePolicy::maxRotations();
		}

		void left() {
			heading = (--heading < 0) ? MovePolicy::maxRotations()-1 : heading;
		}

		void forward() 
		{
			Cell unit = MovePolicy::getNormal(heading);
			cell.x += unit.x;
			cell.y += unit.y;
		}

		Transform peek() 
		{
			Cell unit = MovePolicy::getNormal(heading);
			return Transform { cell.x + unit.x, cell.y + unit.y, heading };
		}

		void set(int x, int y, const std::string& rotation) 
		{
			cell = Cell { x , y };
			heading = MovePolicy::rotationToIndex(rotation);
		}

		void set(const Transform& transform) 
		{
			cell = transform.cell;
			heading = transform.heading;
		}

		std::string getRotationString()
		{
			return MovePolicy::rotationToString(heading);
		}

		Cell cell;		
		RotationIndex heading;	
	};

	struct MovePolicy4Directions {

		inline static constexpr int maxRot = 4;

		// can be a map of <rotations, normals> but that's more work
		// we want to access the normals by index
		//inline static const std::array<Rotation, maxRot> rotations = { "NORTH", "WEST", "SOUTH", "EAST" };
		//inline static const std::array<Cell, maxRot> normals = {
		//	Cell { 0, 1 },
		//	Cell { -1, 0},
		//	Cell { 0, -1},
		//	Cell { 1, 0 },
		//};
		inline static const std::array<Rotation, maxRot> rotations = { "NORTH", "EAST", "SOUTH", "WEST" };
		inline static const std::array<Cell, maxRot> normals = {
			Cell { 0, 1 },
			Cell { 1, 0 },
			Cell { 0, -1},
			Cell { -1, 0},
		};

		static int maxRotations() {
			return maxRot;
		}

		static int rotationToIndex(const Rotation& heading) {
			if (auto iter = std::find(rotations.begin(), rotations.end(), heading);
				iter != rotations.end())
			{
				return static_cast<int>(iter - rotations.begin());
			}

			return -1;
		}

		static std::string rotationToString(int index) {
			if (index < maxRot)
				return rotations[index];

			return {};
		}

		static Cell getNormal(int index) {
			if (index < maxRot)
				return normals[index];

			return Cell{ 0, 0 };
		}
	};

	using Transform4D = toyrobot::Transform<toyrobot::MovePolicy4Directions>;
}