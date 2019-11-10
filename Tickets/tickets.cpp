#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

int getCount(vector<vector<int>> table, int row, int sum) {
    unsigned int count = 0;
    int upperBorder = (sum >= 9) ? 9 : sum;
    for (int i = 0; i <= upperBorder; ++i)
        count += table[row - 1][sum - i];

    return count;
}

int main() {
    int N;
    cout << "Type an even value from 2 to 10 which is a count of digits on a ticket" << endl;
    cin >> N;

    if (N > 10 || N < 2 || (N % 2 != 0))
        throw std::invalid_argument("Wrong input");

    int n = N / 2;
    auto maxSize = 9 * n + 1;
    vector<vector<int>> table(n, vector<int>(maxSize, 0));

    for (int i = 0; i <= 9; ++i)
        table[0][i] = 1;

    for (int i = 1; i < n; ++i) {
        int upperBorder = 9 * (i + 1);
        for (int j = 0; j <= upperBorder; ++j)
            table[i][j] = getCount(table, i, j);
    }

    unsigned int result = 0;
    for (int i = 0; i < maxSize; ++i)
        result += table[n - 1][i] * table[n - 1][i];

    cout << result << endl;

    return 0;
}