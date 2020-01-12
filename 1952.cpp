#include <iostream>

#define MIN(a, b) a < b ? a : b
#define MAXN 12

using namespace std;

int toll[4];
int map[MAXN + 1];
int fee[MAXN + 1];

int solution() {
    fee[1] = min(min(map[1] * toll[0], toll[1]), toll[2]);

    for (int i = 2; i <= MAXN + 1; i++) {
        for (int j = 0; j < 2; j++) {
            switch (j) {
                case 0:
                fee[i] = MIN(fee[i - 1] + map[i] * toll[0], fee[i - 1] + toll[1]);
                break;

                case 1:
                if (i > 2) {
                    fee[i] = MIN(fee[i], fee[i - 3] + toll[2]);

                    if (i == MAXN)
                        fee[i] = MIN(fee[i], toll[3]);
                }
                break;
            }
        }
    }

    return fee[12];
}

int main(int argc, char** argv) {
	int T;
	cin >> T;

	for (int test_case = 1; test_case <= T; ++test_case)
	{
        int ret;

        cin >> toll[0] >> toll[1] >> toll[2] >> toll[3];

        for (int i = 1; i < MAXN + 1; i++)
            cin >> map[i];
        
        ret = solution();
        cout << "#" << test_case << " " << ret << '\n';
	}

	return 0;
}
