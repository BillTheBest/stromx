/* 
*  Copyright 2011 Matthias Fuchs
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

#ifndef STROMX_RUNTIME_WRITEACCESSTEST_H
#define STROMX_RUNTIME_WRITEACCESSTEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>
#include "stromx/runtime/WriteAccess.h"

namespace stromx
{
    namespace runtime
    {
        class Data;
        class DataContainer;
        
        class WriteAccessTest : public CPPUNIT_NS :: TestFixture
        {
            CPPUNIT_TEST_SUITE (WriteAccessTest);
            CPPUNIT_TEST(testWriteAccess);
            CPPUNIT_TEST(testRelease);
            CPPUNIT_TEST(testEmptyWriteAccess);
            CPPUNIT_TEST(testWriteAccessCast);
            CPPUNIT_TEST(testWriteAccessWrongCast);
            CPPUNIT_TEST(testWriteAccessEmptyContainer);
            CPPUNIT_TEST(testWriteAccessReadOnlyContainer);
            CPPUNIT_TEST(testReleaseWriteAccess);
            CPPUNIT_TEST(testWriteAccessDelayed);
            CPPUNIT_TEST(testWriteAccessInterrupt);
            CPPUNIT_TEST(testWriteAccessTimeout);
            CPPUNIT_TEST_SUITE_END ();

        public:
            WriteAccessTest () : m_data(0) {}
            
            void setUp() {}
            void tearDown() { m_data = 0; }

        protected:
            void testWriteAccessEmptyContainer();
            void testWriteAccessReadOnlyContainer();
            void testEmptyWriteAccess();
            void testWriteAccess();
            void testRelease();
            void testWriteAccessCast();
            void testWriteAccessWrongCast();
            void testReleaseWriteAccess();
            void testWriteAccessDelayed();
            void testWriteAccessInterrupt();
            void testWriteAccessTimeout();
                
        private:
            void releaseDelayed(WriteAccess& access);
            void writeAccessInterrupt(DataContainer & container);
            
            Data* m_data;
        };
    }
}

#endif // STROMX_RUNTIME_WRITEACCESSTEST_H