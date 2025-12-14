from datetime import datetime
from flask_sqlalchemy import SQLAlchemy
from flask_login import UserMixin
from werkzeug.security import generate_password_hash, check_password_hash
from . import db

class User(UserMixin, db.Model):
    __tablename__ = 'users'
    
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(80), unique=True, nullable=False, index=True)
    password_hash = db.Column(db.String(255), nullable=False)
    user_type = db.Column(db.String(20), default='user', nullable=False)  # admin, user
    created_at = db.Column(db.DateTime, default=datetime.utcnow)
    last_login = db.Column(db.DateTime)
    is_active = db.Column(db.Boolean, default=True)
    
    # Relationships
    rfid_cards = db.relationship('RFIDCard', backref='user', lazy='dynamic', cascade='all, delete-orphan')
    fingerprints = db.relationship('Fingerprint', backref='user', lazy='dynamic', cascade='all, delete-orphan')
    access_logs = db.relationship('AccessLog', backref='user', lazy='dynamic', cascade='all, delete-orphan')
    
    def set_password(self, password):
        self.password_hash = generate_password_hash(password)
    
    def check_password(self, password):
        return check_password_hash(self.password_hash, password)
    
    def is_admin(self):
        return self.user_type == 'admin'
    
    def __repr__(self):
        return f'<User {self.username}>'

class RFIDCard(db.Model):
    __tablename__ = 'rfid_cards'
    
    id = db.Column(db.Integer, primary_key=True)
    uid = db.Column(db.String(32), unique=True, nullable=False, index=True)
    user_id = db.Column(db.Integer, db.ForeignKey('users.id'), nullable=False)
    created_at = db.Column(db.DateTime, default=datetime.utcnow)
    last_used = db.Column(db.DateTime)
    is_active = db.Column(db.Boolean, default=True)
    description = db.Column(db.String(100))
    
    def __repr__(self):
        return f'<RFIDCard {self.uid}>'

class Fingerprint(db.Model):
    __tablename__ = 'fingerprints'
    
    id = db.Column(db.Integer, primary_key=True)
    finger_id = db.Column(db.Integer, unique=True, nullable=False, index=True)
    user_id = db.Column(db.Integer, db.ForeignKey('users.id'), nullable=False)
    created_at = db.Column(db.DateTime, default=datetime.utcnow)
    last_used = db.Column(db.DateTime)
    is_active = db.Column(db.Boolean, default=True)
    finger_name = db.Column(db.String(50))  # e.g., "Right Index", "Left Thumb"
    
    def __repr__(self):
        return f'<Fingerprint {self.finger_id}>'

class AccessLog(db.Model):
    __tablename__ = 'access_logs'
    
    id = db.Column(db.Integer, primary_key=True)
    method = db.Column(db.String(20), nullable=False, index=True)  # fingerprint, rfid, keypad, web
    user_id = db.Column(db.Integer, db.ForeignKey('users.id'))
    user_identifier = db.Column(db.String(80), nullable=False)  # username, card UID, finger ID
    status = db.Column(db.String(20), nullable=False, index=True)  # GRANTED, DENIED
    timestamp = db.Column(db.DateTime, default=datetime.utcnow, index=True)
    ip_address = db.Column(db.String(45))
    user_agent = db.Column(db.String(200))
    
    def to_dict(self):
        return {
            'id': self.id,
            'method': self.method,
            'user': self.user_identifier,
            'status': self.status,
            'timestamp': self.timestamp.isoformat(),
            'ip_address': self.ip_address
        }
    
    def __repr__(self):
        return f'<AccessLog {self.method}:{self.status}>'

# User loader for Flask-Login
@login_manager.user_loader
def load_user(user_id):
    return User.query.get(int(user_id))