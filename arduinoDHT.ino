//typedef enum {input, output, input_pullup} io;
#include <Maksymov_BitArray.h>

#include <dht.h>

#define INITIAL_PIN 5
#define NUM_OF_PINS 3

#define dht_apin A0

BitArray halls_array = BitArray(NUM_OF_PINS);

dht DHT;

void setup() {
  Serial.begin(9600);
  setup_pins_array(INITIAL_PIN, NUM_OF_PINS, INPUT);
  delay(500);
}

void setup_pins_array(int begin_index, int num_of_pins, int io) {
  for(int index = begin_index; index < begin_index + num_of_pins; index++) pinMode(index, io);
}

void read_data_from_sensors() {
  for(register int index = 0; index < NUM_OF_PINS; index++) {
    halls_array.setBit(digitalRead(INITIAL_PIN + index), index);
  }
}

void loop() {
  read_data_from_sensors();

  DHT.read11(dht_apin);
  
  debug();
}
//-------
void debug() {
  for(int index = 0; index < NUM_OF_PINS; index++)
    Serial.print(halls_array.getBool(index));
  Serial.println("\n---");

    Serial.print("Current humidity = ");
    Serial.print(DHT.humidity);
    Serial.print("%\n");
    Serial.print("temperature = ");
    Serial.print(DHT.temperature); 
    Serial.println("C");

   delay(2000);
}
