#include<fstream>
#include<iostream>
using namespace std;

// CLASS USED IN PROJECT
class product 
{
    int pno;
    char name[50];
    float price, qty, tax, dis;
public:
    void create_product();
    void show_product();
    int retpno(); 
    float retprice();
    char * retname(); 
    int retdis();
}; //class ends here

void product::create_product()
{
    cout << "\nPlease Enter The Product No. of The Product ";
    cin >> pno;
    cout << "\nPlease Enter The Name of The Product ";
    cin.ignore();
	cin.getline(name,50);
    cout << "\nPlease Enter The Price of The Product ";
    cin >> price;
    cout << "\nPlease Enter The Discount (%) ";
    cin >> dis;
}
void product::show_product() 
{
    cout << "\nThe Product No. of The Product : " << pno;
    cout << "\nThe Name of The Product : "<<name;
    cout << "\nThe Price of The Product : " << price;
    cout << "\nDiscount : " << dis;
}
int product::retpno() 
{
    return pno;
}

float product::retprice() 
{
    return price;
}

char* product::retname() 
{
    return name;
}

int product::retdis() 
{
    return dis;
}

// global declaration for stream object, object
fstream fp;
product pr;

// function to write in file
void write_product() 
{
    fp.open("Shop.dat", ios::out | ios::app);
    pr.create_product();
    fp.write((char * ) & pr, sizeof(product));
    fp.close();
    cout << "\n\nThe Product Has Been Created ";
	cin.ignore();
    cin.get();
}

// function to read all records from file
void display_all() 
{
    //clrscr();
    cout << "\nDISPLAY ALL RECORD !!!";
    fp.open("Shop.dat", ios:: in );
    while (fp.read((char * ) & pr, sizeof(product))) 
    {
        pr.show_product();
        cout << "\n====================================";
        cin.ignore();
        cin.get();
    }
    fp.close();
	cin.ignore();
    cin.get();;
}

// function to read specific record from file
void display_sp(int n) 
{
    int flag = 0;
    fp.open("Shop.dat", ios:: in );
    while (fp.read((char * ) & pr, sizeof(product))) 
    {
        if (pr.retpno() == n) 
        {
            pr.show_product();
            flag = 1;
        }
    }
    fp.close();
    if (flag == 0)
        cout << "\nrecord not exist";
    	cin.ignore();
        cin.get();
}

// function to modify record of file
void modify_product() 
{
    int no, found = 0;
    cout << "\nTo Modify ";
    cout << "\nPlease Enter The Product No. of The Product";
    cin >> no;
    fp.open("Shop.dat", ios:: in | ios::out);
    while (fp.read((char * ) & pr, sizeof(product)) && found == 0) 
    {
        if (pr.retpno() == no) 
        {
            pr.show_product();
            cout << "\nPlease Enter The New Details of Product" << endl;
            pr.create_product();
            //int pos = -1 * sizeof(pr);
            int pos=(-1)*static_cast<int>(sizeof(pr));
            fp.seekp(pos, ios::cur);      // 'pos' bytes back from current position (seek get and seek put)
            fp.write((char * ) & pr, sizeof(product));
            cout << "\n Record Updated";
            found = 1;
        }
    }
    fp.close();
    if (found == 0)
        cout << "\nRecord Not Found ";
    	cin.ignore();
        cin.get();
}

// function to delete record of file
void delete_product() 
{
    int no;
    cout << "\nDelete Record";
    cout << "\nPlease Enter The product no. of The Product You Want To Delete";
    cin >> no;
    fp.open("Shop.dat", ios:: in | ios::out);
    fstream fp2;
    fp2.open("Temp.dat", ios::out);
    fp.seekg(0, ios::beg);
    while (fp.read((char * ) & pr, sizeof(product))) 
    {
        if (pr.retpno() != no) 
        {
            fp2.write((char * ) & pr, sizeof(product));
        }
    }
    fp2.close();
    fp.close();
    remove("Shop.dat");
    rename("Temp.dat", "Shop.dat");
    cout << "\nRecord Deleted ..";
    cin.ignore();
    cin.get();
}

