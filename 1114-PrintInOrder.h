class Foo {
  private:
    mutex mtx;
    condition_variable cv;
    mutable int seq = 1;
    
  public:
    Foo() {
        
    }

    void first(function<void()> printFirst) {
        unique_lock<mutex> lk(mtx);
        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();
        seq = 2;
        cv.notify_all();
    }

    void second(function<void()> printSecond) {
        unique_lock<mutex> lk(mtx);
        while (seq != 2) {
            cv.wait(lk);
        }
       
        // printSecond() outputs "second". Do not change or remove this line.
        printSecond();
        seq = 3;
        cv.notify_all();
    }

    void third(function<void()> printThird) {
        unique_lock<mutex> lk(mtx);
        while (seq != 3) {
            cv.wait(lk);
        }
        
        // printThird() outputs "third". Do not change or remove this line.
        printThird();
    }
};
