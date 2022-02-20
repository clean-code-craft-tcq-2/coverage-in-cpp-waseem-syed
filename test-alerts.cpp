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
	CoolingTypeAndTemperatureLimits coolingTypePassiveAndTemperatureLimits(PASSIVE_COOLING, 0, 35);
	REQUIRE(getTemperatureLimitsForCoolingType(PASSIVE_COOLING) == coolingTypePassiveAndTemperatureLimits);
	
  CoolingTypeAndTemperatureLimits coolingTypeHIActiveAndTemperatureLimits(HI_ACTIVE_COOLING, 0, 45);
	REQUIRE(getTemperatureLimitsForCoolingType(HI_ACTIVE_COOLING) == coolingTypeHIActiveAndTemperatureLimits);
	
	CoolingTypeAndTemperatureLimits coolingTypeMedActiveAndTemperatureLimits(MED_ACTIVE_COOLING, 0, 40);
	REQUIRE(getTemperatureLimitsForCoolingType(MED_ACTIVE_COOLING) == coolingTypeMedActiveAndTemperatureLimits);
}
