#include<fstream>
#include<iostream>
using namespace std;

float dc[3]={3,3.5,4};// per unit cost of electricity for different slabs
float df=50;// fixed charge for 'd' type customer
float cf=120;// fixed charge for 'c' type customer

class BILL
{
	private:
		int sub_no;
		char sub_name[80];
		int unit;
		char category;
		float amount;
		void dcalc(int unit);
		void ccalc(int unit);
	public:
		int get_sub_no(){return sub_no;}
		char get_category(){return category;}
		void get_sub_det();
		void cdisp();
		void disp(char c);
};

//class functions
void BILL::dcalc(int unit)
{
	if((unit>0)&&(unit<=200))
		amount=df+(unit*dc[0]);
	if((unit>200)&&(unit<=500))
        amount=df+(200*dc[0])+((unit-200)*dc[1]);
	if(unit>500)
		amount=df+(200*dc[0])+(300*dc[1])+((unit-500)*dc[3]);
}

void BILL::ccalc(int unit)
{
	amount=cf+(unit*3.5);//per unit cost is 3.5 for c type
}
void BILL::cdisp()
{
	cout<<sub_no<<"\t"<<sub_name<<"\t"<<category<<"\t"<<unit<<"\t"<<amount;
}

void BILL::disp(char c)
{
	cout<<"\nSubscriber Number: "<<sub_no;
	cout<<"\nSubscriber Name: "<<sub_name;
	cout<<"\nCategory: "<<category;
	cout<<"\nUnits used (in Watt-Hour) : "<<unit<<"\n";
	if((c=='D')||(c=='d'))
	{
		cout<<"\nFixed Charges = $. "<<df;
		cout<<"\nBulk          = $. "<<(amount-df);
	}
	else if((c=='C')||(c=='c'))
	{
		cout<<"\nFixed Charges = $. "<<cf;
		cout<<"\nBulk          = $. "<<(amount-cf);
	}
	cout<<"\nNet Amount : $. "<<amount;
	cin.ignore();
    cin.get();
}

void BILL::get_sub_det()
{
	cout<<"\nData Entry :";
	cout<<"\n**** *****";
	cout<<"\nEnter Subscriber Number: ";
	cin>>sub_no;
	cout<<"\nEnter Subscriber Name: ";
	cin.ignore();
	cin.getline(sub_name,50);
	cout<<"\nEnter Category (Enter 'D' or 'C') : ";
	cin>>category;
	cout<<"\nEnter Units Consumed: ";
	cin>>unit;
	if((category=='D')||(category=='d'))
	{
		dcalc(unit);
	}
	else if((category=='C')||(category=='c'))
		ccalc(unit);
	else
		cout<<"\nUnable to Process !!!";
}

//Other functions
void add_data();
void view_file();
void search();
void remove();
void print();

//main function
int main()
{
	BILL a;
	char choice;
	char ch;
	main:
		cout<<"Electricity Bill Calculating System";
		cout<<"\n*********** **** *********** ******";
		cout<<"\nMAIN MENU :";
		cout<<"\n---- ----";
		cout<<"\n1.Add Consumer Data";
		cout<<"\n2.View All Consumers";
		cout<<"\n3.Search for a Particular Consumer";
		cout<<"\n4.Delete a Particular Consumer";
		cout<<"\n5.EXIT\n";
		cout<<"select any option form the menu(1-5)";
		cin>>ch;
		switch(ch)
		{
			case '1':
				add_data();
				print();
				cin>>choice;
				if(choice=='1')
					goto main;
				else
					goto exit;
			case '2':
				view_file();
				print();
				cin>>choice;
				if(choice=='1')
					goto main;
				else
					goto exit;
			case '3':
				search();
				print();
				cin>>choice;
				if(choice=='1')
					goto main;
				else
					goto exit;
			case '4':
				remove();
				print();
				cin>>choice;
				if(choice=='1')
					goto main;
				else
					goto exit;
			case '5':
				goto exit;
		}
	exit:
		cout<<"\nTHANKYOU FOR USING THIS APPLICATION !!!\n";
		for(int k=0;k<200;k++)
		{
			//Time Delay for-loop
		}
	cin.ignore();
    cin.get();
}
//****************
void add_data()
{
	BILL a;
	char ch='y',c;
	ofstream fout("CONSUMER.DAT",ios::binary|ios::app);
	while((ch=='y')||(ch=='Y'))
	{
		a.get_sub_det();
		fout.write((char*)&a,sizeof(a));
		cout<<"\nDo you want printed Bill ? (Y/N) :";
		cin>>c;
		if((c=='Y')||(c=='y'))
		{
			a.disp(a.get_category());
		}
		cout<<"\nProcess Another Bill ? (Y/N) :";
		cin>>ch;
	}
	fout.close();
}
//****************
void view_file()
{
	BILL a;
	ifstream fin("CONSUMER.DAT",ios::binary);
	fin.seekg(0);
	cout<<"\nNo\tName\t\t\tCategory\tUnit\tAmount";
	cout<<"\n--\t----\t\t\t--------\t----\t------\n";
	while(fin.read((char*)&a,sizeof(a)))
	{
		a.cdisp();
		cout<<"\n";
	}
	fin.close();
}
//****************
void search()
{
	BILL a;
	ifstream fin("CONSUMER.DAT",ios::binary);
	int s,c;
	cout<<"\nEnter Subscriber Number to Display :\n";
	cin>>s;
	fin.seekg(0);
	while(fin.read((char*)&a,sizeof(a)))
	{
		if(s==a.get_sub_no())
		{
			cout<<"\nDisplaying Details of Subscriber Number : "<<s;
			c=1;
			a.disp(a.get_category());
		}
	}
	if(c!=1)
		cout<<"\nNo Such Data Available to Display !!!";
	fin.close();
}
//****************
void remove()
{
	BILL a;
	ifstream fin("CONSUMER.DAT",ios::binary);
	ofstream fout("temp.DAT",ios::binary);
	int n;
	char f='N';
	cout<<"\nEnter Subscriber Number to Delete :";
	cin>>n;
	fin.seekg(0);
	while(!fin.eof())
	{
		fin.read((char*)&a,sizeof(a));
		if(n==a.get_sub_no())
			f='Y';
		else
			fout.write((char*)&a,sizeof(a));
	}
	fin.close();
	fout.close();
	if(f=='Y')
		cout<<"\nDATA FOUND !";
	else
	{
		cout<<"\nDATA IS UNAVAILABLE !";
		f='U';
		goto abort;
	}
	char d;
	cout<<"Confirm Deletion ?(Y/N) :";
	cin>>d;
	if((d=='Y')||(d=='y'))
	{
		remove("CONSUMER.DAT");
		rename("temp.DAT","CONSUMER.DAT");
		cout<<"\nDeletion Successful !";
	}
	if((d=='N')||(d=='n'))
	{
		remove("temp.DAT");
		cout<<"\nDeletion Aborted by User !";
	}
	abort:
		if(f=='U')
			cout<<"\nABORTING DUE TO UNAVAILABLE DATA !";
}
//****************
void print()
{
	cout<<"\nPRESS 1 TO GO TO MAIN MENU";
	cout<<"\nPRESS 0 TO EXIT APPLICATION";
}


