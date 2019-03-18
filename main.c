int function_add(int a,int b, int c, int d, int e) //callee 
{
	int x[5] = {a,b,c,d,e};
	int ans=(x[0]+x[1])*x[2]-x[3]-x[4];
	return ans;
}
int caller_1(void)   //callee  ARG
{
	const int x[5] = {1,2,3,4,5};
	int ans=function_add( x[4], x[3], x[2], x[1], x[0]);
	return ans;
}
int a=0;
int b=1;
int c=2;
int d=3;
int e=4;
const int f=5;
const int g=6;
const int h=7;
const int i=8;
const int j=9;
void reset_handler(void)
{	
		int k=10;
		int l=11;
		int m=12;
		int n=13;
		int o=14;
		const int p=15;
		const int q=16;
		const int r=17;
		const int s=18;
		const int t=19;
		int ans_1=function_add(k, l, m, n, o);   //caller
		int ans_0=caller_1();               //callermake
	while (1)
	{
	}
}
