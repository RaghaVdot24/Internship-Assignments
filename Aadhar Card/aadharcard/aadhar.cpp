/*
 * aadhar.cpp
 *
 *  Created on: 10-Jun-2019
 *      Author: vinit
 */
#include "aadhar.h"

aadhar::aadhar() {}


string UID()							//generate a unique id for each person
{
	srand(time(0));
	std::ostringstream os;
	for (int i = 0; i < 12; ++i)
	{
	    int digit = rand() % 10;
	    os << digit;
	}
	return os.str();
}

void write(unordered_map <string ,DETAIL> data)
{
	unordered_map<string, DETAIL>:: iterator it;
	DETAIL detail;
	ofstream out;
	out.open("AADHAR",ios::out);

	for(it = data.begin();it != data.end(); it++)
	{
		detail = it->second;
		out<<detail.uid<<" "<<detail.first_name<<" "<<detail.last_name<<" "<<detail.mobile<<" "<<detail.dob.date<<" "<<detail.dob.month<<" "<<detail.dob.year<<" "<<detail.isBlacklisted<<" "<<detail.guardian_name<<endl;
		out<<detail.address<<endl;
	}
	out.close();
}

int aadhar::validate(int j)
{
	if(j == 2)
	{
		if(detail.mobile < 1000000000 || detail.mobile > 9999999999)
		{
			cout<<"Invalid Mobile No. Entered...Please Enter again\n";
			return 1;
		}
	}
	else
	{
		if(detail.dob.date < 1 || detail.dob.date > 30 || detail.dob.month <1 || detail.dob.month >12 || detail.dob.year < 1900 || detail.dob.year >2019)
		{
			cout<<"Invalid Date of Birth...Please Enter again\n";
			return 1;
		}
	}
	return 0;	
}

void aadhar::insert()
{
	int j = 1;
	cout.setf(ios::left);
	cout<<setw(33)<<"\nEnter First Name "<<" : ";
	cin>>detail.first_name;
	cout<<setw(33)<<"Enter Last Name "<<": ";
	cin>>detail.last_name;
	cout<<setw(33)<<"Enter Guardian Name "<<": ";
	cin.ignore();
	getline(cin,detail.guardian_name);
	cout<<setw(33)<<"Enter Address "<<": ";
	getline(cin,detail.address);

	do
	{
		cout<<setw(33)<<"Enter Date of Birth (DD MM YYYY) "<<": ";
		cin>>detail.dob.date>>detail.dob.month>>detail.dob.year;
		j = validate(1);
	}while(j);	
	
	do
	{
		cout<<setw(33)<<"Enter Mobile No. "<<": ";
		cin>>detail.mobile;
		j = validate(2);
	}while(j);
	detail.uid = UID();
	detail.isBlacklisted = 0;
	data[detail.uid] = detail;
	cout<<"\n---------------------------------------------------------------\n";
	cout<<"UID    :     "<<detail.uid;
	cout<<"\n---------------------------------------------------------------\n";
	
	write(data);
}

void aadhar::load()
{
	fstream in;
	DETAIL de;
	in.open("AADHAR",ios::in);
	while(in)
	{
		in>>detail.uid>>detail.first_name>>detail.last_name>>detail.mobile>>detail.dob.date>>detail.dob.month>>detail.dob.year>>detail.isBlacklisted;
		getline(in,detail.guardian_name);
		getline(in,detail.address);
		data[detail.uid] = detail;
	}
	in.close();
}

void aadhar::display()
{
	unordered_map<string, DETAIL>:: iterator it;
	for(it = data.begin();it != data.end(); it++)
	{
		detail = it->second;
		if(detail.isBlacklisted == 0)
			cout<<detail.first_name<<" "<<detail.uid<<" "<<detail.address<<" "<<detail.dob.date<<"-"<<detail.dob.month<<"-"<<detail.dob.year<<endl;
	}
}

void aadhar::delet()
{
	cout<<"\nEnter the UID : ";
	cin>>detail.uid;

	unordered_map<string,DETAIL>::const_iterator it = data.find(detail.uid);

	if(it == data.end() || it->second.isBlacklisted==1)
		cout<<"=> UID NOT FOUND\n";
	else
	{
		data.erase(it);
		cout<<"=> THE RECORD IS SUCCESSFULLY DELETED\n";
	}
	write(data);
}

