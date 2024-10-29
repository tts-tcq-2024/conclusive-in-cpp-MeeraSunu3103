#include "typewise-alert.h"

void printStringToConsole(std::string inputString) {
  std::cout << inputString;
}

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) {
    return TOO_LOW;
  }
  if(value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

void setLowerAndUpperLimits(int lowerLimitList[] ,int upperLimitList[]) {
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

std::string getHeaderString(const int header) {
  std::ostringstream headerStringStream;
  headerStringStream << std::hex << header;
  return (headerStringStream.str());
}

std::string getControllerMessage(const int header, BreachType breachType) {
  return (getHeaderString(header) + " : " + std::to_string(breachType) + "\n");
}

void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printStringToConsole(getControllerMessage(header, breachType));
}

void setEmailMessage(std::string *message, std::string recepient) {
  message[TOO_LOW]  = "To: " +  recepient + "\nHi, the temperature is too low\n";
  message[TOO_HIGH] = "To: " +  recepient + "\nHi, the temperature is too high\n";
  message[NORMAL]   = "";
}

void sendToEmail(BreachType breachType) {
  const std::string recepient = "a.b@c.com";
  std::string message[noOfBreachTypes];
  setEmailMessage(message, recepient);
  printStringToConsole(message[breachType]);
}
