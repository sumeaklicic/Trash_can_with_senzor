#include <Servo.h>

const int trigPin = 12;  // Trig pin za HC-SR04
const int echoPin = 11;  // Echo pin za HC-SR04
const int servoPin = 8;  // Pin za servo motor

Servo myServo;  // Kreiraj objekat za servo

void setup() {
  // Inicijalizuj pinove
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // Inicijalizuj servo motor
  myServo.attach(servoPin);

  // Početno podešavanje servo pozicije (ako je potrebno)
  myServo.write(0);  // Na početku servo je na 0 stepeni

  Serial.begin(9600);  // Počni serijsku komunikaciju za debagovanje
}

void loop() {
  // Izmeri udaljenost pomoću ultrazvučnog senzora
  long duration, distance;
  
  digitalWrite(trigPin, LOW);  // Obezbedi da trig pin bude LOW
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);  // Pošaljemo signal
  delayMicroseconds(10);       // Traje 10 mikrosekundi
  digitalWrite(trigPin, LOW);   // Zaustavimo signal
  
  // Merenje trajanja odjeka
  duration = pulseIn(echoPin, HIGH);
  
  // Izračunaj udaljenost u centimetrima (brzina zvuka je 34300 cm/s)
  distance = duration * 0.0344 / 2;  // Podeljeno sa 2 da bi se dobila prava udaljenost
  
  // Prikazivanje vrednosti udaljenosti u serijskom monitoru
  Serial.print("Udaljenost: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Pokreni while petlju dok je udaljenost manja od 5 cm
  while (distance < 5) {
    // Ako je udaljenost manja od 5 cm, pomeraj servo za 90 stepeni
    myServo.write(90);  // Pomeraj servo na 90 stepeni
    Serial.println("Servo pomeren na 90 stepeni");

    // Ponovo izmeri udaljenost unutar petlje
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.0344 / 2;  // Izračunaj novu udaljenost
    
    // Pauza pre sledeće provere (ne prebrzo)
    delay(700);
  }
  
  // Kada udaljenost postane veća od 5 cm, vrati servo na 0 stepeni
  myServo.write(0);  
  Serial.println("Servo vracen na 0 stepeni");

  // Pauza pre ponovnog merenja udaljenosti
  delay(100);  // Pauza između merenja
}

