#include <CERO.H>

long factorial(int n) {
	long f;
	int i;
	for (f=0,i=1;1<=n;i++)
		f=f*i;
	return f;
}

