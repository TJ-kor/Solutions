#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

//2021.4.16 12:20 ����

/*

- ���̷��� ���� V �� �߿��� M ���� �����ؾ���
- list_virus : 0 ~ 9 ���� �Ѱ��� �̾ư��鼭 ��������� Ž�� (DFS)


*/


int N, M, Minimum_time, count_empty;
int dd[][4] = { {-1,0, 1, 0},{0,1,0,-1 } };

vector< vector <int> > map_input, map_virus;
vector< pair<int, int> > list_virus;

void print_map() {
	for (int c = 0; c < N; c++) {
		for (int r = 0; r < N; r++) {

			if (map_input[c][r] == 1) {
				cout << "# ";
			}
			else if (map_virus[c][r] == -1) {
				cout << "0 ";
			}
			else {
				cout << map_virus[c][r]<<" ";
			}
		}
		cout << endl;
	}

	cout << endl;
}

bool check_dir(int c, int r) {
	if (c < 0 || c >= N) return false;
	if (r < 0 || r >= N) return false;
	if (map_input[c][r] == 1) return false;
	
	return true;
}

int BFS(vector< pair<int, int> > queue_virus) {
	int t = 0;
	int count_copy = 0;
	vector< pair<int, int> > queue_virus_next;
	vector< vector <int> > map_backup = map_virus;


	for (auto val : queue_virus)
		map_virus[val.first][val.second] = 0;

	while (true) {
		if ((queue_virus.size() == 0 && queue_virus_next.size() == 0) || count_empty == count_copy) {
			break;
		}
		else if (queue_virus.size() == 0 && queue_virus_next.size() != 0) {
			t++;
			queue_virus = queue_virus_next;
			queue_virus_next.clear();
			print_map();
		}

		pair<int, int> virus = queue_virus.front();
		queue_virus.erase(queue_virus.begin());

		//��ĭ ���� Ƚ�� üũ
		if (map_input[virus.first][virus.second] == 0) count_copy++;
		
		
		for (int dir = 0; dir < 4; dir++) {
			int c = virus.first + dd[0][dir];
			int r = virus.second + dd[1][dir];

			/*
			 - ��Ģ
			  - �� ��, ���� �ƴϾ�� ��.
			  - ��� �ʿ� �湮�� ���� �������. ( -1 ��)
			  - 
			*/

			if (check_dir(c, r) && map_virus[c][r] == -1) {
				map_virus[c][r] = t+1;
				queue_virus_next.push_back(pair<int, int>(c, r));
			}
		}
	}

	map_virus = map_backup;

	if (count_empty != count_copy) t = Minimum_time;
	return t;
}

void DFS(vector< pair<int, int> > set_virus, int idx_start, int idx_end, int m) {
	
	if (m > M) {
		
		// ��� ���� ���� ��� BFS ����

		int t = BFS(set_virus);

		if (Minimum_time > t ) {
			Minimum_time = t;
		}

		/*
		//���� Ȯ�ο� �ڵ�
		for (auto val : set_virus) cout << val.first << ", " << val.second << " || ";
		cout << endl;
		*/

		return;
	}


	for (int i = idx_start; i <= idx_end; i++) {
		set_virus.push_back(list_virus[i]);
		DFS(set_virus, i + 1, list_virus.size() - (M - m), m+1);
		set_virus.pop_back();
	}
}


void solution() {
	int t = 0;
	
	vector< pair<int, int> > set_virus;
	DFS(set_virus, 0, list_virus.size() - M , 1);

}

int main() {
	cin >> N >> M;

	map_input = vector< vector <int> >(N, vector <int>(N, 0));
	map_virus = vector< vector <int> >(N, vector <int>(N, -1));

	Minimum_time = N * N + 1;
	count_empty = 0;

	for (int c = 0; c < N; c++) {
		for (int r = 0; r < N; r++) {
			cin >> map_input[c][r];
			if (map_input[c][r] == 2) {
				list_virus.push_back(pair<int, int>(c, r));
			}
			else if (map_input[c][r] == 0) {
				count_empty++;
			}
		}
	}

	solution();

	if (Minimum_time == N * N + 1)  Minimum_time - 1;
	cout << Minimum_time;

	return 0;
}

