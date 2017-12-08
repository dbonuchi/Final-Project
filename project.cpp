#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <stack>
#include <fstream>
#include <iomanip>
#include <algorithm>

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
		void correctmoneyamount(float moneyamount);
		float checkfail(float moneyamount);
		int checkfail(int x);
		float getmoneyamount();

		float negativedeposit(float deposit){
			while (deposit<0){
				cout<<"Deposit cannot be negative! Please re-enter the deposit amount"<<endl;
				cin>>deposit;
			}
			return deposit;
		}

		virtual float withdrawtoolarge(float withdraw);
		virtual void print_info(){
			cout<<"Your current checkings balance is:\t "<<moneyamount<<"\n"<<endl;
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
	name = input;						//putting the input name into a string called name
	checkingsfilename = name + file;  	//full file name is now "name"checkingsaccount.txt
	myfile.open(checkingsfilename);
	if(myfile.is_open()){
		check=1;				//check=1 to show that there is a checkings account
		myfile.close();
	}
	else{
		check=2;				//check=2 to show that there is not a checkings account
	}
	moneyamount=0;				//intialized moneyamount and pin as 0
	pinnumber=0;

}

// create checkings creates a text file that contains the
//persons name/(fingerprint), pin number, and money amount in the account.
void Checkings::createcheckings(){
	int i=0,hold=0,yorn=0;
	cout<<"To choose your pin enter 5 digits individually (1 enter 2 enter ect.)"<<endl;
	while(i<5){
		cin>>hold;
		hold=checkfail(hold);	//making sure a number is entered and not a character
		while(hold<0 || hold>9){
			cout<<"Please enter each number individually from 0-9 and a total of 5 numbers to initialize your pin"<<endl;
			cin>>hold;
			hold=checkfail(hold);	//making sure a number is entered and not a character
		}
		pin.push_back(hold);	//this is the person creating the pin and they must input each number individually at to initialize
		++i;
	}
	cout<<"The Pin number you entered is ";
	for(auto i:pin)
		cout << i;
	cout<<". Is this the correct pin number? Enter 1 of yes or 2 for no"<<endl;
	//user is then asked if they would like to keep the pin entered or want a different pin
	cin>>yorn;
	while(yorn==2){				//while the user doesn't want the pin enter they must choose a different pin
		yorn=0;
		cout<<"Please re-enter your 5 digit pin"<<endl;
		pin.clear();			//the pin vector is then clear and a new pin is enter in it
		i=0;
		while(i<5){
			cin>>hold;
			hold=checkfail(hold);	//making sure a number is entered and not a character
			while(hold<0||hold>9){
				cout<<"Please enter each number individually from 0-9 and a total of 5 numbers to initialize your pin"<<endl;
				cin>>hold;
				hold=checkfail(hold);	//making sure a number is entered and not a character
			}
			pin.push_back(hold);
			++i;
		}
		cout<<"The Pin number you entered is ";
		for(auto i:pin)
			cout << i;
		cout<<". Is this the correct pin number? Enter 1 of yes or 2 for no"<<endl;
		cin>>yorn;				//asked if the pin they enter is the one they want to keep if yes then loop ends
	}
	cout<<"How much money would you like to deposit?"<<endl;
	int moneyamountcheck=0;
	while(moneyamountcheck==0){
		cin>>moneyamount;
		moneyamount=checkfail(moneyamount);
		try{
			correctmoneyamount(moneyamount);	//checks if the money entered is greater than 0
		}
		catch(const int s){
			if(s==0){
				cout<<"money amount must be greater than zero please re-enter the amount of money you would like to deposit"<<endl;
			}
			if(s==1){
				moneyamountcheck=1;
			}
		}
	}
	ofstream myfile;
	myfile.open(checkingsfilename);
	myfile<<name<<"\t";			//name/fingerprint of person is entered into the file
	i=0;
	while(i<5){
		myfile<<pin[i];			//desired pin is entered into the file
		i++;
	}
	myfile<<"\t"<<moneyamount;	//money deposited is enter into the file
	myfile.close();
}

