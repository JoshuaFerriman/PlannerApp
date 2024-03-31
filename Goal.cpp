#include "Goal.h"


 std::time_t Goal::getCurrentDateAndTime()
{
	auto current = std::chrono::system_clock::now();
	auto now_timet = std::chrono::system_clock::to_time_t(current);
	
	return now_timet;

}
//auto now_local = localtime(&now_timet);

 bool Goal::GoalCreateRecord(DatabaseAccessor& databaseAccessor, Goal ParentGoal)
 {
	 //CREATES SUB GOAL USING PARENT GOAL
	 std::vector<std::string> fieldValues = {	NULL, std::to_string(ParentGoal.ID), Goal::name, Goal::description, Goal::notes,
												std::to_string(Goal:: setDate_time_t), std::to_string(Goal::startDate_time_t), std::to_string(Goal::dueDate_time_t),
												std::to_string(Goal::stepNumber), std::to_string(Goal::isComplete)
											};

	 databaseAccessor.TableINSERT(goals, fieldValues);

	 return true;
 }

 
 bool Goal::GoalCreateRecord(DatabaseAccessor& databaseAccessor, User& currentUser)
 {
	 //CREATES MAIN GOAL STORING CURRENT USER
	 std::vector<std::string> fieldValues = {	currentUser.GetID(), NULL, Goal::name , Goal::description, Goal::notes,
												std::to_string(Goal::setDate_time_t), std::to_string(Goal::startDate_time_t), std::to_string(Goal::dueDate_time_t),
												std::to_string(Goal::stepNumber), std::to_string(Goal::isComplete)
											};

	 databaseAccessor.TableINSERT(goals, fieldValues);

	 return true;
 }
 

 bool Goal::GoalUpdateRecord(DatabaseAccessor& databaseAccessor)
 {
	 return true;
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

 Goal::Goal(DatabaseAccessor& databaseAccessor, Goal ParentGoal, std::string goalName, std::string description, std::string notes, time_t setDate, time_t startDate, time_t dueDate, int stepNumber, bool isComplete)
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
	 Goal::isComplete = isComplete;



	 GoalCreateRecord(databaseAccessor, ParentGoal);
 }

 Goal::Goal(DatabaseAccessor& databaseAccessor, User& currentUser, std::string goalName, std::string description, std::string notes, time_t setDate, time_t startDate, time_t dueDate, int stepNumber, bool isComplete)
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
	 Goal::isComplete = isComplete;



	 GoalCreateRecord(databaseAccessor, currentUser);
 }

 char* Goal::GetNameData() 
 {
	 return Goal::name.data();
 }

 char* Goal::GetDescriptionData()
 {
	 return Goal::description.data();
 }

 std::string Goal::GetID()
 {
	 return std::to_string(Goal::ID);
 }