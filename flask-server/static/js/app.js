// Smart Locker System JavaScript

// Function to refresh system status
function refreshStatus() {
    console.log('Refreshing system status...');
    // In a real implementation, this would make an API call to check ESP32 status
}

// Function to unlock the door remotely
function unlockDoor() {
    if (confirm('Are you sure you want to unlock the door?')) {
        fetch('/api/unlock', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
            },
            credentials: 'same-origin'
        })
        .then(response => response.json())
        .then(data => {
            console.log('Door unlock response:', data);
            alert('Door unlocked successfully!');
        })
        .catch(error => {
            console.error('Error unlocking door:', error);
            alert('Error unlocking door. Please try again.');
        });
    }
}

// Function to lock the door remotely
function lockDoor() {
    if (confirm('Are you sure you want to lock the door?')) {
        fetch('/api/lock', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
            },
            credentials: 'same-origin'
        })
        .then(response => response.json())
        .then(data => {
            console.log('Door lock response:', data);
            alert('Door locked successfully!');
        })
        .catch(error => {
            console.error('Error locking door:', error);
            alert('Error locking door. Please try again.');
        });
    }
}

// Function to load access logs
function loadAccessLogs(page = 1) {
    fetch(`/api/access-logs?page=${page}`)
        .then(response => response.json())
        .then(data => {
            console.log('Access logs:', data);
            // In a real implementation, this would populate the logs table
        })
        .catch(error => {
            console.error('Error loading access logs:', error);
        });
}

// Document ready function
document.addEventListener('DOMContentLoaded', function() {
    console.log('Smart Locker System UI loaded');
    
    // Add event listeners for buttons if they exist
    const unlockBtn = document.getElementById('unlock-btn');
    const lockBtn = document.getElementById('lock-btn');
    
    if (unlockBtn) {
        unlockBtn.addEventListener('click', unlockDoor);
    }
    
    if (lockBtn) {
        lockBtn.addEventListener('click', lockDoor);
    }
    
    // Load access logs on logs page
    if (window.location.pathname.includes('/logs')) {
        loadAccessLogs();
    }
});