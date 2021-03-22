#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector < int > belt;
vector < int > robot;
int N, K;	//벨트 길이, 내구도 0 갯수


void print_belt() {
	for (int i = 0; i < 2 * N; i++) {
		cout.width(3); // 폭을 10으로 지정
		cout.fill(' '); // 채움 문자는 '0'
		cout << belt[i] << " ";
	}
	cout << endl;
	int j = robot.size()-1;
	for (int i = 0; i < N; i++) {
		cout.width(4); // 폭을 10으로 지정
		cout.fill(' '); // 채움 문자는 '0'
		if (robot.size() > 0 && j < robot.size() && i == robot[j]) {

			cout << "1 ";
			j--;
		}
		else {
			cout << "0 ";
		}
	}
	cout << endl;
}

void rotate_belt() {
	// 회전
	int tmp = belt[2*N-1];

	//벨트 회전
	for (int i = 2 * N -1; i > 0; i--) {
		belt[i] = belt[i - 1];
	}
	//로봇도 같이 회전
	for (int i = 0; i < robot.size(); i++) {
		if (robot[i] < N - 2) {
			robot[i]++;
		}
		else {
			robot.erase(robot.begin());
			i--;
		}
	}

	belt[0] = tmp;
}

void move_robot() {
	// 이동
	if (robot.size() != 0) {
		for (int i = 0; i < robot.size(); i++) {
			// 이동 조건
			// - N-1이 아니여야함
			// - 앞에 로봇이 없어야 함
			// - 앞에 벨트의 내구도가 0이 아니어야함

			if (i > 0 && i + 1 < N - 1 && robot[i] + 1 == robot[i - 1]) {
				// 맨 오른쪽의 로봇이 아니면서, 다음 로봇이 N-1보다 앞의 위치에 있고, 현재로봇의 바로 앞에 있는 경우.
				continue;
			}

			if (robot[i] < N - 1 && belt[robot[i] + 1] > 0) {
				robot[i]++;
				belt[robot[i]]--;
			}

			if (robot[i] == N - 1) {
				robot.erase(robot.begin() + i);
				i--;
			}
		}
	}
}

void push_robot() {
	// 탑승

	if (belt[0] >= 1) {
		robot.push_back(0);
		belt[0]--;
	}
}

int check_belt() {
	// 체크
	int count = 0;

	for (int i = 0; i < belt.size(); i++) {
		if (belt[i] == 0) count++;
	}

	return count;
}



int main() {
	cin >> N >> K;
	
	belt = vector<int>(2 * N, 0);
	
	//input
	for (int i = 0; i < 2 * N; i++) {
		cin >> belt[i];
	}

	//1. 회전
	//2. 로봇 이동
	//3. 앞에 로봇 탑승
	//4. 내구도 0 갯수 체크

	int count = 1;
	while (true) {
		cout << "---------------------------------" << endl;
		rotate_belt();	//1
		print_belt();
		move_robot();	//2
		print_belt();
		push_robot();	//3
		print_belt();
		if (check_belt() >= K) {	//4
			cout << count;
			break;
		}
		else {
			count++;
		}
	}

	return 0;
}