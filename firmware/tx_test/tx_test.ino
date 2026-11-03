// TX 433 OOK — test di trasmissione del frame con contatore fittizio.
// Pro Mini 3.3V/8MHz + STX882 (DATA sul pin 4). Un frame ogni 3 s.
// Formato: vedi docs/protocollo-radio.md
#define TX_PIN 4

const unsigned int  T_SHORT    = 500;    // bit 0
const unsigned int  T_LONG     = 1500;   // bit 1 (rapporto 1:3)
const unsigned int  T_GAP      = 500;    // pausa dopo ogni impulso
const unsigned long T_FRAMEGAP = 10000;  // pausa tra ripetizioni
const byte          REPEATS    = 3;

const byte PREAMBLE = 0xAA;
const byte DEV_ID   = 0x5A;

uint32_t contatore = 0;

void sendBit(byte b) {
  digitalWrite(TX_PIN, HIGH);
  delayMicroseconds(b ? T_LONG : T_SHORT);
  digitalWrite(TX_PIN, LOW);
  delayMicroseconds(T_GAP);
}

void sendByte(byte v) {
  for (int i = 7; i >= 0; i--) sendBit((v >> i) & 0x01);   // MSB first
}

void sendFrame(uint32_t count, byte batt) {
  byte b3 = (count >> 24) & 0xFF, b2 = (count >> 16) & 0xFF;
  byte b1 = (count >> 8)  & 0xFF, b0 =  count        & 0xFF;
  byte checksum = (DEV_ID + b3 + b2 + b1 + b0 + batt) & 0xFF;

  for (byte r = 0; r < REPEATS; r++) {
    sendByte(PREAMBLE);
    sendByte(DEV_ID);
    sendByte(b3); sendByte(b2); sendByte(b1); sendByte(b0);
    sendByte(batt);
    sendByte(checksum);
    digitalWrite(TX_PIN, LOW);
    delayMicroseconds(T_FRAMEGAP);
  }
}

void setup() {
  pinMode(TX_PIN, OUTPUT);
  digitalWrite(TX_PIN, LOW);
}

void loop() {
  contatore++;                // simula un consumo che cresce
  sendFrame(contatore, 0xB4); // 0xB4 = segnaposto batteria
  delay(3000);
}
