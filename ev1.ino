const int buttonPin4 = 4;  // Pin for button 4
const int buttonPin5 = 5;  // Pin for button 5

int ledPin6 = 6;  // Pin for LED 6
int ledPin7 = 7;  // Pin for LED 7

const int pinA4 = A4;  // Use A4 as a digital pin
const int pinA5 = A5;  // Use A5 as a digital pin

const int potentiometerPin = A0;  // Pin for the potentiometer
const int pwmPin = 9;  // Pin for PWM signal to the motor

bool lastButtonState4 = HIGH;  // Previous state of button 4
bool lastButtonState5 = HIGH;  // Previous state of button 5

const int encoderPinA = 2;  // Encoder pin A
const int encoderPinB = 3;  // Encoder pin B

volatile long encoderPosition = 0;  // Current encoder position
volatile int lastEncoded = 0;  // Last encoded position
volatile bool direction = false;  // Encoder direction

unsigned long previousMillis = 0;  // Stores the time of the last cycle
const unsigned long interval = 100;  // Reading interval in milliseconds

void setup() {
  pinMode(buttonPin4, INPUT_PULLUP);  // Configure button 4 pin as input with pull-up
  pinMode(buttonPin5, INPUT_PULLUP);  // Configure button 5 pin as input with pull-up
  pinMode(ledPin6, OUTPUT);    // Configure pin 6 as an output
  pinMode(ledPin7, OUTPUT);    // Configure pin 7 as an output
  pinMode(pwmPin, OUTPUT);     // Configure PWM pin as an output

  pinMode(encoderPinA, INPUT);
  pinMode(encoderPinB, INPUT);
  attachInterrupt(digitalPinToInterrupt(encoderPinA), updateEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderPinB), updateEncoder, CHANGE);

  pinMode(pinA4, OUTPUT);
  pinMode(pinA5, OUTPUT);
  Serial.begin(9600);  // Start serial communication at 9600 baud
}

void loop() {
  int reading4 = digitalRead(buttonPin4);  // Read button 4 state
  int reading5 = digitalRead(buttonPin5);  // Read button 5 state

  int potValue = analogRead(potentiometerPin);  // Read potentiometer value

  // Convert potentiometer value (0-1023) to PWM value (0-255)
  int pwmValue = map(potValue, 0, 1023, 0, 255);
  analogWrite(pwmPin, pwmValue);  // Apply PWM signal to the motor
  
  // Read encoder position
  long currentPosition = encoderPosition;
  Serial.println(currentPosition);

  if (reading4 != lastButtonState4) {
    if (reading4 == LOW) {
      delay(60);  // Wait to debounce
      if (digitalRead(buttonPin4) == LOW) {
        digitalWrite(ledPin6, !digitalRead(ledPin6));  // Toggle LED 6 state
        if (digitalRead(ledPin6)) {
          Serial.println("Right turn on");
          digitalWrite(pinA5, HIGH);
          digitalWrite(pinA4, LOW);
          digitalWrite(pwmPin, HIGH);
        }
        if (!digitalRead(ledPin6)) {
          Serial.println("Right turn off");
          digitalWrite(pinA4, LOW);
          digitalWrite(pinA5, LOW);
          digitalWrite(pwmPin, HIGH);
        }
        
        // Turn off both LEDs if both are on
        if (digitalRead(ledPin6) && digitalRead(ledPin7)) {
          digitalWrite(ledPin6, LOW);
          digitalWrite(ledPin7, LOW);
          Serial.println("Turn stopped");
          digitalWrite(pinA4, LOW);
          digitalWrite(pinA5, LOW);
          digitalWrite(pwmPin, HIGH);
        }
      }
    }
    lastButtonState4 = reading4;
  }

  if (reading5 != lastButtonState5) {
    if (reading5 == LOW) {
      delay(60);  // Wait to debounce
      if (digitalRead(buttonPin5) == LOW) {
        digitalWrite(ledPin7, !digitalRead(ledPin7));  // Toggle LED 7 state
        if (digitalRead(ledPin7)) {
          Serial.println("Left turn on");
          digitalWrite(pinA5, LOW);
          digitalWrite(pinA4, HIGH);
          digitalWrite(pwmPin, HIGH);
        } 
        if (!digitalRead(ledPin7)) {
          Serial.println("Left turn off");
          digitalWrite(pinA4, LOW);
          digitalWrite(pinA5, LOW);
          digitalWrite(pwmPin, HIGH);
        }
        
        // Turn off both LEDs if both are on
        if (digitalRead(ledPin6) && digitalRead(ledPin7)) {
          digitalWrite(ledPin6, LOW);
          digitalWrite(ledPin7, LOW);
          Serial.println("Turn stopped");
          digitalWrite(pinA4, LOW);
          digitalWrite(pinA5, LOW);
          digitalWrite(pwmPin, HIGH);
        }
      }
    }
    lastButtonState5 = reading5;
  }
}

void updateEncoder() {
  int MSB = digitalRead(encoderPinA);
  int LSB = digitalRead(encoderPinB);

  int encoded = (MSB << 1) | LSB;
  int sum = (lastEncoded << 2) | encoded;

  if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) {
    encoderPosition++;
    direction = true;
  }
  if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) {
    encoderPosition--;
    direction = false;
  }

  lastEncoded = encoded;
}
