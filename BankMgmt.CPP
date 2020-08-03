


#include<fstream.h>
#include<ctype.h>
#include<iomanip.h>
#include<conio.h>
#include<stdio.h>



class account//class
{
	int accno;
	char name[50];
	int balance;
	char type;
public:
	void create_account();	
	void show_account();	
	void modify();  
	void dep(int);	
	void draw(int);	
	void report();	
	int retaccno();	
	int retbalance();	
	char rettype();	
};         //class ends here

void account::create_account()
{
	cout<<"\nEnter The account No.";
	cin>>accno;
	cout<<"\n\nEnter The Name of The account Holder : ";
	gets(name);
	cout<<"\nEnter Type of The account (C/S) : ";
	cin>>type;
	type=toupper(type);
	cout<<"\nEnter The Initial amount(>=500 for Saving and >=1000 for current ) : ";
	cin>>balance;
	cout<<"\n\n\nAccount Created..";
}

void account::show_account()
{
	cout<<"\nAccount No. : "<<accno;
	cout<<"\nAccount Holder Name : ";
	cout<<name;
	cout<<"\nType of Account : "<<type;
	cout<<"\nBalance amount : "<<balance;
}


void account::modify()
{
	cout<<"\nThe account No."<<accno;
	cout<<"\n\nEnter The Name of The account Holder : ";
	gets(name);
	cout<<"\nEnter Type of The account (C/S) : ";
	cin>>type;
	type=toupper(type);
	cout<<"\nEnter The amount : ";
	cin>>balance;
}


void account::dep(int x)//deposit
{
	balance+=x;
	cout<<" Successfully deposited !"<<endl;
	cout<<" New balance is "<<balance<<endl;
}

void account::draw(int x)//withdrawing amount 
{
	balance-=x;
	cout<<" Successfully Withdrawed !"<<endl;
	cout<<" New balance is "<<balance<<endl;
}

void account::report()
{
	cout<<accno<<setw(10)<<" "<<name<<setw(10)<<" "<<type<<setw(6)<<balance<<endl;
}

int account::retaccno()//to return account no.
{
	return accno;
}

int account::retbalance()//to return balance of a user
{
	return balance;
}

char account::rettype()//to return the type of the account
{
	return type;
}



void write_account();	
void display_sp(int);	
void modify_account(int);	
void delete_account(int);	
void display_all();		
void deposit_withdraw(int, int); 
void intro();	




void main()
{
	char ch;
	int num;
	clrscr();
	intro();
	do
	{
		clrscr();
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t01. NEW ACCOUNT";
		cout<<"\n\n\t02. DEPOSIT AMOUNT";
		cout<<"\n\n\t03. WITHDRAW AMOUNT";
		cout<<"\n\n\t04. BALANCE ENQUIRY";
		cout<<"\n\n\t05. ALL ACCOUNT HOLDER LIST";
		cout<<"\n\n\t06. CLOSE AN ACCOUNT";
		cout<<"\n\n\t07. MODIFY AN ACCOUNT";
		cout<<"\n\n\t08. EXIT";
		cout<<"\n\n\tSelect Your Option (1-8) ";
		cin>>ch;
		clrscr();
		switch(ch)
		{
		case '1':
			write_account();
			break;
		case '2':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			deposit_withdraw(num, 1);
			break;
		case '3':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			deposit_withdraw(num, 2);
			break;
		case '4':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			display_sp(num);
			break;
		case '5':
			display_all();
			break;
		case '6':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			delete_account(num);
			break;
		 case '7':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			modify_account(num);
			break;
		 case '8':
			cout<<"\n\n\tThanks for using bank management system";
			break;
		 default :cout<<"\a";
		}
		getch();
	}while(ch!='8');
	getch();
}




void write_account()//To register a new account
{
	account ac;
	ofstream outF;
	outF.open("account.dat",ios::binary|ios::app);
	ac.create_account();
	outF.write((char *) &ac, sizeof(account));
	outF.close();
}

void display_sp(int n)//to display a specific record
{
	account ac;
	int flag=0;
	ifstream inF;
	inF.open("account.dat",ios::binary);
	if(!inF)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\nBALANCE DETAILS\n";
	while(inF.read((char *) &ac, sizeof(account)))
	{
		if(ac.retaccno()==n)
		{
			ac.show_account();
			flag=1;
		}
	}
	inF.close();
	if(flag==0)
		cout<<"\n\nAccount number does not exist";
}




void modify_account(int n)//to modify a record of a file
{
	int found=0;
	account ac;
	fstream File;
	File.open("account.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(File.read((char *) &ac, sizeof(account)) && found==0)
	{
		if(ac.retaccno()==n)
		{
			ac.show_account();
			cout<<"\n\nEnter The New Details of account"<<endl;
			ac.modify();
			int pos=(-1)*sizeof(account);
			File.seekp(pos,ios::cur);
			File.write((char *) &ac, sizeof(account));
			cout<<"\n\n\t Record Updated";
			found=1;
		}
	}
	File.close();
	if(found==0)
		cout<<"\n\n Record Not Found ";
}




void delete_account(int n)// to delete record of file
{
	account ac;
	ifstream inF;
	ofstream outF;
	inF.open("account.dat",ios::binary);
	if(!inF)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	outF.open("Temp.dat",ios::binary);
	inF.seekg(0,ios::beg);
	while(inF.read((char *) &ac, sizeof(account)))
	{
		if(ac.retaccno()!=n)
		{
			outF.write((char *) &ac, sizeof(account));
		}
	}
	inF.close();
	outF.close();
	remove("account.dat");
	rename("Temp.dat","account.dat");
	cout<<"\n\n\tRecord Deleted ..";
}


void display_all() //to display all accounts
{
	account ac;
	ifstream inF;
	inF.open("account.dat",ios::binary);
	if(!inF)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout<<"====================================================\n";
	cout<<"A/c no.      NAME           Type  Balance\n";
	cout<<"====================================================\n";
	while(inF.read((char *) &ac, sizeof(account)))
	{
		ac.report();
	}
	inF.close();
}



void deposit_withdraw(int n, int option)// to balance and withdraw amounts
{
	int amt;
	int found=0;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(File.read((char *) &ac, sizeof(account)) && found==0)
	{
		if(ac.retaccno()==n)
		{
			ac.show_account();
			switch(option)
			{
case 1:
				cout<<"\n\n\tTO DEPOSIT AMOUNT ";
				cout<<"\n\nEnter The amount to be deposited ";
				cin>>amt;
				ac.dep(amt);
			break;
			case 2:
			{
				cout<<"\n\n\tTO WITHDRAW AMOUNT ";
				cout<<"\n\nEnter The amount to be withdraw ";
				cin>>amt;
				int bal=ac.retbalance()-amt;
				if((bal<500 && ac.rettype()=='S') || (bal<1000 && ac.rettype()=='C'))
					cout<<"Insufficience balance";
				else
					ac.draw(amt);
			}break;
}
			int pos=(-1)* sizeof(ac);
			File.seekp(pos,ios::cur);
			File.write((char *) &ac, sizeof(account));
			cout<<"\n\n\t Record Updated";
			found=1;
	       }
	}
	File.close();
	if(found==0)
		cout<<"\n\n Record Not Found ";
}




void intro()
{
	cout<<"\n\n\n\t  BANK";
	cout<<"\n\n\tMANAGEMENT";
	cout<<"\n\n\t  SYSTEM";
	cout<<"\n\n\n\nMADE BY : Sanjeev";
	cout<<"\n\nSCHOOL : Indian High School";
	getch();
}

