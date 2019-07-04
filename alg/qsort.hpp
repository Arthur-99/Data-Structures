#include <utility>

void
qsort(int* a, int l, int r)
{
    if (l >= r)
        return;
    int x = a[r];
    int i = l;
    for (int j = l; j < r; j++) {
        if (a[j] < x) {
            std::swap(a[i], a[j]);
            i++;
        }
    }
    std::swap(a[i], a[r]);
    qsort(a, l, i - 1);
    qsort(a, i + 1, r);
}