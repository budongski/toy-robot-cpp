#include <string>
#include <utility>
#include <vector>

namespace test
{
	//commands --> expected result
	//in pairs, to easily see them side by side
	//todo, split input results and business logic results
	const std::vector<std::pair<std::string, std::string>> gTestSequence5X5 =
	{
	{"place X,3,SOUTH\n"					, "failed_to_parse_payload" },
	{"place 2,    3,SOUTH\n"				, "success:2,3,SOUTH" },
	{"place 2,3,4\n"						, "failed_to_parse_payload" },
	{"place  , ,\n"							, "failed_to_parse_payload" },
	{"place 1,3,SOUTH   \n"					, "success:1,3,SOUTH" },
	{"   place 0,3,SOUTH  \n"				, "success:0,3,SOUTH" },
	{" place  2,   3,SOUTH \n"				, "success:2,3,SOUTH" },
	{" place 2,   3 4, SO  UTH \n"			, "failed_to_parse_payload" },
	{"PLACE X,Y,SOUTH\n"					, "failed_to_parse_payload" },
	{"  MOVE\n"								, "success:2,2,SOUTH" },
	{"   \n"								, "unknown_command: \"(empty)\"" },
	{"MOVE   \n"							, "success:2,1,SOUTH" },
	{"MOVE ,  \n"							, "failed_to_parse_payload" },
	{"MOVE ,\n"								, "failed_to_parse_payload" },
	{"  ,MOVE\n"							, "unknown_command: \",MOVE\"" },
	{"  ,move\n"							, "unknown_command: \",MOVE\"" },
	{"PLACE X,Y,SOUTH\n"					, "failed_to_parse_payload" },	
	{"SOMEINVALIDCOMMAND\n"					, "unknown_command: \"SOMEINVALIDCOMMAND\"" },
	{"MOVE\n"								, "success:2,0,SOUTH" },
	{"REPORT\n"								, "report:2,0,SOUTH" },
	{"LEFT\n"								, "success:2,0,EAST" },
	{"LEFT\n"								, "success:2,0,NORTH" },
	{"LEFT\n"								, "success:2,0,WEST" },
	{"LEFT\n"								, "success:2,0,SOUTH" },
	{"REPORT\n"								, "report:2,0,SOUTH" },
	{"MOVE\n"								, "target_position_not_passable_from:2,0,SOUTH" },
	{"MOVE\n"								, "target_position_not_passable_from:2,0,SOUTH" },
	{"MOVE\n"								, "target_position_not_passable_from:2,0,SOUTH" },
	{"MOVE\n"								, "target_position_not_passable_from:2,0,SOUTH" },
	{"REPORT\n"								, "report:2,0,SOUTH" },
	{"RIGHT\n"								, "success:2,0,WEST" },
	{"MOVE\n"								, "success:1,0,WEST" },
	{"REPORT\n"								, "report:1,0,WEST" },
	{"PLACE 6,3,NORTH\n"					, "target_position_not_passable_from:1,0,WEST" },
	{"REPORT\n"								, "report:1,0,WEST" },
	{"MOVE\n"								, "success:0,0,WEST" },
	{"MOVE\n"								, "target_position_not_passable_from:0,0,WEST" },
	{"REPORT\n"								, "report:0,0,WEST" },
	{""										, "unknown_command: \"(empty)\"" }
	}
	;
};

