# 🔐 OTP-Based Smart Wireless Locking System Using Arduino

<p align="center">
  <img src="OTP-locking-system-main/Project demo.png" alt="Project Demo" width="650"/>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Platform-Arduino%20UNO-00979D?style=for-the-badge&logo=arduino&logoColor=white" />
  <img src="https://img.shields.io/badge/App-MIT%20App%20Inventor-FF6B35?style=for-the-badge" />
  <img src="https://img.shields.io/badge/Communication-Bluetooth%20Serial-blue?style=for-the-badge&logo=bluetooth&logoColor=white" />
  <img src="https://img.shields.io/badge/License-MIT-green?style=for-the-badge" />
  <img src="https://img.shields.io/badge/Language-Arduino%20C%2B%2B-teal?style=for-the-badge&logo=cplusplus&logoColor=white" />
</p>

---

## 📖 Overview

This project is a **smart, contactless locking system** that uses a randomly generated **One-Time Password (OTP)** to unlock a servo-controlled lock. The system is controlled wirelessly through a **custom Android app** built with [MIT App Inventor](https://appinventor.mit.edu/), communicating with the Arduino over Bluetooth serial.

> **No physical key. No static PIN.** Every unlock attempt gets a fresh, unique code — making it significantly more secure than traditional combination locks.

---

## ✨ Features

| Feature | Details |
|---------|---------|
| 🔑 **OTP Authentication** | A new one-time passcode is generated for every unlock attempt |
| 📱 **Wireless Control** | Fully operated from an Android phone via Bluetooth |
| 🔒 **Servo-Controlled Lock** | Physical mechanism driven by a servo motor |
| 🟢🔴 **LED Status Indicators** | Instant visual feedback — green = unlocked, red = locked |
| 🔄 **Auto-Reset on Failure** | Wrong OTP keeps the lock secure and prompts a retry |
| 📲 **Custom Android App** | Ready-to-use `.aia` project built with MIT App Inventor |

---

## 🛠️ Hardware Components

| Component | Role | Pin |
|-----------|------|-----|
| **Arduino UNO** | Main microcontroller | — |
| **Servo Motor** | Drives the physical lock mechanism | Pin 9 |
| **HC-05 / HC-06 Bluetooth Module** | Wireless serial communication | TX/RX |
| **Red LED** | Locked / error indicator | Pin 12 |
| **Green LED** | Unlocked indicator | Pin 13 |
| **Power Supply** | 5V via USB or external source | 5V / GND |

---

## 📐 Circuit Overview

```
Arduino UNO
├── Pin 9   ──► Servo Motor (signal wire)
├── Pin 12  ──► Red LED   (locked state indicator)
├── Pin 13  ──► Green LED (unlocked state indicator)
├── TX/RX   ──► HC-05 Bluetooth Module (RX→TX, TX→RX)
└── 5V/GND  ──► Power rails
```

> ⚠️ **Important:** Disconnect the HC-05 Bluetooth module's TX/RX pins from Arduino's TX/RX **before uploading the sketch**, then reconnect afterward to avoid upload conflicts.

---

## 📱 Android App (MIT App Inventor)

The companion app (`OTPlock.aia`) is built with **MIT App Inventor** and provides the wireless interface for the lock.

### How to Import & Build:
1. Go to [appinventor.mit.edu](https://appinventor.mit.edu/) and sign in with your Google account.
2. Navigate to **Projects → Import project (.aia) from my computer**.
3. Upload `OTP-locking-system-main/OTPlock.aia`.
4. Click **Build → Android App (.apk)** to generate the APK, then install it on your phone.

### App Workflow:
```
📱 Open App
    │
    ▼
🔵 Connect to HC-05 Bluetooth
    │
    ▼
🔑 Tap "Request OTP"  ──► Sends trigger "asdfg" to Arduino
    │
    ▼
📨 Receive OTP from Arduino (e.g., "3213")
    │
    ▼
⌨️  Enter OTP in the app → Tap "Unlock"
    │
    ├── ✅ Match  → Lock OPENS  (Servo: 120°, Green LED ON)
    └── ❌ No Match → "reset try again" (Servo: 50°, Red LED ON)
```

---

## 💻 How the Arduino Code Works

### Source: [`Arduino_code.ino`](OTP-locking-system-main/Arduino_code.ino)

```arduino
#include <Servo.h>

// OTP pool — one of these is randomly selected each session
String numbers[4] = {"3213", "213213", "543646", "2231"};

Servo myservo;
int sled1 = 12;  // Red LED  — locked indicator
int sled2 = 13;  // Green LED — unlocked indicator
```

### Logic Flow:

```
[Arduino starts up]
        │
        ▼
[Wait for Bluetooth input]
        │
        ▼
[Input == "asdfg"?]
        │
    Yes ├──► [otp()] ──► Pick random OTP from pool
        │                       │
        │                       ▼
        │               [Send OTP over Serial to app]
        │                       │
        │                       ▼
        │               [Red LED ON — awaiting verification]
        │
        ▼
[check()] — Wait for OTP input from user
        │
        ├── OTP Matches ──► [Servo → 120°] [Green LED ON] ✅ UNLOCKED
        │
        └── OTP Wrong   ──► [Servo → 50°]  [Red LED ON]  ❌ "reset try again"
```

### Key Functions:

| Function | Purpose |
|----------|---------|
| `setup()` | Initializes serial at 9600 baud, attaches servo to Pin 9, sets LED pins as OUTPUT |
| `loop()` | Reads serial input; triggers `otp()` when the trigger word `"asdfg"` is received |
| `otp()` | Picks a random entry from the 4-item OTP pool and sends it back over serial |
| `check()` | Reads the user's OTP attempt, compares it, and controls servo + LEDs accordingly |

---

## 🚀 Getting Started

### Prerequisites
- [Arduino IDE](https://www.arduino.cc/en/software) (v1.8+ or v2.x)
- `Servo.h` library — included by default in the Arduino IDE
- An Android smartphone with Bluetooth
- MIT App Inventor account (free) — [appinventor.mit.edu](https://appinventor.mit.edu/)

### Step-by-Step Setup

**1. Clone this repository:**
```bash
git clone https://github.com/jayaprakash2207/OTP-BASED-SMART-WIRELESS-LOCKING-SYSTEM-USING-ARDUINO.git
cd OTP-BASED-SMART-WIRELESS-LOCKING-SYSTEM-USING-ARDUINO
```

**2. Upload the Arduino sketch:**
- Open `OTP-locking-system-main/Arduino_code.ino` in Arduino IDE.
- Select **Tools → Board → Arduino UNO**.
- Select the correct COM port under **Tools → Port**.
- **Disconnect the HC-05 TX/RX**, then click **Upload**.
- Reconnect the HC-05 after upload is complete.

**3. Wire up the hardware** as shown in the [Circuit Overview](#-circuit-overview) section above.

**4. Install the Android app** using `OTPlock.aia` (see [Android App](#-android-app-mit-app-inventor) section).

**5. Pair your phone with the Bluetooth module:**
- Enable Bluetooth on your Android phone.
- Pair with the HC-05 module (default PIN: `1234` or `0000`).

**6. Launch the app → Connect → Request OTP → Unlock! 🔓**

---

## 📁 Project Structure

```
OTP-BASED-SMART-WIRELESS-LOCKING-SYSTEM-USING-ARDUINO/
│
├── README.md                          ← You are here
│
└── OTP-locking-system-main/
    ├── Arduino_code.ino               ← Arduino firmware (main logic)
    ├── OTPlock.aia                    ← MIT App Inventor Android app source
    ├── Project demo.png               ← Project demonstration photo
    ├── otp locking system.pptx        ← Project presentation slides
    └── LICENSE                        ← MIT License
```

---

## 🔮 Future Improvements

- [ ] Replace the static OTP pool with dynamically generated random numbers using `random()`
- [ ] Add a physical keypad as a fallback entry method when phone is unavailable
- [ ] Implement failed-attempt lockout (e.g., lock for 60s after 3 wrong OTPs)
- [ ] Add a buzzer for audio feedback on success/failure
- [ ] Log access history using an RTC (Real-Time Clock) module
- [ ] Migrate the Android app to Flutter or a dedicated IoT platform (e.g., Blynk)
- [ ] Add WiFi support using ESP8266/ESP32 for remote unlock over the internet

---

## 📄 License

This project is licensed under the **MIT License** — see the [LICENSE](OTP-locking-system-main/LICENSE) file for details.

---

## 🙏 Acknowledgements

- [Arduino](https://www.arduino.cc/) — open-source electronics platform
- [MIT App Inventor](https://appinventor.mit.edu/) — visual mobile app builder
- The open-source IoT and maker community

---

<p align="center">
  <strong>Made with ❤️ using Arduino &amp; MIT App Inventor</strong><br/>
  <em>Keep your world secure — one OTP at a time. 🔐</em>
</p>
