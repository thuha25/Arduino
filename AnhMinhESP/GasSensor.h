class GasSensor {
  private:
    int pin;
  public:
    GasSensor(int anologPin);
    int read();
};