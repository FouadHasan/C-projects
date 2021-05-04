#include<iostream>
#include<fstream>
using namespace std;

class car{
private:
	char model[10];
	int year,carId;
		
public:
	void create_car();
	void show_car();
	int  ret_carId();
};

class customer{
private:
	int custId, custCar;
	char name[50];
public:
	void create_customer();
	void show_customer();
	int ret_custId();
};

void add_car();
void add_customer();
void modify_customer();
void delete_customer();
void display_customer_sp();
void display_all_customer();
void display_all_car();
void display_car_sp(int n);
int main(void){
	
	char ch;
	while(1){
		cout<<"\nRental Car Management";
		cout<<"\n1.Add New customer";
		cout<<"\n2.Modify customer";
		cout<<"\n3.Display specific customer";
		cout<<"\n4.Display All Customer";
		cout<<"\n5.Delete Customer";
		cout<<"\n6.Add new cars";
		cout<<"\n7.Show all cars";
		cout<<"\n0.Quit";
		cout<<"\nSelect your choice :\n";
		
		cin>>ch;
		if (ch=='0') break;
		if (ch=='6'){ add_car();}	
		if (ch=='7'){ display_all_car();}
		if (ch=='1'){ add_customer();}
		if (ch=='2'){ modify_customer();}
		if (ch=='3'){ display_customer_sp();}
		if (ch=='4'){ display_all_customer();}
		if (ch=='5'){ delete_customer();}		
	}
	return 0;
}

void car::create_car(){	

	cout<<"\nEnter car ID :";
	cin>>carId;
	cout<<"\nEnter the car Model :";
	cin.ignore();
	cin.getline(model,10);
	cout<<"\nEnter the car Year :";	
	cin>>year;
}

void car::show_car(){	
	cout<<"\nCar Model :"<<model;
	cout<<"\nCar Year :"<<year;		
}

int car:: ret_carId(){
	return carId;
}

void customer:: create_customer(){
	cout<<"\nEnter customer name: ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nEnter customer ID :";
	cin>>custId;
	cout<<"\nEnter customer's selected car :";
	cin>>custCar;
}

void customer:: show_customer(){
	cout<<"\nCutomer name :"<<name;
	cout<<"\nCustomer ID :"<<custId;
	cout<<"\nCustomer's car :";
	display_car_sp(custCar);
}

int customer:: ret_custId(){
	return custId;
}

void add_car(){
	char ch;
	car mycar;
	fstream fp;
		fp.open("carlist.dat", ios::out|ios::app);
	do{
		mycar.create_car();
		fp.write((char * ) & mycar, sizeof(car));
		cout<<"\nAdd more cars ?(y/n)";
		cin>>ch;
	}while(ch=='y'|ch=='Y');

	fp.close();
	cout<<"\nCar has been created\n=================\n";
	cin.get();	
}

void display_all_car(){
	
	cout<<"\nDisplaying all Available cars";
	fstream fp;
	car mycar;
	fp.open("carlist.dat", ios::in);
	cout<<"\nList of cars";
	while(fp.read((char * ) & mycar, sizeof(car))){
	
		cout<<"\n-----------";
		mycar.show_car();			
	}
	
	cout<<"\n=================\n";
	fp.close();
	cin.get();
}

void display_car_sp(int n){
	fstream fp;
	car mycar;
	fp.open("carlist.dat", ios::in);
	
	while(fp.read((char*)& mycar, sizeof(car))){
		
		if (mycar.ret_carId()==n){
			
			mycar.show_car();
		}		
	}
	cout<<"\n=================\n";
	fp.close();
	cin.get();
}

void add_customer(){	
	char ch;
	fstream fp;
	customer cust;
	fp.open("customer.dat", ios::out|ios::app);
	do{
		cust.create_customer();
		fp.write((char * ) & cust,sizeof(customer));
		cout<<"\nAdd more customer ?(y/n)";
		cin>>ch;
	}while(ch=='y'|ch=='Y');

	fp.close();
	cout<<"\nCustomer is created\n=================\n";
	cin.get();
}

void display_all_customer(){
	
	cout<<"\nDisplaying the List of customers";
	fstream fp;
	customer cust;
	fp.open("customer.dat", ios::in);
	
	while(fp.read((char*) &cust, sizeof(customer))){
		
		cout<<"\n-----------------";
		cust.show_customer();	
	}
	cout<<"\n=================";
	fp.close();
	cin.get();				
}

void display_customer_sp(){
	int n;
	fstream fp;
	customer cust;
	cout<<"\nDispalying Customer Record"<<"\n Enter the customer ID :";
	cin>>n;
	fp.open("customer.dat", ios::in);
	
	while(fp.read((char*)& cust, sizeof(customer))){
		
		if (cust.ret_custId()==n){
			
			cust.show_customer();
		}		
	}
	cout<<"\n=================\n";
	fp.close();
	cin.get();
}

void delete_customer(){
	
	int n;
	fstream fp, fp2;
	customer cust;
	
	cout<<"\nDeleting record"<<"\nEnter the customer ID :";
	cin>>n;
	
	fp.open("customer.dat", ios::in);
	fp2.open("temp.dat",ios::out);
	
	fp.seekg(0,ios::beg);
	
	while(fp.read((char*)& cust, sizeof(customer))){
		
		if (cust.ret_custId()!=n){
			
			fp2.write((char*)& cust, sizeof(customer));
		}
		
		fp.close();
		fp2.close();
		
		remove("customer.dat");
		rename("temp.dat","customer.dat");
		
		cout<<"\ncustomer record deleted";
		cin.get();
	}
}

void modify_customer(){
	
	int n;
	fstream fp;
	customer cust;
	
	cout<<"\nModifying customer record"<<"\nEnter the customer ID :";
	cin>>n;
	
	fp.open("customer.dat", ios::in|ios::out);
	
	while(fp.read((char*)& cust, sizeof(customer))){
		
		if (cust.ret_custId()==n){
			
			cust.show_customer();
			cout<<"\n\nEnter the new details of the customer";
			
			cust.create_customer();
			int pos=(-1)*static_cast<int>(sizeof(cust));
			fp.seekp(pos,ios::cur);
			fp.write((char * ) & cust, sizeof(customer));
		}
	}	
	fp.close();
	cin.get();	
}

 