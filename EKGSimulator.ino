/**
  EKGSimulator - An Arduino based ECG simulator, using Fast PWM

  Copyright (C) 2018 Costin STROIE <costinstroie@eridu.eu.org>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// Normal ECG samples LUT
static const uint8_t ecglut[] = {
  128, 128, 128, 128, 127, 128, 127, 127, 128, 128, 128, 128, 128, 128, 128, 128,
  128, 128, 128, 128, 128, 127, 128, 127, 128, 128, 128, 129, 129, 128, 128, 128,
  128, 128, 128, 128, 128, 127, 127, 128, 128, 128, 128, 128, 128, 128, 128, 128,
  127, 127, 127, 128, 128, 127, 127, 127, 128, 127, 127, 127, 127, 128, 127, 127,
  127, 127, 127, 127, 128, 127, 127, 128, 127, 127, 127, 127, 127, 127, 127, 127,
  126, 125, 125, 125, 125, 125, 127, 127, 126, 126, 126, 127, 128, 129, 129, 127,
  128, 128, 129, 128, 129, 129, 130, 129, 130, 129, 129, 129, 129, 130, 130, 130,
  131, 131, 131, 131, 131, 132, 132, 132, 132, 132, 132, 132, 132, 132, 132, 133,
  133, 133, 134, 133, 133, 134, 134, 134, 135, 134, 135, 135, 135, 135, 135, 136,
  135, 135, 135, 135, 135, 135, 135, 135, 135, 135, 135, 133, 134, 134, 134, 134,
  134, 133, 132, 131, 133, 132, 131, 131, 130, 130, 130, 130, 130, 128, 128, 129,
  129, 128, 128, 128, 126, 126, 126, 126, 126, 126, 126, 125, 124, 124, 124, 123,
  123, 122, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 122,
  122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 121, 122, 122, 122, 122, 122,
  121, 122, 122, 121, 122, 122, 122, 122, 122, 122, 122, 122, 122, 121, 122, 121,
  121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 119, 120, 119, 118, 117,
  117, 116, 115, 114, 114, 113, 113, 113, 113, 113, 113, 113, 113, 113, 119, 121,
  121, 121, 121, 121, 141, 146, 146, 146, 167, 172, 177, 182, 187, 190, 194, 197,
  201, 202, 203, 201, 201, 199, 198, 196, 191, 191, 191, 191, 191, 163, 156, 156,
  145, 145, 145, 132, 129, 129, 129, 129, 129, 129, 121, 121, 120, 121, 120, 119,
  118, 119, 119, 118, 118, 118, 119, 121, 121, 121, 121, 121, 121, 125, 125, 125,
  125, 125, 125, 125, 127, 128, 128, 128, 128, 128, 127, 127, 127, 127, 127, 127,
  126, 125, 126, 126, 126, 126, 126, 127, 127, 127, 127, 127, 125, 125, 125, 125,
  125, 125, 125, 126, 126, 126, 126, 126, 126, 125, 126, 126, 126, 127, 128, 127,
  128, 128, 127, 128, 128, 129, 128, 129, 129, 129, 129, 129, 129, 129, 130, 130,
  130, 130, 130, 130, 131, 132, 132, 132, 133, 133, 132, 133, 133, 135, 134, 135,
  135, 134, 135, 135, 135, 134, 135, 136, 136, 136, 136, 137, 137, 137, 137, 137,
  137, 138, 137, 137, 137, 137, 137, 137, 141, 142, 142, 142, 143, 143, 143, 143,
  144, 143, 144, 144, 143, 146, 146, 146, 146, 146, 146, 146, 148, 148, 148, 148,
  148, 148, 150, 150, 150, 151, 151, 152, 152, 153, 152, 153, 155, 155, 154, 155,
  155, 156, 155, 155, 156, 156, 156, 156, 156, 158, 158, 157, 157, 157, 157, 160,
  159, 159, 159, 159, 159, 160, 160, 160, 159, 159, 159, 159, 158, 159, 157, 158,
  158, 158, 158, 158, 158, 158, 158, 158, 158, 155, 155, 155, 155, 155, 155, 153,
  150, 150, 150, 148, 147, 148, 148, 146, 146, 145, 144, 142, 142, 142, 141, 140,
  140, 139, 139, 138, 137, 135, 134, 134, 134, 133, 133, 132, 132, 131, 131, 130,
  130, 130, 130, 129, 128, 127, 127, 127, 126, 127, 126, 125, 125, 126, 125, 125,
  124, 124, 124, 124, 124, 123, 124, 123, 123, 123, 123, 123, 123, 124, 124, 124,
  123, 124, 123, 124, 123, 124, 124, 123, 122, 123, 123, 122, 123, 122, 123, 122,
  123, 123, 122, 123, 123, 123, 122, 123, 124, 123, 123, 123, 124, 123, 123, 124,
  124, 123, 123, 123, 123, 123, 124, 123, 124, 123, 125, 124, 124, 124, 124, 124,
  124, 124, 123, 124, 125, 125, 125, 125, 124, 125, 124, 125, 124, 124, 126, 126,
  126, 127, 127, 126, 126, 126, 127, 127, 127, 126, 127, 126, 127, 127, 127, 127,
  127, 126, 128, 127, 128, 128, 127, 126, 126, 127, 127, 127, 128, 128, 127, 127,
  127, 127, 128, 128, 127, 127, 128, 128, 129, 128, 128, 128, 127, 128, 127, 129,
  128, 128, 127, 128, 129, 128, 128, 128, 128, 128, 128, 127, 128, 128, 127, 128,
  127, 128, 128, 128, 128, 128, 127, 128, 128, 127, 127, 128, 128, 128, 129, 127,
  128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
  128, 128, 127, 127, 128, 128, 128, 128, 129, 128, 128, 128, 127, 127, 128, 128,
  128, 127, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 129, 128, 128, 128,
  128, 127, 128, 128, 128, 129, 129, 129, 128, 128, 128, 129, 127, 127, 128, 128
};

// Samples count
const uint16_t samples = sizeof(ecglut);

// Adjustable beats per minute
uint16_t bpm = 60;


/**
  Initialize the hardware
*/
void initHW() {
  //Disable interrupts
  cli();

  // TC1 Control Register B: No prescaling, WGM mode 12
  TCCR1A = 0;
  TCCR1B = _BV(CS10) | _BV(WGM13) | _BV(WGM12);
  // Top set for F_SAMPLE
  ICR1 = (F_CPU / (samples * bpm / 60)) - 1;

  // Analog input A0
  DDRC  &= ~_BV(0); // Port C Data Direction Register
  PORTC &= ~_BV(0); // Port C Data Register
  DIDR0 |=  _BV(0); // Digital Input Disable Register 0

  // Timer/Counter1 Capture Event
  ADCSRB = _BV(ADTS2) | _BV(ADTS1) | _BV(ADTS0);
  // ADC Enable, ADC Start Conversion, ADC Auto Trigger Enable,
  // ADC Interrupt Enable, ADC Prescaler 16 (1MHz)
  ADCSRA = _BV(ADEN) | _BV(ADSC) | _BV(ADATE) | _BV(ADIE) | _BV(ADPS2);

  // Set up Timer 2 to do Pulse Width Modulation on PIN 3 or 11
  ASSR    &= ~(_BV(EXCLK) | _BV(AS2));  // Use internal clock (p.213)
  TCCR2A  |=   _BV(WGM21) | _BV(WGM20); // Set fast PWM mode  (p.205)
  TCCR2B  &= ~(_BV(WGM22));

  // Configure the PWM PIN 11 (PB3)
  PORTB &= ~(_BV(PORTB3));
  DDRB  |=   _BV(PORTB3);
  // Configure the PWM PIN 3 (PD3)
  PORTD &= ~(_BV(PORTD3));
  DDRD  |=   _BV(PORTD3);
  // Do non-inverting PWM on pin OC2A and OC2B (p.205)
  TCCR2A = (TCCR2A | _BV(COM2A1) | _BV(COM2B1)) & (~_BV(COM2A0) | ~_BV(COM2B0));
  // No prescaler (p.206)
  TCCR2B = (TCCR2B & ~(_BV(CS22) | _BV(CS21))) | _BV(CS20);

  // Set initial PWM to the first sample
  DAC(getSample());

  // Enable interrupts
  sei();
}

