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
	outs.open("Rectangle.txt");
	gnu.open("gnuRectangle.txt");
	
	// Establish initial conditions
	cout << "Input the height of the rectangle: ";
	cin  >> a;
	cout << "Input the width of the rectangle: ";
	cin  >> b;
	cout << "Input which side the ball starts from according to:"
		 << "\n Top = t"
		 << "\n Bottom = b"
		 << "\n Left = l"
		 << "\n Right = r" << endl;
	cin  >> sideinit;
	
	InitPos = getInitPos(sideinit,a,b);
	
	cout << "Input the x component of the incoming vector: ";
	cin  >> V_in.xcomp;
	cout << "Input the y component of the incoming vector: ";
	cin  >> V_in.ycomp;
	cout << "Input the number of bounces required: ";
	cin  >> bounces;

	/*cout << setw(6) << "Bounce"
		 << setw(20) << "InitPosx"
		 << setw(20) << "InitPosy"
		 << setw(20) << "IncPosx"
		 << setw(20) << "IncPosy"
		 << setw(20) << "Normx"
		 << setw(20) << "Normy"
		 << setw(20) << "VdotN"
		 << setw(20) << "VNNx"
		 << setw(20) << "VNNy" << endl
		 << setw(6) << 0
		 << setw(20) << InitPos.xcomp
		 << setw(20) << InitPos.ycomp
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
		 << setw(25) << InitPos.ycomp << endl;*/
	
	for(int n=1;n<=bounces;n++)
	{
		cout << "n= " << n << endl;
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
		
		else if(InitPos.xcomp==0)
		{
			IncPos = LIncSide(V_out,InitPos,a,b);
		}
		
		else if(InitPos.xcomp==b)
		{
			IncPos = RIncSide(V_out,InitPos,a,b);
		}
		
	/*	cout << setprecision(10) << setw(6) << n
			 << setw(20) << InitPos.xcomp
			 << setw(20) << InitPos.ycomp
			 << setw(20) << IncPos.xcomp
			 << setw(20) << IncPos.ycomp
			 << setw(20) << Norm.xcomp
			 << setw(20) << Norm.ycomp
			 << setw(20) << VdotN
			 << setw(20) << VNN.xcomp
			 << setw(20) << VNN.ycomp << endl;
		outs << setw(15) << n
			 << setw(25) << IncPos.xcomp
			 << setw(25) << IncPos.ycomp << endl;
		gnu  << setw(25) << IncPos.xcomp
			 << setw(25) << IncPos.ycomp << endl; */
			 
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
		INITPOS.xcomp = 0;
		cout << "Input the y coordinate between 0 and " << A << " : ";
		cin  >> INITPOS.ycomp;
	}
	
	if(SIDEINIT=='r')
	{
		INITPOS.xcomp = B;
		cout << "Input the y coordinate between 0 and " << A << " : ";
		cin  >> INITPOS.xcomp;
	}
	
	return INITPOS;
}

Vector getNorm(Vector POS, double A, double B)
{
	Vector NORM;
	if(POS.xcomp==0)
	{
		NORM.xcomp = 1;
		NORM.ycomp = 0;
	}
	
	else if(POS.xcomp==B)
	{
		NORM.xcomp = -1;
		NORM.ycomp = 0;
	}
	
	else if(POS.ycomp==0)
	{
		NORM.xcomp = 0;
		NORM.ycomp = 1;
	}
	
	else if(POS.ycomp==A)
	{
		NORM.xcomp = 0;
		NORM.ycomp = -1;
	}
	
	return NORM;
}

double DotProduct(Vector vec1, Vector vec2)
{
	return (vec1.xcomp*vec2.xcomp) + (vec1.ycomp*vec2.ycomp);
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
	cout << "Tgrad " << grad << endl;
	
	if(grad > 0 && grad < (A/Pos.xcomp))
	{
		INTERCEPT.xcomp = 0;
		L = -1*(Pos.xcomp/Vinc.xcomp);
		INTERCEPT.ycomp = Pos.ycomp + L*Vinc.ycomp;
		cout << "return T1" << endl;
	}
	
	else if(grad < 0 && grad > (A/(Pos.xcomp-B)))
	{
		INTERCEPT.xcomp = B;
		L = (B-Pos.xcomp)/Vinc.xcomp;
		INTERCEPT.ycomp = Pos.ycomp + L*Vinc.ycomp;
		cout << "return T2" << endl;
	}
	
	else
	{
		INTERCEPT.ycomp = 0;
		L = -1*(Pos.ycomp/Vinc.ycomp);
		INTERCEPT.xcomp = Pos.xcomp + L*Vinc.xcomp;
		cout << "return T3" << endl;
	}
	
	return INTERCEPT;
}

