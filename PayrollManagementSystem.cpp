#include <iostream>
#include <fstream>
using namespace std;

class employee
{
private :
    int   code, dd, mm, yy ;
    char  name[50], address[50], phone[50], desig[50] ;
    char  grade;
    float loan, basic ;
public :
    void create_employee();
    void show_employee(); 
    int EmployeeCode();
} ;

void add_employee();
void modify_employee(); 
void display_all() ;
void display_sp();
void delete_employee();

fstream fp;
employee em;

// MAIN FUNCTION CALLING MAIN MENU
int main(void)
{
 char ch ;
    while (1)
    {
        cout <<"PAYROLL MANAGEMENT SYSTEM" ;
        cout <<"\n1: New Employee" ;
        cout <<"\n2: Modify Employee" ;
        cout <<"\n3: Display All Employee" ;
        cout <<"\n4: Display Specific Employee" ;
        cout <<"\n5: Delete Employee" ;
        cout <<"\n0: QUIT" ;
        cout <<"\n\nENTER YOUR CHOICE :" ;

        cin>>ch ;
        if (ch == '0') break ;
        else if (ch == '1')
        { add_employee();}
        else if (ch == '2')
        { modify_employee();}
        else if (ch == '3')
        { display_all();}
        else if (ch == '4')
        { display_sp();}
        else if (ch == '5')
        {delete_employee();}
    }
}

// THIS FUNCTION GIVE DATA TO ADD IN THE FILE  1
void employee :: create_employee()
{
    cout <<"\nEnter the Employee Code # " ;
    cin>>code;
    cout <<"\nEnter the name of the Employee" ;
    cin.ignore();//use this line only once. no before every string input
    cin.getline(name,50);
    cout <<"\nEnter Address of the Employee" ;
    cin.getline(address,50);
    cout <<"\nEnter Phone no. of the Employee" ;
    cin.getline(phone,50);
}
void employee::show_employee() 
{
    cout << "\nEmployee Code # :" << code;
    cout << "\nEmployee name :"<<name;
    cout << "\nAddress of the Employee :" << address;
    cout << "\nPhone no. of the Employee :" << phone;
}

int employee::EmployeeCode() 
{  return code;}

// function to write in file
void add_employee() 
{  
    fp.open("employee.dat", ios::out | ios::app);
    em.create_employee();
    fp.write((char * ) & em, sizeof(employee));
    fp.close();
    cout << "\nThe Employee Has Been Created ";
	//cin.ignore();
    cin.get();
}

// function to modify record of file
void modify_employee() 
{
    int no, found = 0;
    cout << "\nModify Record"<<"\nPlease Enter The Employee No";
    cin >> no;
    fp.open("employee.dat", ios:: in | ios::out);
    while (fp.read((char * ) & em, sizeof(employee)) && found == 0) 
    {
        if (em.EmployeeCode() == no) 
        {
            em.show_employee();
            cout << "\n\nPlease Enter The New Details of Product" << endl;
            em.create_employee();
            int pos=(-1)*static_cast<int>(sizeof(em));
            fp.seekp(pos, ios::cur);      // 'pos' bytes back from current position (seek get and seek put)
            fp.write((char * ) & em, sizeof(employee));
            cout << "\nRecord Updated";
            found = 1;
        }
    }
    fp.close();
    if (found == 0)
        cout << "\nRecord Not Found ";
    	//cin.ignore();
        cin.get();
}

// function to read all records from file
void display_all() 
{

    cout << "\nDisplaying All Employee Record :";
    fp.open("employee.dat", ios:: in );
    while (fp.read((char * ) & em, sizeof(employee))) 
    {
        cout << "\n====================================";
        em.show_employee();
        
    }
    cout << "\n\nAll Employee Records Shown\n\n";
    fp.close();
	//cin.ignore();
    cin.get();
}

// function to read specific record from file
void display_sp() 
{ 
    int n;

    int flag = 0;
    cout << "\nDisplay Record";
    cout<<"\nEnter the employee code:";
    cin>>n;
    fp.open("employee.dat", ios:: in );
    while (fp.read((char * ) & em, sizeof(employee))) 
    {
        if (em.EmployeeCode() == n) 
        {
            em.show_employee();
            flag = 1;
        }
    }
    fp.close();
    if (flag == 0)
        cout << "\nrecord not exist";
	//cin.ignore();
    cin.get();
    cout<<"\n\n";
}

// function to delete record of file
void delete_employee() 
{
    int no;
    fstream fp2;
    cout << "\nDelete Record";
    cout << "\nPlease Enter The Employee code :";
    cin >> no;
    fp.open("employee.dat", ios:: in | ios::out);
    fp2.open("Temp.dat", ios::out);
    fp.seekg(0, ios::beg);
    while (fp.read((char * ) & em, sizeof(employee))) 
    {
        if (em.EmployeeCode() != no) 
        {
            fp2.write((char * ) & em, sizeof(employee));
        }
    }
    fp2.close();
    fp.close();
    remove("employee.dat");
    rename("Temp.dat", "employee.dat");
    cout << "\nRecord Deleted\n\n";
    //cin.ignore();
    cin.get();
}