#include "SubGoal.h"

 std::time_t SubGoal::getCurrentDateAndTime()
{
	auto current = std::chrono::system_clock::now();
	auto now_timet = std::chrono::system_clock::to_time_t(current);
	
	return now_timet;

}
//auto now_local = localtime(&now_timet);

 SubGoal::SubGoal(char* subGoalName, time_t dueDate = NULL, time_t startDate = NULL)
 {
	 setDate_time_t = getCurrentDateAndTime();
	 dueDate_time_t = dueDate;
	 startDate_time_t = startDate;


 }

 SubGoal::SubGoal()
 {

 }
