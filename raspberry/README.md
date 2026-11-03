# Raspberry Pi — ricezione

Documentazione completa: [docs/ricezione-raspberry.md](../docs/ricezione-raspberry.md).

| File | Contenuto |
|---|---|
| `rtl433.service` | Copia di riferimento dell'unità systemd, con credenziali spostate in un file d'ambiente |
| `rtl433.env.example` | Modello del file `/etc/rtl433.env` (il file reale non va nel repo) |
| `decoder/contatore_acqua.conf` | Decoder flex `ContatoreAcquaV2` per il frame a 64 bit (validato e installato) |

## Installare l'unità di riferimento

```bash
which rtl_433                      # verifica il percorso e correggi ExecStart se diverso
sudo cp rtl433.env.example /etc/rtl433.env
sudo nano /etc/rtl433.env          # inserisci le credenziali reali
sudo chmod 600 /etc/rtl433.env
sudo cp rtl433.service /etc/systemd/system/rtl433.service
sudo systemctl daemon-reload
sudo systemctl restart rtl433
journalctl -u rtl433 -f
```

L'unità attualmente installata sul Pi ha le credenziali scritte nel comando: questa versione le sposta in `/etc/rtl433.env`. Coordinarsi con chi gestisce il Pi prima di sostituirla.
