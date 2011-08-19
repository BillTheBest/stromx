#ifndef STREAM_PRIMITIVETEST_H
#define STREAM_PRIMITIVETEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <stream/Primitive.h>

namespace stream
{
    class PrimitiveTest : public CPPUNIT_NS :: TestFixture
    {
        CPPUNIT_TEST_SUITE (PrimitiveTest);
        CPPUNIT_TEST(testInt32);
        CPPUNIT_TEST(testUInt32);
        CPPUNIT_TEST(testInt8);
        CPPUNIT_TEST(testUInt8);
        CPPUNIT_TEST_SUITE_END ();

    public:
        PrimitiveTest() {}
        
        void setUp() {}
        void tearDown() {}

    protected:
        void testInt32();
        void testUInt32();
        void testInt8();
        void testUInt8();
            
    private: 
        Int8 m_int8;
        UInt8 m_uint8;
        Int32 m_int32;
        UInt32 m_uint32;
    };
}

#endif // STREAM_PRIMITIVETEST_H