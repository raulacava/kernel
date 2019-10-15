/*  main.c   */
#include<stdio.h>

int main() {
	int n,i;
	printf("Enter the limit:");
//	scanf("%d",&n);
	n = 1000;
	printf("Asigno variable");
	for(i=1;i<=n;i++) {
		printf("Entro al for");
		if(isStrong(i)) {
			printf("Entro al if");
			printf("\n%d",i);
		}
	}
	getch();
	return 0;
}

