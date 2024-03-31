#pragma once
#include "DataBaseAccessor.h"
#include <chrono>
#include <string>
#include <vector>
#include <ctime>

static const Table goals
{
	"GOALS",
	{
		{"USER_ID", "INTEGER"},
		{"PARENT_ID", "INTEGER"},

		{"IS_SUBGOAL", "INTEGER"},

		{"GOAL_NAME", "TEXT"},
		{"DESCRIPTION", "TEXT"},
		{"NOTES", "TEXT"},

		{"SET_DATE", "INTEGER"},
		{"START_DATE", "INTEGER"},
		{"DUE_DATE", "INTEGER"},

		{"STEP_NUMBER", "INTEGER"},
		{"IS_COMPLETE", "INTEGER"},
	},
};

class Goal
{
	//Member Fields
protected:

	std::string name;
	std::string description;
	std::string notes = "";

	std::time_t setDate_time_t = NULL;
	std::time_t startDate_time_t = NULL;
	std::time_t dueDate_time_t = NULL;

	int numOfObjectives = 0;
	std::vector<Goal> objectives = { };
	int numOfSteps = 0;
	std::vector<Goal> steps = { };

	int stepNumber = NULL;
	bool complete = false;
public:

	

	//Member Functions
protected:
	std::time_t getCurrentDateAndTime();
	void GoalCreateRecord();
	void GoalUpdateRecord();
public:
	Goal();
	Goal(char* GoalName, time_t dueDate, time_t startDate);
	Goal(std::string goalName, std::string description, std::string notes, time_t setDate, time_t startDate, time_t dueDate, int stepNumber, bool isComplete);
	
	
	char* GetNameData();
	char* GetDescriptionData();

};

