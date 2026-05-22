#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class BankAccount
{
private:
    int accountNumber;
    string name;
    float balance;

public:

    bool accountExists(int searchAccNo)
    {
        ifstream file("accounts.txt");

        int accNo;
        string accName;
        float accBalance;

        while (file >> accNo)
        {
            file.ignore();

            getline(file, accName);

            file >> accBalance;

            if (accNo == searchAccNo)
            {
                file.close();
                return true;
            }
        }

        file.close();
        return false;
    }

    void createAccount()
    {
        cout << "Enter Account Number: ";
        cin >> accountNumber;

        if (accountExists(accountNumber))
        {
            cout << "\nAccount Number Already Exists!" << endl;
            return;
        }

        cin.ignore();

        cout << "Enter Account Holder Name: ";
        getline(cin, name);

        cout << "Enter Initial Balance: ";
        cin >> balance;

        ofstream file("accounts.txt", ios::app);

        file << accountNumber << endl;
        file << name << endl;
        file << balance << endl;

        file.close();

        cout << "\nAccount Created Successfully!" << endl;
    }

    void displayAllAccounts()
    {
        ifstream file("accounts.txt");

        int accNo;
        string accName;
        float accBalance;

        cout << "\n========== ALL ACCOUNTS ==========\n" << endl;

        while (file >> accNo)
        {
            file.ignore();

            getline(file, accName);

            file >> accBalance;

            cout << "Account Number : " << accNo << endl;
            cout << "Account Holder : " << accName << endl;
            cout << "Balance        : " << accBalance << endl;

            cout << "----------------------------------" << endl;
        }

        file.close();
    }

    void searchAccount()
    {
        int searchAccNo;

        cout << "Enter Account Number to Search: ";
        cin >> searchAccNo;

        ifstream file("accounts.txt");

        int accNo;
        string accName;
        float accBalance;

        bool found = false;

        while (file >> accNo)
        {
            file.ignore();

            getline(file, accName);

            file >> accBalance;

            if (accNo == searchAccNo)
            {
                cout << "\n========== ACCOUNT FOUND ==========" << endl;

                cout << "Account Number : " << accNo << endl;
                cout << "Account Holder : " << accName << endl;
                cout << "Balance        : " << accBalance << endl;

                found = true;
                break;
            }
        }

        if (!found)
        {
            cout << "\nAccount Not Found!" << endl;
        }

        file.close();
    }

    void depositMoney()
    {
        int searchAccNo;
        float depositAmount;

        cout << "Enter Account Number: ";
        cin >> searchAccNo;

        cout << "Enter Amount to Deposit: ";
        cin >> depositAmount;

        ifstream file("accounts.txt");
        ofstream tempFile("temp.txt");

        int accNo;
        string accName;
        float accBalance;

        bool found = false;

        while (file >> accNo)
        {
            file.ignore();

            getline(file, accName);

            file >> accBalance;

            if (accNo == searchAccNo)
            {
                accBalance += depositAmount;

                found = true;

                cout << "\nAmount Deposited Successfully!" << endl;
            }

            tempFile << accNo << endl;
            tempFile << accName << endl;
            tempFile << accBalance << endl;
        }

        file.close();
        tempFile.close();

        remove("accounts.txt");
        rename("temp.txt", "accounts.txt");

        if (!found)
        {
            cout << "\nAccount Not Found!" << endl;
        }
    }

    void withdrawMoney()
    {
        int searchAccNo;
        float withdrawAmount;

        cout << "Enter Account Number: ";
        cin >> searchAccNo;

        cout << "Enter Amount to Withdraw: ";
        cin >> withdrawAmount;

        ifstream file("accounts.txt");
        ofstream tempFile("temp.txt");

        int accNo;
        string accName;
        float accBalance;

        bool found = false;

        while (file >> accNo)
        {
            file.ignore();

            getline(file, accName);

            file >> accBalance;

            if (accNo == searchAccNo)
            {
                if (withdrawAmount <= accBalance)
                {
                    accBalance -= withdrawAmount;

                    cout << "\nWithdrawal Successful!" << endl;
                }
                else
                {
                    cout << "\nInsufficient Balance!" << endl;
                }

                found = true;
            }

            tempFile << accNo << endl;
            tempFile << accName << endl;
            tempFile << accBalance << endl;
        }

        file.close();
        tempFile.close();

        remove("accounts.txt");
        rename("temp.txt", "accounts.txt");

        if (!found)
        {
            cout << "\nAccount Not Found!" << endl;
        }
    }

    void updateAccount()
    {
        int searchAccNo;

        cout << "Enter Account Number to Update: ";
        cin >> searchAccNo;

        ifstream file("accounts.txt");
        ofstream tempFile("temp.txt");

        int accNo;
        string accName;
        float accBalance;

        bool found = false;

        while (file >> accNo)
        {
            file.ignore();

            getline(file, accName);

            file >> accBalance;

            if (accNo == searchAccNo)
            {
                found = true;

                cin.ignore();

                cout << "\nEnter New Account Holder Name: ";
                getline(cin, accName);

                cout << "Enter New Balance: ";
                cin >> accBalance;

                cout << "\nAccount Updated Successfully!" << endl;
            }

            tempFile << accNo << endl;
            tempFile << accName << endl;
            tempFile << accBalance << endl;
        }

        file.close();
        tempFile.close();

        remove("accounts.txt");
        rename("temp.txt", "accounts.txt");

        if (!found)
        {
            cout << "\nAccount Not Found!" << endl;
        }
    }

    void deleteAccount()
    {
        int searchAccNo;

        cout << "Enter Account Number to Delete: ";
        cin >> searchAccNo;

        ifstream file("accounts.txt");
        ofstream tempFile("temp.txt");

        int accNo;
        string accName;
        float accBalance;

        bool found = false;

        while (file >> accNo)
        {
            file.ignore();

            getline(file, accName);

            file >> accBalance;

            if (accNo == searchAccNo)
            {
                found = true;

                cout << "\nAccount Deleted Successfully!" << endl;

                continue;
            }

            tempFile << accNo << endl;
            tempFile << accName << endl;
            tempFile << accBalance << endl;
        }

        file.close();
        tempFile.close();

        remove("accounts.txt");
        rename("temp.txt", "accounts.txt");

        if (!found)
        {
            cout << "\nAccount Not Found!" << endl;
        }
    }
};

int main()
{
    BankAccount account;

    int choice;

    do
    {
        cout << "\n========== BANK MANAGEMENT SYSTEM ==========" << endl;

        cout << "1. Create Account" << endl;
        cout << "2. Display All Accounts" << endl;
        cout << "3. Search Account" << endl;
        cout << "4. Deposit Money" << endl;
        cout << "5. Withdraw Money" << endl;
        cout << "6. Update Account" << endl;
        cout << "7. Delete Account" << endl;
        cout << "8. Exit" << endl;

        cout << "\nEnter Your Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            account.createAccount();
            break;

        case 2:
            account.displayAllAccounts();
            break;

        case 3:
            account.searchAccount();
            break;

        case 4:
            account.depositMoney();
            break;

        case 5:
            account.withdrawMoney();
            break;

        case 6:
            account.updateAccount();
            break;

        case 7:
            account.deleteAccount();
            break;

        case 8:
            cout << "\nExiting Program..." << endl;
            break;

        default:
            cout << "\nInvalid Choice!" << endl;
        }

    } while (choice != 8);

    return 0;
}