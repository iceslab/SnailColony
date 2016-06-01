/*
 * CommonUtils.h
 *
 *  Created on: 5 maj 2016
 *      Author: user
 */

#ifndef HEADERS_COMMONUTILS_H_
#define HEADERS_COMMONUTILS_H_

#include "../headers/includes.h"
#include "../headers/Map.h"
#include "../headers/StatusBar.h"

class CommonUtils
{
public:
	static bool initLibrary();
	static bool initWindows(Map* &map, StatusBar* &statusBar);
	static const int statusBarHeight;
protected:
private:
	static bool initColors();
};

#endif /* HEADERS_COMMONUTILS_H_ */
