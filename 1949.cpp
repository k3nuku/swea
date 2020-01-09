#include <iostream>

#define MAX(a, b) a > b ? a : b
#define MAXN 9

typedef struct bong {
    int x;
    int y;
    int length;
} bong_t;

int map_data[MAXN][MAXN];
bong_t maxbong[100];

using namespace std;

int solution(int N, int K);
void capable(int x, int y, int k);
int move(int x, int y, int N);

int main(int argc, char** argv) {
	freopen("inputs/1949.txt", "r", stdin);

	int T;
	cin >> T;

	for (int test_case = 1; test_case <= T; ++test_case)
	{
        int N, K, ret;
        cin >> N >> K;

        for (int y = 0; y < N; y++) {
            for (int x = 0; x < N; x++) {
                cin >> map_data[y][x];
            }
        }

        ret = solution(N, K);
        cout << "#" << test_case << " " << ret << '\n';
	}

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}

int solution(int N, int K) {
    int temp_max = 0;
    int maxbong_count = 0;
    int max_length = 0;

    for (int y = 0; y < N; y++)
        for (int x = 0; x < N; x++)
            if (map_data[y][x] > temp_max)
                temp_max = map_data[y][x];

    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            if (temp_max == map_data[y][x]) {
                maxbong[maxbong_count].x = x;
                maxbong[maxbong_count].y = y;
                maxbong_count++;
            }
        }
    }

    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            for (int k = 0; k < K + 1; k++) {
                map_data[y][x] -= k;

                for (int b = 0; b < maxbong_count; b++) {
                    maxbong[b].length = 0;

                    int length;
                    length = move(maxbong[b].x, maxbong[b].y, N);
                    max_length = MAX(max_length, length);
                }

                map_data[y][x] += k;
            }
        }
    }

    return max_length;
}

int move(int x, int y, int N) {
    int move_result = 0, wsize = 0;
    int result;

    if (x > 0 && map_data[y][x - 1] < map_data[y][x]) {
        result = move(x - 1, y, N);
        move_result = MAX(move_result, result);
    }
    if (y > 0 && map_data[y - 1][x] < map_data[y][x]) {
        result = move(x, y - 1, N);
        move_result = MAX(move_result, result);
    }
    if (x < N - 1 && map_data[y][x + 1] < map_data[y][x]) {
        result = move(x + 1, y, N);
        move_result = MAX(move_result, result);
    }
    if (y < N - 1 && map_data[y + 1][x] < map_data[y][x]) {
        result = move(x, y + 1, N);
        move_result = MAX(move_result, result);
    }

    return move_result + 1;
}
