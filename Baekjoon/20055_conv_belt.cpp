#include <iostream> 
#include <vector>


using namespace std;

// 2021.4.2 17:00 시작 

/*
전역변수 : N, K, T, velt, life_velt

- velt[2][] : 로봇이 있으면 true, 없으면 false
- life_velt[2][] : int vector

- pop & push 로 회전 구현
- 내구도 >= 1 && !로봇 
  - 로봇 이동
  - 가능한 케이스 
    1. (n+1)에 아무것도 없음 : velt[n] = false, velt[n+1] = true
	2. (n+1)에 아무것도 없는데 끝임 : velt[n] = false, K--
	3. (n+1)에 있음 : 이동 X
*/


int N, K, T;

vector <bool> velt;
vector <vector <int>> life_velt;

void print_velt() {
	cout << "==========================" << endl;
	
	for (int j = 0; j < N; j++) {
		cout.width(3);
		cout.fill(' ');
		cout << velt[j] << " ";
	}
	cout << endl;

	cout << endl;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < N; j++) {
			cout.width(3);
			cout.fill(' ');
			cout << life_velt[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

}


void rotate() {
	int last, first;
	last = life_velt[0][N-1];
	first = life_velt[1][0];

	life_velt[0].erase(life_velt[0].begin() + (N - 1));
	life_velt[1].erase(life_velt[1].begin());

	life_velt[0].insert(life_velt[0].begin(), first);
	life_velt[1].push_back(last);

	velt.erase(velt.begin() + (N - 1));
	velt.insert(velt.begin(), false);

	if (velt[N - 1] == true) {
		velt[N - 1] = false;
	}
}
void move_robot() {
	for (int i = N - 1; i > 0; i--) {
		// 벨트 끝에서부터 비었는지 확인하고
		// 이동 가능하면 앞의 로봇을 가져옴
		

		if (velt[i-1] == true && velt[i] == false 
			&& life_velt[0][i] > 0) {
			//앞에 로봇이 존재하고, 이동 가능하면,
			velt[i] = true;
			velt[i-1] = false;
			life_velt[0][i]--;

			if (life_velt[0][i] == 0) {
				K--;
			}
		}
	}

	if (velt[N - 1] == true) {
		velt[N - 1] = false;
	}
}
void put_in_robot() {

	if (velt[0] == false && life_velt[0][0] > 0) {
		velt[0] = true;
		life_velt[0][0]--;

		if (life_velt[0][0] == 0) {
			K--;
		}
	}
}


void solve() {
	while (true) {
		rotate();
		//print_velt();
		move_robot();
		//print_velt();
		put_in_robot();
		//print_velt();
		T++;
		//cout << "=============" << T << "============" << endl;
		if (K == 0) break;
	}
}

int main() {
	cin >> N >> K;

	velt = vector<bool>(N, false);
	life_velt = vector<vector<int>>(2, vector<int>(N, 0));

	for (int i = 0; i < N; i++) {
		cin >> life_velt[0][i];
	}
	for (int i = N - 1; i >= 0; i--) {
		cin >> life_velt[1][i];
	}

	T = 0;
	solve();
	cout << T;

	return 0;
}