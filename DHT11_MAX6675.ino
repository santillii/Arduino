// Parte relativa al DHT11

#include <Adafruit_Sensor.h>      // Importazione dei moduli per il DHT11
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 2     // Inizializzazione del pin 2 per comunicare con il DHT11 

#define DHTTYPE    DHT11     // DHT 11    // Tipo di sensore utilizzato

DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;


// Parte relativa al MAX6675

#include "max6675.h"    // Importazione del modulo MAX6675

int thermoDO = 4;       // Assegnazione pin Data Out (è un output dal MAX6675 e trasporta i dati misurati)
int thermoCS = 5;       // Assegnazione pin Chip Select (è un input al MAX6675 e comunica al chip quando leggere i dati della termocoppia ed inviarli ad Arduino)  
int thermoCLK = 6;      // Assegnazione pin Clock (è un input al MAX6675 che indica quando deve comunicare i dati al microcontrollore)

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);


void setup() {
  Serial.begin(9600);            // Impostazione velocità di comunicazione seriale in bits per secondo 
  
  dht.begin();                  // Inizialiizzazione DHT11
  sensor_t sensor;
  
  delayMS = sensor.min_delay / 1000;    // Impostazione intervallo tra misurazioni in base alle specifiche del sensore DHT11

  Serial.println("Temperatura DHT11 (°C), Umidità DHT11 (%), Temperatura MAX6675 (°C)");      // Intestazione delle colonne per file .csv
}

void loop() {
  
  delay(delayMS);       // Applicazione dell'intervallo visto nella fase precedente
  
  sensors_event_t event;      // Determinazione misura della temperatura e mostra del valore
  dht.temperature().getEvent(&event);
  
  if (isnan(event.temperature)) {               // Esecuzione condizionata: il valore della temperatura viene mostrato sul monitor solo se e' un numero
    Serial.println(F("Error reading temperature!"));    // Altrimenti verra' stampato un avviso d'errore
  }
  else {
    Serial.print(event.temperature);      // Se la condizione IF NON e' rispettata allora la temperatura viene stampata
    Serial.print(" , "));                 // " , " necessaria per il file .csv
  }
  
  dht.humidity().getEvent(&event);         // Determinazione misura dell'umidita' e mostra del valore
  
  if (isnan(event.relative_humidity)) {         // Secondo ciclo IF del tutto assimilabile al primo, ovvero il valore dell'umidita' vieme stampato solo se   
    Serial.println(F("Error reading humidity!"));   // il valore determinato e' un numero
  }
  else {
    Serial.print(event.relative_humidity);
    Serial.print(" , ");
  }


  // Fase Loop della termocoppia MAX6675
  
  Serial.print(thermocouple.readCelsius());   // Lettura e mostra del valore temperatura misurato dal MAX6675
  Serial.println();     // A capo di una riga
}
