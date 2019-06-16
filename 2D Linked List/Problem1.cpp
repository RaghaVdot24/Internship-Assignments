//============================================================================
// Name        : Problem1.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include<iomanip>
using namespace std;

//node structure of list element
struct node{
	int data;
	struct node* down;
	struct node* side;
};


class list{
private:
	int **arr;			//will temporarily store matrix dynamically
	struct node *top;	//will store the head of 2d list i.e arr[0][0]
public:
	list();
	~list();
	void input();
	node *new_node(int );
	node * form_list();
	int diagonal_sum();
	int diagonal_sum2();
	node * transpose();
	node * transpose2();
	void display_list(node *);
	void perimeter();
};

//constructor for initializing
list :: list(){
	arr = NULL;
	top = NULL;
}

// destructor
list :: ~list(){
	delete top;

	for(int i=0;i<3;i++){
		delete[] arr[i];
	}
	delete[] arr;
}

//will alocate memory and initialize a new node and return its address
node * list:: new_node(int d){
	struct node* p = new node;
	p->data = d;
	p->down = NULL;
	p->side = NULL;
	return p;
}

//will take matrix
void list::input(){

	arr = new int*[3];	//creation  of rows
	for(int i=0;i<3;i++){
		arr[i] = new int[3];		//creation of columns
	}

	cout << "\nPlease enter the elements of Array\n";
	for(int i=0;i<3;i++){
		cout << "Elements for row " << i+1 << " = ";
		for(int j=0;j<3;j++){
			cin >> arr[i][j];
		}
	}

	cout  << "Given matrix is :\n\n";
	for(int i=0;i<3;i++){
		cout << "\t{ ";
		for(int j=0;j<3;j++){
			cout << setw(6) << setiosflags(ios::left)  << arr[i][j];
		}
		cout << "}\n";
	}
	cout << "\n";
}

node * list:: form_list(){
	struct node *head[3];		//will store head pointers of every row
	struct node *p,*q;
	//creation of side links
	for(int i=0;i<3;i++){
		head[i] = NULL;
		for(int j=0;j<3;j++){
			p = new_node(arr[i][j]);

			if(top == NULL){
				top = p;
			}
			if(head[i]==NULL){
				head[i] = p;
			}
			else{
				q->side = p;
			}
			q = p;
		}
	}
	//creation of down links
	for(int i=0;i<2;i++){
		p = head[i];
		q = head[i+1];
		while(p && q){
			p->down = q;
			p = p->side;
			q = q->side;
		}
	}
	return top;

}

void list::display_list(node *m)
{
	node *temp = m;;
	int i;
	cout<<"\n\t****** Square Nodes ******\n";
	for(i=0;i<3;i++)
	{
		cout<<"\t\t"<<temp->data<<" -> "<<temp->side->data<<" -> "<<temp->side->side->data<<"\n";//print one row
		temp = temp->down;
	}
	cout<<"\t**************************\n";
}

int list ::diagonal_sum()
{
	int sum=0;
	struct node *p=top;
	//arr[0][0]
	sum = p->data;
	//arr[1][1]
	p = p->down->side;
	sum += p->data;
	//arr[2][2]
	p = p->down->side;
	sum += p->data;
	return sum;
}

int list ::diagonal_sum2(){
	int sum=0;
	struct node *p=top;
	//arr[2][0]
	sum += p->down->down->data;
	//arr[0][2]
	sum += p->side->side->data;
	//arr[1][1]
	sum += p->down->side->data;
	return sum;
}

void list::perimeter()
{
	display_list(top);
	int peri = 0,i;					//temp1 => take sum of 1st row and last element of 2nd row
	node *temp1 = top,*temp2 = top->down;	//temp2 => take sum of 3st row and first element of 2nd row
	for(i=0;i<4;i++)
	{
		peri = peri + temp1->data;
		peri = peri + temp2->data;
		if(i==0)//temp2 goes to 3rd row after taking sum of first element of 2nd row
		{
			temp2 = temp2->down;
			temp1 = temp1->side;
		}
		else if(i == 2)//temp1 goes to last element of 2nd row after taking sum of first row
		{
			temp1 = temp1->down;
			temp2 = temp2->side;
		}
		else//both traverse in row
		{
			temp1 = temp1->side;
			temp2 = temp2->side;
		}
	}
	cout<<"\nPerimeter = "<<peri<<endl;
}


//transpose done by interchanging links
node * list :: transpose()
{
	node *p = top,*q;
	node *head[3];
	head[0] = p;
	head[1] = p->side;
	head[2] = p->side->side;
	//herein we will interchange the side and down links to get transpose
	for(int i=0;i<3;i++){
		p = head[i];
		//getting new side links
		while(p!=NULL){
			q = p->down;
			p->side = q;
			p->down = NULL;
			p = q;
		}
	}
	//getting new down links
	for(int i=0;i<2;i++){
			p = head[i];
			q = head[i+1];
			while(p && q){
				p->down = q;
				p = p->side;
				q = q->side;
			}
	}
	return top;
}

//transpose by making a new 2d linked list
node * list::transpose2()
{
	int i;
	node *temp = top;
	node * head2 = new_node(temp->data);
	temp = temp->down;
	node *temp2 = head2,*first2,*headnode2 = head2,*headnode = top;
	for(i=1;i<9;i++)
	{
		if(i%3 != 0)
		{
			temp2->side = new_node(temp->data);
			temp2 = temp2->side;
			temp = temp->down;
		}
		else
		{
			temp = headnode->side;
			headnode = headnode->side;
			temp2 = new_node(temp->data);
			first2 = headnode2;
			headnode2 = temp2;
			temp = temp->down;
		}
		if(i>2)
		{
			first2->down = temp2;
			first2 = first2->side;
		}
	}
	return head2;
}

int main() {
	list L;
	node *t;
	int ch,c=0;
	do
	{
		cout<<"\n--------------------------MENU--------------------------\n1 : Input a 3*3 matrix\n2 : Display\n3 : Perimeter\n4 : Diagonal Element Sum\n5 : Transpose (Physically)\n6 : Transpose (Another Square)\n7 : Exit\n---------------------------------------------------------\n";
		cout<<"\nEnter Your choice = ";
		cin >> ch;

		switch(ch)
		{
			case 1:
				L.input();
				t = L.form_list();
				L.display_list(t);
				c++;
				break;

			case 2:
				L.display_list(t);
				break;
				
			case 3:
				if(c==0){
					cout << "Provide Input First\n";
					break;
				}
				L.perimeter();
				break;

			case 4:
				if(c==0){
					cout << "Provide Input First\n";
					break;
				}
				L.display_list(t);
				cout << "Sum of  diagonal elements of matrix is : " << L.diagonal_sum() << " and " << L.diagonal_sum2() << endl;
				break;

			case 5:
				if(c==0){
					cout << "Provide Input First\n";
					break;
				}
				cout << "1.Transpose by interchanging links : \n";
				t = L.transpose();
				L.display_list(t);	
				break;

			case 6:
				cout << "2.Transpose by making a new 2D linked list : \n";
				L.display_list(L.transpose2());
				break;
				
			case 7:
				exit(1);

			default:
				cout << "Enter valid choice\n";
				break;
		}
	}
	while(ch);
	return 0;
}
