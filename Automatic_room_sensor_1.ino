// MUX Select pins
const int S0 = 2;
const int S1 = 3;

// MUX Output pin
const int muxOutput = A0;

// LED pin
const int ledPin = 7;

// Thresholds
const int lightThreshold = 500;  // Adjust as needed (0-1023)
const int motionThreshold =100; // PIR HIGH gives near 1023 (digital HIGH ≈ 1023)

void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

int readMuxChannel(int channel) {
  // channel: 0 = D0a (LDR), 1 = D1a (PIR)
  digitalWrite(S0, channel & 0x01);
  digitalWrite(S1, (channel >> 1) & 0x01);
  delay(5);  // Short delay for MUX to settle
  return analogRead(muxOutput);
}

void loop() {
  int ldrValue = readMuxChannel(0); // Read from D0a
  int pirValue = readMuxChannel(1); // Read from D1a

  Serial.print("LDR: ");
  Serial.print(ldrValue);
  Serial.print("  PIR: ");
  Serial.println(pirValue);

  // Light turns on only if room is dark AND motion is detected
  if (ldrValue < lightThreshold && pirValue > motionThreshold) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

  delay(200);  // Adjust for responsiveness
}

