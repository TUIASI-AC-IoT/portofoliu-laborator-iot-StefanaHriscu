import io
from flask import Flask, send_file
import os

app = Flask(__name__)

@app.route('/firmware.bin')
def firm():
    with open(".pio\\build\\esp-wrover-kit\\firmware.bin", 'rb') as bites:
        return send_file(
            io.BytesIO(bites.read()),
            mimetype='application/octet-stream'
        )

@app.route("/version")
def version():
    try:
        with open("versioning", 'r') as version_file:
                version = version_file.readline()
                print(version)
                return version
        return "Version not found"
    except FileNotFoundError:
        return "version.h file not found"

@app.route("/")
def hello():
    return "Hello World!"

if __name__ == '__main__':
    app.run(host='0.0.0.0', ssl_context=('ca_cert.pem', 'ca_key.pem'), debug=True)
