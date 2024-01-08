class DCMotor {
  private:
    int in1;
    int in2;
  public:
    int speed = 150;
    DCMotor(int in1, int in2);
    void setSpeed(int speed);
    void rotateClockwise();
    void rotateCounterClockwise();
};