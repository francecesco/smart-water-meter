# Decisioni

## 1. Sensore ottico invece di magnetico
Il magnete del Maddalena non è sfruttabile dall'esterno. Prove fatte: magnetometro dello smartphone, reed Gebildet a blocchetto, reed in vetro KOFU OKI 2×14 mm (10–15 AT) a contatto col vetro su tutta la superficie. Nessuna rilevazione. Scelto il **TCRT5000** puntato sulla lancetta rossa.

## 2. Il microcontrollore trasmette il conteggio cumulativo
Scartato il riuso del sensore porta **PGST PB-68** pilotato da un optoaccoppiatore: lockout tra le trasmissioni e deriva quando un pacchetto si perde. L'ATmega conta da sé e invia il totale assoluto.

## 3. MCU: Arduino Pro Mini 3.3V / 8 MHz
- ATmega328P, gira direttamente da LiPo (3,0–4,2 V), sleep a pochi µA dopo la rimozione di regolatore e LED.
- Scartati: Nano e Uno (5V/16MHz, regolatore + USB a bordo: solo per prototipi), Pro Micro (ATmega32U4, chip diverso), ogni variante 5V/16MHz, ESP32 (WiFi, consumi).

## 4. Trasmettitore STX882
Modulo con risuonatore SAW, stabile in frequenza: decodifica più pulita in rtl_433 rispetto all'FS1000A.

## 5. TCRT5000 nudo, non il modulo con LM393
Il modulo tiene LED e comparatore sempre alimentati. Con il componente nudo il firmware pulsa il LED e legge in modo differenziale (LED spento / acceso), immune alla luce ambientale.

## 6. Batteria LiPo 1S + TP4056 protetto
Una sola cella a 3,7 V: compatibile con Pro Mini a 3,3 V e con il TP4056. Scartati pacchi 2S (7,4 V) e power bank (si spengono con carichi bassi).

## Alternative valutate
- **ESP32-CAM / AI-on-the-edge**: richiede WiFi e alimentazione fissa.
- **Contatore secondario con uscita reed**: intervento idraulico.
- **Modulo radio ufficiale Maddalena (wM-Bus 868 MHz)**: da verificare con un distributore (esistenza per questo modello, cifratura). Se esistesse sostituirebbe il sensore autocostruito, ricevibile con la stessa SDR via wmbusmeters.
- **Piano B** se il 433 dall'armadio fosse instabile: stesso sensore + ATmega con uscita su sensore porta Zigbee (1 impulso/litro), perdendo il conteggio cumulativo.
