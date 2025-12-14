from flask import Blueprint, render_template, request, redirect, url_for, flash
from flask_login import login_user, logout_user, login_required, current_user
from app.models import User
from app import db
from sqlalchemy import func

bp = Blueprint('auth', __name__)

@bp.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        user = User.query.filter_by(username=username).first()
        if user and user.check_password(password):
            login_user(user)
            user.last_login = func.now()
            db.session.commit()
            return redirect(url_for('main.dashboard'))
        else:
            flash('Invalid username or password')
    
    return render_template('auth/login.html')

@bp.route('/logout')
@login_required
def logout():
    logout_user()
    return redirect(url_for('main.index'))

@bp.route('/register', methods=['GET', 'POST'])
@login_required
def register():
    if not current_user.is_admin():
        flash('Access denied')
        return redirect(url_for('main.index'))
    
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        user_type = request.form.get('user_type', 'user')
        
        if User.query.filter_by(username=username).first():
            flash('Username already exists')
        else:
            user = User(username=username, user_type=user_type)
            user.set_password(password)
            db.session.add(user)
            db.session.commit()
            flash('User registered successfully')
    
    return render_template('auth/register.html')