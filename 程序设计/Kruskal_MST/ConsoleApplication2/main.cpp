#include <iostream>
#include "class.h"
using namespace std;
int main()
{
	int n,m;
	cout<<"�����������������";
	cin>>n>>m;
	MST mst=MST(n,m);
	cout<<endl<<endl;
	mst.display();
	getchar();
	getchar();
	return 0;
}