#pragma once

#include <framework/gridmath.h>
#include "toy.h"
#include <vector>
#include <map>
#include <string>


namespace toyrobot
{
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
		BoardError placeRobot(int id, const toyrobot::Transform4D& transform);
		BoardError forwardRobot(int id);
		BoardError turnRobotLeft(int id);
		BoardError turnRobotRight(int id);
		BoardError report(int id, std::string& report);
		static std::string toString(BoardError err);

	private:
		Toy* findRobot(int id);
		Toy* spawnRobot(int id, const toyrobot::Transform4D& to);
		bool isTilePassable(const toyrobot::Transform4D& transform);
		void updateTileContent(Toy* toy, const toyrobot::Transform4D& from, const toyrobot::Transform4D& to);
		void updateTileContent(Toy* toy, const toyrobot::Transform4D& to);

		std::map<int, Toy*> mRobots;				// 
		std::vector< std::vector <Toy*>> mTiles;	// contents of each square in the board
		const int mRows;
		const int mCols;
	};
}
