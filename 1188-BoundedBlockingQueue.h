class BoundedBlockingQueue {
  private:
    mutable mutex mtx;
    queue<int> data_queue;
    condition_variable not_full, not_empty;
    mutable int capacity;
    
    
  public:
    BoundedBlockingQueue(int capacity) {
        this->capacity = capacity;
    }
    
    void enqueue(int element) {
        unique_lock<mutex> lk(mtx);
        not_full.wait(lk, [this]{return data_queue.size() < capacity;});
        data_queue.push(element);
        not_empty.notify_one();
    }
    
    int dequeue() {
        unique_lock<mutex> lk(mtx);
        not_empty.wait(lk, [this]{return !data_queue.empty();});
        int data = data_queue.front();
        data_queue.pop();
        not_full.notify_one();
        return data;
    }
    
    int size() {
        lock_guard<mutex> lk(mtx);
        return data_queue.size();
    }
};
