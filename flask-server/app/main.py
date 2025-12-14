from flask import Blueprint, render_template

bp = Blueprint('main', __name__)

@bp.route('/')
def index():
    return render_template('index.html')

@bp.route('/dashboard')
def dashboard():
    return render_template('dashboard.html')

@bp.route('/users')
def users():
    return render_template('users.html')

@bp.route('/logs')
def logs():
    return render_template('logs.html')