//checkpin takes in the pin_input by the user and
//determine is the pin_input is equal to the bank accounts pin
int Checkings::checkpin(int pin_input){
	ifstream myfile;
	myfile.open(checkingsfilename);
	myfile>>name;
	myfile>>pinnumber;			//notice pinnumber here is an int and when it was intialized it was a vector <int>
	if(pinnumber==pin_input){	//checks if the pin that was input in the main (by the user) was the correct pin
		myfile>>moneyamount;
		myfile.close();
		return 1;				//if correct then it returns 1
	}
	else{
		myfile.close();
		return 0;				//if incorrect it returns a 0
	}
}

//checkingsgetcheck determines if there is a checkings account
int Checkings::checkingsgetcheck(){
	ifstream myfile;
	myfile.open(checkingsfilename);
	if(myfile.is_open()){
		check=1;				//if check=1 then there is a checkings account
		myfile.close();
	}
	else{
		check=2;				//if check=2 then there is not a checkings account
	}
	return check;
}

//getpin gets the pin and brings it to the main.
int Checkings::getpin(){
	ifstream myfile;
	myfile.open(checkingsfilename);
	myfile>>name;
	myfile>>pinnumber;			//notice pinnumber here is an int and when it was intialized it was a vector <int>
	myfile.close();
	return pinnumber;
}


void Checkings::operator -(float withdraw){
	moneyamount-=withdraw;
}

void Checkings::operator +(float deposit){
	moneyamount+=deposit;
}

