#include <iostream> 
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <map>
#include <chrono>
#include <thread>
#include <cstdlib>


using namespace std;

// ====================================== Variabels ===========================================
static string acc_name;
string acc_email;
string passwd_acc;
int choice;
int balance = 0;
int money_added = 0;
int money_limit = 10000;
int money_withraw = 0;
const string BALANCE_FILE = "balance.txt";


// ====================================== Classes =============================================

class Dis_Account {
public:

	void dis_acc() {
		
		cout << " ============================================ " << endl;
		cout << " ============================================ " << endl;
		cout << "              Welcome To Your Account         " << endl;
		cout << " ============================================ " << endl;
		cout << " ============================================ " << endl;
		cout << " Your Name is: " << acc_name << endl;
		cout << " Your Email is: " << acc_email << endl;
		cout << " ============================================ " << endl;
		cout << "              Choose The Service              " << endl;
		cout << " ============================================ " << endl;
		cout << " 1. Show Balance.                             " << endl;
		cout << " 2. Add Money.                                " << endl;
		cout << " 3. Withraw Money.                            " << endl;
		cout << " 4. Edit Account.                             " << endl;
		cout << " 5. Exit.                                     " << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			show_balance();
			break;
		case 2:
			add_money();
			break;
		case 3:
			withraw_money();
			break;
		case 4:
			edit_acc();
			break;
		case 5:
			exit(0);
			break;
		default:
			cout << " Enter A Valid Choice! " << endl;
			break;
		}

	}


	void show_balance() {

		system("cls");
		cout << "=============================================" << endl;
		cout << "Hello " << acc_name << endl;
		cout << "Your Current Balance is: " << balance << endl;
		cout << "=============================================" << endl;
		cout << "Choose What Do You Want: " << endl;
		cout << "1. Go back to Choose Service Page." << endl;
		cout << "2. Exit." << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			dis_acc();
			break;
		case 2:
			exitt();
			break;
		default:
			break;
		}
	}
	

	void create_acc() {
		cout << " Enter Your Name: ";
		cin >> acc_name;
		cout << endl;
		cout << " Enter Your Email Address: ";
		cin >> acc_email;
		cout << endl;
		cout << " Enter Your Password: ";
		cin >> passwd_acc;


		ifstream infile("users.txt");
		string email, passwrd;
		bool found = false;
		while (infile >> email >> passwrd)
		{
			if(email == acc_email) {
				found = true;
			}
		}
		infile.close();

		if (found)
		{
			system("cls");
			cout << " Email Already Taken! Tyr Another One. " << endl;
			create_acc();
		}

		else
		{
			ofstream outfile("users.txt", ios::app);
			outfile << acc_email << " " << passwd_acc << endl;
			outfile.close();

			cout << " Registration Successful!" << endl;
			dis_acc();
		}
		ofstream outfile("users.txt", ios::app);
		outfile << acc_email << " " << passwd_acc << endl;
		outfile.close();

		cout << " Registration Successful!" << endl;
		dis_acc();
		
	}

	void freezeForSeconds(int seconds) {
		std::this_thread::sleep_for(std::chrono::seconds(seconds));
	}

	void login_acc_again() {


		cout << " Enter Your Email Address Again: ";
		cin >> acc_email;
		cout << endl;
		cout << " Enter Your Password Again: ";
		cin >> passwd_acc;
		cout << endl;

		ifstream infile("users.txt");
		string email, password_str;
		bool found = false;
		static int trys = 5;
		while (infile >> email >> password_str)
		{
			if (email == acc_email && password_str == passwd_acc) {
				found = true;
				break;
			}
		}

		infile.close();

		if (found)
		{
			cout << " Login Successful! " << endl;
			dis_acc();
		}

		else
		{
			trys--;
			cout << " Incorrect email or password " << endl;

			if (trys == 0)
			{
				cout << " You Reach the maximmums trys! Try again after 2 Minutes. " << endl;
				freezeForSeconds(120);
				login_acc_again();

			}
			login_acc_again();
		}
	}





	void login_acc() {
		Dis_Account ob2;
		cout << " Enter Your Email Address: ";
		cin >> acc_email;
		cout << endl;
		cout << " Enter Your Password: ";
		cin >> passwd_acc;
		cout << endl;

		ifstream infile("users.txt");
		string email, password_str;
		bool found = false;
		while (infile >> email >> password_str)
		{
			if (email == acc_email && password_str == passwd_acc) {
				found = true;
				break;
			}
		}

		infile.close();

		if (found)
		{
			cout << " Login Successful! " << endl;
			ob2.dis_acc();
		}

		else
		{
			cout << " Incorrect email or password " << endl;
			login_acc_again();
		}
	}

	void add_money() {

		system("cls");
		cout << "Enter The Money You Wanna Add: ";
		cout << " The Account Max Money You can add is (10000). ";
		cin >> money_added;
		
		if (money_added <= 0) {
			
			cout << "Invalid amount" << endl;
		
	
		}
		balance += money_added;
		if (balance > money_limit)
		{
			balance -= money_added;
			cout << " You Can't add more money, You have reached your limits! " << endl;
			cout << " ======================================================= " << endl;
			cout << " Choose:                                                 " << endl;
			cout << " 1. Go back to Choose Service Page                       " << endl;
			cout << " 2. Exit                                                 " << endl;
			cin >> choice;
			switch (choice)
			{
			case 1 :
				dis_acc();
				break;
			case 2:
				exitt();
				break;
			default:
				break;
			}
			
		}
	
		else
		{
			
			ofstream balance_file_out(BALANCE_FILE);
			balance_file_out << balance;
			balance_file_out.close();
			system("cls");
			cout << "Balance updated" << endl;
			dis_acc();
			
		}



	}

	void withraw_money() {
		int current_balance = 0;
		ifstream balance_file(BALANCE_FILE);
		balance_file >> current_balance;
		balance_file.close();
		cout << " Your Current Balance is: " << current_balance << endl;
		cout << " ============================================ " << endl;
		cout << " Enter the Amount of Money you wanna Withraw From your Bank Account: ";
		cin >> money_withraw;
		cout << endl;
		if (money_withraw <= 0)
		{
			system("cls");
			cout << " Invalid Amount Entered. " << endl;
			withraw_money();
		}

		if (money_withraw > current_balance)
		{
			system("cls");
			cout << "Withdrawal Amount Exceeds Current Balance!" << endl;
			withraw_money();
		}

		if (money_withraw > money_limit)
		{
			system("cls");
			cout << "Withdrawal Limit Exceeded!" << endl;
			withraw_money();
		}

		current_balance -= money_withraw;
		ofstream balance_outfile(BALANCE_FILE);
		balance_outfile << current_balance;
		balance_outfile.close();
		cout << "Withdrawal Successful!" << endl;
		cout << "Current Balance: " << current_balance << endl;
		dis_acc();



	}

	void edit_acc() {




		cout << " ================================================ " << endl;
		cout << " Choose What Do You Want to Edit                  " << endl;
		cout << " 1. Edit My Name.                                 " << endl;
		cout << " 2. Edit My Password.                             " << endl;
		cout << " 3. Exit                                          " << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			edit_name();
			break;
		case 2:
			edit_pass();
			break;
		case 3:
			exitt();
			break;
		default:
			cout << " Enter A Valid Answer. " << endl;
			break;
		}
		

	}

	void edit_name() {
		cout << " Enter Your New Name: ";
		cin >> acc_name;
		cout << endl;
		cout << " Your Name Changed to: " << acc_name << endl;

		ifstream infile("users.txt");
		ofstream tempfile("temp.txt");

		string email, password_str;
		while (infile >> email >> password_str)
		{
			if (email == acc_email) {
				tempfile << email << " " << password_str << " " << acc_name << endl;
			}
			else
			{
				tempfile << email << " " << password_str << endl;
			}
		}

		infile.close();
		tempfile.close();
		remove("users.txt");
		rename("temp.txt", "users.txt");
		dis_acc();




	}

	void edit_pass() {
		string new_passwd;
		cout << " Enter Your New Password: ";
		cin >> new_passwd;
		cout << endl;
		cout << " Your Password Changed to: " << new_passwd << endl;
		ifstream infile("users.txt");
		ofstream tempfile("temp.txt");
		string email, passwd;
		while (infile >> email >> passwd)
		{
			if (email == acc_email && passwd == passwd)
			{
				tempfile << email << " " << new_passwd << endl;
			}
			else
			{
				tempfile << email << " " << passwd << endl;
			}
		}

		infile.close();
		tempfile.close();
		remove("users.txt");
		rename("temp.txt", "users.txt");
		dis_acc();


	}

	void exitt() {

		dis_acc();

	}





};



class Menu {
private:
	int choice;
public:
	Menu() {

		Dis_Account ob2;
		

		cout << " =============================================== " << endl;
		cout << " =============================================== " << endl;
		cout << "                 Bank Managment System           " << endl;
		cout << " =============================================== " << endl; 
		cout << " =============================================== " << endl;
		cout << "                Choose The Service You Want      " << endl;
		cout << " =============================================== " << endl;
		cout << " 1. Create Account.                              " << endl;
		cout << " 2. Login.                                       " << endl;
		cout << " 3. Exit                                         " << endl;
		cout << " =============================================== " << endl;
		cin >> choice;


		switch (choice)
		{
		case 1:
			ob2.create_acc();
			break;
		case 2 :
			ob2.login_acc();
			break;
		case 3 :
			exit(0);
			break;

		default:
			break;
		}


	}
};


int main(){
	
	Menu ob;
	return 0;
}