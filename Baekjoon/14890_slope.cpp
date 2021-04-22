#include <iostream>
#include <vector>

using namespace std;
//2021.4.21 16:15 ���� 17:20 ����

/*
 - ����, ���ι��� �� ����
 - 1ĭ ������ ��,���� ĭ�� ����
 - L ���� ��ŭ ������ ���� ��ġ

 - ����� �� 
  1. ������ �� ���
	- �׳� �̵�
  2. ���� ĭ ������ ���
	2.1 �����ϰ� �̵��ϴٰ�
	2.2 ������ ���� ��ġ�� ���
  3. ���� ĭ ������ ���
*/

int N, L;
vector < vector<int> > map;

bool run_road(vector<int> road) {
	int i = 1;				// ��ġ
	int len_flat = 1;		// ������ ������ �� ����
	int cur_h = road.front();

	while (true) {
		if (i >= N) break;
		if (abs(cur_h - road[i]) > 1) return false;
		if (cur_h < road[i]) {
			// �ö󰡴� ���
			// ������ ���� ������ ���̰� L���� ������ ���� ��ġ �Ұ�
			if (len_flat < L) return false;
			cur_h = road[i];
			len_flat = 1;
			i++;
		}
		else if (cur_h > road[i]) {
			// �������� ���
			len_flat = 1;
			cur_h = road[i];
			while (len_flat < L) {
				i++;
				len_flat++;

				if (i >= N) return false;
				if (cur_h != road[i]) return false;
			}
			i++;
			len_flat = 0;
		}
		else {
			// ������ �� ������ ���
			len_flat++;
			i++;
		}
	}

	return true;
}

int solution() {
	int count = 0;

	for (int c = 0; c < N; c++) {
		if (run_road(map[c])) count++;
	}

	for (int r = 0; r < N; r++) {
		vector< int> tmp_road;
		for (int c = 0; c < N; c++)
			tmp_road.push_back(map[c][r]);
		if (run_road(tmp_road)) count++;
	}

	return count;
}

int main() {
	cin >> N >> L;
	map = vector < vector<int> >(N, vector<int>(N));
	
	for (int c = 0; c < N; c++) {
		for (int r = 0; r < N; r++) {
			cin >> map[c][r];
		}
	}

	cout << solution();
	return 0;
}