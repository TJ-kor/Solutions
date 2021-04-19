#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>


using namespace std;
// 15:50분 시작

/*
	- 봄에 양분을 흡수 못하고 죽은 나무 처리, 가을에 번식할때 벡터의 앞에서부터 넣어주면
	  sorting을 할 필요가 없음
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
		//1. 봄
		// 어린순으로 나이 만큼 양분 먹기, 양분이 부족하면 나무 삭제
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

				//2. 여름
				//죽은 나무 양분으로 변환 (list_dead)
				for (int i = 0; i < list_dead.size(); i++) {
					map[c][r] += list_dead[i] / 2;
					cnt_tree--;
				}
			}
		}

		for (int c = 0; c < N; c++) {
			for (int r = 0; r < N; r++) {
				//3. 가을 
				//나무가 5의 배수일때 인접한 8칸에 나이가 1인 나무 추가.
				for (int i = 0; i < map_tree[c][r].size(); i++) {
					if (map_tree[c][r][i] % 5 == 0) {
						//5의 배수
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

				//4. 겨울
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