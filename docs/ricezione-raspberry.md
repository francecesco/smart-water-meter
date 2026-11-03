# Ricezione su Raspberry Pi

## Host (verificato il 23/10/2026)

| Voce | Valore |
|---|---|
| Hardware | Raspberry Pi **1 Model B+** (512 MB, 1 core ARMv6) — non è un Pi 3 |
| Hostname | `rpi3` (nome dato in Imager) |
| IP | `<ip-raspberry>` (rete locale) |
| SDR | RTL-SDR Blog V4 (tuner R828D) |
| Broker MQTT | Home Assistant, `<ip-home-assistant>:1883` |
| Decoder | `ContatoreAcquaV2` (dal 28/10/2026) |
| Carico CPU | ~38% con `-s 1024k` |

`rtl433.service` lancia `rtl_433` direttamente (non esiste uno script wrapper). Copia di riferimento: [raspberry/rtl433.service](../raspberry/rtl433.service). Decoder: [raspberry/decoder/contatore_acqua.conf](../raspberry/decoder/contatore_acqua.conf).

## Topic MQTT

Con il decoder V2 i campi escono separati, con `retain`:

| Topic | Contenuto |
|---|---|
| `rtl_433/rpi3/devices/ContatoreAcquaV2/impulsi` | Conteggio cumulativo (uint32) |
| `rtl_433/rpi3/devices/ContatoreAcquaV2/batteria_raw` | Byte batteria grezzo |
| `rtl_433/rpi3/devices/ContatoreAcquaV2/checksum` | Byte di checksum |
| `rtl_433/rpi3/devices/ContatoreAcquaV2/data` | Frame completo (usato da HA per verificare preambolo e checksum) |
| `rtl_433/rpi3/events` | Eventi grezzi |

## Comandi utili

```bash
# stato e log del servizio
systemctl status rtl433
journalctl -u rtl433 -f

# liberare la SDR per una prova manuale
sudo systemctl stop rtl433

# analisi del segnale grezzo (tempi impulsi, numero bit)
timeout 60 rtl_433 -A -f 433.92M -s 1024k

# ripristinare il servizio
sudo systemctl start rtl433

# gli eventi decodificati NON compaiono nel journal: vanno letti sul broker
mosquitto_sub -h <ip-home-assistant> -u <utente> -P <password> -t 'rtl_433/rpi3/devices/ContatoreAcquaV2/#' -v

# sottotensione del Pi (0x0 = nessun problema)
vcgencmd get_throttled
```

## Note operative

- **Controllo di salute**: un timer di sistema alle 08:00 e alle 20:00 verifica che `rtl433` sia attivo e che un messaggio di prova faccia andata e ritorno sul broker; l'esito va su un monitor *push* di Uptime Kuma, che avvisa su Telegram. Se il servizio viene fermato per una prova, il controllo successivo segnala il guasto: ricordarsi di riavviarlo.
- **Sottotensione (25/10/2026)**: `get_throttled` = `0x50005`. La RTL-SDR V4 si scollegava di continuo (`error -71`) fino a sparire. Dopo un riavvio è tornata, ma la sottotensione resta: serve un alimentatore 5 V 2,5 A buono con cavo corto, oppure un hub USB alimentato per la chiavetta.
- Il vecchio decoder del PB-68 generava falsi eventi ogni ~10 s (codici di 1–3 bit). È stato rimosso il 28/10/2026; il V2 filtra con `bits=64`, `match` e `repeats>=2`.
- La SDR può essere usata da un solo processo alla volta.
- Portata: dallo studio il segnale non arriva; in garage, vicino al Pi, sì. Al contatore (antenna libera, tensione piena di batteria) va verificata sul posto.

## Modifiche previste

- Passare da `-s 1024k` a `-s 250k` per alleggerire il Pi 1.
- Risolvere la sottotensione del Pi.
