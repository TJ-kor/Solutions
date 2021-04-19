#include <iostream> 
#include <deque>
#include <algorithm>

using namespace std;
//2020.04.19 13:30 ���� 14:30 end
// �� ���� �̿��� ȸ�� �̵� ����

int dd[][4] = { {-1,0,1,0},{0,1,0,-1} };
int N, M, T; //N ������ ����, M ���ǿ� ���� ������ ����
deque <int> board[51];

void print_board() {
	for (int n = 1; n <= N; n++) {
		for (int m = 0; m < M; m++) {
			cout.width(2);
			cout.fill(' ');
			cout << board[n][m] << " ";
		}
		cout << endl;
	}
	cout << endl;
}


void rotation(int n, int d, int k) {
	while (k-- > 0) {
		if (d == 0) {
			board[n].push_front(board[n].back());
			board[n].pop_back();
		}
		else{
			board[n].push_back(board[n].front());
			board[n].pop_front();
		}
	}
}

void check_closed_number() {
	deque <int> board_next[51];
	float sum = 0;
	int count = 0;
	//���� ���� ����

	for (int n = 0; n <= N; n++)
		board_next[n] = board[n];


	bool flag = false; // �Ѱ��� ������ ���ڰ� ������ true
	for (int n = 1; n <= N; n++) {
		for (int m = 0; m < M; m++) {
			if (board[n][m] == 0) continue;
			count++;
			sum = sum + board[n][m];

			for (int dir = 0; dir < 4; dir++) {
				// 4�� ���� ���� üũ
				int n_ = n + dd[0][dir];
				int m_ = m + dd[1][dir];


				// �ε��� ����� üũ
				if (n_ < 1 || n_ > N) continue;
				if (m_ < 0) m_ = M - 1;
				else if (m_ >= M) m_ = 0;


				if (board[n_][m_] == board[n][m]) {
					flag = true;
					board_next[n][m] = 0;	//���� ����
					break;
				}
			}
		}
	}

	float mean = sum / count;

	if (flag) {
		for (int n = 0; n <= N; n++)
			board[n] = board_next[n];
	}
	else{
		for (int n = 1; n <= N; n++) {
			for (int m = 0; m < M; m++) {
				if (board[n][m] == 0) continue;
				if (board[n][m] > mean) {
					board[n][m] -= 1;
				}
				else if (board[n][m] < mean) {
					board[n][m] += 1;
				}
			}
		}
	}
}

int solution() {

	int t = 0;
	while (t++ < T) {
		int x, d, k;
		cin >> x >> d >> k;
		//x���, d ����(0, 1), k ĭ ȸ��
		
		for (int n = 1; n <= N; n++) {
			//x ��� ���� üũ
			if (n%x == 0) {
				rotation(n, d, k);
			}
		}
		//print_board();
		check_closed_number();
		//print_board();
	}

	//������ ���� ���
	int sum=0;
	for (int n = 1; n <= N; n++) {
		for (int m = 0; m < M; m++) {
			sum += board[n][m];;
		}
	}
	return sum;
}

int main() {
	cin >> N >> M >> T;

	for (int n = 1; n <= N; n++) {
		for (int m = 0; m < M; m++) {
			int tmp;
			cin >> tmp;

			board[n].push_back(tmp);
		}
	}
	

	cout << solution();

	return 0;
}