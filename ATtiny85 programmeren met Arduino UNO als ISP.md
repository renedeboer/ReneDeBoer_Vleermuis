# ATtiny85 programmeren met Arduino UNO als ISP

Deze handleiding beschrijft hoe je een **ATtiny85** kunt programmeren met behulp van een **Arduino UNO** als ISP-programmer.

---

## 📦 Benodigdheden
- Arduino UNO
- ATtiny85 (DIP‑8)
- Breadboard
- Jumper wires
- (Optioneel) 10 µF condensator (tussen RESET en GND van de UNO)

---

## 🔌 Pin‑aansluitingen

| Arduino UNO | ATtiny85‑pin (DIP‑8) | Functie       |
|-------------|---------------------|---------------|
| **5 V**     | **pin 8**            | VCC (voeding) |
| **GND**     | **pin 4**            | GND           |
| **D10**     | **pin 1**            | RESET         |
| **D11**     | **pin 5**            | MOSI (PB0)    |
| **D12**     | **pin 6**            | MISO (PB1)    |
| **D13**     | **pin 7**            | SCK (PB2)     |

> 💡 **Tip:** de inkeping of stip op de ATtiny‑behuizing markeert **pin 1** (RESET).  
> Plaats een **10 µF condensator** tussen **RESET en GND** van de UNO (pluszijde bij RESET) om auto‑reset tijdens programmeren te voorkomen.

---

## 🖼️ ASCII‑schema breadboard

```
       ATtiny85 (bovenaan inkeping ▷ pin 1)

          ┌───┬───┐
   RESET ◁│1      8│▷ VCC  → UNO 5 V
  (D10)    │       │
   GND  ←▷│4      5│▷ MOSI → UNO D11
           │       │
   SCK  →▷│7      6│▷ MISO → UNO D12
           └───┴───┘
             ▲
             |
           UNO GND → pin 4 (GND)
           UNO D13 → pin 7 (SCK)
           UNO D10 → pin 1 (RESET)

Extra: 10 µF condensator tussen UNO‑RESET en GND
```

---

## 🖼️ SVG‑schema breadboard

 
<svg width="420" height="220" xmlns="http://www.w3.org/2000/svg">
  <rect x="160" y="40" width="100" height="140" rx="10" ry="10" fill="#eee" stroke="#333" stroke-width="2"/>
  <text x="170" y="55" font-size="12" font-family="monospace">ATtiny85</text>
  
  <!-- Pins -->
  <circle cx="160" cy="60" r="4" fill="black"/> <!-- Pin1 -->
  <text x="120" y="63" font-size="12">RESET (D10)</text>

  <circle cx="160" cy="90" r="4" fill="black"/> <!-- Pin4 -->
  <text x="120" y="93" font-size="12">GND</text>

  <circle cx="160" cy="120" r="4" fill="black"/> <!-- Pin7 -->
  <text x="120" y="123" font-size="12">SCK (D13)</text>

  <circle cx="160" cy="150" r="4" fill="black"/> <!-- Pin8 -->
  <text x="120" y="153" font-size="12">VCC (5V)</text>

  <circle cx="260" cy="90" r="4" fill="black"/> <!-- Pin5 -->
  <text x="270" y="93" font-size="12">MOSI (D11)</text>

  <circle cx="260" cy="120" r="4" fill="black"/> <!-- Pin6 -->
  <text x="270" y="123" font-size="12">MISO (D12)</text>
</svg>
 

---

## ⚙️ Arduino UNO voorbereiden
1. Sluit de UNO via USB aan op je computer.  
2. Open de Arduino IDE.  
3. Ga naar **Bestand → Voorbeelden → 11.ArduinoISP → ArduinoISP**.  
4. Upload deze sketch naar de UNO.  
   De UNO werkt nu als programmer.

---

## 🛠️ ATtiny‑ondersteuning installeren (eenmalig)
1. Open **Bestand → Voorkeuren → Extra Board‑beheer‑URL’s**.  
2. Voeg deze URL toe:  
   ```
   https://drazzy.com/package_drazzy.com_index.json
   ```
> ➜ Dit is van **Spence Konde / Drazzy** en bevat de **“ATTinyCore”**:  
> Ondersteunt **ATtiny85**, **ATtiny45**, **ATtiny25** en ook de nieuwere **ATtiny-chips (0/1-serie)**.  
> ➜ **Aanbevolen** voor **ATtiny85-projecten**; werkt goed in **Arduino IDE 1.x** en **2.x**.
3. Ga naar **Hulpmiddelen → Board → Board‑beheerder**, zoek **attiny** en installeer.

---

## 🔧 Instellingen in de IDE
- **Board:** `ATtiny25/45/85`  
- **Processor:** `ATtiny85`  
- **Clock:** `8 MHz (Internal)`  
- **Programmer:** `Arduino as ISP`  

⚠️ Klik daarna op **Hulpmiddelen → Bootloader branden**  
Dit brandt geen bootloader, maar zet de **fuses** zodat de ATtiny85 echt op 8 MHz draait  
(standaard staat CKDIV8 aan en loopt hij op 1 MHz).

---

## 🚀 Sketch uploaden
1. Schrijf of open je Arduino‑code.  
2. Kies **Sketch → Uploaden met programmer** (of **Ctrl + Shift + U**).  
3. De code wordt nu direct naar de ATtiny85 geladen via de UNO‑ISP.

---

## 💡 Tips
- Bij uploadfouten: controleer bedrading en plaats de 10 µF condensator tussen RESET en GND van de UNO.  
- Als je `delay()` of `millis()` gebruikt: zorg dat de gekozen klokinstelling overeenkomt met de gebrande fuses, anders loopt de timing niet juist.

---

© 2025 René de Boer – Handleiding uitsluitend voor hobbygebruik
