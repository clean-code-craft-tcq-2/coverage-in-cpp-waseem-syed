#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits") {
  REQUIRE(inferBreach(12, 20, 30) == TOO_LOW);
  REQUIRE(inferBreach(20, 20, 30) == NORMAL);
  REQUIRE(inferBreach(20, 20, 30) == NORMAL);
  REQUIRE(inferBreach(25, 20, 30) == NORMAL);
  REQUIRE(inferBreach(35, 20, 30) == TOO_HIGH);
}

TEST_CASE("verify limits based on given cooling type")
{
	CoolingTypeAndTemperatureLimits coolingTypeAndTemperatureLimitsResults(PASSIVE_COOLING, 0, 0);//storing some default values
	
	CoolingTypeAndTemperatureLimits coolingTypePassiveAndTemperatureLimits(PASSIVE_COOLING, 0, 35);
	coolingTypeAndTemperatureLimitsResults = getTemperatureLimitsForCoolingType(PASSIVE_COOLING);
	REQUIRE(coolingTypeAndTemperatureLimitsResults.m_coolingType == coolingTypePassiveAndTemperatureLimits.m_coolingType);
	REQUIRE(coolingTypeAndTemperatureLimitsResults.m_lowerLimit == coolingTypePassiveAndTemperatureLimits.m_lowerLimit);
	REQUIRE(coolingTypeAndTemperatureLimitsResults.m_upperLimit == coolingTypePassiveAndTemperatureLimits.m_upperLimit);
	
        CoolingTypeAndTemperatureLimits coolingTypeHIActiveAndTemperatureLimits(HI_ACTIVE_COOLING, 0, 45);
	coolingTypeAndTemperatureLimitsResults = getTemperatureLimitsForCoolingType(HI_ACTIVE_COOLING);
	REQUIRE(coolingTypeAndTemperatureLimitsResults.m_coolingType == coolingTypeHIActiveAndTemperatureLimits.m_coolingType);
	REQUIRE(coolingTypeAndTemperatureLimitsResults.m_lowerLimit == coolingTypeHIActiveAndTemperatureLimits.m_lowerLimit);
	REQUIRE(coolingTypeAndTemperatureLimitsResults.m_upperLimit == coolingTypeHIActiveAndTemperatureLimits.m_upperLimit);
	
	CoolingTypeAndTemperatureLimits coolingTypeMedActiveAndTemperatureLimits(MED_ACTIVE_COOLING, 0, 40);
	coolingTypeAndTemperatureLimitsResults = getTemperatureLimitsForCoolingType(MED_ACTIVE_COOLING) ;
	REQUIRE(coolingTypeAndTemperatureLimitsResults.m_coolingType == coolingTypeMedActiveAndTemperatureLimits.m_coolingType);
	REQUIRE(coolingTypeAndTemperatureLimitsResults.m_lowerLimit == coolingTypeMedActiveAndTemperatureLimits.m_lowerLimit);
	REQUIRE(coolingTypeAndTemperatureLimitsResults.m_upperLimit == coolingTypeMedActiveAndTemperatureLimits.m_upperLimit);
}

TEST_CASE("test temperature breach type based on cooling type")
{ 
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING,36) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING,35) == NORMAL);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING,0) == NORMAL);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING,-1) == TOO_LOW);
  
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING,66) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING,45) == NORMAL);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING,0) == NORMAL);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING,-1) == TOO_LOW);
  
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING,66) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING,40) == NORMAL);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING,0) == NORMAL);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING,-1) == TOO_LOW);

}

TEST_CASE("check alert response")
{
   AlertData alertData;
   alertData.m_alertTarget = TO_CONTROLLER;
   alertData.m_batteryChar.coolingType = PASSIVE_COOLING;
   alertData.m_temperatureInC = 45;
   AlertResponse alertResponse;
   checkAndAlert(alertData, alertResponse);
   REQUIRE(alertResponse.m_isAlertSent == true);
   REQUIRE(alertResponse.m_breachType == TOO_HIGH);


   AlertData alertData1;
   alertData1.m_alertTarget = TO_EMAIL;
   alertData1.m_batteryChar.coolingType = PASSIVE_COOLING;
   alertData1.m_temperatureInC = 45;
   AlertResponse alertResponse1;
   checkAndAlert(alertData1, alertResponse1);
   REQUIRE(alertResponse1.m_isAlertSent == true);
   REQUIRE(alertResponse1.m_breachType == TOO_HIGH);

   AlertData alertData2;
   alertData2.m_alertTarget = TO_EMAIL;
   alertData2.m_batteryChar.coolingType = PASSIVE_COOLING;
   alertData2.m_temperatureInC = -1;
   AlertResponse alertResponse2;
   checkAndAlert(alertData2, alertResponse2);
   REQUIRE(alertResponse2.m_isAlertSent == true);
   REQUIRE(alertResponse2.m_breachType == TOO_LOW);

   AlertData alertData3;
   alertData3.m_alertTarget = TO_CONTROLLER;
   alertData3.m_batteryChar.coolingType = HI_ACTIVE_COOLING;
   alertData3.m_temperatureInC = -1;
   AlertResponse alertResponse3;
   checkAndAlert(alertData3, alertResponse3);
   REQUIRE(alertResponse3.m_isAlertSent == true);
   REQUIRE(alertResponse3.m_breachType == TOO_LOW);

   AlertData alertData4;
   alertData4.m_alertTarget = TO_CONTROLLER;
   alertData4.m_batteryChar.coolingType = HI_ACTIVE_COOLING;
   alertData4.m_temperatureInC = 20;
   AlertResponse alertResponse4;
   checkAndAlert(alertData4, alertResponse4);
   REQUIRE(alertResponse4.m_isAlertSent == true);
   REQUIRE(alertResponse4.m_breachType == NORMAL);

   AlertData alertData5;
   alertData5.m_alertTarget = TO_EMAIL;
   alertData5.m_batteryChar.coolingType = HI_ACTIVE_COOLING;
   alertData5.m_temperatureInC = 20;
   AlertResponse alertResponse5;
   checkAndAlert(alertData5, alertResponse5);
   REQUIRE(alertResponse5.m_isAlertSent == false);
   REQUIRE(alertResponse5.m_breachType == NORMAL);
}

TEST_CASE("test alert for email")
{
   AlertResponse alertResponse;
   alertResponse.m_breachType = NORMAL;
   sendToEmail(alertResponse);
   REQUIRE(alertResponse.m_isAlertSent = false;
	   
   AlertResponse alertResponse1;
   alertResponse1.m_breachType = TOO_HIGH;
   sendToEmail(alertResponse1);
   REQUIRE(alertResponse1.m_isAlertSent = true;

   AlertResponse alertResponse2;
   alertResponse2.m_breachType = TOO_LOW;
   sendToEmail(alertResponse2);
   REQUIRE(alertResponse2.m_isAlertSent = true;
}
