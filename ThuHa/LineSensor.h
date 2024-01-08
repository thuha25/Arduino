class LineSensor {
  private:
    int pin;
  public:
    LineSensor(int pin);
    int read();
};