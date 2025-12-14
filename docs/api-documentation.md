# Smart Locker System API Documentation

## Overview

The Smart Locker System API provides endpoints for communication between the ESP32 device and the Flask web server. The API uses HTTP Basic Authentication for security.

## Authentication

All API endpoints require HTTP Basic Authentication with the credentials configured in the server configuration.

Default credentials:
- Username: `admin`
- Password: `smartlock2025`

## API Endpoints

### Door Control

#### Lock Door
- **URL**: `/api/lock`
- **Method**: `POST`
- **Description**: Remotely lock the door
- **Authentication**: Required
- **Response**:
  ```json
  {
    "status": "locked"
  }
  ```

#### Unlock Door
- **URL**: `/api/unlock`
- **Method**: `POST`
- **Description**: Remotely unlock the door
- **Authentication**: Required
- **Response**:
  ```json
  {
    "status": "unlocked"
  }
  ```

### Access Logging

#### Log Access Attempt
- **URL**: `/api/access-log`
- **Method**: `POST`
- **Description**: Log an access attempt from the ESP32
- **Authentication**: Required
- **Request Body**:
  ```json
  {
    "method": "fingerprint|RFID|keypad",
    "user": "user_identifier",
    "success": true|false
  }
  ```
- **Response**:
  ```json
  {
    "status": "logged",
    "id": 123
  }
  ```

### Validation Endpoints

#### Validate RFID
- **URL**: `/api/validate-rfid/<uid>`
- **Method**: `GET`
- **Description**: Check if an RFID card is registered and active
- **Authentication**: Required
- **Response**:
  ```json
  {
    "valid": true,
    "user_id": 1,
    "username": "user1"
  }
  ```
  or
  ```json
  {
    "valid": false
  }
  ```

#### Validate Fingerprint
- **URL**: `/api/validate-fingerprint/<finger_id>`
- **Method**: `GET`
- **Description**: Check if a fingerprint is registered and active
- **Authentication**: Required
- **Response**:
  ```json
  {
    "valid": true,
    "user_id": 1,
    "username": "user1"
  }
  ```
  or
  ```json
  {
    "valid": false
  }
  ```

### Data Retrieval

#### Get Access Logs
- **URL**: `/api/access-logs`
- **Method**: `GET`
- **Description**: Retrieve access logs with pagination
- **Authentication**: Required (user must be logged in)
- **Query Parameters**:
  - `page`: Page number (default: 1)
  - `per_page`: Items per page (max: 100, default: 20)
- **Response**:
  ```json
  {
    "logs": [
      {
        "id": 1,
        "method": "fingerprint",
        "user": "user1",
        "status": "GRANTED",
        "timestamp": "2023-01-01T10:00:00",
        "ip_address": "192.168.1.100"
      }
    ],
    "total": 100,
    "pages": 5,
    "current_page": 1
  }
  ```

## Error Responses

All error responses follow this format:
```json
{
  "error": "Error message"
}
```

## HTTP Status Codes

- `200`: Success
- `400`: Bad request
- `401`: Unauthorized
- `404`: Not found
- `500`: Server error

## Implementation Notes

### ESP32 Communication
The ESP32 device uses these endpoints to:
1. Send access logs to the server
2. Validate RFID cards and fingerprints
3. Receive remote lock/unlock commands

### Web Interface
The web interface uses these endpoints to:
1. Display access logs
2. Remotely control the lock
3. Manage users and access credentials

## Security Considerations

1. Use HTTPS in production
2. Change default API credentials
3. Implement rate limiting
4. Use strong authentication for web interface
5. Regularly update certificates and passwords