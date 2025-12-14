# Smart Locker System Setup Guide

## Prerequisites

### Hardware Requirements
- ESP32 Development Board
- Servo Motor (SG90 or similar)
- RFID Module (RC522)
- Fingerprint Sensor (GT-511C3 or similar)
- 4x4 Matrix Keypad
- 3x LEDs (Red, Green, Blue)
- Buzzer
- Jumper Wires
- Breadboard
- Power Supply (5V recommended)

### Software Requirements
- PlatformIO IDE (or VS Code with PlatformIO extension)
- Python 3.8+
- Git

## Installation Steps

### 1. Clone the Repository
```bash
git clone <repository-url>
cd smart-locker-system
```

### 2. ESP32 Setup

#### Install PlatformIO
1. Install VS Code
2. Install PlatformIO IDE extension
3. Restart VS Code

#### Configure WiFi Settings
Edit `esp32-platformio/platformio.ini`:
```ini
-DWIFI_SSID=\"YOUR_WIFI_SSID\"
-DWIFI_PASSWORD=\"YOUR_WIFI_PASSWORD\"
-DSERVER_IP=\"YOUR_SERVER_IP\"
```

#### Build and Upload
```bash
cd esp32-platformio
pio run
pio run --target upload
```

### 3. Python Server Setup

#### Create Virtual Environment
```bash
cd flask-server
python -m venv venv
source venv/bin/activate  # On Windows: venv\Scripts\activate
```

#### Install Dependencies
```bash
pip install -r requirements.txt
```

#### Run the Server
```bash
python run.py
```

### 4. Database Initialization
The system will automatically create the database and default admin user on first run:
- Username: `admin`
- Password: `admin123`

## Configuration

### ESP32 Configuration
All ESP32 settings are defined in `esp32-platformio/include/config.h`:
- Pin assignments
- Timing parameters
- Security settings
- WiFi credentials

### Server Configuration
Server settings are in `flask-server/config.py`:
- Database settings
- Security settings
- API credentials

## Testing the System

### 1. Check ESP32 Connection
- Verify ESP32 connects to WiFi
- Check serial monitor for IP address
- Verify connection to server

### 2. Test Access Methods
- Fingerprint: Place finger on sensor
- RFID: Scan RFID card/tag
- Keypad: Enter master password (default: 1234#)

### 3. Verify Server Logs
- Access the web interface
- Check access logs
- Verify user management

## Troubleshooting

### Common Issues

#### ESP32 Won't Connect to WiFi
- Verify credentials in `platformio.ini`
- Ensure 2.4GHz network
- Check router settings

#### Components Not Responding
- Check wiring diagram
- Verify power supply
- Test components individually

#### Server Not Receiving Data
- Verify IP address configuration
- Check firewall settings
- Ensure both devices on same network

### Serial Debugging
```bash
pio device monitor
```

## Security Considerations

### Default Passwords
- Change default passwords immediately
- Use strong passwords
- Enable HTTPS in production

### Network Security
- Use WPA2/WPA3 WiFi
- Consider dedicated network
- Regular firmware updates

## Maintenance

### Regular Tasks
- Update access logs
- Review user access
- Check component functionality
- Backup database regularly

### Database Backup
```bash
python scripts/backup_database.py
```

## Next Steps

1. Customize user interface
2. Add more security features
3. Implement remote monitoring
4. Add mobile app integration