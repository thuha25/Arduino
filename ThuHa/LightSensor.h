class LightSensor {
  private:
    int pin;
  public:
    LightSensor(int anologPin);
    int read();
};