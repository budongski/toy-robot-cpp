#include "board.h"
#include <framework/utils.h>

namespace toyrobot
{
	Board::Board(int rows, int cols)
		: mRows(rows)
		, mCols(cols)
	{
		mTiles.resize(rows, std::vector<ToyPtr>(cols, nullptr));
	}

	Board::~Board()
	{
	}

	BoardError Board::placeRobot(int id, const toyrobot::Transform4D& transform)
	{
		if (!isTilePassable(transform))
			return BoardError::target_position_not_passable;

		auto robot = findRobot(id);
		if (!robot)
		{
			robot = spawnRobot(id, transform);
		}
		else
		{
			auto oldpos = robot->mTransform;
			robot->mTransform.set(transform);

			updateTileContent(oldpos, transform);
		}
		return BoardError::success;
	}

	BoardError Board::forwardRobot(int id)
	{
		auto err = BoardError::success;
		if (auto robot = findRobot(id); robot != nullptr)
		{
			if (isTilePassable(robot->mTransform.peek()))
			{
				auto oldpos = robot->mTransform;
				robot->mTransform.forward();
				updateTileContent(oldpos, robot->mTransform);
			}
			else
			{
				err = BoardError::target_position_not_passable;
			}
		}
		else
		{
			err = BoardError::robot_does_not_exist;
		}
		return err;
	}

	BoardError Board::turnRobotLeft(int id)
	{
		if (auto robot = findRobot(id); robot != nullptr)
		{
			robot->mTransform.left();
			return BoardError::success;
		}

		return BoardError::robot_does_not_exist;
	}

	BoardError Board::turnRobotRight(int id)
	{
		if (auto robot = findRobot(id); robot != nullptr)
		{
			robot->mTransform.right();
			return BoardError::success;
		}

		return BoardError::robot_does_not_exist;
	}

	ToyPtr Board::findRobot(int id) 
	{
		if (auto iter = mRobots.find(id); iter != mRobots.end())
			return iter->second;
		return nullptr;
	}

	ToyPtr Board::spawnRobot(int id, const toyrobot::Transform4D& transform)
	{
		mRobots[id] = std::make_shared<Toy>(id, transform);
		updateTileContent(mRobots[id], transform);
		return mRobots[id];
	}

	bool Board::isTilePassable(const toyrobot::Transform4D& transform) 
	{
		if (
			(transform.cell.x >= 0) &&
			(transform.cell.y >= 0) &&
			(transform.cell.x < static_cast<int>(mTiles.size())) &&
			(transform.cell.y < static_cast<int>(mTiles.at(0).size())))
		{
			// return mTiles[transform.cell.x][transform.cell.y] == nullptr;
			// content of tile does not matter for now
			return true;
		}

		return false;
	}

	void Board::updateTileContent(const Transform4D& from, const Transform4D& to)
	{
		if(mTiles[from.cell.x][from.cell.y] != nullptr)
			mTiles[to.cell.x][to.cell.y] = std::move(mTiles[from.cell.x][from.cell.y]);
	}

	void Board::updateTileContent(ToyPtr toy, const Transform4D& to)
	{
		mTiles[to.cell.x][to.cell.y] = toy;
	}

	BoardError Board::report(int id, std::string& report)
	{
		if (auto robot = findRobot(id); robot != nullptr)
		{
			report = strutils::format("%d,%d,%s",
				robot->mTransform.cell.x, 
				robot->mTransform.cell.y, 
				robot->mTransform.getRotationString().c_str());
			return BoardError::success;
		}

		return BoardError::robot_does_not_exist;
	}

	std::string Board::toString(BoardError err)
	{
		switch (err)
		{
		case BoardError::robot_does_not_exist:
			return "robot_does_not_exist";
			break;
		case BoardError::target_position_not_passable:
			return "target_position_not_passable_from";
			break;
		case BoardError::success:
		default:
			break;
		}

		return "success";
	}

};