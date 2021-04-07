#include <iostream> 
#include <algorithm>
#include <vector>
using namespace std;
// 2021.4.6 17:40 시작 19:15 종료

/*
- NxN 맵, 5개 선거구역
- 경계선 정의
	- d1 :  d1
	- d2 : 1 <= d2
	- x : 1 <= x < x + d1 + d2 <= N
	- y : 1 <= y - d1 < y < y+d2 <= N


- x,y 선택으로 1,3 구역의 경계점 선택
- d1 선택으로 왼쪽에서 오른쪽 윗방향 경계 선택
- d2 선택으로 왼쪽에서 아랫방향 경계 선택
- d1과 d2 가지고 마지막 경계점 계산
*/

int N, min_val;
vector < vector <int> > map;
vector < vector <int> > area;

void print_map() {
	cout << "=========================" << endl;
	for (int c = 0; c < N; c++) {
		for (int r = 0; r < N; r++) {
			cout << area[c][r] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

bool check_range(int x, int y, int d1, int d2) {

	if (x + d1 + d2 >= N) {
		return false;
	}

	if (y-d1 < 0 || y+d2 >= N) {
		return false;
	}

	return true;
}

int fill_area(int x, int y, int d1, int d2) {
	vector< int> count_list = { 0,0,0,0,0,0 };
	vector <pair<int, int>> left_right = vector < pair<int, int>>(21,pair<int,int>(-1,-1));

	int c = x;
	int r = y;
	while (c <= x + d1 && r >= y - d1) {

		left_right[c].first = r;

		area[c][r] = 5;
		count_list[5] += map[c][r];

		c++;
		r--;

	}

	c = x+1;
	r = y+1;
	while (c <= x + d2 && r <= y + d2) {

		left_right[c].second = r;

		area[c][r] = 5;
		count_list[5] += map[c][r];

		c++;
		r++;
	}
	
	c = x + d1+1;
	r = y - d1+1;
	while (c <= x + d1+d2 && r <= y - d1 + d2) {

		left_right[c].first = r;

		area[c][r] = 5;
		count_list[5] += map[c][r];

		c++;
		r++;
	}

	c = x + d2+1;
	r = y + d2-1;
	while (c <= x + d1 + d2 && r > y - d1 + d2) {

		left_right[c].second = r;

		area[c][r] = 5;
		count_list[5] += map[c][r];

		c++;
		r--;
	}

	for (c = x+1; c < x + d1 + d2; c++) {
		for (int r = left_right[c].first + 1; r < left_right[c].second; r++) {
			area[c][r] = 5;
			count_list[5] += map[c][r];
		}
	}

	for (c = 0; c < N; c++) {
		for (r = 0; r < N; r++) {

			if (area[c][r] != 5) { 
				
				if ((c >= 0 && c < x + d1) && (r >= 0 && r <= y)) {
					area[c][r] = 1;
					count_list[1] += map[c][r];
				}
				else if ((c >= 0 && c <= x + d2) && (r > y && r < N)) {
					area[c][r] = 2;
					count_list[2] += map[c][r];
				}
				else if ((c >= x + d1 && c < N) && (r >= 0 && r < y - d1 + d2)) {
					area[c][r] = 3;
					count_list[3] += map[c][r];
				}
				else if ((c > x + d2 && c < N) && (r >= y - d1 + d2 && r < N)) {
					area[c][r] = 4;
					count_list[4] += map[c][r];
				}
			}
		}
	}

	int min_cnt, max_cnt;
	min_cnt = count_list[1];
	max_cnt = count_list[1];
	for (int i = 2; i <= 5; i++) {
		if (count_list[i] > max_cnt) {
			max_cnt = count_list[i];
		}
		else if (count_list[i] < min_cnt) {
			min_cnt = count_list[i];
		}
	}

	return max_cnt - min_cnt;
}


void solutions() {

	vector <int> list_range;

	for (int x = 0; x < N; x++) {
		for (int y = 0; y < N; y++) {
			for (int d1 = 1; d1 < y; d1++) {
				for (int d2 = 1; y+d2 < N; d2++) {

					if (check_range(x,y,d1,d2)) {
						area = vector < vector <int> >(N, vector<int>(N, 0));
						int val = fill_area(x, y, d1, d2);
						//print_map();
						//cout << val << endl;

						if (min_val > val) {
							min_val = val;
						}
					}
				}
			}
		}
	}

}


int main() {
	cin >> N;

	map = area = vector < vector <int> >(N, vector<int>(N, 0));
	min_val = 20 * 20 * 100;

	for (int c = 0; c < N; c++) {
		for (int r = 0; r < N; r++) {
			cin >> map[c][r];
		}
	}
	/*fill_area(3, 2, 1, 1);
	print_map();
*/
	solutions();
	cout << min_val;


	return 0;
}

/*
7
5 5 5 5 5 5 5
5 5 5 5 5 5 5
5 5 5 5 5 5 5
5 5 5 5 5 5 5
5 5 5 5 5 5 5
5 5 5 5 5 5 5
5 5 5 5 5 5 5
40 27
39
*/