# Firmware

## Sketch

| Cartella | Scopo | Stato |
|---|---|---|
| `test_contrasto/` | Lettura differenziale, stampa `amb`, `rifl`, `delta` | ✅ validato |
| `test_contrasto_media/` | Media su 200 letture, valore stabile ogni ~0,5 s | ✅ validato |
| `test_contrasto_reattivo/` | Media su 20 letture, ~10 valori/s, per il Plotter seriale | ✅ validato |
| `tx_test/` | Frame OOK a 433 MHz con contatore fittizio, un frame ogni 3 s | ✅ ricevuto dal Pi |
| `contatore/` | Firmware definitivo | ⏳ da scrivere (specifica nel README) |

## Impostazioni Arduino IDE

- **Scheda**: Arduino Pro or Pro Mini
- **Processore**: ATmega328P (**3.3V, 8 MHz**) — con 16 MHz il seriale esce illeggibile e i tempi radio raddoppiano
- **Porta**: quella del CP2102 (macOS: `/dev/cu.usbserial-*` o `/dev/cu.SLAB_USBtoUART`)
- Monitor seriale: **9600 baud**

## Collegamento CP2102 → Pro Mini (header J2)

| CP2102 | Pro Mini |
|---|---|
| GND | GND |
| 3V3 | VCC |
| TXD | RXI |
| RXD | TXO |
| 5V | **non collegare** |

**Prima di collegare il CP2102, apri J1** (batteria isolata).

## Caricamento con reset manuale

Il CP2102 in uso non ha il pin DTR, quindi il reset automatico non avviene.

1. Premi **Carica**.
2. Quando la barra passa da "Compilazione…" a **"Caricamento…"**, premi e rilascia il tasto **reset** del Pro Mini.
3. Se esce `not in sync` o un timeout, riprova: è solo questione di tempismo.

Variante: tieni premuto reset verso la fine della compilazione e rilascialo appena compare "Caricamento…".
