#include<iostream>
#include <random>
using namespace std;

inline int left(int i)//������
{
	return i << 1;
}
inline int right(int i)//������
{
	return (i << 1) + 1;
}
inline int parent(int i)//���ڵ�
{
	return i >> 1;
}

void maintenance(int *a,int i,int size)//ά���ѵ�����
{
	int l = left(i)-1,r=right(i)-1;
	--i;
	int large = i;
	if (l < size && a[l] > a[i])
		large = l;
	if (r < size && a[r] > a[large])
		large = r;
	if (large!=i)
	{
		a[i] ^= a[large];
		a[large] ^= a[i];
		a[i] ^= a[large];//��򽻻�Ԫ���������ռ�
		if (large<=(size>>1))
			maintenance(a, large+1, size);//�����large+1
	}
}
void build(int *a, int size)//���ѣ����ѵ�ͬʱά����
{
	for (int i = (size >> 1); i >= 1; --i)
		maintenance(a, i, size);
}
void heapSort(int *a, int size)
{
	build(a, size);
	for (int i = size-1; i >= 1;--i)
	{
		a[i] ^= a[0];
		a[0] ^= a[i];
		a[i] ^= a[0];//�����Ѷ������һ��Ԫ��
		--size;
		maintenance(a, 1, size);
	}
}
int main()
{
	uniform_int_distribution<int>u(-100, 100);
	default_random_engine e;
	int a[100] = { 0 };
	for (int i = 0; i < 100; ++i)
		a[i] = u(e);
	int size = sizeof a / sizeof (int);
	heapSort(a, size);
	for (auto &i : a)
		cout << i << " ";
	cout << endl;
	getchar();
	getchar();
	return 0;
}