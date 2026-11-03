# Ricezione su Raspberry Pi

## Host (verificato il 23/10/2026)

| Voce | Valore |
|---|---|
| Hardware | Raspberry Pi **1 Model B+** (512 MB, 1 core ARMv6) — non è un Pi 3 |
| Hostname | `rpi3` (nome dato in Imager) |
| IP | `<ip-raspberry>` (rete locale) |
| SDR | RTL-SDR Blog V4 (tuner R828D) |
| Broker MQTT | Home Assistant, `<ip-home-assistant>:1883` |
| Topic | `rtl_433/rpi3/events` |
| Carico CPU | ~38% con `-s 1024k` |

`rtl433.service` lancia `rtl_433` direttamente (non esiste uno script wrapper). Copia di riferimento: [raspberry/rtl433.service](../raspberry/rtl433.service).

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
mosquitto_sub -h <ip-home-assistant> -u <utente> -P <password> -t 'rtl_433/rpi3/events' -v
```

## Note operative

- Il decoder `-X` storico (`s=430,l=1150,r=11000`, del vecchio PB-68) genera **falsi eventi ogni ~10 s** con codici di 1–3 bit: è rumore. Il nuovo decoder filtra con `bits=64` e `repeats>=2`.
- Controllo automatico alle 08:00 e 20:00 (servizio attivo + broker raggiungibile) con avvisi via Uptime Kuma / Telegram.
- La SDR può essere usata da un solo processo alla volta.
- Portata: dallo studio il segnale non arriva; in garage, vicino al Pi, sì. Al contatore (antenna libera, tensione piena di batteria) va verificata sul posto.

## Modifiche previste

- Nuovo decoder per il frame a 64 bit: bozza in [raspberry/decoder/contatore_acqua.conf](../raspberry/decoder/contatore_acqua.conf), tempi da confermare con `rtl_433 -A`.
- Passare da `-s 1024k` a `-s 250k` per alleggerire il Pi 1.
