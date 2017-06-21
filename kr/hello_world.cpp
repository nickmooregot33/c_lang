




class hello_world_test : public CpppUnit::TestCase {
public:
  hello_world_test(std::string name):CppUnit::TestCase(name){}

  void runTest(){
    CPPUNIT_ASSERT(strcmp(hello_world(),"hello world") == 0);
  }
};
