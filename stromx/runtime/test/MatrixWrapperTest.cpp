/* 
*  Copyright 2013 Matthias Fuchs
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

#include "stromx/runtime/test/MatrixWrapperTest.h"

#include <cppunit/TestAssert.h>
#include <opencv2/core/core.hpp>
#include "stromx/runtime/DirectoryFileInput.h"
#include "stromx/runtime/DirectoryFileOutput.h"
#include "stromx/runtime/MatrixWrapper.h"
#include "stromx/runtime/Variant.h"
#include "stromx/runtime/test/MatrixImpl.h"

CPPUNIT_TEST_SUITE_REGISTRATION (stromx::runtime::MatrixWrapperTest);

namespace stromx
{
    namespace runtime
    {
        const stromx::runtime::Version MatrixWrapperTest::VERSION(STROMX_RUNTIME_VERSION_MAJOR, STROMX_RUNTIME_VERSION_MINOR, STROMX_RUNTIME_VERSION_PATCH);
        
        void MatrixWrapperTest::setUp ( void )
        {
            m_matrix = 0;
        }
        
        void MatrixWrapperTest::testDeserializeFloat64()
        {
            m_matrix = new MatrixImpl();
            
            runtime::DirectoryFileInput input(".");
            input.initialize("", "double_matrix.npy");
            CPPUNIT_ASSERT_NO_THROW(m_matrix->deserialize(input, VERSION));
            CPPUNIT_ASSERT_EQUAL((unsigned int)(50), m_matrix->rows());
            CPPUNIT_ASSERT_EQUAL((unsigned int)(100), m_matrix->cols());
            CPPUNIT_ASSERT_EQUAL(Matrix::FLOAT_64, m_matrix->valueType());
            
            const uint8_t* rowPtr = m_matrix->data();
            for(unsigned int i = 0; i < m_matrix->rows(); ++i)
            {
                double* doubleData = (double*)(rowPtr);
                for(unsigned int j = 0; j < m_matrix->cols(); ++j)
                    CPPUNIT_ASSERT_EQUAL(double(0), doubleData[j]);
                rowPtr += m_matrix->stride();
            }
        }

        void MatrixWrapperTest::testDeserializeUInt16()
        {
            m_matrix = new MatrixImpl();
            
            runtime::DirectoryFileInput input(".");
            input.initialize("", "uint16_matrix.npy");
            CPPUNIT_ASSERT_NO_THROW(m_matrix->deserialize(input, VERSION));
            CPPUNIT_ASSERT_EQUAL((unsigned int)(3), m_matrix->rows());
            CPPUNIT_ASSERT_EQUAL((unsigned int)(4), m_matrix->cols());
            CPPUNIT_ASSERT_EQUAL(Matrix::UINT_16, m_matrix->valueType());
            
            const uint8_t* rowPtr = m_matrix->data();
            for(unsigned int i = 0; i < m_matrix->rows(); ++i)
            {
                uint16_t* uint16Data = (uint16_t*)(rowPtr);
                for(unsigned int j = 0; j < m_matrix->cols(); ++j)
                    CPPUNIT_ASSERT_EQUAL(uint16_t(4 * i + j), uint16Data[j]);
                rowPtr += m_matrix->stride();
            }
        }

        void MatrixWrapperTest::testDeserializeFortranOrder()
        {
            m_matrix = new MatrixImpl();

            runtime::DirectoryFileInput input(".");
            input.initialize("", "fortran_order.npy");
            CPPUNIT_ASSERT_NO_THROW(m_matrix->deserialize(input, VERSION));
            CPPUNIT_ASSERT_EQUAL((unsigned int)(3), m_matrix->rows());
            CPPUNIT_ASSERT_EQUAL((unsigned int)(4), m_matrix->cols());
            CPPUNIT_ASSERT_EQUAL(Matrix::UINT_16, m_matrix->valueType());

            const uint8_t* rowPtr = m_matrix->data();
            for(unsigned int i = 0; i < m_matrix->rows(); ++i)
            {
                uint16_t* uint16Data = (uint16_t*)(rowPtr);
                for(unsigned int j = 0; j < m_matrix->cols(); ++j)
                    CPPUNIT_ASSERT_EQUAL(uint16_t(4 * i + j), uint16Data[j]);
                rowPtr += m_matrix->stride();
            }
        }

        void MatrixWrapperTest::testDeserializeEmpty()
        {
            m_matrix = new MatrixImpl();
            
            runtime::DirectoryFileInput input(".");
            input.initialize("", "empty_float_matrix.npy");
            CPPUNIT_ASSERT_NO_THROW(m_matrix->deserialize(input, VERSION));
            CPPUNIT_ASSERT_EQUAL((unsigned int)(100), m_matrix->rows());
            CPPUNIT_ASSERT_EQUAL((unsigned int)(0), m_matrix->cols());
            CPPUNIT_ASSERT_EQUAL(Matrix::FLOAT_32, m_matrix->valueType());
        }
        
        void MatrixWrapperTest::testSerializeInt16()
        {
            m_matrix = new MatrixImpl(200, 100, Matrix::INT_16);
            memset(m_matrix->data(), 0, m_matrix->rows() * m_matrix->stride());

            runtime::DirectoryFileOutput output(".");
            output.initialize("MatrixTest_testSerializeInt16");
            
            CPPUNIT_ASSERT_NO_THROW(m_matrix->serialize(output));
            CPPUNIT_ASSERT_EQUAL(std::string(""), output.getText());
        }
        
        void MatrixWrapperTest::testSerializeUInt8()
        {
            m_matrix = new MatrixImpl(20, 10, Matrix::UINT_8);
            memset(m_matrix->data(), 0, m_matrix->rows() * m_matrix->stride());

            runtime::DirectoryFileOutput output(".");
            output.initialize("MatrixTest_testSerializeUInt8");
            
            CPPUNIT_ASSERT_NO_THROW(m_matrix->serialize(output));
            CPPUNIT_ASSERT_EQUAL(std::string(""), output.getText());
        }

        void MatrixWrapperTest::testSerializeEmpty()
        {
            m_matrix = new MatrixImpl(0, 100, Matrix::INT_8);

            runtime::DirectoryFileOutput output(".");
            output.initialize("MatrixTest_testSerializeEmpty");
            
            CPPUNIT_ASSERT_NO_THROW(m_matrix->serialize(output));
            CPPUNIT_ASSERT_EQUAL(std::string(""), output.getText());
        }
        
        void MatrixWrapperTest::testResizeLength()
        {
            m_matrix = new MatrixImpl();
            CPPUNIT_ASSERT_NO_THROW(m_matrix->resize(300, 200, runtime::Matrix::FLOAT_32));
            CPPUNIT_ASSERT_EQUAL((unsigned int)(300), m_matrix->rows());
            CPPUNIT_ASSERT_EQUAL((unsigned int)(200), m_matrix->cols());
            CPPUNIT_ASSERT(m_matrix->data());
            CPPUNIT_ASSERT_EQUAL(runtime::Matrix::FLOAT_32, m_matrix->valueType());
            CPPUNIT_ASSERT_EQUAL(runtime::Variant::FLOAT_32_MATRIX, m_matrix->variant());
        }

        void MatrixWrapperTest::testResizeDimension()
        {
            m_matrix = new MatrixImpl();
            CPPUNIT_ASSERT_NO_THROW(m_matrix->resize(1024));
            CPPUNIT_ASSERT_EQUAL((unsigned int)(1024), m_matrix->bufferSize());
        }
        
        void MatrixWrapperTest::testAt()
        {
            MatrixImpl matrix(3, 2, Matrix::INT_32);
            
            CPPUNIT_ASSERT_NO_THROW(matrix.at<int32_t>(0, 1) = 42);
            CPPUNIT_ASSERT_EQUAL((int32_t)(42), const_cast<const MatrixImpl &>(matrix).at<int32_t>(0,1));
        }
        
        void MatrixWrapperTest::testValue()
        {
            MatrixImpl matrix(3, 2, Matrix::INT_32);
            
            CPPUNIT_ASSERT_NO_THROW(matrix.at<int32_t>(0, 1) = 42);
            CPPUNIT_ASSERT_EQUAL((uint8_t)(42), matrix.value<uint8_t>(0, 1));
            CPPUNIT_ASSERT_EQUAL((uint16_t)(42), matrix.value<uint16_t>(0, 1));
            CPPUNIT_ASSERT_EQUAL((uint32_t)(42), matrix.value<uint32_t>(0, 1));
            CPPUNIT_ASSERT_EQUAL((int8_t)(42), matrix.value<int8_t>(0, 1));
            CPPUNIT_ASSERT_EQUAL((int16_t)(42), matrix.value<int16_t>(0, 1));
            CPPUNIT_ASSERT_EQUAL((int32_t)(42), matrix.value<int32_t>(0, 1));
            CPPUNIT_ASSERT_EQUAL((float)(42), matrix.value<float>(0, 1));
            CPPUNIT_ASSERT_EQUAL((double)(42), matrix.value<double>(0, 1));
        }
        
        void MatrixWrapperTest::testAtWrongPosition()
        {
            MatrixImpl matrix(3, 2, Matrix::INT_32);
            
            CPPUNIT_ASSERT_THROW(matrix.at<int8_t>(0, 2) = 42, WrongArgument);
            CPPUNIT_ASSERT_THROW(matrix.at<int8_t>(3, 0) = 42, WrongArgument);
        }
        
        void MatrixWrapperTest::testEquality()
        {
            MatrixImpl lhs(3, 2, Matrix::INT_32);
            MatrixImpl rhs(3, 2, Matrix::INT_32);
            
            for (unsigned int i = 0; i < 3; ++i)
            {
                for (unsigned int j = 0; j < 2; ++j)
                {
                    lhs.at<int32_t>(i, j) = i + j;
                    rhs.at<int32_t>(i, j) = i + j;
                }
            }
            
            CPPUNIT_ASSERT(lhs == rhs);
        }
        
        void MatrixWrapperTest::testEqualityWrongEntry()
        {
            MatrixImpl lhs(3, 2, Matrix::INT_32);
            MatrixImpl rhs(3, 2, Matrix::INT_32);
            
            for (unsigned int i = 0; i < 3; ++i)
            {
                for (unsigned int j = 0; j < 2; ++j)
                {
                    lhs.at<int32_t>(i, j) = i + j;
                    rhs.at<int32_t>(i, j) = i + j;
                }
            }
            
            rhs.at<int32_t>(1, 1) = 0;
            
            CPPUNIT_ASSERT(! (lhs == rhs));
        }
        
        void MatrixWrapperTest::testEqualityWrongDimension()
        {
            MatrixImpl lhs(3, 2, Matrix::INT_32);
            MatrixImpl rhs(3, 2, Matrix::UINT_32);
            
            CPPUNIT_ASSERT(! (lhs == rhs));
        }
        
        void MatrixWrapperTest::testEqualityWrongValueType()
        {
            MatrixImpl lhs(3, 2, Matrix::INT_32);
            MatrixImpl rhs(2, 2, Matrix::INT_32);
            
            CPPUNIT_ASSERT(! (lhs == rhs));
        }

        void MatrixWrapperTest::testAtWrongType()
        {
            MatrixImpl matrix(3, 2, Matrix::INT_32);
            
            CPPUNIT_ASSERT_THROW(matrix.at<int8_t>(0, 1) = 42, WrongArgument);
        }
            
        void MatrixWrapperTest::tearDown ( void )
        {
            delete m_matrix;
        }
    }
}
