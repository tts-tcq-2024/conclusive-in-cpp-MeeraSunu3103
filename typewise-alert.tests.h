#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "typewise-alert.h"

class mockClass {
  public:
    MOCK_METHOD(void, printStringToConsole, (std::string inputString), ());
};

mockClass* globalMockObject;

void printStringToConsole(std::string inputString) {
  globalMockObject->printStringToConsole(inputString);
}