/**
  Send the sample to the primary DAC

  @param sample the sample to output to DAC
*/
inline void DAC(uint8_t sample) {
  OCR2B = sample;
  //OCR2A = sample;
}


/**
  Get an instant wave sample
*/
uint8_t getSample() {
  // Static index
  static uint16_t idx = 0;
  // Get the value
  uint8_t result = ecglut[idx];
  // Next index, modulo samples
  idx++;
  if (idx >= samples) idx = 0;
  return result;
}

/**
  ADC Interrupt vector, called for each sample
*/
ISR(ADC_vect) {
  // Clear the Interrupt Flag Register
  TIFR1 = _BV(ICF1);
  // Hadle ECG signal
  DAC(getSample());
}

/**
  Main Arduino setup function
*/
void setup() {
  // Serial port configuration
  Serial.begin(9600);

  // Hardware init
  initHW();
}

/**
  Main Arduino loop
*/
void loop() {
  static uint32_t rpmTimeout = millis() + 100;
  // Adjust the heartbeat rate
  if (millis() > rpmTimeout) {
    rpmTimeout += 100;
    // Read the BPM potentiometer
    uint16_t rpm = map(analogRead(A0), 0, 1024, 30, 150);
    // Low pass the BPM read
    bpm = ((bpm << 4) - bpm + rpm + 8) >> 4;
    // Set the new ICR1
    uint16_t icr = (F_CPU / ((uint32_t)bpm * samples / 60)) - 1;
    ICR1 = icr;
    // Print the RPM and BPM
    Serial.print(rpm); Serial.print(" "); Serial.println(bpm);
  }
}
