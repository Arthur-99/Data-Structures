namespace SJTU_CS358 {

template<class T>
class queue
{
    T* storage;
    int maxSize;
    int _front, _rear;
    void dbSpace()
    {
        T* tmp = storage;
        storage = new T[2 * maxSize];
        for (int i = 1; i < maxSize; i++)
            storage[i] = tmp[(_front + i) % maxSize];
        _front = 0;
        _rear = maxSize - 1;
        maxSize *= 2;
        delete[] tmp;
    }

  public:
    queue(int initSize = 10)
    {
        storage = new T[initSize];
        maxSize = initSize;
        _front = _rear = 0;
    }
    ~queue() { delete[] storage; }

    bool empty() { return _front == _rear; }

    void push(const T& x)
    {
        if ((_rear + 1) % maxSize == _front)
            dbSpace();
        _rear = (_rear + 1) % maxSize;
        storage[_rear] = x;
    }
    T& front() { return storage[(_front + 1) % maxSize]; }
    T pop()
    {
        _front = (_front + 1) % maxSize;
        return storage[_front];
    }
};

}