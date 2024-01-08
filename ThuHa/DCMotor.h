class DCMotor {
  private:
    int in1;
    int in2;
    int speed = 150;
  public:
    DCMotor(int in1, int in2);
    void setSpeed(int speed);
    void rotateClockwise();
    void rotateCounterClockwise();
};