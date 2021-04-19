#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>


using namespace std;
// 15:50�� ����

/*
	- ���� ����� ��� ���ϰ� ���� ���� ó��, ������ �����Ҷ� ������ �տ������� �־��ָ�
	  sorting�� �� �ʿ䰡 ����
	- 
*/

int dd[][8] = { {-1,-1,0,1,1,1,0,-1},{0,1,1,1,0,-1,-1,-1} };

int N, M, K, cnt_tree;;

int map[10][10];
int map_val[10][10];
vector<int> map_tree[10][10];

bool check_dir(int c, int r) {
	if (c < 0 || c >= N) return false;
	if (r < 0 || r >= N) return false;

	return true;
}

void print_arr(){
	for (int c = 0; c < N; c++) {
		for (int r = 0; r < N; r++) {
			cout.width(2);
			cout.fill(' ');
			cout << map[c][r] << " ";
		}
		cout << "\t";

		for (int r = 0; r < N; r++) {
			cout << map_tree[c][r].size() << " ";
		}
		cout << endl;
	}
	cout << endl;
}


void solution() {
	int k = 0;
	while (k++ < K) {
		//1. ��
		// ������� ���� ��ŭ ��� �Ա�, ����� �����ϸ� ���� ����
		for (int c = 0; c < N; c++) {
			for (int r = 0; r < N; r++) {
				vector <int> list_dead;
				
				for (int i = 0; i < map_tree[c][r].size(); i++) {

					if (map[c][r] >= map_tree[c][r][i]) {
						map[c][r] -= map_tree[c][r][i];
						map_tree[c][r][i]++;
					}
					else {
						list_dead.push_back(map_tree[c][r][i]);
						map_tree[c][r].erase(map_tree[c][r].begin() + i);
						i--;
					}
				}

				//2. ����
				//���� ���� ������� ��ȯ (list_dead)
				for (int i = 0; i < list_dead.size(); i++) {
					map[c][r] += list_dead[i] / 2;
					cnt_tree--;
				}
			}
		}

		for (int c = 0; c < N; c++) {
			for (int r = 0; r < N; r++) {
				//3. ���� 
				//������ 5�� ����϶� ������ 8ĭ�� ���̰� 1�� ���� �߰�.
				for (int i = 0; i < map_tree[c][r].size(); i++) {
					if (map_tree[c][r][i] % 5 == 0) {
						//5�� ���
						for (int dir = 0; dir < 8; dir++) {
							int c_ = c + dd[0][dir];
							int r_ = r + dd[1][dir];
							if (check_dir(c_, r_)) {
								map_tree[c_][r_].insert(map_tree[c_][r_].begin(), 1);
								cnt_tree++;
							}
						}
					}
				}

				//4. �ܿ�
				map[c][r] += map_val[c][r];
			}
		}
		print_arr();
	}

}

int main() {
	cin >> N >> M >> K;
	cnt_tree = M;

	for (int c = 0; c < N; c++) {
		for (int r = 0; r < N; r++) {
			cin >> map_val[c][r];
			map[c][r] = 5;
		}
	}

	for (int m = 0; m < M; m++) {
		int c, r, z;
		cin >> c >> r >> z;
		map_tree[c-1][r-1].push_back(z);
	}

	print_arr();
	solution();

	cout << cnt_tree;

	return 0;
}