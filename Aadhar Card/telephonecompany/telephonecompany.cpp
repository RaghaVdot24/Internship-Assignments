//============================================================================
// Name        : telephonecompany.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "AADHAR.cpp"

int main()
{
	AADHAR record;
	int e;
	record.load();
	do
	{
		cout<<"\n--------------------------MENU--------------------------\n1 : Check UID against First Name\n2 : Exit\n--------------------------------------------------------\n";
		cout<<"Enter Your Choice = ";
		cin>>e;
		switch(e)
		{
			case 1:
				record.check();
				break;

			case 2:
				exit(1);
		}
	}while(e);
	return 0;
}
