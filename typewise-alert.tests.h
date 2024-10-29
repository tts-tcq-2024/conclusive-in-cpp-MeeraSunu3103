#include <gtest/gtest.h>
#include <gmock/gmock.h>

class mockClass {
  public:
    MOCK_METHOD(void, printStringToConsole, (std::string inputString), ());
};

mockClass* globalMockObject;
