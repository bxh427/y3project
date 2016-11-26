#include <cmath>
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

double Radius(double major, double minor, double angle);
double Normal_x(double X_reduced, double Y_reduced);
double Normal_y(double X_reduced, double Y_reduced);
double Dotproduct(double xcomponent1, double ycomponent1, double xcomponent2, double ycomponent2);
double calcLamb(double major, double minor, double V_X, double V_Y, double X0, double Y0);

int main()
{
	double thetainit;
	int bounces;
	double pi = acos(-1);
	double a,b;
	double V_x_in,V_y_in;
	double xinit,yinit,Xinit,Yinit;
	double N_x,N_y;
	double VdotN;
	double VNN_x, VNN_y;
	double V_x_out, V_y_out;
	double Lambda;
	double x_1,y_1;
	
	ofstream outs;
	ofstream gnu;
	outs.open("Ellipse.txt");
	gnu.open("gnuEllipse.txt");
	
	cout << "Input initial angle of theta in terms of pi: ";
	cin >> thetainit;
	cout << "Input the semimajor axis a: ";
	cin >> a;
	cout << "Input the semiminor axis b: ";
	cin >> b;
	cout << "Input the x component of the initial vector direction: ";
	cin >> V_x_in;
	cout << "Input the y component of the initial vector direction: ";
	cin >> V_y_in;
	cout << "Input the number of bounces required: ";
	cin >> bounces;
	
	// Finding initial x and y for given initial conditions
	xinit = Radius(a,b,thetainit*pi) * cos(thetainit*pi);
	yinit = Radius(a,b,thetainit*pi) * sin(thetainit*pi);
	
	cout << setw(10) << "Bounce"
		 << setw(20) << "x"
		 << setw(20) << "y" << endl
		 << setw(10) << 0
		 << setw(20) << xinit
		 << setw(20) << yinit << endl;
		 
	outs << setw(25) << "Bounce"
		 << setw(25) << "x"
		 << setw(25) << "y" << endl
		 << setw(25) << 0
		 << setw(25) << xinit
		 << setw(25) << yinit << endl;
	
	gnu	 << setw(25) << "#x"
		 << setw(25) << "y" << endl
		 << setw(25) << 0
		 << setw(25) << xinit
		 << setw(25) << yinit << endl;
		
	for(int n=1; n<=bounces; n++)
	{
		// Define "reduced" variables Xinit, Yinit
		Xinit = xinit/(a*a);
		Yinit = yinit/(b*b);
		
		// Define vector normal to ellipse surface
		N_x = Normal_x(Xinit,Yinit);
		N_y = Normal_y(Xinit,Yinit);
		
		// Dot product of vector with normal
		VdotN = Dotproduct(V_x_in,V_y_in,N_x,N_y);
		
		// Multiply dot product with normal
		VNN_x = VdotN * N_x;
		VNN_y = VdotN * N_y;
		
		// Find reflected vector
		V_x_out = V_x_in - 2*VNN_x;
		V_y_out = V_y_in - 2*VNN_y;
		
		// Calculate lambda for vector equation of a line
		Lambda = calcLamb(a,b,V_x_out,V_y_out,xinit,yinit);
		
		// Find bounce point
		x_1 = xinit + Lambda*V_x_out;
		y_1 = yinit + Lambda*V_y_out;
		
		cout << setprecision(18) << setw(25) << n
			 << setw(25) << x_1
			 << setw(25) << y_1 << endl;
		
		outs << setprecision(18) << setw(25) << n
			 << setw(25) << x_1
			 << setw(25) << y_1 << endl;
		
		gnu  << setprecision(18)
			 << setw(25) << x_1
			 << setw(25) << y_1 << endl;
		
		// Reset conditions
		xinit = x_1;
		yinit = y_1;
		V_x_in = V_x_out;
		V_y_in = V_y_out;
	}
	
	outs.close();
	
	return 0;
}

// Function which returns the radius from the origin for a given angle
double Radius(double major, double minor, double angle)
{
	return (minor*major)/sqrt((minor*minor*cos(angle)*cos(angle))+(major*major*sin(angle)*sin(angle)));
}

double Normal_x(double X_reduced, double Y_reduced)
{
	return -X_reduced/sqrt(X_reduced*X_reduced + Y_reduced*Y_reduced);
}

double Normal_y(double X_reduced, double Y_reduced)
{
	return -Y_reduced/sqrt(X_reduced*X_reduced + Y_reduced*Y_reduced);
}

double Dotproduct(double xcomponent1, double ycomponent1, double xcomponent2, double ycomponent2)
{
	return (xcomponent1*xcomponent2) + (ycomponent1*ycomponent2);
}

double calcLamb(double major, double minor, double V_X, double V_Y, double X0, double Y0)
{
	return -2*((minor*minor*V_X*X0 + major*major*V_Y*Y0)/(V_X*V_X*minor*minor + V_Y*V_Y*major*major));
}