# Hardware

Schema completo: [schema_elettrico_definitivo.svg](../hardware/schemi/schema_elettrico_definitivo.svg). Distinta: [BOM.md](../hardware/BOM.md).

## Collegamenti

| Da | A | Note |
|---|---|---|
| Pro Mini **7** | R1 220 Ω → TCRT5000 **LED-A** | Il firmware pulsa il LED solo durante la misura |
| TCRT5000 **LED-K** | GND | |
| TCRT5000 **PT-C** | +BATT | Collettore fototransistor |
| TCRT5000 **PT-E** | Pro Mini **A0** + R2 10 kΩ → GND | R2 è la resistenza di carico |
| Pro Mini **4** | STX882 **DATA** | Dati OOK |
| STX882 **VCC** | +BATT | Tensione piena di batteria = più portata |
| STX882 **ANT** | Antenna a molla λ/4 (~17 cm) | Senza antenna la portata crolla |
| C1 100 µF + C2 100 nF | tra VCC e GND dello STX882 | Il più vicino possibile al modulo; C1 polarizzato (− a GND) |
| LiPo + / − | TP4056 **B+ / B−** | |
| TP4056 **OUT+** | J1 → +BATT | |
| TP4056 **OUT−** | GND | |
| Pro Mini GND/VCC/RXI/TXO | J2 → CP2102 GND/3V3/TXD/RXD | Solo per programmare |
| Pro Mini **A1** | libero | Riservato al partitore di lettura batteria |

## Regole di sicurezza

1. **Il − della batteria va solo su B− del TP4056**, mai su GND: la protezione da sovrascarica sta tra B− e OUT−.
2. **Prima di collegare il CP2102, apri J1** (togli il ponticello o scollega la batteria). Altrimenti i 3,3 V del CP2102 e la batteria (fino a 4,2 V) si contrastano sullo stesso nodo.
3. Il CP2102 si usa **solo sull'uscita 3V3**. Il pin 5V resta scollegato.

## J1 — interruttore di alimentazione

Due pin di header maschio (avanzati dalle strisce del Pro Mini) chiusi da un jumper dupont femmina-femmina o da un cappuccio jumper. Serve a isolare la batteria durante la programmazione e a misurare la corrente in sleep mettendo il multimetro in serie al posto del ponticello.

## Resistenze

| Rif. | Valore | Colori | Misurata |
|---|---|---|---|
| R1 | 220 Ω (150–470 Ω accettabile) | rosso · rosso · marrone · oro | 216 Ω |
| R2 | 10 kΩ | marrone · nero · arancio · oro | 10,1 kΩ |
| (riserva) | 100 kΩ | marrone · nero · giallo · oro | 95,5 kΩ — per il partitore batteria |

Con +BATT a 4,2 V la corrente di picco nel LED IR è ~13 mA: entro i limiti del pin (40 mA max).

## TCRT5000 — identificazione dei pin

- **Lente blu = LED IR**, **lente nera = fototransistor**.
- Multimetro in modalità diodo: la coppia del LED segna **~1,10 V in un solo verso** (punta rossa = anodo LED-A). La coppia del fototransistor dà **OL in entrambi i versi**.
- C ed E del fototransistor sono stati assegnati e verificati sperimentalmente (il segnale reagisce correttamente). **Marcare i piedini sul componente** prima di smontare il prototipo.
- Nello schema i pin sono disegnati in un ordine diverso da quello fisico, solo per leggibilità.

## Pro Mini — modifiche per la batteria

- Rimuovere il **regolatore onboard** e il **LED di alimentazione** (consumano anche in sleep).
- Alimentare direttamente sul pin **VCC** a tensione di batteria.

## Strumenti

- Multimetro: per resistenze basse usare il fondoscala 200 Ω o 2 kΩ, per 10 kΩ il 20 kΩ, per 100 kΩ il 200 kΩ. Su un fondoscala troppo piccolo le letture sono prive di senso.
