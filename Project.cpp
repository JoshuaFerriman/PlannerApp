#include "Project.h"


Project::Project(char* projectName, time_t dueDate, time_t startDate)
{
	name = projectName;
	setDate_time_t = getCurrentDateAndTime();
	startDate_time_t = startDate;
	dueDate_time_t = dueDate;
}