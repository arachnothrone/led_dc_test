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
  unsigned int cdsCellValue;        /* 10-bit A0 value */
  unsigned int timeIntervalUs;      /* execution time of current cycle */
} Sensor_Readings_T;

static Sensor_Readings_T dataTable[NUM_OR_RECORDS] = {0};

void setup()
{
    Serial.begin(115200);
}

/**
 * This function reads CdS Cell data from analog input A0 into a data array.
 * Each record has execution time measurement in microseconds.
 * 
 * \param   pDataTable  - pointer to an array of records Sensor_Readings_T
 * \param   numberOfReadings - int number of records
 * 
 * \return  void
 */
void readDataSet(Sensor_Readings_T* pDataTable, int numberOfReadings)
{
    for (int i = 0; i < numberOfReadings; i++)
    {
        unsigned long int timeStart = micros();
        (pDataTable + i)->cdsCellValue = analogRead(A0);
        unsigned long int timeStop = micros();
        (pDataTable + i)->timeIntervalUs = timeStop - timeStart;
    }
}

/**
 * Function performs the output of all the records from the array pointed by 
 * pDataTable into a serial interface.
 * 
 * \param   pDataTable - poiter to an array of records
 * \param   numberOfReadings - int number of readings
 * 
 * \return  void
 */
void printDataSetSerial(Sensor_Readings_T* pDataTable, int numberOfReadings)
{
    for (int i = 0; i < numberOfReadings; i++)
    {
        Serial.print(F("CdS_cell: "));
        Serial.print((pDataTable + i)->cdsCellValue);
        Serial.print(F(" period_us: "));
        Serial.println((pDataTable + i)->timeIntervalUs);
    }
}

void loop()
{
    unsigned int execTimeStart = millis();
    
    /* Read light sensor data set with execution time for each record */
    readDataSet(dataTable, NUM_OR_RECORDS);

    unsigned int execTimeMiddle = millis();

    /* Print the whole data array to serial port */
    printDataSetSerial(dataTable, NUM_OR_RECORDS);
    
    unsigned int execTimeStop = millis();

    Serial.print(F("\nreadDataSet execution time: "));
    Serial.print(execTimeMiddle - execTimeStart);
    Serial.print(F(" ms, printDataSetSerial execution time: "));
    Serial.print(execTimeStop - execTimeMiddle);
    Serial.println(F(" ms\n--------------------"));

    /* Delay before next loop for IDE program uploading purpuses */
    delay(5000);

}
