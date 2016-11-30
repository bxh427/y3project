#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main()
{
	double thetastart;
	double alpha;
	double bounces;
	double pi = acos(-1);
	
	ofstream outs;
	ofstream gnu;
	outs.open("Circle.txt");
	gnu.open("Circlegnu.txt");
	
	cout << "This program calculates subsequent positions of bounces of a billiard ball within a circular table."
		 << "\n" << "The circular table is set at the origin and the results are independent of the table radius."
		 << "\n" << "The angle theta is the angle measured from the positive axis to the ball's location in radians."
		 << "\n" << "The angle alpha is the angle measured from the tangent of the circle and indicates the"
		 << "\n" << "direction of the ball's bounce. It is measured anticlockwise from the tangent in radians."
		 << "\n" << "Please input the initial value of theta in units of pi and press [rtn]: ";
	cin  >> thetastart;
	cout << "Please input the value of alpha in units of pi and press [rtn]: ";
	cin  >> alpha;
	cout << "Please input the number of bounces required and press [rtn]: ";
	cin	 >> bounces;
	
	
	cout << "\n" << "For a billiard ball starting at a position "
		 << thetastart << " pi from the positive x axis and making bounces of angle "
		 << alpha << " pi, the following path is taken: \n"
		 << setw(10) << "Bounce"
	//	 << setw(25) << "Theta/rads"
	//	 << setw(25) << "Theta/pi"
		 << setw(25) << "x position"
		 << setw(25) << "y position" << endl;
	
	outs << "\n" << "For a billiard ball starting at a position "
		 << thetastart << " pi from the positive x axis and making bounces of angle "
		 << alpha << " pi, the following path is taken: \n"
		 << setw(10) << "Bounce"
	//	 << setw(25) << "Theta/rads"
	//	 << setw(25) << "Theta/pi"
		 << setw(25) << "x position"
		 << setw(25) << "y position" << endl;
	
	gnu  << setw(25) << "#x position"
		 << setw(25) << "y position" << endl;
	
	
	double theta = thetastart;
		 
	for(int n=0; n<=bounces; n++)
	{
		cout << setprecision(18) << setw(10) << n
		//	 << setw(25) << theta*pi
		//	 << setw(25) << theta
			 << setw(25) << cos(theta*pi)
			 << setw(25) << sin(theta*pi) << endl;
			 
		outs << setprecision(18) << setw(10) << n
		//	 << setw(25) << theta*pi
		//	 << setw(25) << theta
			 << setw(25) << cos(theta*pi)
			 << setw(25) << sin(theta*pi) << endl;
		
		gnu  << setprecision(18) << setw(25) << cos(theta*pi)
			 << setw(25) << sin(theta*pi) << endl;
		
		theta+=2*alpha;
		
		if(theta>=2) theta-=2;
	}
	
	outs.close();
	gnu.close();
	
	return 0;
}

