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
