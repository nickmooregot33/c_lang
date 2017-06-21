#include"hello_world.h"
#include<cppunit/CompilerOutputter.h>
#include<cppunit/extensions/TestFactoryRegistry.h>
#include<cppunit/ui/text/TestRunner.h>

int main(
	 int argc, 
	 char *argv[]
	 )
{
  using namespace CppUnit;

  //Get the top level suite from the registry
  //CppUnit::
  Test *Suite = TestFactoryRegistry::getRegistry().makeTest();

  //Adds the test to the list of test to run
  //CppUnit::
  TextUi::TestRunner runner;
  
  runner.addTest(suite);

  //Change the default outputter to a compiler error format outputter
  runner.setOutputter(new CompilerOutputter(&runner.Result(), std::cerr));
  
  //run the tests
  bool wasSuccessful = runner.run();

  //return error code 1 if one of the tests failed
  return wasSuccessful ? 0 : 1;
  

}
