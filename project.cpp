#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <fstream>
#include <iomanip>

using namespace std;



class Checkings{

	private:
		vector <int> pin;
		float moneyamount;
		int pinnumber;
	public:

		string name,checkingsfilename;
		int check=0;
		Checkings();
		Checkings(string input);
		int checkingsgetcheck();
		void createcheckings();
		int checkpin(int pin_input);
		int getpin();
		virtual void operator+(float deposit);
		virtual void operator-(float withdraw);
		void updatefile();
		virtual void print_info(){
			cout<<"Your current checkings balance is:\t "<<moneyamount<<endl;
		}
};

Checkings::Checkings(){
	//cout<<"Checkings Default constructor"<<endl;
	moneyamount=0;
	pinnumber=0;
}

Checkings::Checkings(string input){
	ifstream myfile;
	string file = "checkingsaccount.txt";
	name = input;	//putting the input name into a string called name
	checkingsfilename = name + file;  //full file name is now "name"checkingsaccoutn.txt
	myfile.open(checkingsfilename);
	if(myfile.is_open()){
		check=1;
		myfile.close();
	}
	else{
		check=2;
	}
	moneyamount=0;
	pinnumber=0;

}

int Checkings::checkingsgetcheck(){
	ifstream myfile;
	myfile.open(checkingsfilename);
	if(myfile.is_open()){
		check=1;
		myfile.close();
	}
	else{
		check=2;
	}
	return check;
}

/*
 * a function that creates a text file that contains the persons name(fingerprint), pin number, and money amount in the account.
 */
void Checkings::createcheckings(){
	int i=0,hold=0,yorn=0;
	cout<<"To choose your pin enter 5 digits individually (1 enter 2 enter ect.)"<<endl;
	while(i<5){
		cin>>hold;
		while(hold<0 || hold>9){
			cout<<"Please enter each number individually from 0-9 and a total of 5 numbers to initialize your pin"<<endl;
			cin>>hold;
		}
		pin.push_back(hold);		//this is the person creating the pin and they must input each number individually at to initialize
		++i;
	}
	cout<<"The Pin number you entered is ";
	for(auto i:pin)
		cout << i;
	cout<<". Is this the correct pin number? Enter 1 of yes or 2 for no"<<endl;
	cin>>yorn;
	while(yorn==2){
		yorn=0;
		cout<<"Please re-enter your 5 digit pin"<<endl;
		pin.clear();
		i=0;
		while(i<5){
			cin>>hold;
			while(hold<0||hold>9){
				cout<<"Please enter each number individually from 0-9 and a total of 5 numbers to initialize your pin"<<endl;
				cin>>hold;
			}
			pin.push_back(hold);
			++i;
		}
		cout<<"The Pin number you entered is ";
		for(auto i:pin)
			cout << i;
		cout<<". Is this the correct pin number? Enter 1 of yes or 2 for no"<<endl;
		cin>>yorn;
	}
	cout<<"How much money would you like to deposit?"<<endl;
	cin>>moneyamount;
	ofstream myfile;
	myfile.open(checkingsfilename);
	myfile<<name<<"\t";
	i=0;
	while(i<5){
		myfile<<pin[i];
		i++;
	}
	myfile<<"\t"<<moneyamount;
	myfile.close();
}

int Checkings::checkpin(int pin_input){
	ifstream myfile;
	myfile.open(checkingsfilename);
	myfile>>name;
	myfile>>pinnumber;				//notice pinnumber here is an int and when it was intialized it was a vector <int>
	if(pinnumber==pin_input){		//checks if the pin that was input in the main (by the user) was the correct pin
		myfile>>moneyamount;
		myfile.close();
		return 1;					//if correct then it returns 1
	}
	else{
		myfile.close();
		return 0;					//if incorrect it returns a 0
	}
}

int Checkings::getpin(){
	ifstream myfile;
	myfile.open(checkingsfilename);
	myfile>>name;
	myfile>>pinnumber;				//notice pinnumber here is an int and when it was intialized it was a vector <int>
	myfile.close();
	return pinnumber;
}


void Checkings::operator -(float withdraw){
	moneyamount-=withdraw;
}

void Checkings::operator +(float deposit){
	moneyamount+=deposit;
}

/*
 * file information is updated and the money amount is changed
 */
void Checkings::updatefile(){
	ofstream myfile;
	myfile.open(checkingsfilename);
	myfile<<name<<"\t";
	myfile<<pinnumber<<"\t";
	myfile<<moneyamount;
	myfile.close();
}

