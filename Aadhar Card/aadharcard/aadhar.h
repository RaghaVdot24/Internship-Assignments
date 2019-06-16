/*
 * aadhar.h
 *
 *  Created on: 10-Jun-2019
 *      Author: vinit
 */

#ifndef AADHAR_H_
#define AADHAR_H_

#include <iostream>
#include <iomanip>
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

class aadhar
{
		DETAIL detail;
		unordered_map <string ,DETAIL> data;
	public:
		aadhar();
		void load();
		void insert();
		void display();
		void delet();
		void update();
		void search();
		int validate(int);
		void addblacklist();
		void remblacklist();
};

#endif /* AADHAR_H_ */
