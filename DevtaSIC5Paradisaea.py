import json
from flask import Flask, request, jsonify

app = Flask(_name_)

SENSOR_DATA = []

@app.route("/")
def root_route():
    return "Hello, ESP32!"

@app.route("/data", methods=["GET"])
def get_data():
    return jsonify(SENSOR_DATA)

@app.route("/submit", methods=["POST"])
def post_data():
    data = request.get_json()
    sensor_value = data.get("sensor_value")
    SENSOR_DATA.append(sensor_value)
    print(f"Received sensor value: {sensor_value}")

    response = {
        "status": "success",
        "message": "Data received successfully",
        "received_value": sensor_value
    }
    return jsonify(response), 200

if _name_ == "_main_":
    app.run(host='0.0.0.0', port=5000,debug=True)