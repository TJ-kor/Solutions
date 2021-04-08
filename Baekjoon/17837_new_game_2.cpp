#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
// 2021.4.7 16:00 시작 

/*

- 칸 색깔 : 흰, 빨, 파
	- 흰색 : 그냥 이동
	- 빨간색 : 이동한 말을 기준으로 포함해서 순서 바꿈
	- 파란색,체스판 벗어나는 경우 : 이동방향 반대로 바꾼후 한칸 이동
		%% 파란색 사이에 껴있을때는 움직임 x
- 말 번호, 이동방향 네방향
- 한 턴당 말 전부 이동, 말이 겹쳐져있으면 같이 이동
- 턴이 진행되던 중, 말이 네개 %이상% 쌓이면 종료 

 1. 말 선택
   1.1 선택 된 말 위에 있는 모든 말 번호 저장? 
 2. 말 이동할 위치 색 확인
   2.1 파랑색이면 방향 반전
   2.2 빨간색이면 저장된 번호 순서 반대로 변환
 3. 이동
*/
typedef struct info_chess {
	int num, dir;
}chess;

int N, K;

int dd[][4] = { {0,0,-1,1},{1,-1,0,0} };
vector< vector< int > > map_color;
vector< vector< vector <chess> > > map_chess;
vector < pair<int, int> > pos_chess;

void print_map() {
	for (int c = 1; c < N + 1; c++) {
		for (int r = 1; r < N + 1; r++) {
			cout << map_chess[c][r].size() << " ";
		}
		cout << endl;
	}
	cout << endl;
}


int move_chess(int k) {
	int count = 0;
	vector <chess> list_moving;
	int i = 0;
	int c, r, dir;
	bool flag = true;
	
	c = pos_chess[k].first;
	r = pos_chess[k].second;
	dir = 0;

	for (i = 0; i < map_chess[c][r].size(); i++) {
		if (map_chess[c][r][i].num == k) {
			dir = map_chess[c][r][i].dir;
			break;
		}
	}

	while (true) {
		list_moving.push_back(map_chess[c][r][i]);
		map_chess[c][r].erase(map_chess[c][r].begin() + i);

		if (map_chess[c][r].size() == i) {
			break;
		}
	}

	int c_next = c + dd[0][dir];
	int r_next = r + dd[1][dir];

	if (map_color[c_next][r_next] == 2) {
		// 방향 반전
		if (dir % 2 == 0) {
			dir++;
		}
		else {
			dir--;;
		}
		list_moving[0].dir = dir;
		c_next = c + dd[0][dir];
		r_next = r + dd[1][dir];

		if (map_color[c_next][r_next] == 2) {
			// 반대 방향도 파랑색이면 이동 X
			c_next = c;
			r_next = r;
			flag = false;
		}
	}

	if (map_color[c_next][r_next] == 1 && flag == true) {
		// 순서 반전
		vector <chess> list_moving_ = list_moving;
		for (int j = 0; j < list_moving.size(); j++) {
			list_moving[list_moving_.size() - 1 - j] = list_moving_[j];
		}
	}

	for (auto tmp : list_moving) {
		map_chess[c_next][r_next].push_back(tmp);
		pos_chess[tmp.num] = pair<int, int>(c_next, r_next);
	}



	return map_chess[c_next][r_next].size();
}

int solution() {
	int t = 0;

	while (t <= 1000) {
		t++;

		for (int k = 0; k < K;k++) {
			if (move_chess(k) >= 4) return t;
			print_map();
		}
		cout << "===========================" << endl;
		//print_map();
	}

	if (t == 1001) t = -1;
	return t;
}

int main() {
	cin >> N >> K;
	map_color = vector< vector< int > >(N+2, vector< int >(N+2, 0));
	map_chess = vector< vector< vector <chess> > >(N+2, vector< vector <chess> >(N+2));

	for (int c = 0; c < N + 2; c++) {
		for (int r = 0; r < N + 2; r++) {
			if (c == 0 || c == N + 1 || r == 0 || r == N + 1)
				map_color[c][r] = 2;
			else
				cin >> map_color[c][r];
		}
	}

	for (int k = 0; k < K; k++) {
		chess tmp;
		pair<int, int> pos_tmp;
		cin >> pos_tmp.first >> pos_tmp.second >> tmp.dir;
		tmp.dir--;
		tmp.num = k;

		map_chess[pos_tmp.first][pos_tmp.second].push_back(tmp);
		pos_chess.push_back(pos_tmp);
	}

	//print_map();
	cout << solution();

	return 0;
}

/*

4 4
0 0 0 0
2 1 2 0
0 0 0 0
0 0 0 0
2 2 2
2 2 1
2 2 2
3 3 3

*/