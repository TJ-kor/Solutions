#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
// 2021.4.17. 14:10 ���� 15:50 �ߴ�

int dd[][4] = { {-1,0,1,0 },{0,1,0,-1 } };

int N, M, sz_shark, cnt_eat;
int map[20][20];
pair<int, int> pos_shark;

/*
 - ���� ó�� ����� ũ�� 2
 - ���� ū������ ��������
 - ���� ������ �԰� ������
 - ������ �׳� �������⸸

 - �̵� ���� 
	1. ����� ������ ���� ����
	2. 1���� ������ ������ ����
	3. �׿ܿ� ����� ������ �̵�.
		- ĭ�� ������ �Ÿ�
		- �ʿ��� ����, ���� ������ �̱�

*/



void print_map() {

	for (int c = 0; c < N; c++) {
		for (int r = 0; r < N; r++) {
			cout << map[c][r] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

bool check_dir(int c, int r) {
	if (c < 0 || c >= N) return false;
	if (r < 0 || r >= N) return false;

	return true;
}

int find() {
	int t = 1;

	vector< pair < int, int> > queue_;
	vector< pair < int, int> > queue_next;
	vector < pair<int,int> > list_fish;
	int map_path[20][20];
	memset(map_path, -1, sizeof(int) * 20 * 20);
	queue_.push_back(pos_shark);
	map_path[pos_shark.first][pos_shark.second] = 0;

	while (true) {
		if (queue_.size() == 0 && list_fish.size() > 0) break;
		if (queue_.size() == 0 && queue_next.size() == 0) break;
		if (queue_.size() == 0 && queue_next.size() != 0) {
			queue_ = queue_next;
			queue_next.clear();
			t++;
		}

		int c = queue_.front().first;
		int r = queue_.front().second;
		queue_.erase(queue_.begin());


		for (int dir = 0; dir < 4; dir++) {
			int c_ = c + dd[0][dir];
			int r_ = r + dd[1][dir];

			
			if (check_dir(c_, r_) == true && map[c_][r_] <= sz_shark && map_path[c_][r_] < 0) {
				//���� �°�, ũ�� �°�, �湮�� �� �ƴϸ�.
				queue_next.push_back(pair<int, int>(c_, r_));
				map_path[c_][r_] = t;

				// ť�� �������߿� ������ ������ list_fish�� �߰�
				if (map[c_][r_] < sz_shark && map[c_][r_] > 0 ) {
					list_fish.push_back(pair<int, int>(c_, r_));
				}
			}
		}
	}

	if (list_fish.size() == 0) return 0;

	int c = list_fish.front().first;
	int r = list_fish.front().second;

	for (auto elem : list_fish) {
		if (c > elem.first) {
			c = elem.first;
			r = elem.second;
		}
		else if (c == elem.first && r > elem.second) {
			c = elem.first;
			r = elem.second;
		}
	}

	if (map[c][r] < sz_shark) cnt_eat++;
	if (cnt_eat == sz_shark) {
		sz_shark++;
		cnt_eat = 0;
	}

	map[pos_shark.first][pos_shark.second] = 0;
	map[c][r] = 9;
	pos_shark = pair<int, int>(c, r);

	return t;
}


int solution() {
	int t = 0;
	int m = 0;


	while (true) {
		//������ ���ǿ� ���� ����
		// 1. 
		//if (m == M) 
		//	break;

		// 2.
		int dist = find();
		if (dist > 0) {
			//cout << "�̵� : " << dist << endl;
			//cout << "���� Ƚ�� : " << cnt_eat<< endl;
			//cout << "ũ�� : " << sz_shark << endl;
			t += dist;
			m+=1;
		}
		else
			break;

		//print_map();
	}

	return t;
}

int main() {
	cin >> N;
	M = 0;
	sz_shark = 2;
	cnt_eat = 0;
	for (int c = 0; c < N; c++) {
		for (int r = 0; r < N; r++) {
			cin >> map[c][r];
			if (map[c][r] == 9) {
				pos_shark = pair<int, int>(c, r);
			}
			else if(map[c][r] != 0){
				M++;
			}
		}
	}

	cout << solution() << endl;

	return 0;
}



/*

10
0 1 4 6 1 4 5 4 0 3
2 0 0 9 0 0 6 0 0 0
4 3 2 4 6 3 0 2 1 6
0 0 0 0 1 0 0 1 0 6
0 0 0 6 0 4 1 4 0 1
0 3 0 1 6 0 3 1 0 4
6 5 0 2 0 0 5 1 0 1
0 4 0 4 1 1 2 5 6 6
1 0 5 6 5 1 0 1 2 0
5 6 3 0 6 0 1 1 6 0

answer:103

10
5 6 3 0 5 5 4 4 3 0
2 4 0 4 0 1 0 1 0 6
0 3 4 1 0 0 3 1 1 0
0 5 1 0 1 6 1 3 5 1
0 3 0 1 1 0 4 0 1 0
0 5 1 5 6 0 3 4 0 9
0 5 5 3 0 0 4 5 0 3
2 5 0 3 3 2 0 0 3 2
2 6 5 0 0 4 1 1 6 3
1 3 1 3 0 1 0 0 0 5

answer:105

10
5 3 2 0 0 1 2 0 4 0
3 0 3 1 0 0 3 0 6 1
0 3 0 5 0 5 4 4 2 5
3 0 0 3 0 6 1 5 4 2
1 0 2 0 2 0 3 0 0 6
1 1 1 1 1 1 1 1 0 0
2 0 2 1 9 6 0 0 4 3
1 6 1 0 6 0 5 0 1 0
6 5 4 0 1 2 1 3 5 0
0 1 6 6 1 4 3 0 1 1

answer:102

10
2 0 2 0 1 1 1 0 1 0
0 4 4 0 4 0 0 0 3 0
4 3 5 0 1 0 2 6 0 0
0 0 5 5 3 1 3 1 3 4
6 0 5 1 4 2 4 0 5 0
0 0 5 0 2 1 1 2 1 0
2 0 5 2 4 0 9 1 6 2
4 1 2 0 3 0 3 2 4 6
3 0 1 0 4 0 0 5 0 1
0 4 1 1 6 6 1 6 0 0

answer:87



10
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 9 0
0 0 0 0 0 0 0 0 1 0
0 0 0 0 0 0 0 0 1 2
*/