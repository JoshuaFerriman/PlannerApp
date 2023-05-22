#pragma once
#include "SubGoal.h"

static const Table projects
{
	"PROJECTS",
	{
		{"USERNAME", "TEXT"},
		{"PASSWORD", "TEXT"},
		{"SALT", "TEXT"},
	},
};

class Project: public SubGoal
{
//Member Fields
	//in SubGoal
	// 
	// 
//Member Functions
private:

public:
	Project(char* projectName, time_t dueDate, time_t startDate = NULL);

};

