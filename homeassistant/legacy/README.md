# Configurazione storica (PB-68)

Da rimuovere quando il nuovo sensore è in funzione.

| Entità | Ruolo |
|---|---|
| `binary_sensor.impulso_contatore_acqua` | Sensore MQTT su `rtl_433/rpi3/events`; `{25}<codice ON>` = ON, `{25}<codice OFF>` = OFF |
| Automazione "contatore acqua" | +1 su `counter.litri_acqua_totali` a ogni OFF→ON |
| `counter.litri_acqua_totali` | Totale litri (incrementale) |
| `sensor.lettura_reale_contatore` | Template |
| Automazione `contatore_acqua_test_notifica` | Telegram a ogni impulso se `input_boolean.test_contatore_acqua` è attivo |

Prima della rimozione annotare l'ultimo valore di `sensor.lettura_reale_contatore`: serve come offset del nuovo sensore.
