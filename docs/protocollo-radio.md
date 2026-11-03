# Protocollo radio

Il formato del frame è **congelato**: decoder rtl_433 e sensore Home Assistant dipendono da questo documento. Ogni modifica va concordata con il lato ricezione.

## Modulazione

- OOK PWM a 433,92 MHz (STX882), dato sul pin 4 del Pro Mini.
- **bit 0 = impulso corto 500 µs**, **bit 1 = impulso lungo 1500 µs** (rapporto 1:3).
- Pausa fissa di **500 µs** dopo ogni impulso.
- **10 ms** di pausa tra le ripetizioni. Il frame viene ripetuto **3 volte**.
- Bit inviati **MSB first**.

> Nota per il decoder: in rtl_433 `OOK_PWM` interpreta per default l'impulso corto come 1. Con questa codifica (corto = 0) serve l'opzione `invert`, altrimenti i byte risultano invertiti (0xAA → 0x55). Verificato il 28/10/2026: grezzo `55a5fffffd574b47` → invertito `AA 5A 000002A8 B4 B8`, checksum corretto. Il decoder installato usa `invert`.

## Struttura del frame (64 bit)

| Byte | Campo | Valore |
|---|---|---|
| 0 | Preambolo | `0xAA` |
| 1 | ID dispositivo | `0x5A` |
| 2–5 | Conteggio cumulativo impulsi | uint32 big-endian |
| 6 | Batteria | 1 byte (mappatura in volt da definire; oggi segnaposto `0xB4`) |
| 7 | Checksum | `(ID + C3 + C2 + C1 + C0 + BATT) mod 256` (preambolo escluso) |

Il frame porta **impulsi grezzi**. La conversione in litri (`impulsi × risoluzione + offset`) la fa Home Assistant, così il firmware non dipende da quale lancetta viene letta.

## Quando trasmettere (da implementare)

- Non a ogni impulso: con l'acqua che scorre il conteggio cambia di continuo.
- Accumulare e inviare il totale **quando cambia, con un intervallo minimo** tra un invio e l'altro.
- **Messaggio di vita** anche ad acqua ferma (es. ogni ora), con la tensione della batteria: HA distingue un sensore morto da un periodo senza consumi.
- Tra un invio e l'altro il micro dorme.
- Il firmware di test (un frame ogni 3 s) occupa ~8,5% del tempo, vicino al limite tipico del 10% per i 433 MHz: il firmware definitivo deve stare ben sotto.
