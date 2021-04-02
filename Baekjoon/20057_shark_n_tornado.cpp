#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, result;
vector<vector<int>> map;

int dd[][4] = { {0,1,0,-1},{-1,0,1,0} };

float ratio_sand[9] = { 0.01,0.01,0.02,0.07,0.07,0.02,0.1,0.1,0.05 };
int idx_c[4][9] = {
{ -1,1,-2,-1,1,2,-1,1,0 },
{ -1,-1,0,0,0,0,1,1,2 },
{ -1,1,-2,-1,1,2,-1,1,0 },
{ 1,1,0,0,0,0,-1,-1,-2 }
};
int idx_r[4][9] = {
{ 1,1,0,0,0,0,-1,-1,-2},
{ -1,1,-2,-1,1,2,-1,1,0 },
{ -1,-1,0,0,0,0,1,1,2 },
{ -1,1,-2,-1,1,2,-1,1,0 }
};






void print_map() {
	cout << "================================" << endl;
	for (int c = 0; c < N; c++) {
		for (int r = 0; r < N; r++) {
			cout << map[c][r] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

bool check_dir(int c, int r) {
	if (c < 0 || c >= N) {
		return false;
	}
	if (r < 0 || r >= N) {
		return false;
	}

	return true;
}

void tornado(int c, int r, int dir) {
	int y = map[c][r];
	int sum = 0;
	map[c][r] = 0;

	for (int i = 0; i < 9; i++) {
		int c_t = c + idx_c[dir][i];
		int r_t = r + idx_r[dir][i];
		int val = y * ratio_sand[i];

		if (check_dir(c_t, r_t)) {
			// 맵 안이면 해당 장소에 모래 추가
			map[c_t][r_t] += val;
		}
		else {
			// 맵 밖이면 정답결과에 모래 추가
			result += val;
		}
		sum += val;
	}

	int a = y - sum;

	if (check_dir(c+dd[0][dir], r+dd[1][dir])) {
		map[c + dd[0][dir]][r + dd[1][dir]] += a;
	}
	else {
		result += a;
	}
}

void solve() {

	int c, r, dist_move;
	c = r = N / 2;
	dist_move = 1;

	while (1) {
		for (int dir = 0; dir < 4; dir++) {
			for (int moved = 0; moved < dist_move; moved++) {
				c += dd[0][dir];
				r += dd[1][dir];
				tornado(c, r, dir);
			}

			//print_map();
			//cout << "토네이도 위치 : " << c << ", " << r << endl;
			if (dir % 2 == 1 && dist_move < N - 1) {
				dist_move++;
			}

			if (c == 0 && r == 0)
				break;
		}

		if (c == 0 && r == 0)
			break;
	}

}

int main() {

	cin >> N;
	map = vector < vector <int> >(N, vector<int>(N));

	for (int c = 0; c < N; c++) {
		for (int r = 0;r < N; r++) {
			cin >> map[c][r];
		}
	}
	
	solve();
	cout << result;

	return 0;
}