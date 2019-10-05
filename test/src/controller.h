#pragma once

#include <functional>
#include <vector>

namespace CppTest {

    class Controller {

            std::vector<std::function<void()>> testSuites;

        public:

            void addTestSuite(const std::function<void()>& testSuite){
                testSuites.push_back(testSuite);
            } 

            void runAllTestSuites() const {
                for (const auto& suite : testSuites)
                    suite();

                std::cout << "Executed " << testSuites.size() << " test suites.\n";
            }
        
            static Controller& get(){
                static Controller instance; 
                return instance;
            }
        private:
            Controller() {}                    

        public:
            Controller(Controller const&)     = delete;
            void operator=(Controller const&) = delete;

    };

}
