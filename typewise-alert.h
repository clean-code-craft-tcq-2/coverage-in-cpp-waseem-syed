#pragma once

typedef enum {
  PASSIVE_COOLING,
  HI_ACTIVE_COOLING,
  MED_ACTIVE_COOLING
} CoolingType;

typedef enum {
  NORMAL,
  TOO_LOW,
  TOO_HIGH
} BreachType;

BreachType inferBreach(double value, double lowerLimit, double upperLimit);
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);

typedef enum {
  TO_CONTROLLER,
  TO_EMAIL
} AlertTarget;

typedef struct {
  CoolingType coolingType;
  char brand[48];
} BatteryCharacter;

struct CoolingTypeAndTemperatureLimits
{
   CoolingType m_coolingType;
   int m_lowerLimit;
   int m_upperLimit;
   CoolingTypeAndTemperatureLimits(CoolingType coolingType, int lowerLimit,int upperLimit)
   : m_coolingType(coolingType)
   , m_lowerLimit(lowerLimit)
   , m_upperLimit(upperLimit)
   {
   } 
};

struct AlertData
{
  AlertTarget m_alertTarget;
  BatteryCharacter m_batteryChar;
  double m_temperatureInC;
};

struct AlertResponse
{
   BreachType m_breachType;
   bool m_isAlertSent;
};

void checkAndAlert(AlertData alertData, AlertResponse& alertResponse);

void sendToController(BreachType breachType);
void sendToEmail(BreachType breachType);
CoolingTypeAndTemperatureLimits getTemperatureLimitsForCoolingType(CoolingType coolingType);
void printBreachType(BreachType breachType);
