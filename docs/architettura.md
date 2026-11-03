# Architettura

## Obiettivo e vincoli

- Leggere il consumo del contatore Maddalena CD SD PLUS TCM 142/10 e portarlo in Home Assistant.
- **Vincolo 1 — 433 MHz**: riusare il ricevitore esistente (RTL-SDR + rtl_433 sul Raspberry Pi).
- **Vincolo 2 — batteria**: al contatore non c'è alimentazione. Il dispositivo deve durare mesi.
- Il contatore è in un **armadio buio**: nessun IR ambientale, condizione favorevole al sensore ottico.

## Catena dati

| Stadio | Componente | Ruolo |
|---|---|---|
| Sensore | TCRT5000 (LED IR + fototransistor) | Vede passare la lancetta rossa |
| Elaborazione | Arduino Pro Mini 3.3V/8MHz (ATmega328P) | Conta gli impulsi, salva il totale, decide quando trasmettere |
| Trasmissione | STX882 (SAW) 433,92 MHz OOK + antenna λ/4 | Invia il frame con il **conteggio cumulativo** |
| Ricezione | RTL-SDR Blog V4 su Raspberry Pi 1 B+ | rtl_433 con decoder flex `-X` |
| Trasporto | MQTT (broker su Home Assistant) | Topic `rtl_433/rpi3/events` |
| Presentazione | Home Assistant | Sensore litri `total_increasing`, sensore batteria |

## Principio chiave: conteggio cumulativo

Il dispositivo non invia "è passato un impulso", ma **il totale assoluto** degli impulsi, ripetuto 3 volte per frame. Un pacchetto perso non crea deriva: il successivo riallinea il valore. Per questo il vecchio sensore porta PGST PB-68 (un evento per impulso, con lockout) è stato abbandonato.

## Alimentazione

LiPo 1S 3,7 V 3000 mAh (con BMS) → TP4056 USB-C protetto → nodo unico **+BATT** (3,0–4,2 V). Il Pro Mini, senza regolatore, e lo STX882 sono alimentati direttamente a tensione di batteria. Schema: [hardware/schemi/schema_elettrico_definitivo.svg](../hardware/schemi/schema_elettrico_definitivo.svg).
