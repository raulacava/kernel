/* second.c */
int isStrong(int n) {
	int temp;
	long s;
	for(temp=n,s=0;n!=0;n=n/10)
		s=s+factorial(n%10);
	return ((s==temp)?1:0);
}

