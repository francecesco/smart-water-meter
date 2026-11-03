# Roadmap

## Firmware (`firmware/contatore/`)
- [x] Blocco 1 — TX OOK e formato frame (`tx_test`, validato in ricezione)
- [ ] Blocco 2 — Rilevazione impulsi veloce (soglia + isteresi, centinaia di campioni/s durante il flusso)
- [ ] Blocco 3 — Contatore reale + persistenza EEPROM (non a ogni impulso; ogni N impulsi o a tempo, wear leveling)
- [ ] Blocco 4 — Logica di invio (su variazione con intervallo minimo + messaggio di vita) e sleep
- [ ] Blocco 5 — Lettura batteria reale (partitore su A1) e mappatura del byte in volt
- [ ] Soglia brown-out (BMS stacca ~3 V, ATmega a 8 MHz regge fino a ~2,7 V)

## Hardware
- [ ] Test al contatore: contrasto attraverso il vetro, velocità reale, ricerca lancetta ×0,001
- [ ] Misure per il supporto 3D
- [ ] Partitore batteria nello schema
- [ ] Modifica Pro Mini (regolatore e LED) e saldatura su millefori
- [ ] Misura della corrente in sleep tramite J1

## Ricezione e Home Assistant
- [ ] Decoder `-X` definitivo con `bits=64` e `repeats>=2`
- [ ] `-s 250k` sul Pi 1
- [ ] Nuovo sensore HA (litri, batteria, messaggio di vita) e dismissione delle entità PB-68
- [ ] Verifica litri/impulso con la lancetta scelta

## Da valutare
- [ ] Esistenza del modulo wM-Bus ufficiale Maddalena per il TCM 142/10
