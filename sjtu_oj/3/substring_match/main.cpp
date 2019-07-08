#include <iostream>
#include <cstring>

using namespace std;

int main() {
    char a[800], b[80];
    cin >> a >> b;

    int lena = strlen(a), lenb = strlen(b);
    const int L = lenb;

    int i, j;
    int p[L];
    p[0] = -1;
    for (i = 1; i < L; i++) {
        j = i - 1;
        while (j >= 0 && b[p[j] + 1] != b[i]) j = p[j];
        if (j < 0) p[i] = -1;
        else p[i] = p[j] + 1;
    }

    i = j = 0;
    while (i < lena && j < lenb) {
        if (a[i] == b[j]) {
            i++;
            j++;
        } else if (j == 0) i++;
        else j = p[j - 1] + 1;
    }

    if (j == lenb) cout << i - j;
    else cout << -1;

    return 0;
}