#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
int n;
int point_x, point_y;
int res=987654321;
int map[21][21];
int gu[21][21];
int cnt[6];
int dx[] = { 0,0,1,-1 };
int dy[] = { 1,-1,0,0 };
void gucount() //�α������.
{
	memset(cnt, 0, sizeof(cnt));//�α�
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			cnt[gu[i][j]] += map[i][j];
	int maxnum =-987654321; int minnum = 987654321;
	for (int i = 1; i <= 5; i++)
	{
		maxnum = max(maxnum, cnt[i]);
		minnum = min(minnum, cnt[i]);
	}
	res = min(res, maxnum - minnum);
}
void printgu() //������� Ȯ��.
{
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
			cout << gu[i][j] << " ";
		puts("");
	}
	return;
}
void sol(int x, int y,int d1,int d2)
{
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			gu[i][j] = 0;
	//��輱
	int j1 = y, j2 = y;
	bool flag1 = false, flag2 = false;
	for (int i = x; i <= x + d1 + d2; i++)
	{
		for (int w = j1; w <= j2; w++)
			gu[i][w] = 5;
		if (j1 == y - d1) {
			j1++;
			flag1 = true;
		}
		else if (!flag1)
			j1--;
		else
			j1++;
		if (j2 == y + d2) {
			j2--;
			flag2 = true;
		}
		else if (!flag2)
			j2++;
		else
			j2--;
		
	}
	//���ű� ����.
	for (int i = 1; i < x + d1; i++)
		for (int j = 1; j <= y; j++)
			if(gu[i][j]!=5)
				gu[i][j] = 1;
	for (int i = 1; i <= x + d2; i++)
		for (int j = y + 1; j <= n; j++)
			if (gu[i][j] != 5)
				gu[i][j] = 2;
	for (int i = x + d1; i <= n; i++)
		for (int j = 1; j <= y - d1 + d2; j++)
			if (gu[i][j] != 5)
				gu[i][j] = 3;
	for (int i = x + d2 + 1; i <= n; i++)
		for (int j = y - d1 + d2; j <= n; j++)
			if (gu[i][j] != 5)
				gu[i][j] = 4;
	
	/*printgu();*/
	gucount();
	return;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	/*
		1) x = d1,d2>=1,1<=x<x+d1+d2<=n,
		   y = 1<=y-d1<y<y+d2<=n
		��輱
		1-1)(x, y), (x+1, y-1), ..., (x+d1, y-d1)
		1-2)(x, y), (x+1, y+1), ..., (x+d2, y+d2)
		1-3)(x+d1, y-d1), (x+d1+1, y-d1+1), ... (x+d1+d2, y-d1+d2)
		1-4)(x+d2, y+d2), (x+d2+1, y+d2-1), ..., (x+d2+d1, y+d2-d1)
	*/
	//2)��輱�� ��輱�ȿ� ���Ե� ���ű��� 5��.
	/*
		3)5�� ���ű��� ���Ե��� ���� ���� (r, c)�� ���ű� ��ȣ�� ���� ������ ������.
		1�� ���ű� : 1 �� r < x + d1, 1 �� c �� y
		2�� ���ű� : 1 �� r �� x + d2, y < c �� N
		3�� ���ű� : x + d1 �� r �� N, 1 �� c < y - d1 + d2
		4�� ���ű� : x + d2 < r �� N, y - d1 + d2 �� c �� N
	*/
	//�� �� point_x,point_y �� ���ƺ��� d�� ũ�⸦ ������ŭ �÷����� -> ���ű��� �ִ��ּ� ����� ���غ��� ������� ����ִ´�.
	cin >> n;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			cin >> map[i][j];
	for (int x = 1; x <= n; x++) 
	{
		for (int y = 1; y <= n; y++)
		{
			for (int d1 = 1; d1 <= n; d1++)
			{
				for (int d2 = 1; d2 <= n; d2++)
				{
					//x,y check d1,d2>=1,1<=x<x+d1+d2<=n , 1<=y-d1<y<y+d2<=n
					if (x + d1 + d2 <= n)
						if (y + d2 <= n)
							sol(x, y, d1, d2);
				}
			}
		}
	}
	cout << res;
	return 0;
}