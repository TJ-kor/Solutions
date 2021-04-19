#include <iostream> 
#include <deque>
#include <algorithm>

using namespace std;
//2020.04.19 13:30 시작 14:30 end
// 덱 구조 이용한 회전 이동 응용

int dd[][4] = { {-1,0,1,0},{0,1,0,-1} };
int N, M, T; //N 원판의 갯수, M 원판에 적힌 숫자의 갯수
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
	//기존 보드 복사

	for (int n = 0; n <= N; n++)
		board_next[n] = board[n];


	bool flag = false; // 한개라도 삭제한 숫자가 있으면 true
	for (int n = 1; n <= N; n++) {
		for (int m = 0; m < M; m++) {
			if (board[n][m] == 0) continue;
			count++;
			sum = sum + board[n][m];

			for (int dir = 0; dir < 4; dir++) {
				// 4개 인접 숫자 체크
				int n_ = n + dd[0][dir];
				int m_ = m + dd[1][dir];


				// 인덱스 벗어난거 체크
				if (n_ < 1 || n_ > N) continue;
				if (m_ < 0) m_ = M - 1;
				else if (m_ >= M) m_ = 0;


				if (board[n_][m_] == board[n][m]) {
					flag = true;
					board_next[n][m] = 0;	//숫자 삭제
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
		//x배수, d 방향(0, 1), k 칸 회전
		
		for (int n = 1; n <= N; n++) {
			//x 배수 보드 체크
			if (n%x == 0) {
				rotation(n, d, k);
			}
		}
		//print_board();
		check_closed_number();
		//print_board();
	}

	//보드의 총합 계산
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