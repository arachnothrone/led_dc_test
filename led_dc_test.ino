/**
 * LED Duty Cycle measurement tool
 * 
 * arachnothrone 2019
 *  
 */

#include <Arduino.h>

#define NUM_OR_RECORDS (500)

typedef struct
{
  unsigned int cdsCellValue;
  unsigned int timeIntervalUs;
} Sensor_Readings_T;

static Sensor_Readings_T dataTable[NUM_OR_RECORDS] = {0};
unsigned long int taskPeriodMeasStart   = 0;
unsigned long int taskPeriodMeasStop    = 0;

void setup()
{
    Serial.begin(115200);
}

void loop()
{
    for (int i = 0; i < NUM_OR_RECORDS; i++)
    {
        taskPeriodMeasStart = micros();
        dataTable[i].cdsCellValue = analogRead(A0);
        taskPeriodMeasStop = micros();
        dataTable[i].timeIntervalUs = taskPeriodMeasStop - taskPeriodMeasStart;
    }

    for (int i = 0; i < NUM_OR_RECORDS; i++)
    {
        Serial.print(F("CdS_cell: "));
        Serial.print(dataTable[i].cdsCellValue);
        Serial.print(F(" period_us: "));
        Serial.println(dataTable[i].timeIntervalUs);
    }
    
    Serial.println(F("--------------------"));
    delay(500);

}