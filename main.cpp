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

    void logTransaction(string type, int accNo, float amount)
    {
        ofstream file("transactions.txt", ios::app);

        file << "Transaction Type : " << type << endl;
        file << "Account Number   : " << accNo << endl;
        file << "Amount           : " << amount << endl;
        file << "----------------------------------" << endl;

        file.close();
    }

    void createAccount()
    {
        try
        {
            cout << "Enter Account Number: ";
            cin >> accountNumber;

            if (cin.fail())
            {
                throw "Invalid Account Number!";
            }

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

            if (balance < 0)
            {
                throw "Balance Cannot Be Negative!";
            }

            ofstream file("accounts.txt", ios::app);

            file << accountNumber << endl;
            file << name << endl;
            file << balance << endl;

            file.close();

            cout << "\nAccount Created Successfully!" << endl;
        }

        catch (const char* error)
        {
            cout << "\nError: " << error << endl;

            cin.clear();
            cin.ignore(1000, '\n');
        }
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

    void searchByAccountNumber()
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

    void searchByName()
    {
        string searchName;

        cin.ignore();

        cout << "Enter Account Holder Name: ";
        getline(cin, searchName);

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

            if (accName == searchName)
            {
                cout << "\n========== ACCOUNT FOUND ==========" << endl;

                cout << "Account Number : " << accNo << endl;
                cout << "Account Holder : " << accName << endl;
                cout << "Balance        : " << accBalance << endl;

                cout << "----------------------------------" << endl;

                found = true;
            }
        }

        if (!found)
        {
            cout << "\nNo Matching Account Found!" << endl;
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

                logTransaction("DEPOSIT", accNo, depositAmount);

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

                    logTransaction("WITHDRAW", accNo, withdrawAmount);

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

    void exportAccountsReport()
    {
        ifstream file("accounts.txt");
        ofstream report("account_report.txt");

        int accNo;
        string accName;
        float accBalance;

        report << "========== BANK ACCOUNT REPORT ==========\n\n";

        while (file >> accNo)
        {
            file.ignore();

            getline(file, accName);

            file >> accBalance;

            report << "Account Number : " << accNo << endl;
            report << "Account Holder : " << accName << endl;
            report << "Balance        : " << accBalance << endl;

            report << "----------------------------------" << endl;
        }

        file.close();
        report.close();

        cout << "\nAccount Report Exported Successfully!" << endl;
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
        cout << "3. Search By Account Number" << endl;
        cout << "4. Search By Account Holder Name" << endl;
        cout << "5. Deposit Money" << endl;
        cout << "6. Withdraw Money" << endl;
        cout << "7. Export Account Report" << endl;
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
            account.searchByAccountNumber();
            break;

        case 4:
            account.searchByName();
            break;

        case 5:
            account.depositMoney();
            break;

        case 6:
            account.withdrawMoney();
            break;

        case 7:
            account.exportAccountsReport();
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