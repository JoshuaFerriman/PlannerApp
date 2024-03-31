#include "Goal.h"

 std::time_t Goal::getCurrentDateAndTime()
{
	auto current = std::chrono::system_clock::now();
	auto now_timet = std::chrono::system_clock::to_time_t(current);
	
	return now_timet;

}
//auto now_local = localtime(&now_timet);

 bool Goal::GoalCreateRecord()
 {
	 std::vector<std::string> fieldValues = { User::username, User::hashedPassword, User::salt };

	 databaseAccessor.TableINSERT(users, fieldValues);

	 return true;
 }

 bool Goal::GoalUpdateRecord()
 {

 }

 Goal::Goal(char* subGoalName, time_t dueDate = NULL, time_t startDate = NULL)
 {
	 Goal::name = subGoalName;
	 Goal::setDate_time_t = getCurrentDateAndTime();
	 Goal::dueDate_time_t = dueDate;
	 Goal::startDate_time_t = startDate;


 }

 Goal::Goal()
 {

 }

 Goal::Goal(std::string goalName, std::string description, std::string notes, time_t setDate, time_t startDate, time_t dueDate, int stepNumber, bool isComplete)
 {

	 Goal::name = goalName;
	 Goal::description = description;
	 Goal::notes = notes;

	 Goal::setDate_time_t = setDate;
	 Goal::startDate_time_t = NULL;
	 Goal::dueDate_time_t = NULL;

	 Goal::objectives = { };
	 Goal::steps = { };

	 Goal::stepNumber = stepNumber;
	 Goal::complete = isComplete;

	 GoalCreateRecord();
 }

 

 char* Goal::GetNameData() 
 {
	 return Goal::name.data();
 }

 char* Goal::GetDescriptionData()
 {
	 return Goal::description.data();
 }