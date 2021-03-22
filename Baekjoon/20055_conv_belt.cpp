#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector < int > belt;
vector < int > robot;
int N, K;	//��Ʈ ����, ������ 0 ����


void print_belt() {
	for (int i = 0; i < 2 * N; i++) {
		cout.width(3); // ���� 10���� ����
		cout.fill(' '); // ä�� ���ڴ� '0'
		cout << belt[i] << " ";
	}
	cout << endl;
	int j = robot.size()-1;
	for (int i = 0; i < N; i++) {
		cout.width(4); // ���� 10���� ����
		cout.fill(' '); // ä�� ���ڴ� '0'
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
	// ȸ��
	int tmp = belt[2*N-1];

	//��Ʈ ȸ��
	for (int i = 2 * N -1; i > 0; i--) {
		belt[i] = belt[i - 1];
	}
	//�κ��� ���� ȸ��
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
	// �̵�
	if (robot.size() != 0) {
		for (int i = 0; i < robot.size(); i++) {
			// �̵� ����
			// - N-1�� �ƴϿ�����
			// - �տ� �κ��� ����� ��
			// - �տ� ��Ʈ�� �������� 0�� �ƴϾ����

			if (i > 0 && i + 1 < N - 1 && robot[i] + 1 == robot[i - 1]) {
				// �� �������� �κ��� �ƴϸ鼭, ���� �κ��� N-1���� ���� ��ġ�� �ְ�, ����κ��� �ٷ� �տ� �ִ� ���.
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
	// ž��

	if (belt[0] >= 1) {
		robot.push_back(0);
		belt[0]--;
	}
}

int check_belt() {
	// üũ
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

	//1. ȸ��
	//2. �κ� �̵�
	//3. �տ� �κ� ž��
	//4. ������ 0 ���� üũ

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