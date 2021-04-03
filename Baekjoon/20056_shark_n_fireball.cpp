#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
// 2021.4.3 13:50 시작, 15:40분 종료

/*
- 전역 변수 : N, map, list_ball(겹친 위치 기록)
- 파이어볼 : m,d,s (질량,방향,속력)

- 파이어볼 이동, 겹치기 가능(map에서 리스트 형태로 저장).
- 과정
  - 이동 > 합체 > 4개로 다시 나뉨 > 질량이 0이면 소멸

  - 이동 시, 2개 겹쳐있을때 list_ball에 좌표 추가.
    - 2개일때만 추가해도 됨, 그 이상 계속 넣으면 중복 좌표 추가.
  - 합쳤다가 다시 4개로 나뉘었을때 그자리에 그대로 겹쳐져있음 

*/

typedef struct info_fireball {
	int m, d, s;
} fireball;

int N, M, K;
int dd[][8] = { {-1,-1,0,1,1,1,0,-1},{0,1,1,1,0,-1,-1,-1} };

vector < vector< vector<fireball> > > map, map_next;
vector< pair<int, int> > list_merge;


void print_map(int val) {
	cout << "==========================================" << endl;
	for (int c = 0; c < N; c++) {
		for (int r = 0; r < N; r++) {
			cout.width(2);
			cout.fill(' ');
			if(val ==0)
				cout << map[c][r].size() << " ";
			else if(val == 1)
				cout << map_next[c][r].size() << " ";
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

void moving(int c, int r, fireball ball) {

	// 속도 s가 N보다 클수도 있기 때문에 N의 나머지만큼 이동
	int c_next = c + (dd[0][ball.d] * ball.s) % N;	
	int r_next = r + (dd[1][ball.d] * ball.s) % N;

	// 이동했는데 인덱스를 벗어난 값이면 다시 조정
	if (c_next < 0) {
		c_next = N + c_next;
	}
	else if (c_next >= N) {
		c_next = c_next - N;;
	}

	if (r_next < 0) {
		r_next = N + r_next;
	}
	else if (r_next >= N) {
		r_next = r_next - N;;
	}

	// 계산 된 위치에 파이어볼 추가
	map_next[c_next][r_next].push_back(ball);


	// 해당 위치에 파이어볼이 2개가 되면 합쳐야 할 위치 리스트에 좌표 추가
	// 3개 이상부터는 할 필요 없음, 오히려 중복 처리 문제 발생
	if (map_next[c_next][r_next].size() == 2) {
		list_merge.push_back(pair<int, int>(c_next, r_next));
	}
}

void move_ball() {
	for (int c = 0; c < N; c++) {
		for (int r = 0; r < N; r++) {
			//파이어볼이 없으면 패스
			if (map[c][r].size() == 0) {
				continue; 
			}

			// 파이어볼이 있으면 next_map에서 이동된 위치에 기록
			
			while(map[c][r].size()>0){
				fireball ball_cur = map[c][r].front();
				map[c][r].erase(map[c][r].begin());

				moving(c, r, ball_cur);
			}
		}
	}
}

void merge_ball() {

	while (list_merge.size() > 0) {
		// 이동하면서 저장한 겹친 좌표들 한개씩 불러내어 처리
		int c = list_merge.front().first;
		int r = list_merge.front().second;
		list_merge.erase(list_merge.begin());

		bool same = true;
		int d, m, s;
		m = s = 0;
		d = map_next[c][r][0].d % 2;

		for (int i = 0; i < map_next[c][r].size(); i++) {
			//겹치는 위치에서 파이어볼을 하나씩 꺼내어 총합 계산.
			m += map_next[c][r][i].m;
			s += map_next[c][r][i].s;

			if (map_next[c][r][i].d % 2 != d) {
				//하나라도 홀짝이 틀린게 있으면 체크
				same = false;
			}
		}

		m = m / 5;
		s = s / map_next[c][r].size();

		map_next[c][r].clear();

		if (m > 0) {
			//질량이 존재 하면 4개의 fireball 추가
			for (int i = 0; i < 4; i++) {
				fireball tmp;
				tmp.m = m;
				tmp.s = s;
				if (same) {
					// 같은 홀or짝이였다면, 짝수 방향
					tmp.d = i * 2;
				}
				else {
					// 아니면 홀수 방향
					tmp.d = i * 2 + 1;
				}				

				map_next[c][r].push_back(tmp);
			}
		}

	}
}

int count_mass() {
	int sum = 0;
	for (int c = 0; c < N; c++) {
		for (int r = 0; r < N; r++) {
			// 겹쳐져있는지 확인 필요
			for (int i = 0; i < map[c][r].size(); i++) {
				sum += map[c][r][i].m;
			}
		}
	}

	return sum;
}

int solution() {

	while (K > 0) {
		map_next = vector < vector< vector<fireball> > >(N, vector< vector<fireball> >(N)); 

		move_ball();	// 파이어볼 이동
		//print_map(1);
		merge_ball();	// 겹친 파이어볼 합치기 & 분배
		
		K--;
		map = map_next;	// 맵 갱신
		//print_map(0);
	}

	return count_mass();// 총 질량 계산
}

int main() {
	cin >> N >> M >> K;
	map = vector < vector< vector<fireball> > >(N, vector< vector<fireball> >(N));

	for (int m = 0; m < M; m++) {
		fireball tmp;
		int c, r;

		cin >> c >> r >> tmp.m >> tmp.s >> tmp.d;
		map[c-1][r-1].push_back(tmp);
	}
	//print_map(0);
	cout << solution();


	return 0;
}