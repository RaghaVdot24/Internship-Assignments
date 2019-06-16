/*
 * AADHAR.h
 *
 *  Created on: 12-Jun-2019
 *      Author: vinit
 */

#ifndef AADHAR_H_
#define AADHAR_H_

#include <iostream>
#include <unordered_map>
#include <sstream>
#include <fstream>
using namespace std;

struct DOB
{
	int date,month,year;
};

struct DETAIL
{
	string first_name,last_name,guardian_name,address,uid;
	DOB dob;
	int isBlacklisted;
	long int mobile;
};

class AADHAR
{
	DETAIL detail;
	unordered_map <string ,DETAIL> data;
	public:
		AADHAR();
		void load();
		void check();
		void display();
};

#endif /* AADHAR_H_ */
