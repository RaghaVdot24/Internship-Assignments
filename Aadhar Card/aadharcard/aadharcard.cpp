//============================================================================
// Name        : aadharcard.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include "aadhar.cpp"

int main()
{
	aadhar record;
	record.load();
	int e;

	do
	{
		cout<<"\n--------------------------MENU--------------------------\n1 : Insert\n2 : Display\n3 : Delete\n4 : Update\n5 : Search\n6 : Blacklist an entry\n7 : Remove from blacklist\n8 : Exit\n---------------------------------------------------------\n";
		cout<<"\nEnter Your choice = ";
		cin>>e;
		switch(e)
		{
			case 1:
				record.insert();
				break;

			case 2:
				record.display();
				break;

			case 3:
				record.delet();
				break;

			case 4:
				record.update();
				break;

			case 5:
				record.search();
				break;

			case 6:
				record.addblacklist();
				break;

			case 7:
				record.remblacklist();
				break;

			case 8:
				exit(1);
		}

	}while(e);

	return 0;
}
