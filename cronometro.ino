#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

#define DEBUG 1

#if DEBUG
#define PRINT(s, x) { Serial.print(F(s)); Serial.print(x); }
#define PRINTS(x) Serial.print(F(x))
#define PRINTX(x) Serial.println(x, HEX)
#else
#define PRINT(s, x)
#define PRINTS(x)
#define PRINTX(x)
#endif

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CLK_PIN   13
#define DATA_PIN  11
#define CS_PIN    10

MD_Parola P = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

const uint8_t BUTTON_START = 5;
const uint8_t BUTTON_UP = 4;
const uint8_t BUTTON_DOWN = 3;

bool isRunning = false;
bool isPaused = false;
unsigned long startTime = 0;
unsigned long timeRemaining = 0;
unsigned long initialTime = 0; // Tempo inicial
char timeBuffer[10];

const int buzzerPin = 2;
bool buzzerOn = false;

void setup() {
  Serial.begin(57600);
  Serial.println("\n[Parola Scrolling Display - Timer Programável]\n");

  pinMode(buzzerPin, OUTPUT);
  pinMode(BUTTON_START, INPUT_PULLUP);
  pinMode(BUTTON_UP, INPUT_PULLUP);
  pinMode(BUTTON_DOWN, INPUT_PULLUP);

  P.begin();
  displayTime(initialTime); // Mostrar o tempo inicial
}

void loop() {
  handleButtons();

  if (isRunning && !isPaused) {
    unsigned long currentTime = millis();
    if (currentTime >= startTime) {
      timeRemaining -= (currentTime - startTime);
      startTime = currentTime;
    }

    if (timeRemaining <= 0) {
      timeRemaining = 0;
      if (!buzzerOn) {
        Serial.println("Tempo esgotado, buzzer ligado");
        tone(buzzerPin, 400); // Ajuste a frequência conforme necessário
        buzzerOn = true;
      }
      isRunning = false; // Parar o timer
    }

    displayTime(timeRemaining);
  }

  if (P.displayAnimate()) {
    P.displayReset();
  }
}

void handleButtons() {
  static unsigned long lastDebounceTime = 0;
  static const unsigned long debounceDelay = 200;

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (digitalRead(BUTTON_START) == LOW) {
      if (!isRunning) {
        timeRemaining = initialTime;
        startTime = millis();
        isRunning = true;
        isPaused = false;
        buzzerOn = false;
        noTone(buzzerPin); // Parar o buzzer se estiver tocando
        Serial.println("Timer iniciado");
      } else {
        isPaused = !isPaused;
        if (isPaused) {
          Serial.println("Timer pausado");
          noTone(buzzerPin); // Parar o buzzer se estiver tocando
        } else {
          Serial.println("Timer retomado");
          startTime = millis();
        }
      }
    }

    if (digitalRead(BUTTON_UP) == LOW && !isRunning) {
      initialTime += 60000; // Aumentar 1 minuto
      if (initialTime > 3599999) { // Limite máximo de 59:59
        initialTime = 3599999;
      }
      Serial.print("Tempo ajustado para: ");
      Serial.println(initialTime / 1000);
      displayTime(initialTime);
    }

    if (digitalRead(BUTTON_DOWN) == LOW) {
      if (!isRunning || isPaused) {
        initialTime = 0; // Reseta p/ qualquer valor inicial desejado
        timeRemaining = initialTime;
        isPaused = false;
        isRunning = false;
        buzzerOn = false;
        noTone(buzzerPin); // Parar o buzzer se estiver tocando
        Serial.println("Timer resetado");
        displayTime(initialTime);
      }
    }

    lastDebounceTime = millis();
  }
}

void displayTime(unsigned long milliseconds) {
  unsigned int totalSeconds = milliseconds / 1000;
  unsigned int minutes = totalSeconds / 60;
  unsigned int seconds = totalSeconds % 60;

  sprintf(timeBuffer, "%02d:%02d", minutes, seconds);
  P.setTextBuffer(timeBuffer);
}
