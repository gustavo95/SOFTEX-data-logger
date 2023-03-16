#include "ads8668.h"

void ADS8668::init(uint16_t conf, int nDisp_)
{

  settingsA = SPISettings(8000000, MSBFIRST, SPI_MODE1);

  nDisp = nDisp_;

  digitalWrite(RSTadc, LOW);
  digitalWrite(RSTadc, HIGH);
  SPI.beginTransaction(settingsA);
  digitalWrite(CSadc, LOW);
  SPI.transfer16(conf);
  for(int i = 0; i < (16*nDisp); i++){
    SPI.transfer(0x00);
    SPI.transfer(0x00);
  }
  digitalWrite(CSadc, HIGH);
  SPI.endTransaction();

  for(int i = 0; i < nDisp; i++){
    data[i][0] = 0;
    data[i][1] = 0;
    data[i][2] = 0;
    data[i][3] = 0;
    data[i][4] = 0;
    data[i][5] = 0;
    data[i][6] = 0;
    data[i][7] = 0;
  }
}

double ADS8668::getData(int adcNum, int adcCH)
{
  return data[adcNum][adcCH];
}

void ADS8668::convertAllData()
{
  byte hiByte[nDisp];
  byte loByte[nDisp];

  SPI.beginTransaction(settingsA);

  digitalWrite(CSadc, LOW);
  SPI.transfer16(0xC000); //Write ch0
  for(int i = nDisp-1; i >= 0; i--){
    SPI.transfer(0x00); //read trash
    SPI.transfer(0x00);
  }
  digitalWrite(CSadc, HIGH);

  digitalWrite(CSadc, LOW);
  SPI.transfer16(0xC400); //Write ch1
  for(int i = nDisp-1; i >= 0; i--){
    hiByte[i] = SPI.transfer(0x00); //read ch0
    loByte[i] = SPI.transfer(0x00);
  }
  digitalWrite(CSadc, HIGH);

  for(int i = 0; i < nDisp; i++){
    data[i][0] = convert2Bytes(hiByte[i], loByte[i]);
  }

  digitalWrite(CSadc, LOW);
  SPI.transfer16(0xC800); //Write ch2
  for(int i = nDisp-1; i >= 0; i--){
    hiByte[i] = SPI.transfer(0x00); //read ch1
    loByte[i] = SPI.transfer(0x00);
  }
  digitalWrite(CSadc, HIGH);

  for(int i = 0; i < nDisp; i++){
    data[i][1] = convert2Bytes(hiByte[i], loByte[i]);
  }

  digitalWrite(CSadc, LOW);
  SPI.transfer16(0xCC00); //Write ch3
  for(int i = nDisp-1; i >= 0; i--){
    hiByte[i] = SPI.transfer(0x00); //read ch2
    loByte[i] = SPI.transfer(0x00);
  }
  digitalWrite(CSadc, HIGH);

  for(int i = 0; i < nDisp; i++){
    data[i][2] = convert2Bytes(hiByte[i], loByte[i]);
  }

  digitalWrite(CSadc, LOW);
  SPI.transfer16(0xD000); //Write ch4
  for(int i = nDisp-1; i >= 0; i--){
    hiByte[i] = SPI.transfer(0x00); //read ch3
    loByte[i] = SPI.transfer(0x00);
  }
  digitalWrite(CSadc, HIGH);

  for(int i = 0; i < nDisp; i++){
    data[i][3] = convert2Bytes(hiByte[i], loByte[i]);
  }

  digitalWrite(CSadc, LOW);
  SPI.transfer16(0xD400); //Write ch5
  for(int i = nDisp-1; i >= 0; i--){
    hiByte[i] = SPI.transfer(0x00); //read ch4
    loByte[i] = SPI.transfer(0x00);
  }
  digitalWrite(CSadc, HIGH);

  for(int i = 0; i < nDisp; i++){
    data[i][4] = convert2Bytes(hiByte[i], loByte[i]);
  }

  digitalWrite(CSadc, LOW);
  SPI.transfer16(0xD800); //Write ch6
  for(int i = nDisp-1; i >= 0; i--){
    hiByte[i] = SPI.transfer(0x00); //read ch5
    loByte[i] = SPI.transfer(0x00);
  }
  digitalWrite(CSadc, HIGH);

  for(int i = 0; i < nDisp; i++){
    data[i][5] = convert2Bytes(hiByte[i], loByte[i]);
  }

  digitalWrite(CSadc, LOW);
  SPI.transfer16(0xDC00); //Write ch7
  for(int i = nDisp-1; i >= 0; i--){
    hiByte[i] = SPI.transfer(0x00); //read ch6
    loByte[i] = SPI.transfer(0x00);
  }
  digitalWrite(CSadc, HIGH);

  for(int i = 0; i < nDisp; i++){
    data[i][6] = convert2Bytes(hiByte[i], loByte[i]);
  }

  digitalWrite(CSadc, LOW);
  SPI.transfer16(0xC000); //Write ch0
  for(int i = nDisp-1; i >= 0; i--){
    hiByte[i] = SPI.transfer(0x00); //read ch7
    loByte[i] = SPI.transfer(0x00);
  }
  digitalWrite(CSadc, HIGH);

  for(int i = 0; i < nDisp; i++){
    data[i][7] = convert2Bytes(hiByte[i], loByte[i]);
  }
  SPI.endTransaction();
}

double ADS8668::convert2Bytes(byte hiByte, byte loByte)
{
  int adcRead = (hiByte<<4) + (loByte>>4);
  return adcRead*0.005;
}

void writebit(uint8_t val)
{
  digitalWrite(MOSI, val);
  digitalWrite(SCK, HIGH);
  delay(1);
  digitalWrite(SCK, LOW);
  delay(1);
}

void readbit()
{
  digitalWrite(SCK, HIGH);
  Serial.println(digitalRead(MISO));
  delay(1);
  digitalWrite(SCK, LOW);
  delay(1);
}
