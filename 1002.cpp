#include <iostream>
using namespace std;

int distance(int x1, int y1, int x2, int y2) {
	int d = (x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1);
	return d;
}

int main() {
	int T;
	cin >> T;
	int x1, y1, r1, x2, y2, r2;
	int d;
	int result;
	while (T--) {
		cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;
		d = distance(x1, y1, x2, y2);
		if (d == 0) //���ɿ��� ���
		{
			if (r1 == r2) result = -1;
			else result = 0;
		}
		else {
			if ((r2 - r1)*(r2 - r1) < d && (r1 + r2)*(r1 + r2) > d) result = 2; //�� ���� �� ������ ������ ���
			else if ((r1 + r2)*(r1 + r2) == d || (r2 - r1)*(r2 - r1) == d) result = 1; // �ο��� �� ������ ������ ���
			else result = 0; // �� ��찡 �ƴ� ���
		}
		cout << result << '\n';
	}
	return 0;
}