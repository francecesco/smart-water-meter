# Firmware definitivo — specifica

Da scrivere a blocchi, validando ognuno prima del successivo.

1. **TX e frame** — riusa `tx_test` senza modificare il formato ([protocollo](../../docs/protocollo-radio.md)).
2. **Rilevazione impulsi** — lettura differenziale veloce, soglia con isteresi, nessun `delay`. A Q3 la lancetta ×0,0001 fa ~7 giri/s: servono centinaia di campioni/s durante il flusso. Soglie da tarare al contatore.
3. **Contatore + EEPROM** — uint32 cumulativo; salvataggio ogni N impulsi o a tempo, con wear leveling (~100.000 scritture per cella).
4. **Invio e sleep** — invio su variazione con intervallo minimo, messaggio di vita periodico (es. 1 h), sleep tra le misure, campionamento adattivo (lento ad acqua ferma).
5. **Batteria** — partitore su A1 (con la 100 kΩ) o misura del riferimento interno; mappatura del byte in volt da documentare nel protocollo.
6. **Brown-out** — soglia coerente con la LiPo (BMS ~3 V, ATmega a 8 MHz ≥ ~2,7 V).

Parametri da tenere configurabili: soglie del sensore, intervallo minimo di invio, periodo del messaggio di vita, ogni quanti impulsi salvare.
