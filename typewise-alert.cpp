#include "typewise-alert.h"
#include <stdio.h>

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) {
    return TOO_LOW;
  }
  if(value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

void setLowerAndUpperLimits (int lowerLimitList[] ,int upperLimitList[]) {
  lowerLimitList[PASSIVE_COOLING] = 0;
  upperLimitList[PASSIVE_COOLING] = 35;
  
  lowerLimitList[HI_ACTIVE_COOLING] = 0;
  upperLimitList[HI_ACTIVE_COOLING] = 45;
  
  lowerLimitList[MED_ACTIVE_COOLING] = 0;
  upperLimitList[MED_ACTIVE_COOLING] = 40;
}

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) {
  int lowerLimit[noOfCoolingTypes];
  int upperLimit[noOfCoolingTypes];
  setLowerAndUpperLimits(lowerLimit,upperLimit);
  
  return inferBreach(temperatureInC, lowerLimit[coolingType], upperLimit[coolingType]);
}

void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {

  BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);

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

void sendToEmail(BreachType breachType) {
  const char* recepient = "a.b@c.com";
  switch(breachType) {
    case TOO_LOW:
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too low\n");
      break;
    case TOO_HIGH:
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too high\n");
      break;
    case NORMAL:
      break;
  }
}
