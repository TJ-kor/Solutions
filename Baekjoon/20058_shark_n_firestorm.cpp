#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
//2��° Ǯ��
//2021.4.2 14:00 ���� 15:35 ����



/*
���� ���� : N, Q, A

- ��� : A�� �����ִ� �� ������ ��, ����ū ��� ĭ�� ����

- 2^N ũ���� �������� 2^Lũ�� ������ 90�� ȸ��.
- 0���� �ѷ����� ������ �� ���.
*/



int N, Q, sz_A, sum_ice;
vector < vector <int> > A, A_next;
vector <int> list_L;

void print_map() {

	cout << "====================================" << endl;
	for (int c = 0; c < N; c++) {
		for (int r = 0; r < N; r++) {
			cout << A[c][r] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

bool check_dir(int c, int r) {
	if (c < 0 || c >= N) 
		return false;
	if (r < 0 || r >= N)
		return false;
	return true;
}

void check_ice(){
	// ������ �ִ� ĭ 3�� �Ǵ� �� �̻�� ���������� ���� ĭ�� ������ ���� 1 �پ���

	int dd[][4] = { {-1,0,1,0},{0,1,0,-1 } };
	sum_ice = 0;
	for (int c = 0; c < N; c++) {
		for (int r = 0; r < N; r++){
			int c_t, r_t, cnt_ice;

			cnt_ice = 0;
			for (int dir = 0; dir < 4; dir++) {
				//4������ ���� ���� ���� üũ
				c_t = c + dd[0][dir];
				r_t = r + dd[1][dir];
				
				if (check_dir(c_t, r_t) && A_next[c_t][r_t] > 0) {
					cnt_ice++;
				}
			}

			//������ �����ϸ� ���� ���� ����
			if (cnt_ice < 3 && A[c][r]>0)
				A[c][r]--;
			sum_ice += A[c][r];
		}
	}
}

int BFS(int c, int r) {

	int dd[][4] = { { -1,0,1,0 },{ 0,1,0,-1 } };
	int sz_area = 0;
	vector<pair<int, int>> q;
	q.push_back(pair<int, int>(c, r));
	A_next[c][r] = 1;
	while (true) {
		if (q.size() == 0)
			break;
		int c = q.front().first; 
		int r = q.front().second;
		q.erase(q.begin());
		sz_area++;
		
		for (int dir = 0; dir < 4; dir++) {
			int c_t = c + dd[0][dir];
			int r_t = r + dd[1][dir];

			if (check_dir(c_t, r_t) && A_next[c_t][r_t] == 0 && A[c_t][r_t] > 0) {
				q.push_back(pair<int, int>(c_t, r_t));
				A_next[c_t][r_t]++;

			}
		}
	}

	return sz_area;
}

int check_max_area() {
	//BFS Ž��
	A_next = vector< vector <int> >(N, vector<int>(N,0));
	int sz_area = 0;

	for (int c = 0; c < N; c++) {
		for (int r = 0; r < N; r++) {

			if (A_next[c][r] == 0 && A[c][r] != 0) {

				//�湮������ ���� ������ 0�� �ƴϸ� BFS ����
				int sz = BFS(c, r);

				//�ִ� ũ�� ����
				if (sz > sz_area)
					sz_area = sz;
			}
		}
	}

	return sz_area-1;
}

void fire_storm(int c,int r, int sz_area) {
	// A_next�� ���� ���� ȸ������ ������.
	int c_next, r_next;

	for (int c_t = 0; c_t < sz_area; c_t++) {
		for (int r_t = 0; r_t < sz_area; r_t++) {
			c_next = c + r_t;
			r_next = r + (sz_area-1) - c_t;
			// 1 = 0 + 3 - 2; 
			A_next[c_next][r_next] = A[c+c_t][r+r_t];
		}
	}
}

void solve() {
	//������ ������ ���̾�� ����
	
	for (int i = 0; i < Q; i++) {
		int L = list_L[i];
		int sz_area = pow(2, L);	//���̾� ������ ũ�� ����

		// ���� ���� ���� ���̾�� ����
		for (int c = 0; c < N; c += sz_area) {
			for (int r = 0; r < N; r += sz_area) {
				fire_storm(c,r,sz_area);
			}
		}

		A = A_next;	// ȸ�� �� ������ ����
		check_ice();// ���� ���� üũ
	}


}

int main() {
	cin >> N >> Q;
	N = pow(2, N);
	A = vector< vector <int> >(N, vector<int>(N));
	A_next = vector< vector <int> >(N, vector<int>(N));

	for (int c = 0; c < N; c++) {
		for (int r = 0; r < N; r++) {
			cin >> A[c][r];
		}
	}

	
	for (int i = 0; i < Q; i++) {
		int tmp;
		cin >> tmp;
		list_L.push_back(tmp);
	}
	solve();

	cout << sum_ice << endl;
	cout << check_max_area();
	return 0;
}
