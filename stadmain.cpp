#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

using namespace std;

struct Vector
{
	double xcomp;
	double ycomp;
};

Vector getInitPos(char SIDEINIT,double A,double B);
Vector getNorm(Vector POS,double A,double B);
double DotProduct(Vector vec1,Vector vec2);
double solveQuadEq(double A, double B, double C);
Vector ScalVec(double scal,Vector vec);
Vector VecOut(Vector VecIn,Vector Vec2);
Vector TIncSide(Vector Vinc,Vector Pos,double A,double B);
Vector BIncSide(Vector Vinc,Vector Pos,double A,double B);
Vector LIncSide(Vector Vinc,Vector Pos,double A,double B);
Vector RIncSide(Vector Vinc,Vector Pos,double A,double B);

int main()
{
	double a,b;
	char sideinit;
	Vector InitPos;
	Vector V_in;
	Vector Norm;
	double VdotN;
	Vector VNN;
	Vector V_out;
	Vector IncPos;
	int bounces;
	
	ofstream outs;
	ofstream gnu;
	outs.open("Stadium.txt");
	gnu.open("gnuStadium.txt");
	
	// Establish initial conditions
	cout << "Input the height of the stadium: ";
	cin  >> a;
	cout << "Input the width of the rectangular part of the stadium: ";
	cin  >> b;
	cout << "Input which side the ball starts from according to:"
		 << "\n Top, straight = t"
		 << "\n Bottom, straight = b"
		 << "\n Left, curved = l"
		 << "\n Right, curved = r" << endl;
	cin  >> sideinit;
	
	InitPos = getInitPos(sideinit,a,b);
	
	cout << "Input the x component of the incoming vector: ";
	cin  >> V_in.xcomp;
	cout << "Input the y component of the incoming vector: ";
	cin  >> V_in.ycomp;
	cout << "Input the number of bounces required: ";
	cin  >> bounces;

	cout << setw(6)  << "Bounce"
		 << setw(20) << "x"
		 << setw(20) << "y" << endl
		 << setw(6) << 0
		 << setw(20) << InitPos.xcomp
		 << setw(20) << InitPos.ycomp << endl;
	outs << setw(15) << "Bounce"	
		 << setw(25) << "x"
		 << setw(25) << "y" << endl
		 << setw(15) << 0
		 << setw(25) << InitPos.xcomp
		 << setw(25) << InitPos.ycomp << endl;
	gnu  << setw(25) << "#x"
		 << setw(25) << "y" << endl
		 << setw(25) << InitPos.xcomp
		 << setw(25) << InitPos.ycomp << endl;
	
	for(int n=1;n<=bounces;n++)
	{
		// Find normal at surface
		Norm = getNorm(InitPos,a,b);
		
		// Dot incoming vector with normal
		VdotN = DotProduct(V_in,Norm);
		
		// Multiply dot product by normal
		VNN = ScalVec(VdotN,Norm);
		
		// Find outward vector
		V_out = VecOut(V_in,VNN);
		
		// Find the incident point
		if(InitPos.ycomp==a)
		{
			IncPos = TIncSide(V_out,InitPos,a,b);
		}
		
		else if(InitPos.ycomp==0)
		{
			IncPos = BIncSide(V_out,InitPos,a,b);
		}
		
		else if(InitPos.ycomp!=a && InitPos.ycomp!=0 && InitPos.xcomp<0)
		{
			IncPos = LIncSide(V_out,InitPos,a,b);
		}
		
		else if(InitPos.ycomp!=a && InitPos.ycomp!=0 && InitPos.xcomp>0)
		{
			IncPos = RIncSide(V_out,InitPos,a,b);
		}
		
		cout << setprecision(10) << setw(6) << n
			 << setw(20) << IncPos.xcomp
			 << setw(20) << IncPos.ycomp << endl;
		outs << setw(15) << n
			 << setw(25) << IncPos.xcomp
			 << setw(25) << IncPos.ycomp << endl;
		gnu  << setw(25) << IncPos.xcomp
			 << setw(25) << IncPos.ycomp << endl;
			 
		InitPos = IncPos;
		V_in = V_out;
	}
	
	outs.close();
	gnu.close();
	
	return 0;
}

