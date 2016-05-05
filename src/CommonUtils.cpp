/*
 * CommonUtils.cpp
 *
 *  Created on: 5 maj 2016
 *      Author: user
 */
#include "../headers/CommonUtils.h"

bool initLibrary()
{
	bool retVal = false;

	if(NULL != initscr())
	{
		cbreak();
		refresh();
		retVal = true;
	}

	return retVal;
}