// function to display all products price list
void menu() 
{
    fp.open("Shop.dat", ios:: in );
    if (!fp) 
    {
        cout << "\nERROR!!! FILE COULD NOT BE OPEN. Go To Admin Menu to create File ";
        cout << "\n Program is closing ....";
        cin.ignore();
        cin.get();
        exit(0);
    }

    cout << "\nProduct MENU";
    cout << "\n====================================================";
    cout << "\nP.NO.\t\tNAME\t\tPRICE\n";
    cout << "====================================================\n";

    while (fp.read((char * ) & pr, sizeof(product))) 
    {
        cout << pr.retpno() << "\t\t" << pr.retname() << "\t\t" << pr.retprice() << endl;
    }
    fp.close();
}

// function to place order and generating bill for Products
void place_order() 
{
    int order_arr[50], quan[50], c = 0;
    float amt, damt, total = 0;
    char ch = 'Y';
    menu();
    cout << "\n============================";
    cout << "\n PLACE YOUR ORDER";
    cout << "\n============================";
    do 
    {
        cout << "\nEnter The Product No. Of The Product : ";
        cin >> order_arr[c];
        cout << "\nQuantity in number : ";
        cin >> quan[c];
        c++;
        cout << "\nDo You Want To Order Another Product ? (y/n)";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    cout << "\nThank You For Placing The Order";
	cin.ignore();
    cin.get();
    cout << "\n******************************** INVOICE ************************";
    cout << "\nPr No.\tPr Name\tQuantity \tPrice \tAmount \tAmount after discount\n ";
    for (int x = 0; x <= c; x++) 
    {
        fp.open("Shop.dat", ios::     in );
        fp.read((char * ) & pr, sizeof(product));
        while (!fp.eof()) 
        {
            if (pr.retpno() == order_arr[x]) 
            {
                amt = pr.retprice() * quan[x];
                damt = amt - (amt * pr.retdis())/100;
                cout << "\n" << order_arr[x] << "\t" << pr.retname() <<
                    "\t" << quan[x] << "\t\t" << pr.retprice() << "\t" << amt << "\t\t" << damt;
                total += damt;
            }
            fp.read((char * ) & pr, sizeof(product));
        }

        fp.close();
    }
    cout << "\nTOTAL = " << total;
    cin.ignore();
    cin.get();
}   

// INTRODUCTION FUNCTION
void intro() 
{  
    cout << "SUPER MARKET BILLING PROJECT";
    cout << "\nFouad Hasan";
    cout << "\nBUET";
    //cin.ignore();
    cin.get();          
}

// ADMINSTRATOR MENU FUNCTION
void admin_menu() 
{
    char ch2;
    cout << "\nADMIN MENU";
    cout << "\n1.CREATE PRODUCT";
    cout << "\n2.DISPLAY ALL PRODUCTS";
    cout << "\n3.QUERY ";
    cout << "\n4.MODIFY PRODUCT";
    cout << "\n5.DELETE PRODUCT";
    cout << "\n6.VIEW PRODUCT MENU";
    cout << "\n7.BACK TO MAIN MENU";
    cout << "\nPlease Enter Your Choice (1-7) ";
    cin>>ch2;
    switch (ch2) 
    {
    case '1':
        write_product();break;
    case '2':
        display_all();break;
    case '3':
        int num;
        cout << "\nPlease Enter The Product No. ";
        cin >> num;
        display_sp(num);
        break;
    case '4':
        modify_product(); break;
    case '5':
        delete_product(); break;
    case '6':
        menu();
        cin.ignore();
        cin.get();
    case '7':
        break;
    default:
        cout << "\a";
        admin_menu();
    }
}

// THE MAIN FUNCTION OF PROGRAM
int main() 
{
    char ch;
    intro();
    do 
    {
        cout << "\nMAIN MENU";
        cout << "\n01. CUSTOMER";
        cout << "\n02. ADMINISTRATOR";
        cout << "\n03. EXIT";
        cout << "\nPlease Select Your Option (1-3) ";
        cin>>ch;
        switch (ch) 
        {
        case '1':
            place_order(); 	cin.ignore();cin.get(); break;
        case '2':
            admin_menu();break;
        case '3':
            exit(0);
        default:
            cout << "\a";
        }
    } while (ch != '3');
}
