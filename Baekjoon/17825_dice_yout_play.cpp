#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;
// 2021.04.19 14:30 ���� 17:40 ����

//������ �ִ� - DFS;

int val_dice[10];
int num_mal[10];
int max_score = 0;


vector <vector <int> > board = {
	{ 0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,0 },
{ 0, 13,16,19,25,30,35,40,0 },
{ 0, 22,24,25,30,35,40,0 },
{ 0, 28,27,26,25,30,35,40,0 }
};

pair<int, int> move(vector <pair<int, int> > pos_mal, int mal, int idx_dice, int &num) {
	pair<int, int> pos_mal_cur = pos_mal[mal];
	int i = pos_mal_cur.first;
	int j = pos_mal_cur.second;

	if (j + val_dice[idx_dice] >= board[i].size() - 1) {
		// ���� ó�� 
		pos_mal_cur.first = -1;
		pos_mal_cur.second = -1;
		num = 0;
		return pos_mal_cur;
	}

	// ������ ������ üũ

	// �ٱ� ����̸鼭 �Ķ��� �ƴѰ�� 
	j += val_dice[idx_dice];
	num = board[i][j];
	if (i == 0 && board[0][j] % 10 == 0) {
		// �ٱ� ����̸鼭 �Ķ��� �ΰ�� 
		if (board[i][j] != 40) {
			i = board[i][j] / 10;
			j = 0;
		}
	}


	bool flag = true;

	for (int m = 0; m < 4; m++) {
		if (mal == m) continue;
		if (pos_mal[m].first == -1) continue;
		if (pos_mal[m] == pair<int, int>(i, j)) {
			flag = false;
			break;
		}

		// ��ġ�°�� 
		// 1. ���� �ٸ���, 25~40 ���� 
		if (pos_mal[m].first != i && board[pos_mal[m].first].size() - pos_mal[m].second <= 5 && board[i].size() - j <= 5) {
			if (board[pos_mal[m].first][pos_mal[m].second] == board[i][j])
				flag = false;
		}
		else if (board[pos_mal[m].first][pos_mal[m].second] == 40 && board[i][j] == 40)
			flag = false;


		// �߸��� ���� ó��
		//if (pos_mal[m] == pair<int, int>(i, j))
		//	flag = false;
		//else if (pos_mal[m].first > 0 && i > 0 &&
		//	board[pos_mal[m].first][pos_mal[m].second] == board[i][j])
		//	flag = false;
		//else if (board[pos_mal[m].first][pos_mal[m].second] == 40 && board[i][j] == 40)
		//	flag = false;	
		//else if(pos_mal[m].first > 0 && i > 0 &&
		//	board[pos_mal[m].first].size()-pos_mal[m].second == board[i].size() - j && board[i].size() - j <= 5)
		//	flag = false;
	}


	if (!flag) {
		// �̵��� ���� ���� �ִ� ��� ����ġ
		pos_mal_cur = pos_mal[mal];
		num = 0;
	}
	else {
		pos_mal_cur = pair<int, int>(i, j);
	}

	return pos_mal_cur;
}

void DFS(vector < pair<int, int> > pos_mal, int idx_dice, int score) {
	/*for (auto val : pos_mal) {
	cout << val.first << ", " << val.second << " // ";
	}
	cout << " score: " << score << endl;;
	*/
	if (idx_dice == 10) {
		if (max_score < score) {
			max_score = score;
		}
		return;
	}
	else {

		for (int mal = 0; mal < 4; mal++) {
			// ���õ� �� �̵� �������� üũ
			if (pos_mal[mal].first == -1 || pos_mal[mal].second == -1) continue;

			if (score + (10 - idx_dice) * 40 < max_score) continue;

			pair<int, int> pos_back = pos_mal[mal];
			// ���� ���
			int num = 0;
			pos_mal[mal] = move(pos_mal, mal, idx_dice, num);	// �� �̵�
			if (pos_back == pos_mal[mal]) continue;				// �̵��� ���� �������� ���̿��� �������� ���� ���,


			num_mal[idx_dice] = mal;
			DFS(pos_mal, idx_dice + 1, score + num);			// DFS Ž��
			pos_mal[mal] = pos_back;							// �� �� ��ġ
		}
	}
}

int main() {
	for (int i = 0; i < 10; i++) {
		cin >> val_dice[i];
	}

	vector < pair<int, int> > pos_mal;
	pos_mal = vector<pair<int, int>>(4, pair<int, int >(0, 0));
	DFS(pos_mal, 0, 0);

	cout << max_score;
	return 0;
}