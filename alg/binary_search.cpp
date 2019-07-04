int
first_larger(int* a, int n, int key)
{
    int l = 0, r = n - 1, mid;
    while (l <= r) {
        mid = (l + r) / 2;
        if (a[mid] > key)
            r = mid - 1;
        else
            l = mid + 1;
    }
    return l;
}

int
last_smaller(int* a, int n, int key)
{
    int l = 0, r = n - 1, mid;
    while (l <= r) {
        mid = (l + r) / 2;
        if (a[mid] < key)
            l = mid + 1;
        else
            r = mid - 1;
    }
    return r;
}