Vector getInitPos(char SIDEINIT, double A, double B)
{
	Vector INITPOS;
	double theta;
	
	if(SIDEINIT=='t')
	{
		INITPOS.ycomp = A;
		cout << "Input the x coordinate between 0 and " << B << " : ";
		cin  >> INITPOS.xcomp;
	}
	
	if(SIDEINIT=='b')
	{
		INITPOS.ycomp = 0;
		cout << "Input the x coordinate between 0 and " << B << " : ";
		cin  >> INITPOS.xcomp;
	}
	
	if(SIDEINIT=='l')
	{
		cout << "Input the angle theta from the negative x axis measured as if the end cap was a full circle"
			 << endl << "between pi/2 and -pi/2: ";
		cin  >> theta;
		INITPOS.xcomp = -A*0.5*cos(theta);
		INITPOS.ycomp = A*0.5*(1+sin(theta));
	}
	
	if(SIDEINIT=='r')
	{
		cout << "Input the angle theta from the positive x axis measured as if the end cap was a full circle"
			 << endl << "between pi/2 and -pi/2: ";
		cin  >> theta;
		INITPOS.xcomp = B + A*0.5*cos(theta);
		INITPOS.ycomp = A*0.5*(1+sin(theta));
	}
	
	return INITPOS;
}

Vector getNorm(Vector POS, double A, double B)
{
	Vector NORM;
	
	if(POS.ycomp==0)
	{
		NORM.xcomp = 0;
		NORM.ycomp = 1;
	}
	
	else if(POS.ycomp==A)
	{
		NORM.xcomp = 0;
		NORM.ycomp = -1;
	}
	
	else
	{
		NORM.xcomp = (-1*POS.xcomp)/sqrt((POS.xcomp*POS.xcomp)+(POS.ycomp*POS.ycomp));
		NORM.ycomp = (-1*POS.ycomp)/sqrt((POS.xcomp*POS.xcomp)+(POS.ycomp*POS.ycomp));
	}
	
	return NORM;
}

double DotProduct(Vector vec1, Vector vec2)
{
	return (vec1.xcomp*vec2.xcomp) + (vec1.ycomp*vec2.ycomp);
}

double solveQuadEq(double A, double B, double C)
{
	double Q;
	Q = -0.5*(B-sqrt(B*B - 4*A*C));
	return Q/A;
}

Vector ScalVec(double scal, Vector vec)
{
	Vector scalvec;
	scalvec.xcomp = scal*vec.xcomp;
	scalvec.ycomp = scal*vec.ycomp;
	
	return scalvec;
}

Vector VecOut(Vector VecIn, Vector Vec2)
{
	Vector VOUT;
	VOUT.xcomp = VecIn.xcomp - 2*Vec2.xcomp;
	VOUT.ycomp = VecIn.ycomp - 2*Vec2.ycomp;
	
	return VOUT;
}