class Savings: public Checkings{
	private:
		float savings_money;
	public:
		string savingsfilename;
		Savings();
		Savings(string input);
		int savingsgetcheck();
		void createsavingsaccount(float savingsstart);
		void operator+(float deposit);			//this operator is a virtual operator
		void operator-(float withdraw);			//this operator is also a virtual operator
		void updatesavingsfile();
		void print_info(){
			cout<<"The money that is in your savings account is "<<savings_money<<endl;
		}

};


Savings::Savings(){
	cout<<"You do not have a savings account"<<endl;
	savings_money=0;

}

Savings::Savings(string input){
	savings_money=0;
	ifstream myfile;
	string file = "savingsaccount.txt";
	name = input;	//putting the input name into a string called name
	savingsfilename = name + file;  //full file name is now "name"checkingsaccoutn.txt
	myfile.open(savingsfilename);
	if(myfile.is_open()){
		check=1;
		myfile>>savings_money;
		myfile.close();
	}
	else{
		check=2;
	}

}

void Savings::createsavingsaccount(float savingsstart){
	savings_money=savingsstart;
	ofstream myfile;
	myfile.open(savingsfilename);
	myfile<<savings_money;
	myfile.close();
}

int Savings::savingsgetcheck(){
	ifstream myfile;
	myfile.open(savingsfilename);
	if(myfile.is_open()){
		check=1;
		myfile.close();
	}
	else{
		check=2;
	}
	return check;

}

void Savings::operator -(float withdraw){
	savings_money-=withdraw;
}

void Savings::operator +(float deposit){
	savings_money+=deposit;
}

void Savings::updatesavingsfile(){
	ofstream myfile;
	myfile.open(savingsfilename);
	myfile<<savings_money;
	myfile.close();
}





