# 🔐 OTP-Based Smart Wireless Locking System Using Arduino

<p align="center">
  <img src="Project demo.png" alt="Project Demo" width="600"/>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Platform-Arduino%20UNO-00979D?style=for-the-badge&logo=arduino&logoColor=white" />
  <img src="https://img.shields.io/badge/App-MIT%20App%20Inventor-FF6B35?style=for-the-badge" />
  <img src="https://img.shields.io/badge/Communication-Bluetooth%20Serial-blue?style=for-the-badge" />
  <img src="https://img.shields.io/badge/License-MIT-green?style=for-the-badge" />
</p>

---

## 📖 Overview

This project is a **smart, contactless locking system** that uses a randomly generated **One-Time Password (OTP)** to unlock a servo-controlled lock. The entire system is controlled wirelessly through a **custom Android app** built with [MIT App Inventor](https://appinventor.mit.edu/), communicating with the Arduino over Bluetooth serial.

No physical key. No static PIN. Every unlock attempt gets a fresh, one-time code — making it significantly harder to compromise than traditional locks.

---

## ✨ Features

- 🔑 **OTP-based authentication** — a new passcode is generated for every unlock attempt
- 📱 **Wireless control** — operated entirely from an Android smartphone via Bluetooth
- 🔒 **Servo-controlled lock** — physical lock mechanism driven by a servo motor
- 🟢🔴 **Dual LED status indicators** — instant visual feedback for locked/unlocked state
- 🔄 **Auto-reset on failure** — wrong OTP keeps the lock secure and prompts a retry
- 📲 **Custom Android app** — ready-to-use `.aia` app built with MIT App Inventor

---

## 🛠️ Hardware Components

| Component | Description |
|-----------|-------------|
| **Arduino UNO** | Main microcontroller |
| **Servo Motor** | Drives the physical lock mechanism |
| **HC-05 / HC-06 Bluetooth Module** | Wireless serial communication |
| **LED (Green)** | Indicates unlocked state (Pin 13) |
| **LED (Red)** | Indicates locked / error state (Pin 12) |
| **Power Supply** | 5V via USB or external source |

---

## 📐 Circuit Overview

```
Arduino UNO
├── Pin 9   ──► Servo Motor (signal wire)
├── Pin 12  ──► Red LED (locked indicator)
├── Pin 13  ──► Green LED (unlocked indicator)
├── TX/RX   ──► HC-05 Bluetooth Module
└── 5V/GND  ──► Power rails
```

> ⚠️ **Note:** Disconnect the Bluetooth module's TX/RX from Arduino's TX/RX pins while uploading the sketch, then reconnect.

---

## 📱 Android App (MIT App Inventor)

The companion app (`OTPlock.aia`) is built with **MIT App Inventor**.

### How to install:
1. Open [MIT App Inventor](https://appinventor.mit.edu/) and sign in.
2. Go to **Projects → Import project (.aia) from my computer**.
3. Upload the `OTPlock.aia` file.
4. Build and install the APK on your Android device.

### App Workflow:
1. Connect to the Arduino's Bluetooth module from the app.
2. Tap **"Request OTP"** — the app sends the trigger code (`asdfg`) to the Arduino.
3. The Arduino generates a random OTP and sends it back to the app.
4. Enter the received OTP in the app and tap **"Unlock"**.
5. If the OTP matches, the lock opens! ✅

---

## 💻 How the Arduino Code Works

```arduino
// Predefined OTP pool — a random one is chosen per session
String numbers[4] = {"3213", "213213", "543646", "2231"};
```

### Flow:

```
[Wait for Serial input]
        │
        ▼
[Received "asdfg"?] ──Yes──► [Generate random OTP]
        │                           │
        No                     [Send OTP to app]
        │                           │
        ▼                           ▼
  [Check OTP]         [Wait for user to enter OTP]
        │
        ├── Match ──► [Rotate Servo to 120°] + [Green LED ON] ✅
        │
        └── No Match ─► [Servo stays at 50°] + [Red LED ON] ❌
                         [Send "reset try again"]
```

### Key Functions:

| Function | Purpose |
|----------|---------|
| `setup()` | Initializes serial (9600 baud), servo, and LED pins |
| `loop()` | Waits for the trigger word `asdfg` from the app |
| `otp()` | Picks a random OTP from the pool and sends it over Serial |
| `check()` | Validates user-entered OTP and controls the servo and LEDs |

---

## 🚀 Getting Started

### Prerequisites
- [Arduino IDE](https://www.arduino.cc/en/software) installed
- `Servo.h` library (included by default in Arduino IDE)
- An Android device with Bluetooth

### Steps

1. **Clone this repository:**
   ```bash
   git clone <repository-url>
   ```

2. **Open the sketch:**
   - Launch Arduino IDE and open `Arduino_code.ino`.

3. **Upload the code:**
   - Select **Board: Arduino UNO** and the correct COM port.
   - Upload the sketch.

4. **Wire up the hardware** as described in the [Circuit Overview](#-circuit-overview) section.

5. **Install the Android app** from `OTPlock.aia` (see [Android App](#-android-app-mit-app-inventor)).

6. **Pair your phone** with the HC-05 Bluetooth module (default PIN: `1234` or `0000`).

7. **Launch the app**, connect to the module, and start using your smart lock! 🔓

---

## 📁 Project Structure

```
OTP-locking-system-main/
├── Arduino_code.ino      # Arduino sketch (main firmware)
├── OTPlock.aia           # MIT App Inventor source for the Android app
├── Project demo.png      # Project demonstration image
├── otp locking system.pptx   # Project presentation slides
├── LICENSE               # MIT License
└── README.md             # This file
```

---

## 🔮 Future Improvements

- [ ] Replace static OTP pool with dynamically generated random numbers
- [ ] Add a keypad as a fallback input method
- [ ] Implement failed attempt lockout (e.g., lock after 3 wrong attempts)
- [ ] Add buzzer for audio feedback
- [ ] Log access history with a real-time clock (RTC) module
- [ ] Migrate app to Flutter or a dedicated IoT platform

---

## 📄 License

This project is licensed under the **MIT License** — see the [LICENSE](LICENSE) file for details.

---

## 🙏 Acknowledgements

- [Arduino](https://www.arduino.cc/) — open-source electronics platform
- [MIT App Inventor](https://appinventor.mit.edu/) — visual mobile app development
- All contributors and supporters of open-source IoT projects

---

<p align="center">Made with ❤️ using Arduino &amp; MIT App Inventor</p>
