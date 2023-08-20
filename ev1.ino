const int buttonPin4 = 4;  // Pin para el pulsador 4
const int buttonPin5 = 5;  // Pin para el pulsador 5

int ledPin6 = 6;  // Pin para el LED 6
int ledPin7 = 7;  // Pin para el LED 7

bool lastButtonState4 = HIGH;  // Estado previo del pulsador 4
bool lastButtonState5 = HIGH;  // Estado previo del pulsador 5

void setup() {
  pinMode(buttonPin4, INPUT_PULLUP);  // Configurar el pin del pulsador 4 como entrada con pull-up
  pinMode(buttonPin5, INPUT_PULLUP);  // Configurar el pin del pulsador 5 como entrada con pull-up
  pinMode(ledPin6, OUTPUT);    // Configurar el pin 6 como salida
  pinMode(ledPin7, OUTPUT);    // Configurar el pin 7 como salida

  Serial.begin(9600);  // Iniciar comunicación serial a 9600 baudios
}

void loop() {
  int reading4 = digitalRead(buttonPin4);  // Leer estado del pulsador 4
  int reading5 = digitalRead(buttonPin5);  // Leer estado del pulsador 5

  if (reading4 != lastButtonState4) {
    if (reading4 == LOW) {
      delay(60);  // Esperar para manejar el antirrebote
      if (digitalRead(buttonPin4) == LOW) {
        digitalWrite(ledPin6, !digitalRead(ledPin6));  // Cambiar estado del LED 6
        if (digitalRead(ledPin6)) {
          Serial.println("LED 6 encendido.");
        } else {
          Serial.println("LED 6 apagado.");
        }
        
        // Apagar ambos LEDs si ambos están encendidos
        if (digitalRead(ledPin6) && digitalRead(ledPin7)) {
          digitalWrite(ledPin6, LOW);
          digitalWrite(ledPin7, LOW);
          Serial.println("Ambos LEDs apagados.");
        }
      }
    }
    lastButtonState4 = reading4;
  }

  if (reading5 != lastButtonState5) {
    if (reading5 == LOW) {
      delay(60);  // Esperar para manejar el antirrebote
      if (digitalRead(buttonPin5) == LOW) {
        digitalWrite(ledPin7, !digitalRead(ledPin7));  // Cambiar estado del LED 7
        if (digitalRead(ledPin7)) {
          Serial.println("LED 7 encendido.");
        } else {
          Serial.println("LED 7 apagado.");
        }
        
        // Apagar ambos LEDs si ambos están encendidos
        if (digitalRead(ledPin6) && digitalRead(ledPin7)) {
          digitalWrite(ledPin6, LOW);
          digitalWrite(ledPin7, LOW);
          Serial.println("Ambos LEDs apagados.");
        }
      }
    }
    lastButtonState5 = reading5;
  }
}
