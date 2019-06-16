/*
 * AADHAR.cpp
 *
 *  Created on: 12-Jun-2019
 *      Author: vinit
 */

#include "AADHAR.h"

AADHAR::AADHAR() {}

void AADHAR::load()
{
	fstream in;
	DETAIL de;
	in.open("C:/Users/Raghav Utpat/Documents/aadharcard/aadharcard/src/AADHAR",ios::in);
	while(in)
	{
		in>>detail.uid>>detail.first_name>>detail.last_name>>detail.mobile>>detail.dob.date>>detail.dob.month>>detail.dob.year>>detail.isBlacklisted;
		getline(in,detail.guardian_name);
		getline(in,detail.address);
		data[detail.uid] = detail;
	}
	in.close();
}

void AADHAR::display()
{
	unordered_map<string, DETAIL>:: iterator it;
	for(it = data.begin();it != data.end(); it++)
	{
		detail = it->second;
		if(detail.isBlacklisted == 0)
		cout<<detail.first_name<<" "<<detail.uid<<" "<<detail.address<<" "<<detail.dob.date<<"-"<<detail.dob.month<<"-"<<detail.dob.year<<endl;
	}
}

void AADHAR::check()
{
	cout<<"\nEnter UID : ";
	cin>>detail.uid;
	cout<<"Enter First Name : ";
	cin>>detail.first_name;

	unordered_map <string, DETAIL>::iterator it = data.find(detail.uid);
	if(it != data.end() && it->second.isBlacklisted == 0)
	{
		if((it->second.first_name).compare(detail.first_name) == 0)
			cout<<"=> ENTRY IS PRESENT\n";
		else
			cout<<"=> FIRST NAME IS INCORRECT\n";
	}
	else
		cout<<"=> UID IS NOT PRESENT\n";
}
