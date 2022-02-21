#include "typewise-alert.h"
#include <stdio.h>
#include <vector>

::std::vector<CoolingTypeAndTemperatureLimits> coolingTypeAndTemperatureLimitsList {
	CoolingTypeAndTemperatureLimits(PASSIVE_COOLING, 0, 35),
	CoolingTypeAndTemperatureLimits(HI_ACTIVE_COOLING, 0, 45),
	CoolingTypeAndTemperatureLimits(MED_ACTIVE_COOLING, 0, 40)
};

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) {
    return TOO_LOW;
  }
  if(value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

CoolingTypeAndTemperatureLimits getTemperatureLimitsForCoolingType(CoolingType coolingType)
{
   ::std::vector<CoolingTypeAndTemperatureLimits>::iterator it;
   for(it = coolingTypeAndTemperatureLimitsList.begin(); it < coolingTypeAndTemperatureLimitsList.end(); it++)
   {
	   if(it->m_coolingType == coolingType)
	   {
		  break;
	   }
   }
   return *it;
}

BreachType classifyTemperatureBreach(
    CoolingType coolingType, double temperatureInC) {
		
  CoolingTypeAndTemperatureLimits coolingTypeAndTemperatureLimits = getTemperatureLimitsForCoolingType(coolingType);

  return inferBreach(temperatureInC, coolingTypeAndTemperatureLimits.m_lowerLimit, coolingTypeAndTemperatureLimits.m_upperLimit);
}

void checkAndAlert(
    AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {

  BreachType breachType = classifyTemperatureBreach(
    batteryChar.coolingType, temperatureInC
  );

  switch(alertTarget) {
    case TO_CONTROLLER:
      sendToController(breachType);
      break;
    case TO_EMAIL:
      sendToEmail(breachType);
      break;
  }
}

void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void printBreachType(BreachType breachType)
{
   const char* recepient = "a.b@c.com";
    printf("To: %s\n", recepient);
    if(TOO_LOW == breachType)
    {
      printf("Hi, the temperature is too low\n");
    }
    else
    {
      printf("Hi, the temperature is too high\n");
    }
}
void sendToEmail(BreachType breachType)
{
  if(NORMAL != breachType)
  {
      printBreachType(breachType);
  }
}
