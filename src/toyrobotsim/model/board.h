#pragma once

#include <framework/gridmath.h>
#include "toy.h"
#include <vector>
#include <map>
#include <string>
#include <memory>

namespace toyrobot
{
	using ToyPtr = std::shared_ptr<Toy>;

	enum class BoardError
	{
		success,
		target_position_not_passable,
		robot_does_not_exist,
	};

	class Board 
	{
	public:
		Board(int rows, int cols);
		virtual ~Board();
		BoardError placeRobot(int id, const Transform4D& transform);
		BoardError forwardRobot(int id);
		BoardError turnRobotLeft(int id);
		BoardError turnRobotRight(int id);
		BoardError report(int id, std::string& report);
		static std::string toString(BoardError err);

	private:
		ToyPtr findRobot(int id);
		ToyPtr spawnRobot(int id, const Transform4D& to);
		bool isTilePassable(const Transform4D& transform);
		void updateTileContent(const Transform4D& from, const Transform4D& to);
		void updateTileContent(ToyPtr toy, const Transform4D& to);

		std::map<int, ToyPtr> mRobots;				// 
		std::vector< std::vector <ToyPtr>> mTiles;	// contents of each square in the board
		const int mRows;
		const int mCols;
	};
}
