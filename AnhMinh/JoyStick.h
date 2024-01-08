class JoyStick {
  private:
    int xPin;
    int yPin;
    int bPin;
  public:
    JoyStick(int xPin, int yPin, int bPin);
    int getX();
    int getY();
    bool isButtonDown();
};