//this function checks the withdraw for error of being to large or being negative.
float Checkings::withdrawtoolarge(float withdraw){
	int i=0;
	while(i==0){
		if (withdraw>moneyamount){		//if the withdraw is more then the money in the account then it will not happen
			cout<<"\nDenied!\nThe money amount you are trying to withdraw is too large. Please re-enter a withdraw amount."<<endl;
			cin>>withdraw;
		}
		if(withdraw<0){					//if the withdraw is negative then the withdraw will not happen.
			cout<<"Withdraw amount cannout be negative! Please re-enter withdraw amount"<<endl;
			cin>>withdraw;
		}
		if(withdraw<moneyamount && withdraw>=0){
			i=1;				//when i=1 then the withdraw has no error
		}
	}
	return withdraw;
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


void Checkings::correctmoneyamount(float moneyamount){
	if(moneyamount<=0)
		throw(0);
	if(moneyamount>0)
		throw(1);
}

//checkfail checks to see if a float was input instead of a char
float Checkings::checkfail(float moneyamount){
	while (cin.fail()) {
		cout<<"money amount entered must be a number"<<endl;
		cin.clear();
		cin.ignore(256,'\n');
		cin>>moneyamount;
	}
	return moneyamount;
}

//checkfail checks to see if an interger value was input instead of a char
int Checkings::checkfail(int x){
	while (cin.fail()) {
		cout<<"Must enter a number."<<endl;
		cin.clear();
		cin.ignore(256,'\n');
		cin>>x;
	}
	return x;
}

float Checkings::getmoneyamount(){
	return moneyamount;
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
		virtual void operator+(float deposit);	//this operator is a virtual operator
		virtual void operator-(float withdraw);	//this operator is also a virtual operator
		void updatesavingsfile();
		float withdrawtoolarge(float withdraw);
		float transfercheck(float transfer,float checkingsmoney, int transfertype);
		virtual void print_info(){
			cout<<"The money that is in your savings account is "<<savings_money<<"\n"<<endl;
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
	name = input;					//putting the input name into a string called name
	savingsfilename = name + file;  //full file name is now "name"checkingsaccount.txt
	myfile.open(savingsfilename);
	if(myfile.is_open()){
		check=1;					//check=1 to show that there is a savings account
		myfile>>savings_money;
		myfile.close();
	}
	else{
		check=2;					//check=2 to show that there is no savings account
	}

}

//createsavingsaccount makes a txt file and puts the
//desired money inside.
void Savings::createsavingsaccount(float savingsstart){
	savings_money=savingsstart;
	ofstream myfile;
	myfile.open(savingsfilename);
	myfile<<savings_money;
	myfile.close();
}

//savingsgetcheck determine is the person
//has a savings account or not
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

//updates the savings file information which is
//just the money that is inside.
void Savings::updatesavingsfile(){
	ofstream myfile;
	myfile.open(savingsfilename);
	myfile<<savings_money;
	myfile.close();
}

//this function checks the withdraw for error of being to large or being negative.
float Savings::withdrawtoolarge(float withdraw){
	int i=0;
	while(i==0){
		if (withdraw>savings_money){	//if the withdraw is more then the money in the account then it will not happen
			cout<<"\nDenied!\nThe money amount you are trying to withdraw is too large. Please re-enter a withdraw amount."<<endl;
			cin>>withdraw;
		}
		if(withdraw<0){			//if the withdraw is negative then the withdraw will not happen.
			cout<<"Withdraw amount cannout be negative! Please re-enter withdraw amount"<<endl;
			cin>>withdraw;
		}
		if(withdraw<savings_money && withdraw>=0){
			i=1;				//when i=1 then the withdraw has no error
		}
	}
	return withdraw;
}

//makes sure money transfer does not exceed the amount that an account
float Savings::transfercheck(float transfer,float checkingsmoney, int transfertype){
	if(transfertype==1){		//type 1 is tranfer from checkings to savings
		//if the transfer amount is larger than the money in the checkings the transfer cannot happen
		while(transfer>checkingsmoney){
			cout<<"The money transfered from the checkings cannot exceed the money in the account"<<endl;
			cout<<"Please re-enter a transfer amount from your checkings to your savings"<<endl;
			cin>>transfer;
		}
	}

	if(transfertype==2){		//type 2 is a transfer from savings to checkings
		//if the transfer amount is larger than the money in the savings the transfer cannot happen
		while(transfer>savings_money){
			cout<<"The money transfered from the savings cannot exceed the money in the account"<<endl;
			cout<<"Please re-enter a transfer amount from your savings to your checkings"<<endl;
			cin>>transfer;
		}
	}
	return transfer;
}




int main() {
	//Since we do not have a finger print  ready yet I will have the user input a name
	//cout<<"Put you finger print to set up an account or access an old account"<<endl;
	//cin>>fingerprint;
	//put create an object with a fingerprint
	std::cout<<std::setprecision(2)<<std::fixed;
	string name;
	int exitcheck=0, checkings_check=0, yorn=0, pin=0, pin_correctness=0;
	int enterpinonce=0, choice=0, savings_check=0, transferbool=0;
	float deposit,withdraw,savings_start, savings_deposit,savings_withdraw,transfer_amount;
	cout<<"Enter your name to set up an account or access an old account"<<endl;
	getline(cin,name);						//inputs fingerprint/name
	for (auto &c :name)
		c = toupper(c);	
	remove( name.begin(), name.end(), ' ');
	Checkings checkingsaccount(name);		//name or fingerprint is then checked to see if it is in the system
	Savings savingsaccount(name);
	Checkings &x = checkingsaccount;
	Checkings &y = savingsaccount;
	while(exitcheck==0){					//this check is to see if the user wants to exit the program or not.
		checkings_check = checkingsaccount.checkingsgetcheck();		//this check is to see if the person already has an existing checkings account.
		savings_check = savingsaccount.savingsgetcheck();			//this check is to see if the person already has an existing savings account.
		if (checkings_check==1 && savings_check==2){				//checkings_check=1 && savings_check==2 means there is a checkings account but no savings
			if(enterpinonce==0){			//if has not been entered yet then it must be enter once per transaction
				cout<<"Has an existing account"<<endl;
				cout<<"please enter your pin number:\t"<<endl;
				cin>>pin;					//this pin can be entered continously unlike when the pin is initialized
				pin=checkingsaccount.checkfail(pin);			//making sure number entered is not a character
				pin_correctness=checkingsaccount.checkpin(pin);	//checks to see if the pin entered is the same as the pin for the account
				if (pin_correctness!=1){
					cout<<"The pin that was entered was incorrected please re-enter, you have one more chance to re-enter:\t"<<endl;
					cin>>pin;				//gives the person a second chance to enter their pin correctly
					pin=checkingsaccount.checkfail(pin);			//making sure number entered is not a character
					pin_correctness=checkingsaccount.checkpin(pin);
					if(pin_correctness!=1){
						cout<<"pin number was entered incorrectly twice program is now terminated"<<endl;
						return 0;			//if the pin is not entered correctly a second time then the program ends
					}
				}
				else{
					cout<<"Your pin was Entered successfully, ";
				}
				enterpinonce=1;				//makes it so the pin does not need to be entered again.
			}
			cout<<"Please choose an option for your bank account.\nEnter 1 to withdraw.\nEnter 2 to Deposit."<<endl;
			cout<<"Enter 3 To create a savings account \nEnter 4 to display your account information \nEnter 5 to exit."<<endl;
			cin>>choice;
			choice=checkingsaccount.checkfail(choice);
			switch(choice){
			case 1:
				cout<<"Enter the amount of that you would like to withdraw:\t";
				cin>>withdraw;
				withdraw=checkingsaccount.checkfail(withdraw);		//makes sure withdraw is a float
				withdraw=checkingsaccount.withdrawtoolarge(withdraw);//makes sure withdraw is not too large
				checkingsaccount-withdraw;		//uses an operator to do the withdraw
				checkingsaccount.updatefile();	//update all the information in the file
				break;
			case 2:
				cout<<"Enter the amount of money that you would like to deposit:\t";
				cin>>deposit;
				deposit=checkingsaccount.checkfail(deposit);		//makes sure deposit is a float
				deposit=checkingsaccount.negativedeposit(deposit); //makes sure deposit is nonnegative
				checkingsaccount+deposit;		//uses an operator to do the deposit
				checkingsaccount.updatefile();	//updates all the information in the file
				break;
			case 3:
				cout<<"How much money would you like to start with in your savings accout?"<<endl;
				cin>>savings_start;
				savings_start=checkingsaccount.checkfail(savings_start);	//makes sure deposit is a float
				savingsaccount.createsavingsaccount(savings_start);			//creates a savings account is the desired money
				break;
			case 4:
				checkingsaccount.print_info();	//informs the user of the money in the checkings account
				break;
			case 5:
				cout<<"Thank you and have a great day!"<<endl;
				exitcheck=1;					//exits the program when exitcheck==1
				break;
			default:
				cout<<"The wrong value was input"<<endl;
				break;
			}
		}


		if (checkings_check==1 && savings_check == 1){			//checkings_check==1 && savings_check==1 means there is a checkings and a savings account
			if(enterpinonce==0){
				cout<<"Has an existing account"<<endl;
				cout<<"please enter your pin number:\t"<<endl;
				cin>>pin;						//this pin can be entered continously unlike when the pin is initialized
				pin=checkingsaccount.checkfail(pin);			//making sure number entered is not a character
				pin_correctness=checkingsaccount.checkpin(pin);	//checks to see if the pin entered is the same as the pin for the account
				if (pin_correctness!=1){
					cout<<"The pin that was entered was incorrected please re-enter, you have one more chance to re-enter:\t"<<endl;
					cin>>pin;					//gives the person a second chance to enter their pin correctly
					pin=checkingsaccount.checkfail(pin);			//making sure number entered is not a character
					pin_correctness=checkingsaccount.checkpin(pin);
					if(pin_correctness!=1){
						cout<<"pin number was entered incorrectly twice program is now terminated"<<endl;
						return 0;				//if the pin is not entered correctly a second time then the program ends
					}
				}
				enterpinonce=1;
			}
			cout<<"Please choose an option for your bank account.\nEnter 1 to withdraw from your checkings account.\nEnter 2 to Deposit money into your checkings account."<<endl;
			cout<<"Enter 3 to withdraw money into your savings account. \nEnter 4 to deposit money out of the savings \nEnter 5 to make a transfer."<<endl;
			cout<<"Enter 6 display your account information. \nEnter 7 to exit."<<endl;
			cin>>choice;
			switch(choice){
			case 1:
				cout<<"Enter the amount of that you would like to withdraw:\t";
				cin>>withdraw;
				withdraw=checkingsaccount.checkfail(withdraw);		//makes sure withdraw is a float
				withdraw=checkingsaccount.withdrawtoolarge(withdraw);//makes sure withdraw isn't too large
				checkingsaccount-withdraw;		//uses an operator to do the withdraw
				checkingsaccount.updatefile();	//update all the information in the file
				break;
			case 2:
				cout<<"Enter the amount of money that you would like to deposit:\t";
				cin>>deposit;
				deposit=checkingsaccount.checkfail(deposit);		//makes sure deposit is only a float
				deposit=checkingsaccount.negativedeposit(deposit);	//makes sure deposit is nonnegative
				checkingsaccount+deposit;		//uses an operator to do the deposit
				checkingsaccount.updatefile();	//updates all the information in the file
				break;
			case 3:
				cout<<"How much money would you like to withdraw from you savings account?"<<endl;
				cin>>savings_withdraw;
				savings_withdraw=checkingsaccount.checkfail(savings_withdraw);		//makes sure withdraw is only a float
				savings_withdraw=savingsaccount.withdrawtoolarge(savings_withdraw);	//makes sure withdraw isn't too large
				savingsaccount-savings_withdraw;	//does a withdraw from savings using an operator
				savingsaccount.updatesavingsfile();	//updates all the information in the file
				break;
			case 4:
				cout<<"How much money would you like to deposit into your savings account?"<<endl;
				cin>>savings_deposit;
				savings_deposit=checkingsaccount.checkfail(savings_deposit);		//makes sure deposit is only a float
				savings_deposit=checkingsaccount.negativedeposit(savings_deposit);	//makes sure deposit is nonnegative
				savingsaccount+savings_deposit;		//does a deposit in the savings using a operator
				savingsaccount.updatesavingsfile();	//updates all the information in the file
				break;
			case 5:
				cout<<"\nEnter 1 to transfer money from your checkings into your savings \nEnter 2 to transfer money from your savings into your checkings"<<endl;
				cin>>transferbool;
				cout<<"Enter the amount of money you would like to transfer"<<endl;
				cin>>transfer_amount;
				transfer_amount=checkingsaccount.checkfail(transfer_amount);
				float checkingsmoney;
				checkingsmoney=checkingsaccount.getmoneyamount();
				transfer_amount=savingsaccount.transfercheck(transfer_amount,checkingsmoney,transferbool);
				if(transferbool==1){
					checkingsaccount-transfer_amount;//transfers money from checkings to savings
					savingsaccount+transfer_amount;
					savingsaccount.updatesavingsfile();	//updates their files
					checkingsaccount.updatefile();
				}
				if(transferbool==2){
					savingsaccount-transfer_amount;		//transfers money from savings to checkings
					checkingsaccount+transfer_amount;
					savingsaccount.updatesavingsfile();	//updates their files
					checkingsaccount.updatefile();
				}
				break;
			case 6:
				x.print_info();						//uses dynamic binding to use the correct print statment
				y.print_info();
				break;
			case 7:
				cout<<"Thank you and have a great day!"<<endl;
				exitcheck=1;
				break;
			default:
				cout<<"The wrong value was input"<<endl;
				break;
			}

		}




		if(checkings_check==2){				//if checkings_check==2 then there is no checkings account which means there no way a savings account has been made
			cout<<"Does not have an account"<<endl;
			cout<<"would you like to create a checkings account? Enter 1 for yes and 2 for no:\t"<<endl;
			cin>>yorn;						//if 1 then a checkings account is created and the information is input into a txt file if 2 then the program exits
			pin=checkingsaccount.checkfail(pin);			//making sure number entered is not a character
			if(yorn==2){
				cout<<"Thank you and have a great day!"<<endl;
				exitcheck=1;
			}
			if(yorn==1){
				checkingsaccount.createcheckings();	//creates a file win the name, pin, and money input stored inside
				checkingsaccount.getpin();
				enterpinonce=1;				//since a pin was created the pin doesn't need to be entered again.
			}
		}


	}


	cout<<"Hello World"<<endl;
	return 0;
}