void aadhar::update()
{
	int e;
	cout<<"\nEnter the UID : ";
	cin>>detail.uid;
	unordered_map<string,DETAIL>::const_iterator it = data.find(detail.uid);

	if(it == data.end())
		cout<<"=> UID NOT FOUND\n";
	else
	{
		detail = it->second;
		data.erase(detail.uid);
		cout<<"\n\t\t*Update Choice = \n\t\t1 : First Name\n\t\t2 : Last Name\n\t\t3 : Guardian Name\n\t\t4 : Address\n\t\t5 : Date of Birth\n\t\t6 : Mobile No.\n\t\t7 : Back\n\t\t";
		cout<<"Enter your Choice : ";
		cin>>e;
		switch(e)
		{
			case 1:
				cout<<"\n\t\tEnter First Name : ";
				cin>>detail.first_name;
				break;

			case 2:
				cout<<"\n\t\tEnter Last Name : ";
				cin>>detail.last_name;
				break;

			case 3:
				cout<<"\n\t\tEnter Guardian Name : ";
				cin.ignore();
				getline(cin,detail.guardian_name);
				break;

			case 4:
				cout<<"\n\t\tEnter New Address : ";
				cin.ignore();
				getline(cin,detail.address);
				break;

			case 5:
				cout<<"\n\t\tEnter Date of Birth : ";
				cin>>detail.dob.date>>detail.dob.month>>detail.dob.year;
				break;

			case 6:
				cout<<"\n\t\tEnter Mobile No. : ";
				cin>>detail.mobile;
				break;
		}
		data[detail.uid] = detail;
		cout<<"=> THE RECORD IS SUCCESSFULLY UPDATED\n";
	}
	write(data);
}

void aadhar::addblacklist()
{
	cout<<"\nEnter the UID to be blacklisted: ";
	cin>>detail.uid;

	unordered_map<string,DETAIL>::iterator it = data.find(detail.uid);

	if(it == data.end())
		cout<<"=> UID NOT FOUND\n";
	else
	{
		it->second.isBlacklisted = 1;
		cout<<"=> THE RECORD IS SUCCESSFULLY BLACKLISTED\n";
	}
	write(data);
}

void aadhar::remblacklist()
{
	cout<<"\nEnter the UID to be removed from the blacklist: ";
	cin>>detail.uid;

	unordered_map<string,DETAIL>::iterator it = data.find(detail.uid);

	if(it == data.end() && it->second.isBlacklisted==0)
		cout<<"=> UID NOT FOUND\n";
	else
	{
		it->second.isBlacklisted = 0;
		cout<<"=> THE RECORD IS SUCCESSFULLY REMOVED FROM THE BLACKLIST\n";
	}
	write(data);
}

void searchfirst(unordered_map <string ,DETAIL> data)
{
	string name;
	cout<<"\n\t\tEnter First Name : ";
	cin>>name;
	int i=1;
	unordered_map <string ,DETAIL>::iterator it;
	cout.setf(ios::left);
	for(it = data.begin(); it != data.end(); it++)
	{
		if(it->second.first_name.find(name) != string::npos && it->second.isBlacklisted != 1)
		{
			cout<<"\n\t\t:: "<<i<<" ::"<<setw(14)<<"\n\t\tFirst Name "<<": "<<it->second.first_name<<setw(14)<<"\n\t\tLast Name "<<": "<<it->second.last_name<<setw(14)<<"\n\t\tUid "<<": "<<it->second.uid<<endl;
			i++;
		}
	}
	if(i==1)
		cout<<"=> RECORD NOT FOUND";
}

void searchguardian(unordered_map <string ,DETAIL> data)
{
	string name;
	cout<<"\n\t\tEnter Guardian Name : ";
	cin>>name;
	int i=1;
	cout.setf(ios::left);
	unordered_map <string ,DETAIL>::iterator it;
	for(it = data.begin(); it != data.end(); it++)
	{
		if(it->second.guardian_name.find(name) != string::npos && it->second.isBlacklisted != 1)
		{
			cout<<"\n\t\t:: "<<i<<" ::"<<setw(14)<<"\n\t\tFirst Name "<<": "<<it->second.first_name<<setw(14)<<"\n\t\tLast Name "<<": "<<it->second.last_name<<setw(14)<<"\n\t\tUid "<<": "<<it->second.uid<<endl;
			i++;
		}
	}
	if(i==1)
		cout<<"NOT FOUND";
}

void searchuid(unordered_map <string ,DETAIL> data)
{
	string uid;
	cout<<"\n\t\tEnter UID : ";
	cin>>uid;
	unordered_map<string,DETAIL>::const_iterator it = data.find(uid);
	cout.setf(ios::left);

	if(it != data.end() && it->second.isBlacklisted!=1)
		cout<<setw(14)<<"\n\t\tFirst Name "<<": "<<it->second.first_name<<setw(14)<<"\n\t\tLast Name "<<": "<<it->second.last_name<<setw(14)<<"\n\t\tUid "<<": "<<it->second.uid<<endl;
	else
		cout<<"=> RECORD NOT FOUND\n";
}



void aadhar::search()
{
	int e;
	cout<<"\n\t\t*SearchBy = \n\t\t1 : First Name\n\t\t2 : Guardian Name\n\t\t3 : UID\n\t\t4 : Back\n\t\t";
	cout<<"Enter Your Choice = ";
	cin>>e;
	switch(e)
	{
		case 1:
			searchfirst(data);
			break;

		case 2:
			searchguardian(data);
			break;

		case 3:
			searchuid(data);
			break;
	}
}
