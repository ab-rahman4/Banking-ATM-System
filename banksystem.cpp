
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class Person
{
protected:
    string name;

public:
    void setname(string n) { name = n; }
    string getname() { return name; }
};

class User
{
protected:
    string address;

public:
    void setaddress(string a) { address = a; }
    string getaddress() { return address; }
};

class Account : public Person, public User
{
protected:
    int id;
    int pin;
    int balance;

public:
    void setbalance(int balance) { this->balance = balance; }
    int getbalance() { return balance; }
    virtual void setpin(int pin) { this->pin = pin; }
    virtual int getpin() { return pin; }
    virtual void setid(int id) { this->id = id; }
    virtual int getid() { return id; }
    static int totalusers;
    static int totalbalance;
};

class Banker : public Account
{
public:
    void setid(int id) override { this->id = id; }
    int getid() override { return id; }
    void setpin(int pin) override { this->pin = pin; }
    int getpin() override { return pin; }
};

const int MAX_USERS = 1000;
int Account::totalusers = 0;
Account *acc = new Account[MAX_USERS];
int Account::totalbalance = 0;
Banker exective[4];

void displayline()
{
    cout << "-----------------------------------------------------\n";
}

void readdata()
{
    ifstream f1("usersdata.txt");
    if (!f1.is_open())
    {
        cout << "THE FILE FAILED TO OPEN.\n";
        return;
    }
    string line;
    int i = 0;
    while (getline(f1, line) && i < MAX_USERS)
    {
        stringstream ss(line);
        string id_str, pin_str, balance_str, name_str, address_str;

        getline(ss, id_str, ',');
        acc[i].setid(stoi(id_str));
        getline(ss, pin_str, ',');
        acc[i].setpin(stoi(pin_str));
        getline(ss, balance_str, ',');
        acc[i].setbalance(stoi(balance_str));
        Account::totalbalance += stoi(balance_str);
        getline(ss, name_str, ',');
        acc[i].setname(name_str);

        getline(ss, address_str);
        acc[i].setaddress(address_str);
        i++;
    }
    Account::totalusers = i;
    f1.close();
}

void displayaccountinfo(int i)
{
    displayline();
    cout << "\n- ID : " << acc[i].getid();
    cout << "\n- NAME : " << acc[i].getname();
    cout << "\n- BALANCE : " << acc[i].getbalance();
    cout << "\n- ADDRESS : " << acc[i].getaddress() << "\n";
    displayline();
}

void checkvalidity()
{
    displayline();
    cout << "           ENTER THE ACCOUNT INFORMATION\n";
    displayline();
    cout << "- ENTER THE ID : ";
    int idtocheck;
    cin >> idtocheck;
    bool found = false;
    for (int i = 0; i < Account::totalusers; i++)
    {
        if (acc[i].getid() == idtocheck)
        {
            found = true;
            cout << "\n- ENTER THE PIN : ";
            int pintocheck;
            cin >> pintocheck;
            if (acc[i].getpin() == pintocheck)
            {
                displayaccountinfo(i);
            }
            else
            {
                cout << "- THE PIN DOESN'T MATCH.\n";
            }
            break;
        }
    }
    if (!found)
    {
        cout << "SUCH ID DOESN'T EXIST.\n";
    }
}

void displaymenu1()
{
    displayline();
    cout << "               BANK MANAGEMENT SYSTEM\n";
    displayline();
    cout << "1- BANKING SYSTEM \n";
    cout << "2- ATM SYSTEM \n";
    cout << "3- EXIT\n";
    displayline();
    cout << "CHOOSE THE OPTION: ";
}

void displaybankingmenu()
{
    displayline();
    cout << "1- CHECK ACCOUNT INFORMATION\n";
    cout << "2- CREATE AN ACCOUNT\n";
    cout << "3- DELETE ACCOUNT\n";
    cout << "4- EXTERNAL INFORMATION (OFFICIALS ONLY)\n";
    cout << "5- GO BACK\n";
    displayline();
    cout << "CHOOSE THE OPTION: ";
}

