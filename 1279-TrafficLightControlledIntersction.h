class TrafficLight {
  private:
    mutex mtx;
    bool road1CanGo = true;
    bool road2CanGo = false;
    
  public:
    TrafficLight() {
        
    }

    void carArrived(
        int carId,                   // ID of the car
        int roadId,                  // ID of the road the car travels on. Can be 1 (road A) or 2 (road B)
        int direction,               // Direction of the car
        function<void()> turnGreen,  // Use turnGreen() to turn light to green on current road
        function<void()> crossCar    // Use crossCar() to make car cross the intersection
    ) {
        lock_guard<mutex> lk(mtx);
        if (roadId == 1 && !road1CanGo) {
            road1CanGo = true;
            road2CanGo = false;
            turnGreen();
        } else if (roadId == 2 && !road2CanGo) {
            road2CanGo = true;
            road1CanGo = false;
            turnGreen();
        }
        
        crossCar();
    }


};
