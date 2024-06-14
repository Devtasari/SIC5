#include <WiFi.h>
#include <HTTPClient.h>

// Konfigurasi WiFi
const char* ssid = "Kuco ngek";
const char* password = "09042019";

// URL server lokal
const char* serverName = "http://192.168.1.100:5000/submit";

// Pin sensor (misalnya, pin untuk sensor suhu atau kelembapan)
const int sensorPin = 34;

void setup() {
  Serial.begin(115200);

  // Menghubungkan ke WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Menghubungkan ke WiFi...");
  }
  Serial.println("Terhubung ke WiFi");
}

void loop() {
// Membaca data dari sensor
  int sensorValue = analogRead(sensorPin);
  float voltage = sensorValue * (3.3 / 4095.0); // Mengonversi nilai ADC ke tegangan

  // Membuat objek HTTPClient
  HTTPClient http;

  // Memulai koneksi HTTP
  http.begin(serverName);

  // Menentukan tipe konten
  http.addHeader("Content-Type", "application/json");

  // Membuat payload JSON
  String jsonPayload = "{\"sensor_value\": " + String(voltage) + "}";

  // Mengirim permintaan POST
  int httpResponseCode = http.POST(jsonPayload);

  // Memeriksa kode respon HTTP
  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.println(httpResponseCode);
    Serial.println(response);
  } else {
    Serial.print("Error pada pengiriman POST: ");
    Serial.println(httpResponseCode);
  }

  // Mengakhiri koneksi
  http.end();

// Tunggu sebelum membaca data lagi
  delay(10000);
}