void createaccount()
{
    displayline();
    cout << "\n             WELCOME TO OUR BANK         \n";
    cout << "\nFILL THE FOLLOWING DETAIL.\n";
    if (Account::totalusers == MAX_USERS)
    {
        cout << "\nNO SPACE FOR NEW ACCOUNTS.";
    }
    else
    {
        cout << "\nYOUR ID WILL BE : " << Account::totalusers + 1 << endl;
        int idfornewaccount = Account::totalusers;

        cout << "ENTER THE NAME : ";
        string namefornewacc;
        cin.ignore();
        getline(cin, namefornewacc);

        cout << "\nENTER THE PIN : ";
        int pinfornewaccount;
        cin >> pinfornewaccount;
        while (pinfornewaccount < 0)
        {
            cout << "\nNEGATIVE VALUES ARE NOT ALLOWED IN PIN.";
            cout << "\nENTER PIN AGAIN : ";
            cin >> pinfornewaccount;
        }

        cout << "ENTER THE AMOUNT YOU WANT TO DEPOSIT : ";
        int balancefornewaccount;
        cin >> balancefornewaccount;
        while (balancefornewaccount <= 0)
        {
            cout << "ENTER THE VALID AMOUNT : ";
            cin >> balancefornewaccount;
        }
        Account::totalbalance += balancefornewaccount;

        cout << "\nENTER THE ADDRESS : ";
        string addressfornewaccount;
        cin.ignore();
        getline(cin, addressfornewaccount);

        acc[idfornewaccount].setid(idfornewaccount + 1);
        acc[idfornewaccount].setpin(pinfornewaccount);
        acc[idfornewaccount].setbalance(balancefornewaccount);
        acc[idfornewaccount].setname(namefornewacc);
        acc[idfornewaccount].setaddress(addressfornewaccount);

        Account::totalusers++;

        ofstream f1("usersdata.txt", ios::app);
        if (f1.is_open())
        {
            f1 << acc[idfornewaccount].getid() << ","
               << acc[idfornewaccount].getpin() << ","
               << acc[idfornewaccount].getbalance() << ","
               << acc[idfornewaccount].getname() << ","
               << acc[idfornewaccount].getaddress() << "\n";
            f1.close();
            cout << "\n";
            displayline();
            cout << "THANKS FOR CHOOSING OUR BANK.\n";
        }
    }
}

void writedata()
{
    ofstream f2("usersdata.txt");
    if (!f2.is_open())
    {
        cout << "THE FILE FAILED TO OPEN.\n";
        return;
    }
    for (int j = 0; j < Account::totalusers; j++)
    {
        f2 << acc[j].getid() << ","
           << acc[j].getpin() << ","
           << acc[j].getbalance() << ","
           << acc[j].getname() << ","
           << acc[j].getaddress() << "\n";
    }
    f2.close();
}

void deleteaccount()
{
    displayline();
    cout << "DISCLAIMER! THE DELETED ACCOUNTS CAN'T BE RETRIEVED AGAIN.\n";
    displayline();
    cout << "ENTER THE ID : ";
    int idtodelete;
    cin >> idtodelete;

    for (int i = 0; i < Account::totalusers; i++)
    {
        if (acc[i].getid() == idtodelete)
        {
            cout << "ENTER THE PIN : ";
            int pintodelete;
            cin >> pintodelete;
            if (acc[i].getpin() == pintodelete)
            {
                Account::totalbalance -= acc[i].getbalance();
                for (int K = i; K < Account::totalusers - 1; K++)
                {
                    acc[K] = acc[K + 1];
                }
                Account::totalusers--;
                writedata();
                cout << endl;
                displayline();
                cout << "THE ACCOUNT IS SUCCESSFULLY DELETED.\n";
            }
            else
            {
                cout << "- THE PIN DOESN'T MATCH.\n";
            }
            break;
        }
    }
}

