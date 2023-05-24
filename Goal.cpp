#include "Goal.h"

 std::time_t Goal::getCurrentDateAndTime()
{
	auto current = std::chrono::system_clock::now();
	auto now_timet = std::chrono::system_clock::to_time_t(current);
	
	return now_timet;

}
//auto now_local = localtime(&now_timet);

 Goal::Goal(char* subGoalName, time_t dueDate = NULL, time_t startDate = NULL)
 {
	 setDate_time_t = getCurrentDateAndTime();
	 dueDate_time_t = dueDate;
	 startDate_time_t = startDate;


 }

 Goal::Goal()
 {

 }

 Goal::Goal(std::string goalName, std::string description, std::string notes, int setDate, int startDate, int dueDate, int stepNumber, bool isComplete)
 {

 }
