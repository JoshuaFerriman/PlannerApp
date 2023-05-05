#pragma once
#include "SubGoal.h"

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

