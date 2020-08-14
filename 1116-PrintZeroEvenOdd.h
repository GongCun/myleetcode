class ZeroEvenOdd {
  private:
    int n;
    mutex mtx;
    condition_variable cv;
    mutable bool flagZero = true, flagNum = false;
    mutable int seq = 1;
    

  public:
    ZeroEvenOdd(int n) {
        this->n = n;
    }

    // printNumber(x) outputs "x", where x is an integer.
    void zero(function<void(int)> printNumber) {
        for (auto i = 0; i < n; i++) {
            unique_lock<mutex> lk(mtx);
            cv.wait(lk, [this]{return flagZero;});
            printNumber(0);
            flagZero = false, flagNum = true;
            cv.notify_all();
        }
        
    }

    void odd(function<void(int)> printNumber) {
        for (auto i = 1; i <= n; i+=2) {
            unique_lock<mutex> lk(mtx);
            cv.wait(lk, [this]{return flagNum && (seq % 2 == 1);});
            printNumber(i);
            flagZero = true, flagNum = false, seq += 1;
            cv.notify_all();
        }
    }

    void even(function<void(int)> printNumber) {
        for (auto i = 2; i <= n; i+=2) {
            unique_lock<mutex> lk(mtx);
            cv.wait(lk, [this]{return flagNum && (seq % 2 == 0);});
            printNumber(i);
            flagZero = true, flagNum = false, seq += 1;
            cv.notify_all();
        }
    }

};
