#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
bool ar[4][8]; 
bool visit[4];
//4���� ��Ϲ��� 8���� ����. 12�� 0idx���� �ð��������++
//3�ù���� 9�ù�����Ϲ������̴ٸ���� ������ȸ��.
//0�� idx�� 0�̸� N 1�̸� S  S�ϰ�� 1, 2, 4, 8 ��.
int K; //ȸ��Ƚ��.
void print()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 8; j++)
			printf("%d", ar[i][j]);
		printf("\n");
	}
}
void left_turn(int a);
void right_turn(int idx)
{
	visit[idx] = true;
	bool temp = ar[idx][7];
	if (idx==1||idx==2) //idx�� 1�� 2�ǰ��
	{
		if (ar[idx][2] != ar[idx + 1][6])
			if(!visit[idx+1])
				left_turn(idx + 1);
		if (ar[idx][6] != ar[idx - 1][2])
			if(!visit[idx-1])
				left_turn(idx - 1);
	}
	else if(idx==0)
	{
		if (ar[idx][2] != ar[idx + 1][6])
			if(!visit[idx+1])
				left_turn(idx + 1);
	}
	else if(idx==3)
	{
		if (ar[idx][6] != ar[idx - 1][2])
			if(!visit[idx-1])
				left_turn(idx - 1);
	}
	for (int i = 7; i >=0; i--)
	{
		ar[idx][i] = ar[idx][i - 1];
	}
	ar[idx][0] = temp;
}
void left_turn(int idx)
{
	visit[idx] = true;
	bool temp = ar[idx][0];
	if (idx==1||idx==2) //idx�� 1�� 2�ǰ��
	{
		if (ar[idx][2] != ar[idx + 1][6])
			if(!visit[idx+1])
				right_turn(idx + 1);
		if (ar[idx][6] != ar[idx - 1][2])
			if(!visit[idx-1])
				right_turn(idx - 1);
	}
	else if (idx == 0)
	{
		if (ar[idx][2] != ar[idx + 1][6])
			if(!visit[idx+1])
				right_turn(idx + 1);
	}
	else if (idx == 3)
	{
		if (ar[idx][6] != ar[idx - 1][2])
			if(!visit[idx-1])
				right_turn(idx - 1);
	}
	for (int i = 0; i <8; i++)
	{
		ar[idx][i] = ar[idx][i+1];
	}
	ar[idx][7] = temp;
}
int sum()
{
	int res=0;
	int dum = 1;
	for (int i = 0; i < 4; i++) {
		if (ar[i][0] == 1)
			res += dum;
		dum *= 2;
	}
	return res;
}
int main()
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 8; j++)
			scanf("%1d", &ar[i][j]);
	scanf("%d", &K);
	while (K--)
	{
		memset(visit, false, sizeof(visit));
		int idx = 0, turn = 0;
		scanf("%d %d", &idx, &turn);
		idx--;
		if (turn == 1)
			right_turn(idx);
		else
			left_turn(idx);
	}
	printf("%d", sum());
}