void displayexternalinfo()
{
    cout << "                WELCOME  \n";
    cout << "\nALL BANK DETAILS ARE AS FOLLOWING :\n";
    displayline();
    cout << "\nTOTAL ACCOUNT HOLDERS : " << Account::totalusers;
    cout << "\nTOTAL BALANCE IN VAULT : " << Account::totalbalance << endl;
    displayline();
    for (int i = 0; i < Account::totalusers; i++)
    {
        displayline();
        cout << "                ACCOUNTHOLDER " << i + 1 << endl;
        displayline();
        cout << "ID : " << acc[i].getid();
        cout << "\nNAME : " << acc[i].getname();
        cout << "\nBALANCE : " << acc[i].getbalance();
        cout << "\nADDRESS : " << acc[i].getaddress();
        cout << endl;
    }
}

void externalinfo()
{
    displayline();
    cout << "             THIS IS ONLY FOR EXECUTIVES.";
    cout << "\nENTER THE ID : ";
    int idtocheck;
    cin >> idtocheck;
    cout << "\nENTER THE PIN : ";
    int pintocheck;
    cin >> pintocheck;

    ifstream exe("executivesdata.txt");
    if (!exe.is_open())
    {
        cout << "THE FILE FAILED TO OPEN.\n";
        return;
    }

    string line;
    int i = 0;
    while (getline(exe, line) && i < 4)
    {
        stringstream ss(line);
        string id_str, pin_str;
        getline(ss, id_str, ',');
        exective[i].setid(stoi(id_str));
        getline(ss, pin_str);
        exective[i].setpin(stoi(pin_str));
        i++;
    }
    exe.close();

    bool valid = false;
    for (int j = 0; j < 4; j++)
    {
        if (exective[j].getid() == idtocheck && exective[j].getpin() == pintocheck)
        {
            valid = true;
            break;
        }
    }

    if (!valid)
    {
        cout << "\nACCESS DENIED. INVALID EXECUTIVE CREDENTIALS.\n";
        return;
    }

    displayline();
    displayexternalinfo();
    displayline();
}
void atmmenu()
{
    displayline();
    cout << "\nCHOOSE ANY OF THE FOLLOWING.\n";
    cout << "1- WITHDRAW MONEY\n";
    cout << "2- DEPOSIT MONEY\n";
    cout << "3- CHECK BALANCE\n";
    cout << "4- GO BACK\n\n";
}
void withdrawmoney()
{
    displayline();
    cout << "\n- ENTER THE ID : ";
    int idforatm = 0;
    cin >> idforatm;
    bool found = false;
    for (int i = 0; i < Account::totalusers; i++)
    {
        if (acc[i].getid() == idforatm)
        {
            found = true;
            cout << "\nENTER THE PIN : ";
            int pinforatm = 0;
            cin >> pinforatm;
            if (acc[i].getpin() == pinforatm)
            {
                displayline();
                cout << "\n               LOGIN SUCCESSFUL\n";
                displayline();
                cout << "ENTER THE AMOUNT OF MONEY YOU WANT TO WITHDRAW : ";
                int withdrawamount = 0;
                cin >> withdrawamount;
                while (withdrawamount <= 0 || withdrawamount > acc[i].getbalance())
                {
                    if (withdrawamount <= 0)
                    {
                        cout << "\nTHE ENTERED AMOUNT ISNT VALID.TRY AGAIN : ";
                    }
                    else
                    {
                        cout << "\nNOT ENOUGH MONEY IN THE ACCOUNT : ";
                    }
                    cin >> withdrawamount;
                }
                acc[i].setbalance(acc[i].getbalance() - withdrawamount);

                Account ::totalbalance = Account ::totalbalance - withdrawamount;
                writedata();
                displayline();
                cout << "\nREMAINING BALANCE IN YOUR ACCOUNT : " << acc[i].getbalance();
                cout << "\n\n               TRANSACTION COMPLETED\n\n";
            }
            else
            {
                cout << "\nYOU ENTERED THE WRONG PIN.";
                break;
            }
        }
    }
    if (!found)
    {
        cout << "\nWRONG ID ENTERED. ";
        return;
    }
}
void depositmoney(){
displayline();
    cout << "\n- ENTER THE ID : ";
    int idfordep = 0;
    cin >> idfordep;
    bool found = false;
    for (int i = 0; i < Account::totalusers; i++)
    {
        if (acc[i].getid() == idfordep)
        {
            found = true;
            cout << "\nENTER THE PIN : ";
            int pinfordep = 0;
            cin >> pinfordep;
            if (acc[i].getpin() == pinfordep)
            {
                displayline();
                cout << "\n               LOGIN SUCCESSFUL\n";
                displayline();
                cout << "ENTER THE AMOUNT OF MONEY YOU WANT TO DEPOSIT : ";
                int depositamount = 0;
                cin >> depositamount;
                while (depositamount <= 0 )
                {
                    if (depositamount <= 0)
                    {
                        cout << "\nTHE ENTERED AMOUNT ISNT VALID.TRY AGAIN : ";
                    }
                    else
                    {
                        cout << "\nNOT ENOUGH MONEY IN THE ACCOUNT : ";
                    }
                    cin >> depositamount;
                }
                acc[i].setbalance(acc[i].getbalance() + depositamount);

                Account ::totalbalance = Account ::totalbalance + depositamount;
                writedata();
                displayline();
                cout << "\nCURRENT BALANCE IN YOUR ACCOUNT : " << acc[i].getbalance();
                cout << "\n\n               TRANSACTION COMPLETED\n\n";
            }
            else
            {
                cout << "\nYOU ENTERED THE WRONG PIN.";
                break;
            }
        }
    }
    if (!found)
    {
        cout << "\nWRONG ID ENTERED. ";
    }
}
void showbalance(){
    displayline();
    cout << "           ENTER THE ACCOUNT INFORMATION\n";
    displayline();
    cout << "- ENTER THE ID : ";
    int idtocheck;
    cin >> idtocheck;
    bool found = false;
    for (int i = 0; i < Account::totalusers; i++)
    {
        if (acc[i].getid() == idtocheck)
        {
            found = true;
            cout << "\n- ENTER THE PIN : ";
            int pintocheck;
            cin >> pintocheck;
            if (acc[i].getpin() == pintocheck)
            {
                displayline();
                cout<<"\nTHE TOTAL BALANCE IN YOUR ACCOUNT IS : " <<acc[i].getbalance();   
            }
            else
            {
                cout << "- THE PIN DOESN'T MATCH.\n";
            }
            break;
        }
    }
    if (!found)
    {
        cout << "SUCH ID DOESN'T EXIST.\n";
    }
    
}
int main()
{
    readdata();
    while (true)
    {
        displaymenu1();
        int chooseoption;
        cin >> chooseoption;
        while (chooseoption <= 0 || chooseoption > 3)
        {
            cout << "YOU ENTERED THE WRONG VALUE. TRY AGAIN: ";
            cin >> chooseoption;
        }

        if (chooseoption == 3)
            break;

        if (chooseoption == 1)
        {
            int choosebankingopt;
            while (true)
            {
                displaybankingmenu();
                cin >> choosebankingopt;
                while (choosebankingopt <= 0 || choosebankingopt > 5)
                {
                    cout << "YOU ENTERED THE WRONG VALUE. TRY AGAIN: ";
                    cin >> choosebankingopt;
                }

                if (choosebankingopt == 5)
                    break;
                if (choosebankingopt == 1)
                    checkvalidity();
                if (choosebankingopt == 2)
                    createaccount();
                if (choosebankingopt == 3)
                    deleteaccount();
                if (choosebankingopt == 4)
                    externalinfo();
            }
        }
        if (chooseoption == 2)
{
    int chooseforatm = 0;
    while (true)
    {
        atmmenu();
        cin >> chooseforatm;
        while (chooseforatm <= 0 || chooseforatm > 4)
        {
            cout << "INVALID OPTION SELECTED. PLEASE TRY AGAIN: ";
            cin >> chooseforatm;
        }
        if (chooseforatm == 4)
            break;
        if (chooseforatm == 1)
            withdrawmoney();
        if (chooseforatm == 2)
            depositmoney();
        if (chooseforatm == 3)
            showbalance();
    }
}

    }

    delete[] acc;
    return 0;
}
