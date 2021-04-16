#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

//2021.4.16 12:20 시작 14:00 종료

/*

- 바이러스 갯수 V 개 중에서 M 개를 선택해야함
- list_virus : 0 ~ M 에서 한개씩 뽑아가면서 재귀적으로 탐색 (DFS)
- map_virus : 선택 된 바이러스부터 한개씩 큐에 넣어 탐색 (BFS)
*/


int N, M, Minimum_time, count_empty;		// Minimum_time : 최소 탐색 시간, count_empty : 빈칸의 갯수 

int dd[][4] = { {-1,0, 1, 0},{0,1,0,-1 } };	

vector< vector <int> > map_input, map_virus;	// map_input : 초기 연구소 정보, map_virus : BFS 탐색 위한 방문 맵
vector< pair<int, int> > list_virus;			// list_virus : DFS 방법으로 조합을 만들기 위한 리스트

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
	vector< pair<int, int> > queue_virus_next;		// t시간에서 다음에 방문할 큐를 만듬, 그래야 t와 t+1이 구분되고 중복 방문 방지
	vector< vector <int> > map_backup = map_virus;	// map_virus 이 전역변수이기 떄문에 백업.


	// map_virus 이 초기에는 -1 채워져 있기 때문에 선택된 바이러스에 시간 0 입력
	for (auto val : queue_virus)
		map_virus[val.first][val.second] = 0;


	while (true) {
		if ((queue_virus.size() == 0 && queue_virus_next.size() == 0) || count_empty == count_copy) {
			// 큐가 전부 비어있거나, 앞으로 방문할 빈칸이 없다면 종료.
			break;
		}
		else if (queue_virus.size() == 0 && queue_virus_next.size() != 0) {
			// 현시간의 큐가 비었고, 다음 시간의 방문 할 큐가 존재하면 
			// 다음 시간으로 진행

			t++;
			queue_virus = queue_virus_next;
			queue_virus_next.clear();
			//print_map();
		}
		
		//큐에서 한개 뽑음
		pair<int, int> virus = queue_virus.front();
		queue_virus.erase(queue_virus.begin());

		//빈칸에 복제 횟수 체크
		if (map_input[virus.first][virus.second] == 0) count_copy++;
		


		for (int dir = 0; dir < 4; dir++) {
			int c = virus.first + dd[0][dir];
			int r = virus.second + dd[1][dir];

			/*
			 - 탐색 규칙
			  - 맵 밖, 벽이 아니어야 함.
			  - 경로 맵에 방문한 적이 없어야함. ( -1 값)
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
		// 모두 선택 됬을 경우 BFS 진행

		int t = BFS(set_virus);

		if (Minimum_time > t ) {
			Minimum_time = t;
		}
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

	if (Minimum_time == N * N + 1)  Minimum_time = - 1;
	cout << Minimum_time;

	return 0;
}

