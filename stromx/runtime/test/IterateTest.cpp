/* 
*  Copyright 2015 Matthias Fuchs
*
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
*/

#include "stromx/runtime/test/IterateTest.h"

#include <cppunit/TestAssert.h>

#include "stromx/runtime/DataContainer.h"
#include "stromx/runtime/Iterate.h"
#include "stromx/runtime/OperatorTester.h"
#include "stromx/runtime/ReadAccess.h"
#include "stromx/runtime/test/TestData.h"

CPPUNIT_TEST_SUITE_REGISTRATION (stromx::runtime::IterateTest);

namespace stromx
{
    using namespace runtime;

    namespace runtime
    {
        void IterateTest::setUp ( void )
        {
            m_operator = new runtime::OperatorTester(new Iterate());
        }
        
        void IterateTest::testExecute()
        {
            m_operator->initialize();
            m_operator->activate();
        }
        
        void IterateTest::tearDown ( void )
        {
            delete m_operator;
        }
    }
}
