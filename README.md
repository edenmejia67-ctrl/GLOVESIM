# Sign Language Glove - 3D Circuit Simulator
Single-file Three.js (r128, cdnjs) simulator. Open `index.html`, or publish on GitHub Pages (Settings > Pages > main, root).

## Controls
Drag = rotate, wheel = zoom, click a part = info card. Sliders or presets bend the fingers. Switch between **Original** and **Fixed** code. Fault tests: loose A2 wire, stuck A1 sensor, LCD address 0x27, low 9V battery.

## Wiring
| Part | Nano pin |
|---|---|
| Flex 1 thumb + 10k to GND | A0 |
| Flex 2 index + 10k to GND | A1 |
| Flex 3 middle + 10k to GND | A2 |
| Flex 4 ring + 10k to GND | A3 |
| Flex other tail | 5V |
| LCD SDA / SCL | A4 / A5 |
| LCD VCC / GND | 5V / GND |
| VC-02 RX | D3 via 1k (D3 side) + 2k to GND divider |
| VC-02 VCC / GND | per your board (5V or 3.3V), common GND |
| Speaker | VC-02 speaker pins only |
| 9V battery | VIN / GND |

ADC = 1023 x 10k / (Rflex + 10k). Flat is about 290, bent 90 degrees is about 90.

## Original code issues
1. `delay(2000)` blocks all sensing; a fist plays 3 words one after another over 8 seconds.
2. Only the last `if` has an `else`, so NOTHING is written after the delays.
3. LCD address 0x3F may be 0x27 on your backpack (fixed code scans).
4. 9V sags under load. Prefer 2 x 18650 or 4 x AA.
5. The original has no audio code.

## VC-02 note
Not verified for your exact board. The sketch sends one byte `'1'`-`'4'` at 9600 baud; set the module's UART commands and phrases on the vendor platform to match, or change `vc.write()`.
