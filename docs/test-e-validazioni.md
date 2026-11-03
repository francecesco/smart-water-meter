# Test e validazioni

## Strada magnetica (abbandonata)
| Prova | Esito |
|---|---|
| Magnetometro smartphone su tutto il quadrante | Nessun campo rilevato |
| Reed Gebildet a blocchetto a contatto col vetro | Nessuna chiusura |
| Reed KOFU OKI 2×14 mm nudo, scansione completa e tre orientamenti | Nessuna chiusura |

## Sensore ottico (banco, Pro Mini via CP2102)
| Prova | Esito |
|---|---|
| Lettura differenziale, nulla davanti | `amb≈0`, delta stabile |
| Dito davanti | `rifl` e `delta` salgono, `amb` resta fermo |
| Torcia puntata | `amb` sale, `delta` resta stabile → reiezione ambientale OK |
| Contrasto su carta (media 200 letture, a contatto) | bianco 9–10, **rosso 17–20**, nero 1 |
| Dinamico: fondo bianco a ~3 cm, oggetto rosso mosso a mano | baseline 4, picco 6–8–10, ritorno a 4 |
| Ripresa dopo la pausa | baseline ~10 ±1, reagisce al dito |

**Limite**: il test dinamico è a velocità "umana". La lancetta ×0,0001 a Q3 fa ~7 giri/s: va ripetuto al contatore a velocità reale.

## Radio
| Prova | Esito |
|---|---|
| Firmware `tx_test`, ricezione dallo studio | Nessun pacchetto (distanza/muri) |
| Firmware `tx_test`, breadboard in garage vicino al Pi (28/10/2026) | ✅ 64 bit, 3 ripetizioni ogni ~3 s; checksum verificato |
| Decoder `ContatoreAcquaV2` installato nel servizio (28/10/2026) | ✅ campi `impulsi`, `batteria_raw`, `checksum` sul broker |

## Catena a valle (23/10/2026)
- Impulso simulato pubblicato su MQTT con i codici veri → `counter.litri_acqua_totali` da 0 a 1. ✅
- rtl_433 → broker → Home Assistant. ✅

## Catena a valle con il frame nuovo (28/10/2026)
- Frame a conteggio 0 (`aa5a00000000b40e`) pubblicato sul broker → `sensor.contatore_acqua_litri_totali` = 0. ✅

## Problemi incontrati
- Seriale illeggibile: processore impostato a 16 MHz invece di 8 MHz.
- Upload bloccato: CP2102 senza DTR → reset manuale all'inizio di "Caricamento…".
- Sottotensione del Pi 1 (`get_throttled` 0x50005, 25/10/2026): la RTL-SDR si scollegava (`error -71`) fino a sparire.
- Misure di resistenze incoerenti: fondoscala sbagliato e multimetro inaffidabile (sostituito).