Vector TIncSide(Vector Vinc,Vector Pos,double A,double B)
{
	Vector INTERCEPT;
	double grad = Vinc.ycomp/Vinc.xcomp;
	double L;
	double quada,quadb,quadc;
	
	// Left hand cap intercept
	if(grad > 0 && grad < (A/Pos.xcomp))
	{
		quada = Vinc.xcomp*Vinc.xcomp + Vinc.ycomp*Vinc.ycomp;
		quadb = 2*(Vinc.xcomp*Pos.xcomp + Vinc.ycomp*(Pos.ycomp - 0.5*A));
		quadc = Pos.xcomp*Pos.xcomp + Pos.ycomp*Pos.ycomp - A*Pos.ycomp;
		L = solveQuadEq(quada,quadb,quadc);
		INTERCEPT.xcomp = Pos.xcomp + L*Vinc.xcomp;
		INTERCEPT.ycomp = Pos.ycomp + L*Vinc.ycomp;
	}
	
	// Right hand cap intercept
	else if(grad < 0 && grad > (A/(Pos.xcomp-B)))
	{
		quada = Vinc.xcomp*Vinc.xcomp + Vinc.ycomp*Vinc.ycomp;
		quadb = 2*(Vinc.xcomp*(Pos.xcomp-B)	+ Vinc.ycomp*(Pos.ycomp - 0.5*A));
		quadc = B*B - 2*Pos.xcomp*B;
		L = solveQuadEq(quada,quadb,quadc);
		INTERCEPT.xcomp = Pos.xcomp + L*Vinc.xcomp;
		INTERCEPT.ycomp = Pos.ycomp + L*Vinc.ycomp;
	}
	
	// Bottom rectangular side intercept
	else
	{
		INTERCEPT.ycomp = 0;
		L = -1*(Pos.ycomp/Vinc.ycomp);
		INTERCEPT.xcomp = Pos.xcomp + L*Vinc.xcomp;
	}
	
	return INTERCEPT;
}

Vector BIncSide(Vector Vinc,Vector Pos,double A,double B)
{
	Vector INTERCEPT;
	double grad = Vinc.ycomp/Vinc.xcomp;
	double L;
	double quada,quadb,quadc;
	
	// Right hand cap intercept
	if(grad > 0 && grad < (A/(B-Pos.xcomp)))
	{
		quada = Vinc.xcomp*Vinc.xcomp + Vinc.ycomp*Vinc.ycomp;
		quadb = 2*(Vinc.xcomp*(Pos.xcomp-B)	+ Vinc.ycomp*(Pos.ycomp - 0.5*A));
		quadc = B*B - 2*Pos.xcomp*B;
		L = solveQuadEq(quada,quadb,quadc);
		INTERCEPT.xcomp = Pos.xcomp + L*Vinc.xcomp;
		INTERCEPT.ycomp = Pos.ycomp + L*Vinc.ycomp;
	}
	
	// Left hand cap intercept
	else if(grad < 0 && grad > (-1*A/Pos.xcomp))
	{
		quada = Vinc.xcomp*Vinc.xcomp + Vinc.ycomp*Vinc.ycomp;
		quadb = 2*(Vinc.xcomp*Pos.xcomp + Vinc.ycomp*(Pos.ycomp - 0.5*A));
		quadc = Pos.xcomp*Pos.xcomp + Pos.ycomp*Pos.ycomp - A*Pos.ycomp;
		L = solveQuadEq(quada,quadb,quadc);
		INTERCEPT.xcomp = Pos.xcomp + L*Vinc.xcomp;
		INTERCEPT.ycomp = Pos.ycomp + L*Vinc.ycomp;
	}
	
	else
	{
		INTERCEPT.ycomp = A;
		L = (A-Pos.ycomp)/Vinc.ycomp;
		INTERCEPT.xcomp = Pos.xcomp + L*Vinc.xcomp;
	}
	
	return INTERCEPT;
}

