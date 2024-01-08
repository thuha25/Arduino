class Bell {
  private:
    int pin;
    bool isOn = false;
  public:
    Bell(int pin);
    void turnOn();
    void turnOff();
    void bellTone(int val);
    void bellNoTone();
    static void beginTask(Bell* bell);
    static void bellTask(void* parameter);
};