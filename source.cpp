#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;

class Matrix{
public:
int n=0; //dimension of polynom
double first=0;//interval's first point
double second=0;//interval's second point
double tol=0;//tolerance
int iteNum=0;//iteration number
void getParameters(double* val, double frst, double sec, double tl,int size);//gets parameters from main method and declares of function
double returnRes(double val);//returns the value of function for given input
void results();//prints the roots of bisection secant and hybrid method
void intervalBisect();//evoluates the root using bisection method
void secantMet(double frst,double scond,int type);//evaluates the root using secant method
void Hybrid();//evaluates the root using hybrid method
double *function;//an array that holds the coeffiencts of function 
};

//the method that gets parameters from main method and declares function 
void Matrix::getParameters(double *val,double frst, double sec, double tl,int size){
	first=frst;
	second=sec;
	tol=tl;
	n=size;
	function=new double[size];
	for(int i=0;i<size;i++)
	function[i]=val[i];	
}
//the method that returns the value of function for given input
double Matrix::returnRes(double val){
	double res=0;
	
	for(int i=0;i<n;i++){
	res += function[i]*pow(val,i);
}
	
	return res;
}
//the method that evaluates the root using bisection method and prints the root and iteration number for bisection method
void Matrix::intervalBisect(){
	double a=first;
	double b=second;
	double m=0;
	double res1=0;
	double res2=0;
	while(fabs(b-a)>tol){
		m=(a + (b-a)/2);
		
		res1=returnRes(a);
		res2=returnRes(m);
		
		if(res1*res2>0)
		a=m;
		else
		b=m;
		
		iteNum++;
	}
	
	cout<<"Root of bisection method: "<<m<<endl;
}
//the method that evaluates the root using secant method and prints the root and iteration number for secant method and also hybrid methods' last part is calculated
void Matrix::secantMet(double frst,double scond,int type){
	double a=frst;
	double b=scond;
	double res1=0,res2=0;
	double temp=0;
	while(fabs(b-a)>tol){
		res1=returnRes(a);
		res2=returnRes(b);
		temp=b;
		b=b-((res2)*(b-a)/(res2-res1));
		a=temp;
		iteNum++;
	}
	
	if(!type)
	cout<<"Root of secant method: "<<b<<endl;
	
	else
	cout<<"Root of hybrid method: "<<b<<endl;
}
//the method that evaluates the root using hybrid method and prints the root and iteration number for hybrid method
void Matrix::Hybrid(){
	double a=first;
	double b=second;
	double m=0;
	double res1=0;
	double res2=0;
	for(int i=0;i<2;i++){
		m=(a + (b-a)/2);
		
		res1=returnRes(a);
		res2=returnRes(m);
		
		if(res1*res2>0)
		a=m;
		else
		b=m;
		iteNum++;
	}
	
	secantMet(a,b,1);
}
//this is the result part, prints root and iteration number for each method
void Matrix::results(){
	intervalBisect();
	cout<<"Iteration number is: "<<iteNum<<endl;
	iteNum=0;
	secantMet(first,second,0);
	cout<<"Iteration number is: "<<iteNum<<endl;
	iteNum=0;
	Hybrid();
	cout<<"Iteration number is: "<<iteNum<<endl;
}


int main(int argc,char * argv[]){
	
	if(argc<=5){
		cout<<"Wrong input format."<<endl;
		return 0;
	}
//gets the coeffiencts of polynom by using parameters
double* values= new double[argc-4];
for(int i=0;i<argc-4;i++){
values[argc-5-i]=atof(argv[i+1]);
}

int size=argc-4;
double tol=atof(argv[argc-1]);
double first=atof(argv[argc-3]);
double second=atof(argv[argc-2]);

//class to calculate roots 
Matrix m;
m.getParameters(values,first,second,tol,size);
m.results();

return 0;

}

