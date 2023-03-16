#include <Arduino.h>
#include <SPI.h>

#define SCK     5    // GPIO5  -- SX127x's SCK
#define MISO    19   // GPIO19 -- SX127x's MISO
#define MOSI    27   // GPIO27 -- SX127x's MOSI
#define CSadc   17   // GPIO18 -- SX127x's ADS8668 - CS
#define RSTadc  32   // GPIO14 -- SX127x's RESET

class ADS8668
{

  SPISettings settingsA;

  int nDisp;
  double data[][8];

public:
  void init(uint16_t conf, int nDisp);
  double getData(int adcNum, int adcCH);
  void convertAllData();

private:
  double convert2Bytes(byte hiByte, byte loByte);
  void readBit();
  void writeBit(uint8_t val);
};
