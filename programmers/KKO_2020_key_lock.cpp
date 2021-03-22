#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector < vector < int > > key;
vector < vector < int > > lock;
vector < vector < int > > padded_lock;
vector < vector < vector < int > > > key_set;
int N,M,P; // N은 자물쇠 크기, M은 열쇠 크기


void print_arr(vector < vector < int > > arr) {
	for (int c = 0; c < arr.size(); c++) {
		for (int r = 0; r < arr.size(); r++) {
			cout<< arr[c][r]<< " ";
		}
		cout << endl;
	}
	cout << "==============================" << endl;
}

bool check_unlock() {
	bool res = true;

	for (int c = M; c < N+M-1; c++) {
		for (int r = M; r < N+M-1; r++) {
			if (padded_lock[c][r] == 0)
				res = false;
		}
	}
	return res;
}

bool insert_key(int c, int r, int d) {
	
	for (int dc = 0; dc < M; dc++) {
		for (int dr = 0; dr < M; dr++) {
			padded_lock[c + dc][r + dr] += key_set[d][dc][dr];

			if (padded_lock[c + dc][r + dr] == 2) return false;
		}
	}

	bool res = check_unlock();
	print_arr(padded_lock);
	if (res)
		return true;
	else
		return false;
}

int main() {
	N = 3;
	M = 4;
	P = N + 2 * (M - 1);

	key = vector < vector < int > >(M, vector <int> (M,0));
	lock = vector < vector < int > >(N, vector <int>(N,0));
	padded_lock = vector < vector < int > >(P, vector <int>(P,0));
	key_set = vector < vector < vector < int > > >(4, vector< vector <int > >(M, vector <int>(M, 0)));

	key = { { 0,0,0,0 } ,{0,0,0,0},{ 0,1,0,0 },{ 0,0,1,1 } };
	lock = { { 1,1,1 },{ 1,1,0 },{ 1,0,1 } };

	//padded lock 생성
	for (int c = 0; c < N; c++) {
		for (int r = 0; r < N; r++) {
			padded_lock[c + M - 1][r + M - 1] = lock[c][r];
		}
	}

	//key set 생성
	key_set[0] = key;
	for (int d = 1; d < 4; d++) {
		for (int c = 0; c < M; c++) {
			for (int r = 0; r < M; r++) {
				int c_ = r;
				int r_ = M - c - 1;
				
				key_set[d][c_][r_] = key_set[d - 1][c][r];
			}
		}
		//print_arr(key_set[d]);
	}

	vector < vector < int > > lock_backup = padded_lock;
	//----------------초기화 끝------------------//

	
	for (int c = 0; c < padded_lock.size() - (M - 1); c++) {
		for (int r = 0; r < padded_lock.size() - (M - 1); r++) {
			for (int d = 0; d < 4; d++) {
				if (insert_key(c, r, d) == true) {
					cout << "true";
				}
				//print_arr(padded_lock);
				padded_lock = lock_backup;
			}
		}
	}



}