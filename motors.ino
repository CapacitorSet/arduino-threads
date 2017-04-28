/* A simple application of multitasking: MotorManager moves a servo depending on
 * the light level. Adapted from
 * http://zuccala.blogspot.it/2010/02/multitasking-arduino-millis-parte-2.html
 */

#include <Servo.h>
#include "threadmanager.cpp"

ThreadManager threadManager;

class MotorManager {
  private:
    int lightReading;
    Servo servo;
    int servoPos;
    int sensorPin;
    int id;
    unsigned long startTime;

  public:
    MotorManager(int _sensorPin, int _pinServo, int _id) {
      sensorPin = _sensorPin;
      id = _id;
      servo.attach(_pinServo);
    }
    void setup(void) {
      pinMode(sensorPin, INPUT);
    }
    uint16_t tick(uint16_t thseq, uint16_t thseqtemp) {
      THREAD_START;
        startTime = micros();
        lightReading = analogRead(sensorPin);
      THREAD_BREAK;
        servoPos = map(lightReading, 0, 1023, 0, 179);
      THREAD_BREAK;
        servo.write(servoPos);
      THREAD_BREAK;
        Serial.print("Sensor reading #");
        Serial.print(id);
        Serial.print(": ");
        Serial.println(lightReading, DEC);
      THREAD_BREAK;
        Serial.print("Motor position #");
        Serial.print(id);
        Serial.print(": ");
        Serial.println(servoPos, DEC);
      THREAD_BREAK;
        Serial.print("Cycle duration #");
        Serial.print(id);
        Serial.print(": ");
        Serial.print(micros() - startTime, DEC);
        Serial.println(" uS");
      THREAD_END;
    }
};


MotorManager manager1(A0, 8, 1);
MotorManager manager2(A1, 9, 2);

/* Ugly wrappers around the methods, because for whatever reason C++ doesn't
 * allow function pointers to non-static methods - though simple wrappers like
 * these are perfectly fine.
 */
uint16_t tick1(uint16_t thseq, uint16_t thseqtemp) {
  return manager1.tick(thseq, thseqtemp);
}
uint16_t tick2(uint16_t thseq, uint16_t thseqtemp) {
  return manager2.tick(thseq, thseqtemp);
}

void setup() {
  Serial.begin(9600);
  manager1.setup();
  manager2.setup();
  threadManager.addThread(tick1);
  threadManager.addThread(tick2);
}

void loop() {
  threadManager.tick();
  /* Tick at least once every 10 ms. The actual duration will be 10 ms + a
   * variable amount, depending on how much work is done in each thread.
   */
  delay(10);
}