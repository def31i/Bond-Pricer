#include <iostream>
using namespace std;



//for exponential calculation

double expon (double t, double ytm) {
	
	double power = t;
	double rate = ytm; 
	double base = 1 + rate/100;          /*To convert rate to decimal*/
	double result = 1;                               

	for (int i = 0; i < power; i++) {

		result = result * base;          /*base gets multiplied by itself through each iteration depending on power amount*/	 
	}
	return result;
}

/*for calculating present value of Coupon payments*/
double annuity_pv(double c_p, double ytm, double t) {

	return (c_p / (ytm/100)) * (1 - 1 / expon(t,ytm));

}

/*Present Value of face value*/

double faceval_pv(double f_v, double ytm, double t) {

    return f_v / expon(t, ytm);

}

//for calculating coupon payments//
double c_p(double c_r, double f_v) {

	return c_r/100 * f_v;

}

//for approximating Yield to maturity (if necessary)

double approx_ytm (double (*c_ptr)(double,double), double f_v, double present_value, double c_r, double t) {

	return ((c_ptr(c_r,f_v) + (f_v - present_value) / t) / (f_v + present_value)) / 2.0;

}


int main() {

	int check;
	double ytm;                                                     //Doubles used for precision and to avoid truncation
	double f_v;
	double c_r;
	double t;
	double present_value = 0.0;
	double approximated_ytm = 0.0;
	double (*c_ptr)(double, double);                                //Function pointer for coupon payment function to store its address
	c_ptr = c_p;                                                // function pointer equal to function so it can be passed as a paremeter outside of main




	//While loop wrapping to ensure program does not continue until valid input is taken

	while (true) {

		cout << "What is the face value of the bond?" << endl;
		cin >> f_v;
		if (std::cin.fail()) {                                                        // cin.fail raises an error flag for incorrect input type
			std::cin.clear();                                                         // cin.clear clears the error flag so program can continue 
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');       //the template class "numeric_limits" takes a type of std::streamsize and applies its max function to find the total amount of characters to be cleared in buffer for new input to be entered

			cout << "Invalid input, please enter a number" << endl;

		}
		else{
			break;
		}
	}


	while (true) {

		cout << "What is annual coupon rate in percent form?" << endl;
		cin >> c_r;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			cout << "Invalid input, please enter a number" << endl;
		
		}
		else {
			break;
		}
	}

	while (true) {

		cout << "What is the number of years to maturity?" << endl;
		cin >> t;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			cout << "Invalid input, please enter a number" << endl;
			

		}
		else {
			break;
		}
	
	}



	cout << "Do you have the yield to maturity? Type 1 or 2 to continue" << endl;
	cout << "1. Yes" << endl;
	cout << "2. No" << endl;
	cin >> check;


	switch (check) {

	case 1:                                                                                                         /*If "Yes" is chosen*/
	{
		cout << "What is the Yield to Maturity in percent form?" << endl;
		cin >> ytm;

		present_value = annuity_pv(c_p(c_r, f_v), ytm, t) + faceval_pv(f_v, ytm, t);

		cout << "The present value of your bond is: " << present_value << endl;
		cout << "The present value of your coupon payments is: " << annuity_pv(c_p(c_r, f_v), ytm, t) << endl;
		cout << "Your coupon payment is: " << c_p(c_r, f_v) << endl;
		cout << "Your result from exponential equation is: " << expon(t, ytm);
		break;
	}

	case 2:                                                                                                       /*If "No" is chosen*/
	{
		
		cout << "What is the present value of your bond?" << endl;
		cin >> present_value;

		approximated_ytm = approx_ytm(c_ptr, f_v, present_value, c_r, t);

		
		cout << "The approximated Yield to Maturity based on input is" << approximated_ytm * 100 << endl;                      //*100 To show result in percentage form
		cout << "The present value of your bond is: " << present_value << endl;
		cout << "The present value of your coupon payments is: " << annuity_pv(c_p(c_r, f_v), approximated_ytm, t) << endl;
		cout << "Your coupon payment is: " << c_p(c_r, f_v) << endl;
		cout << "Your result from exponential equation is: " << expon(t, approximated_ytm);
		break;

	}
   }
	return 0;

}