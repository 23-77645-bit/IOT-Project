from flask import Blueprint, request, jsonify, Response
from flask_login import login_required
from app.models import User, RFIDCard, Fingerprint, AccessLog
from app import db
import json
from datetime import datetime

bp = Blueprint('api', __name__)

@bp.route('/lock', methods=['POST'])
def lock_door():
    # API endpoint for locking the door remotely
    # Authenticate with ESP32 credentials
    auth = request.authorization
    if not auth or not (auth.username == 'admin' and auth.password == 'smartlock2025'):
        return Response('Could not verify credentials', 401, {'WWW-Authenticate': 'Basic realm="Login Required"'})
    
    # Process lock command
    # This would typically send a signal to the ESP32
    return jsonify({'status': 'locked'})

@bp.route('/unlock', methods=['POST'])
def unlock_door():
    # API endpoint for unlocking the door remotely
    # Authenticate with ESP32 credentials
    auth = request.authorization
    if not auth or not (auth.username == 'admin' and auth.password == 'smartlock2025'):
        return Response('Could not verify credentials', 401, {'WWW-Authenticate': 'Basic realm="Login Required"'})
    
    # Process unlock command
    # This would typically send a signal to the ESP32
    return jsonify({'status': 'unlocked'})

@bp.route('/access-log', methods=['POST'])
def log_access():
    # API endpoint for ESP32 to log access attempts
    # Authenticate with ESP32 credentials
    auth = request.authorization
    if not auth or not (auth.username == 'admin' and auth.password == 'smartlock2025'):
        return Response('Could not verify credentials', 401, {'WWW-Authenticate': 'Basic realm="Login Required"'})
    
    data = request.get_json()
    if not data:
        return jsonify({'error': 'No data provided'}), 400
    
    method = data.get('method')
    user_identifier = data.get('user')
    success = data.get('success', False)
    status = 'GRANTED' if success else 'DENIED'
    ip_address = request.remote_addr
    
    # Create access log entry
    access_log = AccessLog(
        method=method,
        user_identifier=user_identifier,
        status=status,
        ip_address=ip_address
    )
    
    # Find user if possible
    # Try matching with RFID card first
    rfid_card = RFIDCard.query.filter_by(uid=user_identifier).first()
    if rfid_card:
        access_log.user_id = rfid_card.user_id
    else:
        # Try matching with fingerprint
        fingerprint = Fingerprint.query.filter_by(finger_id=int(user_identifier.split(':')[1]) if ':' in user_identifier else int(user_identifier)).first()
        if fingerprint:
            access_log.user_id = fingerprint.user_id
    
    db.session.add(access_log)
    db.session.commit()
    
    return jsonify({'status': 'logged', 'id': access_log.id})

@bp.route('/validate-rfid/<uid>', methods=['GET'])
def validate_rfid(uid):
    # API endpoint to validate an RFID card
    # Authenticate with ESP32 credentials
    auth = request.authorization
    if not auth or not (auth.username == 'admin' and auth.password == 'smartlock2025'):
        return Response('Could not verify credentials', 401, {'WWW-Authenticate': 'Basic realm="Login Required"'})
    
    rfid_card = RFIDCard.query.filter_by(uid=uid).first()
    if rfid_card and rfid_card.is_active:
        return jsonify({
            'valid': True,
            'user_id': rfid_card.user_id,
            'username': rfid_card.user.username
        })
    else:
        return jsonify({
            'valid': False
        })

@bp.route('/validate-fingerprint/<int:finger_id>', methods=['GET'])
def validate_fingerprint(finger_id):
    # API endpoint to validate a fingerprint
    # Authenticate with ESP32 credentials
    auth = request.authorization
    if not auth or not (auth.username == 'admin' and auth.password == 'smartlock2025'):
        return Response('Could not verify credentials', 401, {'WWW-Authenticate': 'Basic realm="Login Required"'})
    
    fingerprint = Fingerprint.query.filter_by(finger_id=finger_id).first()
    if fingerprint and fingerprint.is_active:
        return jsonify({
            'valid': True,
            'user_id': fingerprint.user_id,
            'username': fingerprint.user.username
        })
    else:
        return jsonify({
            'valid': False
        })

@bp.route('/access-logs', methods=['GET'])
@login_required
def get_access_logs():
    # API endpoint for web interface to get access logs
    page = request.args.get('page', 1, type=int)
    per_page = min(request.args.get('per_page', 20, type=int), 100)
    
    logs = AccessLog.query.order_by(AccessLog.timestamp.desc()).paginate(
        page=page, per_page=per_page, error_out=False
    )
    
    return jsonify({
        'logs': [log.to_dict() for log in logs.items],
        'total': logs.total,
        'pages': logs.pages,
        'current_page': logs.page
    })