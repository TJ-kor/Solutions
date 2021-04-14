#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
// 2021.4.13 16:45 시작 19:00 종료

typedef struct info_shark {
	int n, sz, s, d;
} shark;

int R, C, M, cnt_M;

int dd[][5] = { {0,-1,1,0,0},{0,0,0,1,-1} };
vector< vector<vector <shark> >> map, map_next;
vector <pair<int, int>>  list_shark;


void print_map() {
	for (int c = 0; c < C; c++) {
		for (int r = 0; r < R; r++) {
			if(map[c][r].size()> 0)
				cout << map[c][r].front().n+1 << " ";
			else
				cout<< "0 ";

		}
		cout << endl;
	}
	cout << endl;
}

bool check_dir(int c, int r) {
	if (c < 0 || c >= C) return false;
	if (r < 0 || r >= R) return false;

	return true;
}

int fishing_shark(int pos_king) {
	//열에서 제일 가까운 상어 킬
	int c, sz, n;
	for (c = 0; c < C; c++) {
		if (map[c][pos_king].size() > 0)
			break;
	}
	if (c == C) return 0;

	sz = map[c][pos_king].front().sz;
	n = map[c][pos_king].front().n;
	map[c][pos_king].clear();
	list_shark[n].first = -1;
	list_shark[n].second= -1;
	cnt_M--;
	return sz;
}

void merge_shark() {

	for (int m = 0; m < M; m++) {
		int max_n;
		int c = list_shark[m].first;
		int r = list_shark[m].second;

		if (c == -1 || map[c][r].size() <= 1) continue;
		
		shark largest_shark = map[c][r][0];


		cnt_M = cnt_M - map[c][r].size() + 1;
		for (int i = 1; i < map[c][r].size(); i++) {
			if (largest_shark.sz < map[c][r][i].sz) {
				list_shark[largest_shark.n].first = -1;
				list_shark[largest_shark.n].second = -1;
				largest_shark = map[c][r][i];
			}
			else {
				list_shark[map[c][r][i].n].first = -1;
				list_shark[map[c][r][i].n].second = -1;
			}
		}
		
		map[c][r].clear();
		map[c][r].push_back(largest_shark);
	}
}

void move_shark() {
	
	for (int m = 0; m < M; m++) {
		int c, r, d, sz;
		if (list_shark[m].first == -1) continue;
		

		c = list_shark[m].first;
		r = list_shark[m].second;

		shark tmp = map[c][r].front();
		d = tmp.d;

		
		if ((d == 1 || d == 2) && (tmp.s >= ((C - 1) * 2))) {
			tmp.s = tmp.s % ((C - 1) * 2);
		}
		if ((d == 3 || d == 4) && (tmp.s >= ((R - 1) * 2))) {
			tmp.s = tmp.s % ((R - 1) * 2);
		}

		for (int s = 0; s < tmp.s; s++) {
			c += dd[0][d];
			r += dd[1][d];

			if (c == -1) {
				c = 1;
				d = 2;
			}
			if (c == C) {
				c = C - 2;
				d = 1;
			}
			if (r == -1) {
				d = 3;
				r = 1;
			}
			if (r == R ) {
				r = R - 2;
				d = 4;
			}
		}
		tmp.d = d;
		list_shark[m].first = c;
		list_shark[m].second = r;
		map_next[c][r].push_back(tmp);
	}


}

int solution() {
	int answer = 0;
	int pos_king = -1;
	print_map();
	while (true) {
		map_next = vector < vector<vector< shark> > >(C, vector<vector< shark> >(R));
		//1. 낚시왕 이동
		//2. 상어 낚시

		pos_king++;
		if (pos_king == R) break;
		if (cnt_M == 0) break;

		answer += fishing_shark(pos_king);
		
		//3. 상어 이동
		move_shark();
		map = map_next;
		merge_shark();

		print_map();
	}


	return answer;
}

int main() {
	cin >> C >> R >> M;
	map = vector < vector<vector< shark> > >(C, vector<vector< shark> >(R));
	list_shark = vector<pair<int, int>>(M);
	cnt_M = M;
	for (int m = 0; m < M; m++) {
		cin >> list_shark[m].first >> list_shark[m].second;

		list_shark[m].first--;
		list_shark[m].second--;

		shark tmp;
		cin >> tmp.s >> tmp.d >> tmp.sz;

		tmp.n = m;

		map[list_shark[m].first][list_shark[m].second].push_back(tmp);
	}


	cout << solution();
	return 0;
}