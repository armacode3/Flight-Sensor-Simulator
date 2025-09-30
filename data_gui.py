import socket
import sys
from PyQt5.QtWidgets import QApplication, QWidget, QLabel, QVBoxLayout
from PyQt5.QtCore import QObject, QThread, pyqtSignal

class Worker(QObject):
    # Wait for signal
    telemetry_update = pyqtSignal(float, float, float)

    def __init__(self):
        # Initializes the parent class (QObject)
        super().__init__()

        # Create socket with IP address (IPv4) and socket type (UDP)
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

        # Tuple that holds the IP address and port
        server_address = ("127.0.0.1", 9000)

        # Bind the server_address to socket (recieve data)
        self.sock.bind(server_address)

    # Infinite Loop
    def run(self):
        while True:
            try:
                data, address = self.sock.recvfrom(1024) # Recieving data (1024 bytes)
                
                message = data.decode() # Decode data into human readable
                telemetry_data = message.split(',') # Split data into list

                flight_time = float(telemetry_data[0])
                altitude = float(telemetry_data[1])
                est_altitude = float(telemetry_data[2])
                
                # Emite the signal with data
                self.telemetry_update.emit(flight_time, altitude, est_altitude)
            except (ValueError, IndexError):
                # If data is bad ignore
                pass

# Main application
if __name__ == "__main__":
    # Create instance of QApplication
    app = QApplication(sys.argv)
    # Create basic widget (main window)
    window = QWidget()
    window.setWindowTitle('Rocket Telemetry')
    window.setGeometry(100, 100, 400, 200) # (x, y, width, height)

    # Create layout
    layout = QVBoxLayout()
    # Create the labels
    timeLabel = QLabel("Time: --")
    altitudeLabel = QLabel("Altitude: --")
    estAltLabel = QLabel("Est. Altitude: --")

    # Add each label to layout
    layout.addWidget(timeLabel) 
    layout.addWidget(altitudeLabel)
    layout.addWidget(estAltLabel)

    # Apply layout to window
    window.setLayout(layout)

    def update_telemetry(time, alt, est_alt, time_label, altitude_label, est_label):
        time_label.setText(f"Time: {time:.2f} s")
        altitude_label.setText(f"Altitude: {alt:.2f} m")
        est_label.setText(f"Est. Altitude: {est_alt:.2f} m")

    # Create new thread
    thread = QThread()
    # Create worker from Worker class
    worker = Worker()
    # Move worker to thread
    worker.moveToThread(thread)

    # Start workers run() method when the thread starts
    thread.started.connect(worker.run)
    #Conncect worker's signal to slot function
    worker.telemetry_update.connect(lambda t, a, e: update_telemetry(t, a, e, timeLabel, altitudeLabel, estAltLabel))
    # Start the thread
    thread.start()

    # Show window
    window.show()
    # Start even loop
    sys.exit(app.exec())