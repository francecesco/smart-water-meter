# Configurazione storica (PB-68)

| Entità | Ruolo | Stato |
|---|---|---|
| `binary_sensor.impulso_contatore_acqua` | Sensore MQTT su `rtl_433/rpi3/events`; `{25}<codice ON>` = ON, `{25}<codice OFF>` = OFF | ⏳ da togliere dallo YAML |
| Automazione "contatore acqua" | +1 su `counter.litri_acqua_totali` a ogni OFF→ON | ✅ rimossa il 28/10/2026 |
| `counter.litri_acqua_totali` | Totale litri (incrementale) | ✅ rimosso il 28/10/2026 |
| `sensor.lettura_reale_contatore` | Template | ⏳ da togliere dallo YAML |
| Automazione `contatore_acqua_test_notifica` | Telegram a ogni impulso se `input_boolean.test_contatore_acqua` è attivo | ✅ rimossa il 28/10/2026 (con l'`input_boolean`) |

Il decoder del PB-68 non è più in `rtl433.service` dal 28/10/2026, quindi le due entità rimaste non ricevono più dati.
