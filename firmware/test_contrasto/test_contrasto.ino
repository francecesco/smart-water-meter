// Test contrasto IR — TCRT5000 + Pro Mini, lettura differenziale su seriale.
// Collegamenti: pin 7 -> 220 ohm -> LED-A, LED-K -> GND,
//               PT-C -> VCC, PT-E -> A0 e 10 kohm -> GND.
#define LED_IR 7
#define PT_PIN A0

void setup() {
  Serial.begin(9600);
  pinMode(LED_IR, OUTPUT);
  digitalWrite(LED_IR, LOW);
}

void loop() {
  digitalWrite(LED_IR, LOW);          // misura ambiente (LED spento)
  delayMicroseconds(200);
  int amb = analogRead(PT_PIN);

  digitalWrite(LED_IR, HIGH);         // misura con LED acceso
  delayMicroseconds(500);             // stabilizzazione
  int rifl = analogRead(PT_PIN);
  digitalWrite(LED_IR, LOW);

  int delta = rifl - amb;             // segnale depurato dall'ambiente
  Serial.print("amb="); Serial.print(amb);
  Serial.print("  rifl="); Serial.print(rifl);
  Serial.print("  delta="); Serial.println(delta);

  delay(100);
}
