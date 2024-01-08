class Led {
  private:
    int pin;
  public:
    Led(int pin);
    void turnOn();
    void turnOff();
};