#include <stdio.h>

int main()
{
	int n,i,sum;

	for(n=1;n<=10000;n++)
	{
		//��n������֮�� 
		for(sum=0,i=1;i<=n/2;i++)
		{
			if(n%i==0)
				sum+=i;
		}
		//�ж�n�ǲ������� 
		if(sum==n)
			printf("%d\n",n);
	}
	return 0;
}
