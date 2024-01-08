class UltrasnonicSensor {
  private:
    int trigPin;
    int echoPin;
  public:
    UltrasnonicSensor(int triggerPin, int echoPin);
    int readDistance();
    int readDuration();
};