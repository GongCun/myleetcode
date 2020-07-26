class Foo {
  private:
    mutex mtx;
    condition_variable cv_two, cv_three;
    mutable int seq = 1;
    
  public:
    Foo() {
        
    }

    void first(function<void()> printFirst) {
        //lock_guard<mutex> lk(mtx);
        unique_lock<mutex> lk(mtx);
        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();
        seq = 2;
        cv_two.notify_one();
    }

    void second(function<void()> printSecond) {
        unique_lock<mutex> lk(mtx);
        while (seq != 2) {
            cv_two.wait(lk);
        }
       
        // printSecond() outputs "second". Do not change or remove this line.
        printSecond();
        seq = 3;
        cv_three.notify_one();
    }

    void third(function<void()> printThird) {
        unique_lock<mutex> lk(mtx);
        while (seq != 3) {
            cv_three.wait(lk);
        }
        
        // printThird() outputs "third". Do not change or remove this line.
        printThird();
    }
};
