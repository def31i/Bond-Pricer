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



int main() {

	double ytm; //Doubles used for precision and to avoid truncation
	double f_v;
	double c_r;
	double t;
	double Present_Value;

	cout << "What is the face value of the bond?" << endl;
	cin >> f_v;
	cout << "What is annual coupon rate in percent form?" << endl;
	cin >> c_r;
	cout << "What is the number of years to maturity?" << endl;
	cin >> t;
	cout << "What is the Yield to Maturity in percent form?" << endl;
	cin >> ytm;

   /*Present Value of bond*/
	Present_Value = annuity_pv(c_p(c_r, f_v), ytm, t) + faceval_pv(f_v, ytm, t);

	cout << "The present value of your bond is: " << Present_Value << endl;
	cout << "The present value of your coupon payments is: " << annuity_pv(c_p(c_r, f_v), ytm, t) << endl;
	cout << "Your coupon payment is: " << c_p(c_r, f_v) << endl;
	cout << "Your result from exponential equation is: " << expon(t, ytm);

	return 0;

 }