int main() {
	//Since we do not have a finger print  ready yet I will have the user input a name
	//cout<<"Put you finger print to set up an account or access an old account"<<endl;
	//cin>>fingerprint;
	//put create an object with a fingerprint
	std::cout<<std::setprecision(2)<<std::fixed;
	string name;
	int exitcheck=0, check=0, yorn=0, pin=0, pin_correctness=0;
	int onlyonce=0, choice=0, savings_check=0, transferbool=0;
	float deposit,withdraw,savings_start, savings_deposit,savings_withdraw;
	cout<<"Enter your name to set up an account or access an old account"<<endl;
	getline(cin,name);					//inputs fingerprint/name
	Checkings checkingsaccount(name);			//name or fingerprint is then checked to see if it is in the system
	Savings savingsaccount(name);
	while(exitcheck==0){
	//Checkings checkingsaccount(name);			//name or fingerprint is then checked to see if it is in the system
	//Savings savingsaccount(name);
	savings_check = savingsaccount.savingsgetcheck();
	check = checkingsaccount.checkingsgetcheck();			//this check is to see if the person already has an existing account with us
	//while(exitcheck=0){
	if (check==1 && savings_check==2){
		//This is a very long if statement and may not be the best approach but it checks if there is an existing file
		if(onlyonce==0){
			cout<<"Has an existing account"<<endl;
			cout<<"please enter your pin number:\t"<<endl;
			cin>>pin;					//this pin can be entered continously unlike when the pin is initialized
			pin_correctness=checkingsaccount.checkpin(pin);	//checks to see if the pin entered is the same as the pin for the account
			if (pin_correctness!=1){
				cout<<"The pin that was entered was incorrected please re-enter, you have one more chance to re-enter:\t"<<endl;
				cin>>pin;				//gives the person a second chance to enter their pin correctly
				pin_correctness=checkingsaccount.checkpin(pin);
				if(pin_correctness!=1){
					cout<<"pin number was entered incorrectly twice program is now terminated"<<endl;
					//exitcheck=1;
					return 0;			//if the pin is not entered correctly a second time then the program ends
				}
			}
			onlyonce=1;
		}
		cout<<"Your pin was Entered successfully, ";
		checkingsaccount.print_info();			//prints out the checkings account info
		//if(savings_check == 2){				//if savings_check is 2 there is not an existing savings account made for a person
			cout<<"Please choose an option for your bank account.\nEnter 1 to withdraw.\nEnter 2 to Deposit."<<endl;
			cout<<"Enter 3 To create a savings account \nEnter 4 to exit."<<endl;
			cin>>choice;
			switch(choice){
			case 1:
				cout<<"Enter the amount of that you would like to withdraw:\t";
				cin>>withdraw;
				checkingsaccount-withdraw;		//uses an operator to do the withdraw
				checkingsaccount.updatefile();		//update all the information in the file
				break;
			case 2:
				cout<<"Enter the amount of money that you would like to deposit:\t";
				cin>>deposit;
				checkingsaccount+deposit;				//uses an operator to do the deposit
				checkingsaccount.updatefile();		//updates all the information in the file
				break;
			case 3:
				cout<<"How much money would you like to start with in your savings accout?"<<endl;
				cin>>savings_start;
				savingsaccount.createsavingsaccount(savings_start);
				break;
			case 4:
				cout<<"Thank you and have a great day!"<<endl;
				exitcheck=1;
				break;
			default:
				cout<<"The wrong value was input"<<endl;
				break;
			}
		}


		if (check==1 && savings_check == 1){				//if saving_check is a 1 then there is already a savings account made for the person and there is an existing file.
			if(onlyonce==0){
				cout<<"Has an existing account"<<endl;
				cout<<"please enter your pin number:\t"<<endl;
				cin>>pin;					//this pin can be entered continously unlike when the pin is initialized
				pin_correctness=checkingsaccount.checkpin(pin);	//checks to see if the pin entered is the same as the pin for the account
				if (pin_correctness!=1){
					cout<<"The pin that was entered was incorrected please re-enter, you have one more chance to re-enter:\t"<<endl;
					cin>>pin;				//gives the person a second chance to enter their pin correctly
					pin_correctness=checkingsaccount.checkpin(pin);
					if(pin_correctness!=1){
						cout<<"pin number was entered incorrectly twice program is now terminated"<<endl;
						//exitcheck=1;
						return 0;			//if the pin is not entered correctly a second time then the program ends
					}
				}
				onlyonce=1;
			}
			cout<<"Please choose an option for your bank account.\nEnter 1 to withdraw.\nEnter 2 to Deposit money into your checkings account."<<endl;
			cout<<"Enter 3 To Deposit money into your savings account. \nEnter 4 To withdraw money out of the savings \nEnter 5 to make a transfer."<<endl;
			cout<<"Enter 6 to exit."<<endl;
			cin>>choice;
			switch(choice){
			case 1:
				cout<<"Enter the amount of that you would like to withdraw:\t";
				cin>>withdraw;
				checkingsaccount-withdraw;			//uses an operator to do the withdraw
				checkingsaccount.updatefile();		//update all the information in the file
				break;
			case 2:
				cout<<"Enter the amount of money that you would like to deposit:\t";
				cin>>deposit;
				checkingsaccount+deposit;				//uses an operator to do the deposit
				checkingsaccount.updatefile();		//updates all the information in the file
				break;
			case 3:
				cout<<"How much money would you like to deposit into your savings account?"<<endl;
				cin>>savings_deposit;
				savingsaccount+savings_deposit;
				savingsaccount.updatesavingsfile();

				break;
			case 4:
				cout<<"How much money would you like to withdraw from you savings account?"<<endl;
				cin>>savings_withdraw;
				savingsaccount-savings_withdraw;
				savingsaccount.updatesavingsfile();
				break;
			case 5:
				cout<<"Would you like to transfer money from your checkings into your savings enter 1. or your savings into your checkings enter 2.";
				cin>>transferbool;

				/*if(transferbool==1){
					//global operator for transfering
					 * here is where we will use another adding operator to achieve operator overloading
				}
				if(transferbool=2){
					//global operator for transfering
				}*/


				break;
			case 6:
				cout<<"Thank you and have a great day!"<<endl;
				exitcheck=1;
				break;
			default:
				cout<<"The wrong value was input"<<endl;
				break;
			}

		}




	if(check==2){
		cout<<"Does not have an account"<<endl;
		cout<<"would you like to create a checkings account? Enter 1 for yes and 2 for no:\t"<<endl;
		cin>>yorn;						//if 1 then a checkings account is created and the information is input into a txt file if 2 then the program exits
		if(yorn==2){
			cout<<"Thank you for coming in today!"<<endl;
			exitcheck=1;
			//return 0;
		}
		if(yorn==1){
			checkingsaccount.createcheckings();	//creates a file win the name, pin, and money input stored inside
			checkingsaccount.getpin();
			onlyonce=1;
		}
	}


	}
	//Checkings &x = checkingsaccount;
	//Checkings &y = savingsaccount;
	//x.print_info();								//uses dynamic binding to use the correct print statment
	//y.print_info();



	cout<<"Hello World"<<endl;
	return 0;
}