Vector BIncSide(Vector Vinc,Vector Pos,double A,double B)
{
	Vector INTERCEPT;
	double grad = Vinc.ycomp/Vinc.xcomp;
	double L;
	cout << "Bgrad " << grad << endl;
	
	if(grad > 0 && grad < (A/(B-Pos.xcomp)))
	{
		INTERCEPT.xcomp = B;
		L = (B-Pos.xcomp)/Vinc.xcomp;
		INTERCEPT.ycomp = Pos.ycomp + L*Vinc.ycomp;
		cout << "return B1 and L = " << L << " INTERCEPT.xcomp = " << INTERCEPT.xcomp << "INTERCEPT.ycomp = " << INTERCEPT.ycomp << endl;
	}
	
	else if(grad < 0 && grad > (-1*A/Pos.xcomp))
	{
		INTERCEPT.xcomp = 0;
		L = -1*(Pos.xcomp/Vinc.xcomp);
		INTERCEPT.ycomp = Pos.ycomp + L*Vinc.ycomp;
		cout << "return B2" << endl;
	}
	
	else
	{
		INTERCEPT.ycomp = A;
		L = (A-Pos.ycomp)/Vinc.ycomp;
		INTERCEPT.xcomp = Pos.xcomp + L*Vinc.xcomp;
		cout << "return B3" << endl;
	}
	
	return INTERCEPT;
}

Vector LIncSide(Vector Vinc,Vector Pos,double A,double B)
{
	Vector INTERCEPT;
	double grad = Vinc.ycomp/Vinc.xcomp;
	double L;
	cout << "Lgrad " << grad << endl;
	
	if(grad > ((A-Pos.ycomp)/B))
	{
		INTERCEPT.ycomp = A;
		L = (A-Pos.ycomp)/Vinc.ycomp;
		INTERCEPT.xcomp = Pos.xcomp + L*Vinc.xcomp;
		cout << "return L1" << endl;
	}
	
	else if(grad < (-1*Pos.ycomp/B))
	{
		INTERCEPT.ycomp = 0;
		L = -1*(Pos.ycomp/Vinc.ycomp);
		INTERCEPT.xcomp = Pos.xcomp + L*Vinc.xcomp;
		cout << "return L2" << endl;
	}
	
	else
	{
		INTERCEPT.xcomp = B;
		L = (B-Pos.xcomp)/Vinc.xcomp;
		INTERCEPT.ycomp = Pos.ycomp + L*Vinc.ycomp;
		cout << "return L3" << endl;
	}
	
	return INTERCEPT;
}

Vector RIncSide(Vector Vinc,Vector Pos,double A,double B)
{
	Vector INTERCEPT;
	double grad = Vinc.ycomp/Vinc.xcomp;
	double L;
	cout << "Rgrad " << grad << endl;
	
	if(grad > (Pos.ycomp/B))
	{
		INTERCEPT.ycomp = 0;
		L = -1*(Pos.ycomp/Vinc.ycomp);
		INTERCEPT.xcomp = Pos.xcomp + L*Vinc.xcomp;
		cout << "return R1" << endl;
	}
	
	else if(grad < 0 && grad < ((Pos.ycomp-A)/B))
	{
		INTERCEPT.ycomp = A;
		L = (A-Pos.ycomp)/Vinc.ycomp;
		INTERCEPT.xcomp = Pos.xcomp + L*Vinc.xcomp;
		cout << "return R2" << endl;
	}
	
	else
	{
		INTERCEPT.xcomp = 0;
		L = -1*(Pos.xcomp/Vinc.xcomp);
		INTERCEPT.ycomp = Pos.ycomp + L*Vinc.ycomp;
		cout << "return R3" << endl;
	}
	
	return INTERCEPT;
}



