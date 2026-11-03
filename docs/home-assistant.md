# Home Assistant

## Configurazione attuale (dal 28/10/2026)

Entità create tramite **MQTT discovery**: le configurazioni sono messaggi `retain` pubblicati dal Pi su `homeassistant/sensor/contatore_acqua_433/*/config`. Dispositivo: **Contatore acqua**.

| Entità | Contenuto |
|---|---|
| `sensor.contatore_acqua_litri_totali` | Litri, `device_class: water`, `state_class: total_increasing`. Template sul topic `.../ContatoreAcquaV2/data`: controlla preambolo e checksum; se il frame non è valido mantiene il valore precedente. Oggi 1 L/impulso, come la catena vecchia |
| `sensor.contatore_acqua_batteria_valore_grezzo` | Byte batteria grezzo |
| `sensor.contatore_acqua_ultimo_segnale` | Ora dell'ultimo frame ricevuto |

- Plancia **consumi-acqua** riscritta sui sensori nuovi: stato, statistiche di oggi, settimana e mese, grafico di 7 giorni. Il pulsante di azzeramento non c'è più, perché il contatore è cumulativo.
- Il 28/10/2026 storico e statistiche di litri e batteria sono stati azzerati, per togliere i dati finti del firmware di test (contatore +1 ogni ~3,3 s). Vanno ripuliti di nuovo prima di installare il firmware vero.
- Le configurazioni di discovery **non sono ancora nel repo**: vanno esportate qui. La bozza [homeassistant/BOZZA_mqtt_contatore_acqua.yaml](../homeassistant/BOZZA_mqtt_contatore_acqua.yaml) leggeva `rtl_433/rpi3/events` ed è superata.

## Da fare

- Sensore della tensione batteria in volt (dipende dal blocco 5 del firmware).
- Allarme se manca il messaggio di vita oltre una soglia.
- Offset (lettura del contatore) e litri/impulso definitivi in base alla lancetta scelta.

## Configurazione storica (PB-68, in dismissione)

Rimosse il 28/10/2026: le automazioni **contatore acqua** e `contatore_acqua_test_notifica`, l'helper `counter.litri_acqua_totali` e `input_boolean.test_contatore_acqua`.

Restano nello YAML di HA, da togliere a mano: `binary_sensor.impulso_contatore_acqua` e `sensor.lettura_reale_contatore`. Riferimento: [homeassistant/legacy/README.md](../homeassistant/legacy/README.md).
