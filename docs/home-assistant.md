# Home Assistant

## Configurazione attuale (vecchio PB-68, da dismettere)

- `binary_sensor.impulso_contatore_acqua` — sensore MQTT in YAML su `rtl_433/rpi3/events`. Riconosce solo `{25}<codice ON>` = ON e `{25}<codice OFF>` = OFF.
- Automazione **contatore acqua**: +1 su `counter.litri_acqua_totali` a ogni OFF→ON.
- `sensor.lettura_reale_contatore` (template).
- Automazione `contatore_acqua_test_notifica`: Telegram a ogni impulso se `input_boolean.test_contatore_acqua` è attivo.

Con il conteggio cumulativo queste entità diventano inutili. Riferimento: [homeassistant/legacy/README.md](../homeassistant/legacy/README.md).

## Configurazione nuova (da scrivere quando il frame è definitivo)

- Sensore MQTT che legge il frame da `rtl_433/rpi3/events`, verifica preambolo, ID e checksum, ed estrae il conteggio.
- Litri = `conteggio × risoluzione + offset`; offset in un `input_number`, `state_class: total_increasing`.
- Sensore separato per la tensione della batteria.
- Allarme se manca il messaggio di vita oltre una soglia.

Bozza non testata: [homeassistant/BOZZA_mqtt_contatore_acqua.yaml](../homeassistant/BOZZA_mqtt_contatore_acqua.yaml).