Vector LIncSide(Vector Vinc,Vector Pos,double A,double B)
{
	Vector INTERCEPT;
	double grad = Vinc.ycomp/Vinc.xcomp;
	double L;
	double quada,quadb,quadc;
	
	// Left hand cap intercept
	if(grad > ((Pos.ycomp - A)/Pos.xcomp) || grad < (Pos.ycomp/Pos.xcomp) || Vinc.xcomp<0)
	{
		L = -2*(Vinc.xcomp*Pos.xcomp + Vinc.ycomp*(Pos.ycomp - 0.5*A))/(Vinc.xcomp*Vinc.xcomp + Vinc.ycomp*Vinc.ycomp);
		INTERCEPT.xcomp = Pos.xcomp + L*Vinc.xcomp;
		INTERCEPT.ycomp = Pos.ycomp + L*Vinc.ycomp;
	}
	
	// Top rectangular side intercept
	else if(grad > ((A-Pos.ycomp)/(B-Pos.xcomp)) && grad < ((Pos.ycomp - A)/Pos.xcomp))
	{
		INTERCEPT.ycomp = A;
		L = (A-Pos.ycomp)/Vinc.ycomp;
		INTERCEPT.xcomp = Pos.xcomp + L*Vinc.xcomp;
	}
	
	// Bottom rectangular side intercept
	else if(grad < (Pos.ycomp/(Pos.xcomp-B)) && grad > (Pos.ycomp/Pos.xcomp))
	{
		INTERCEPT.ycomp = 0;
		L = -1*(Pos.ycomp/Vinc.ycomp);
		INTERCEPT.xcomp = Pos.xcomp + L*Vinc.xcomp;
	}
	
	// Right hand cap intercept
	else
	{
		quada = Vinc.xcomp*Vinc.xcomp + Vinc.ycomp*Vinc.ycomp;
		quadb = 2*(Vinc.xcomp*(Pos.xcomp-B)	+ Vinc.ycomp*(Pos.ycomp - 0.5*A));
		quadc = B*B - 2*Pos.xcomp*B;
		L = solveQuadEq(quada,quadb,quadc);
		INTERCEPT.xcomp = Pos.xcomp + L*Vinc.xcomp;
		INTERCEPT.ycomp = Pos.ycomp + L*Vinc.ycomp;
	}
	
	return INTERCEPT;
}

Vector RIncSide(Vector Vinc,Vector Pos,double A,double B)
{
	Vector INTERCEPT;
	double grad = Vinc.ycomp/Vinc.xcomp;
	double L;
	double quada,quadb,quadc;
	
	// Right hand cap intercept
	if(grad < ((Pos.ycomp-A)/(Pos.xcomp-B)) || grad < (Pos.ycomp/(Pos.xcomp-B)) || Vinc.xcomp > 0)
	{
		L = -2*(Vinc.xcomp*(Pos.xcomp-B) + Vinc.ycomp*(Pos.ycomp - 0.5*A))/(Vinc.xcomp*Vinc.xcomp + Vinc.ycomp*Vinc.ycomp);
		INTERCEPT.xcomp = Pos.xcomp + L*Vinc.xcomp;
		INTERCEPT.ycomp = Pos.ycomp + L*Vinc.ycomp;
	}
	
	// Bottom rectangular side intercept
	else if(grad > (Pos.ycomp/Pos.xcomp) && grad < (Pos.ycomp/(Pos.xcomp-B)))
	{
		INTERCEPT.ycomp = 0;
		L = -1*(Pos.ycomp/Vinc.ycomp);
		INTERCEPT.xcomp = Pos.xcomp + L*Vinc.xcomp;
	}
	
	// Top rectangular side intercept
	else if(grad < ((Pos.ycomp-A)/Pos.xcomp) && grad > ((Pos.ycomp-A)/(Pos.xcomp-B)))
	{
		INTERCEPT.ycomp = A;
		L = (A-Pos.ycomp)/Vinc.ycomp;
		INTERCEPT.xcomp = Pos.xcomp + L*Vinc.xcomp;
	}
	
	// Left hand cap intercept
	else
	{
		quada = Vinc.xcomp*Vinc.xcomp + Vinc.ycomp*Vinc.ycomp;
		quadb = 2*(Vinc.xcomp*Pos.xcomp + Vinc.ycomp*(Pos.ycomp - 0.5*A));
		quadc = Pos.xcomp*Pos.xcomp + Pos.ycomp*Pos.ycomp - A*Pos.ycomp;
		L = solveQuadEq(quada,quadb,quadc);
		INTERCEPT.xcomp = Pos.xcomp + L*Vinc.xcomp;
		INTERCEPT.ycomp = Pos.ycomp + L*Vinc.ycomp;
	}
	
	return INTERCEPT;
}




