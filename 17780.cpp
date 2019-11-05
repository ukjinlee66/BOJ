#include<iostream>
#include<vector>
#include<deque>
#include<algorithm>
using namespace std;
int n, k;
int map[13][13];
bool level[11];//���� �ٴ����� �ö�Ÿ�ִ���.
deque<int> M[13][13];//2���� ��������.
pair<int, int> dir[4] = { {0,1},{0,-1},{-1,0},{1,0} }; //-> <- ^ v
vector<pair<int, pair<int, int>>> hor;//���� ��ǥ�� �������.
void checksize()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << M[i][j].size() << " ";
		cout << "\n";
	}
}
bool checkturn()
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (M[i][j].size() >= 4) //�����4�̻��� ���������Ұ��.
			{
				return true;
			}
	return false;
}
void moving(int idx)//���ǹ�ȣ.
{
	if (!level[idx]) return; //�ö�Ÿ�ִ³��ϰ�� skip.
	int curx = hor[idx].first; //x��ǥ
	int cury = hor[idx].second.first; // y��ǥ
	int mo = hor[idx].second.second; //����
	int nx = curx + dir[mo].first;//�̵��Ϸ��� x��ǥ
	int ny = cury + dir[mo].second;//�̵��Ϸ��� y��ǥ
	int w = map[nx][ny];
	if (w == 2 || (nx < 0 || ny < 0 || nx >= n || ny >= n))//�Ķ� �ϰ�� �ݴ�ٲ㼭�̵�.
	{
		//������ȯ.
		if (mo == 0) hor[idx].second.second = 1;
		else if (mo == 1) hor[idx].second.second = 0;
		else if (mo == 2) hor[idx].second.second = 3;
		else hor[idx].second.second = 2;
		mo = hor[idx].second.second; //�ٲ���� ������Ʈ.
		nx = curx + dir[mo].first;
		ny = cury + dir[mo].second;//���ο��̵�.
		if ((nx < 0 || ny < 0 || nx >= n || ny >= n) || map[nx][ny] == 2)//�Ķ��̰ų� �������Ѿ���.
			return;//�������مf���� �״������.
		else //�Ķ��̰ų� �������̾ƴϹǷ� �̵�.
			moving(idx);
	}
	else if (w == 1)//���� ���������´�.
	{
		//������ǥ�Ͱ����� �̵���Ų�� ������ �����´�.
		if (M[nx][ny].size() >= 1) //���������� ���� �̹� �����Ұ��.
		{
			while (!M[curx][cury].empty()) //���鼭 ���縻�ǹ������� �����̵���Ų��. ����ĭ�ǵڿ������� �ڷ��������.
			{
				int val = M[curx][cury].back(); //���� idx
				M[curx][cury].pop_back();
				M[nx][ny].push_back(val);
				if (M[nx][ny].size() >= 4)
					return;
				hor[val].first = nx;
				hor[val].second.first = ny; //������ǥ���ٲپ��ش�.
				level[val] = false;
			}
		}
		else //�������.
		{
			while (!M[curx][cury].empty()) //���鼭 ���縻�ǹ������� �����̵���Ų��. //�ؿ������� �Ʒ����������.
			{
				int val = M[curx][cury].front();
				M[curx][cury].pop_front();
				M[nx][ny].push_front(val);
				if (M[nx][ny].size() >= 4)
					return;
				hor[val].first = nx;
				hor[val].second.first = ny; //������ǥ���ٲپ��ش�. �� �� ������ִ��� �ٴ����ΰ���.
				level[val] = false;
			}
			level[M[nx][ny].front()] = true;
		}
	}
	else//�Ͼ�
	{
		if (M[nx][ny].size() >= 1)//���� �̹� �����Ұ��.
		{
			while (!M[curx][cury].empty())//�����ִ�ĭ�� ���κ��
			{
				int val = M[curx][cury].front();//���� ��ȣ.
				M[nx][ny].push_back(val);//���ο�ĭ�� ���� �׾ƿø�.
				if (M[nx][ny].size() >= 4)
					return;
				M[curx][cury].pop_front();

				//���� ��ǥ���� ������ �״�εд�.
				hor[val].first = nx;
				hor[val].second.first = ny;
				level[val] = false;//���οö�Ż����.
			}
		}
		else //�������������������״���̵�. level ��ȭ�¾���.
		{
			while (!M[curx][cury].empty())
			{
				int val = M[curx][cury].front();//���� ��ȣ.
				M[nx][ny].push_back(M[curx][cury].front());
				if (M[nx][ny].size() >= 4)
					return;
				M[curx][cury].pop_front();

				//���� ��ǥ���� ������ �״�εд�.
				hor[val].first = nx;
				hor[val].second.first = ny;
			}
		}
	}
	return;
}
int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> k;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> map[i][j];
	//�̵����� -> <- ^ v 1 2 3 4
	//ü���� 0�� 1�� 2��
	for (int i = 0; i < k; i++) //ü���� ����.
	{
		int row, column, move;
		cin >> row >> column >> move;
		move--;
		row--;
		column--;
		hor.push_back({ row,{column,move} }); //���� ��ǥ�� ����������.
		M[row][column].push_back(i); //ü������ ������ �Ҵ�.(i��)
		//����ĭ�� ���̵ΰ��̻� �Է������־������ʴ´�.
		level[i] = true; //�ʱ� ��縻�� �ǾƷ� �ٴ�ĭ�� �����Ѵ�.
	}
	int turn = 1;
	while (true)
	{
		if (turn >= 1000) {
			turn = -1;
			break;
		}
		for (int i = 0; i < k; i++) {//�������ƺ��� ��������.
			moving(i);
			if (checkturn()) //���� ���̰�4�̻��θ���������� ����.
				break;
		}
		/*checksize();*/
		if (checkturn()) //���� ���̰�4�̻��θ���������� ����.
			break;
		turn++;//�ƴҰ�� ��������.
	}
	cout << turn;
	return 0;
}