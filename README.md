# Soil Buddy RE – 3D Circuit Simulator (v2)
Single-file Three.js (r128, cdnjs) simulator: ESP32 WROOM on an expansion board, breadboard with TIP120 driver, 5 V mini pump in a 500 mL tank, HW-038 water sensor, resistive soil probe, and a separate ESP32-CAM (simulated). Laptop camera feed and a phone app.

**Run:** open `index.html`, or GitHub Settings > Pages > Deploy from branch `main` / root.

**Use:** drag to rotate, wheel to zoom, click a numbered marker or part for info. Use the arrows beside the pot (or Left/Right keys) to switch plant: sili, ampalaya, kangkong, pechay, tomato. All switches are in the Controls dropdown, including sliders for water in the tank (mL) and soil moisture (SMS) level. Works on phones (touch orbit, pinch zoom, full-screen app). Click the laptop for the camera feed (top 3 guesses with confidence). Click the hand to open the phone app: Bluetooth connect, camera Wi-Fi, then dashboard (water bucket in mL, soil gauge or pot), camera and terminal (`help`).

**Wiring (matches the firmware):** soil AO > GPIO35, HW-038 > GPIO34, GPIO26 > 330 ohm > TIP120 base, emitter > GND, collector > pump negative, pump positive > separate 5 V, common GND, flyback diode across the pump, 10k base pull-down. The ESP32-CAM is a separate module (AI-Thinker ESP32-CAM does not expose GPIO34/35).

**Firmware note:** the simulator follows Soil Buddy RE v3.0 (AUTO off at boot, `pump auto` to enable, 30 s pump test that bypasses the water guard). Replace the .ino in `firmware/` with your v3.0 file and set `SOIL_START_INDEX = 50.0f` and `SOIL_STOP_INDEX = 65.0f` (the simulator uses 50 / 65 for all five plants).

**Honest notes:** soil moisture is hidden and the app gets a noisy reading; plant detection is simulated; watering thresholds are pilot values; water ml is an estimate. Firmware: `firmware/Soil_Buddy_RE_v2_3_ESP32_TIP120/`.
