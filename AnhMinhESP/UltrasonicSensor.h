class UltrasnonicSensor {
  private:
    int trigPin;
    int echoPin;
    long duration;
    float distance;
  public:
    UltrasnonicSensor(int triggerPin, int echoPin);
    void trigger();
    int readDistance();
    int readDuration();
};