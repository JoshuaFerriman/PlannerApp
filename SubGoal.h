#pragma once
#include "DataBaseAccessor.h"
#include <chrono>
#include <string>
#include <vector>
#include <ctime>

class SubGoal
{
	//Member Fields
protected:
	std::time_t setDate_time_t = NULL;

public:
	std::time_t startDate_time_t = NULL;
	std::time_t dueDate_time_t = NULL;
	
	bool complete = false;

	std::string name;
	std::string description;
	std::string notes;

	std::vector<SubGoal> objectives = { };
	std::vector<SubGoal> steps = { };

	//Member Functions
protected:
	std::time_t getCurrentDateAndTime();
public:
	SubGoal();
	SubGoal(char* subGoalName, time_t dueDate, time_t startDate);

};

