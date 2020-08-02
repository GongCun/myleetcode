class FooBar {
  private:
    int n;
    mutex mtx;
    condition_variable cvFoo, cvBar;
    bool fooFlag = true, barFlag = false;

  public:
    FooBar(int n) {
        this->n = n;
    }

    void foo(function<void()> printFoo) {
        
        for (int i = 0; i < n; i++) {
            unique_lock<mutex> lk(mtx);
            cvFoo.wait(lk, [this]{return fooFlag;});
            
            // printFoo() outputs "foo". Do not change or remove this line.
            printFoo();
            fooFlag = false, barFlag = true;
            cvBar.notify_one();
        }
    }

    void bar(function<void()> printBar) {
        unique_lock<mutex> lk(mtx);
        for (int i = 0; i < n; i++) {
            cvBar.wait(lk, [this]{return barFlag;});
            
            // printBar() outputs "bar". Do not change or remove this line.
            printBar();
            fooFlag = true, barFlag = false;
            cvFoo.notify_one();
        }
    }
};
