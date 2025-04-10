struct PinInfo {
  uint8_t pinNumber;       // Номер пина
  uint32_t toggleInterval; // Интервал переключения (полупериод)
  volatile uint32_t lastToggleTime; // Время последнего переключения
  bool currentState;       // Текущее состояние пина
};

PinInfo pinArray[] = {
  {3,  10000, 0, LOW}, // 10 мс
  {5,   1000, 0, LOW}, // 1 мс
  {6,    500, 0, LOW}, // 500 мкс
  {9,    100, 0, LOW}, // 100 мкс
  {10,    50, 0, LOW}  // 50 мкс
};
const uint8_t pinCount = sizeof(pinArray) / sizeof(PinInfo);

void setup() {
  for (uint8_t index = 0; index < pinCount; index++) {
    pinMode(pinArray[index].pinNumber, OUTPUT);
  }
}

void loop() {
  uint32_t now = micros();

  for (uint8_t index = 0; index < pinCount; index++) {
    if (now - pinArray[index].lastToggleTime >= pinArray[index].toggleInterval) {
      pinArray[index].lastToggleTime = now;

      pinArray[index].currentState = !pinArray[index].currentState;
      digitalWrite(pinArray[index].pinNumber, pinArray[index].currentState);
    }
  }
}