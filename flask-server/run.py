#!/usr/bin/env python3
"""
Smart Locker Flask Server
Main entry point for the web server
"""

import os
from app import create_app, db
from app.models import User, RFIDCard, Fingerprint, AccessLog

# Get configuration from environment variable or use default
config_name = os.environ.get('FLASK_CONFIG') or 'default'
app = create_app(config_name)

# Shell context for Flask CLI
@app.shell_context_processor
def make_shell_context():
    return {
        'db': db,
        'User': User,
        'RFIDCard': RFIDCard,
        'Fingerprint': Fingerprint,
        'AccessLog': AccessLog
    }

# Create database tables and default admin user
@app.before_first_request
def create_tables():
    db.create_all()
    
    # Create default admin user if not exists
    if not User.query.filter_by(username='admin').first():
        admin = User(
            username='admin',
            password='admin123',
            user_type='admin'
        )
        db.session.add(admin)
        db.session.commit()
        print("Default admin user created - username: admin, password: admin123")

if __name__ == '__main__':
    app.run(
        host=app.config['SERVER_HOST'],
        port=app.config['SERVER_PORT'],
        debug=app.config['DEBUG']
    )