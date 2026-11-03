// Test contrasto IR — versione reattiva (media su 20 letture, ~10 valori/s).
// Stampa solo il numero: usare il Plotter seriale dell'IDE.
#define LED_IR 7
#define PT_PIN A0

long leggiDelta() {
  digitalWrite(LED_IR, LOW);
  delayMicroseconds(200);
  int amb = analogRead(PT_PIN);
  digitalWrite(LED_IR, HIGH);
  delayMicroseconds(500);
  int rifl = analogRead(PT_PIN);
  digitalWrite(LED_IR, LOW);
  return (long)rifl - amb;
}

void setup() {
  Serial.begin(9600);
  pinMode(LED_IR, OUTPUT);
  digitalWrite(LED_IR, LOW);
}

void loop() {
  long somma = 0;
  const int N = 20;
  for (int i = 0; i < N; i++) {
    somma += leggiDelta();
  }
  Serial.println(somma / N);
  delay(80);
}
