#include <iostream>
#include <vector>

using namespace std;
//2021.4.21 16:15 시작 17:20 종료

/*
 - 가로, 세로방향 길 연결
 - 1칸 차이의 높,낮은 칸을 연결
 - L 길이 만큼 공간에 경사로 설치

 - 경우의 수 
  1. 평평한 땅 경우
	- 그냥 이동
  2. 낮은 칸 만나는 경우
	2.1 평평하게 이동하다가
	2.2 직전에 경사로 설치한 경우
  3. 높은 칸 만나는 경우
*/

int N, L;
vector < vector<int> > map;

bool run_road(vector<int> road) {
	int i = 1;				// 위치
	int len_flat = 1;		// 지나온 평평한 길 길이
	int cur_h = road.front();

	while (true) {
		if (i >= N) break;
		if (abs(cur_h - road[i]) > 1) return false;
		if (cur_h < road[i]) {
			// 올라가는 경우
			// 지나온 땅의 평평한 길이가 L보다 작으면 경사로 설치 불가
			if (len_flat < L) return false;
			cur_h = road[i];
			len_flat = 1;
			i++;
		}
		else if (cur_h > road[i]) {
			// 내려가는 경우
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
			// 평평한 길 지나는 경우
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