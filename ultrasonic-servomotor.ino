#include <Arduino.h>

#include <servo.h> // Include the Servo library

#define SERVO_PIN 3 // Defi3e the pin for the servo motor
#define TriG_PIN 9 // Define the pin for the trigger
#define Echo_PIN 8 // Define the pin for the echo

Servo myServo; // Create a Servo object

void setup() {
  Serial.begin(9600); // Start the serial communication at 9600 baud rate
  myServo.attach(SERVO_PIN); // Attach the servo motor to the defined pin
  pinMode(TriG_PIN, OUTPUT); // Set the trigger pin as output
  pinMode(Echo_PIN, INPUT); // Set the echo pin as input
  myServo.write(0); // Initialize the servo position to 0 degrees
} 

void loop () {
  long duration; // Variable to store the duration of the echo pulse
  int distance; // Variable to store the calculated distance

  digitalWrite(TriG_PIN, LOW); // Ensure the trigger pin is low
  delayMicroseconds(2); // Wait for 2 microseconds
  digitalWrite(TriG_PIN, HIGH); // Set the trigger pin high to send a pulse
  delayMicroseconds(10); // Wait for 10 microseconds
  digitalWrite(TriG_PIN, LOW); // Set the trigger pin low again

  duration = pulseIn(Echo_PIN, HIGH); // Read the echo pin and get the duration of the pulse
  distance = duration * 0.034 / 2; // Calculate the distance in cm (speed of sound is 0.034 cm/µs)
  Serial.print("Jarak: "); // Print the distance label
  Serial.print(distance); // Print the calculated distance
  Serial.println(" cm"); // Print the unit of measurement


  if (distance > 0 && distance < 50) { // If the distance is less than 10 cm
    myServo.write(90); // Move the servo to 90 degrees
    //delay(1000); // Wait for 1 second
  } else {
    myServo.write(0); // Keep the servo at 0 degrees if the distance is greater than or equal to 10 cm
  }

  delay(500); // Wait for 100 milliseconds before the next reading
}
