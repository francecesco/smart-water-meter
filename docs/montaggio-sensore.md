# Montaggio del sensore

## Regole
- Il sensore deve essere **solidale al contatore**: uno spostamento di 2–3 mm lo rende cieco.
- **Prima calibrare, poi fissare**: con il Plotter seriale trovare posizione, distanza e inclinazione con il picco più netto, segnare il punto, fissare e ricontrollare con l'acqua aperta.
- Un'inclinazione di pochi gradi evita il riflesso speculare del LED sul vetro.
- Scarico della trazione sui fili a qualche cm dal sensore.
- Il contatore è del gestore: il fissaggio deve essere **reversibile**.

## Soluzione prevista: supporto stampato in 3D
- Stampante disponibile tramite un amico.
- Prima cercare modelli pronti (Printables/Thingiverse: "water meter TCRT5000 mount").
- In alternativa script **OpenSCAD parametrico** in [hardware/supporto-3d/](../hardware/supporto-3d/).

## Misure da prendere al contatore
- Diametro esterno della ghiera
- Distanza della lancetta dal centro del quadrante
- Distanza sensore–vetro con il segnale migliore
- Inclinazione ottimale
- Presenza e leggibilità di una lancetta ×0,001 (1 L/giro, 10 volte più lenta)
