#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<omp.h>
using namespace std;

int main(int argc, char *argv[]){
	int *a;
	int *b;
	int *c;	
	int n=10000;
	int np;
	int tt=5;
	int i;
double initialtime,finaltime;
initialtime=omp_get_wtime();

a=(int *)malloc(sizeof(int)*n);
b=(int *)malloc(sizeof(int)*n);
c=(int *)malloc(sizeof(int)*n);

for(int i=0;i<n;i++){
	a[i]=i;
	b[i]=i;
}
for(int i=0;i<n;i++){
	c[i]=a[i]+b[i];
	
}
cout<<endl;
cout<<"i\ta[i]\t+\tb[i]\t=\tc[i]\n"<<endl;
cout<<endl;
for(int i=0;i<n;i++){
cout<<i<<"\t"<<a[i]<<"\t\t"<<b[i]<<"\t\t"<<c[i]<<"\n"<<endl;
}
finaltime=omp_get_wtime();
cout<<"Total Serial Execution time is "<<finaltime-initialtime<<endl;
cout<<endl;
free(a);
free(b);
free(c);

return 0;
}
