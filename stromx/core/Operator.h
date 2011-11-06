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

#ifndef STROMX_CORE_OPERATOR_H
#define STROMX_CORE_OPERATOR_H

#include <map>
#include <string>
#include "DataContainer.h"
#include "Exception.h"
#include "OperatorInfo.h"

namespace stromx
{
    namespace core
    {
        class Data;
        class Id2DataMapper;
        class OperatorInfo;
        class OperatorKernel;
        
        namespace impl
        {
            class InputNode;
            class Network;
            class OutputNode;
            class SynchronizedOperatorKernel;
        }
        
        /**
         * \brief Abstract operator
         * 
         * Operators are the core elements of a stream. The have inputs and outputs which
         * can be connected to other operators of the same stream. Moreover, it is possible
         * to access these inputs and outputs from outside to pass data to the stream or
         * obtain data from it.
         * 
         * Moreover, each operator has a current status and a number of parameters. If the 
         * value of a specific parameter can be read or written dependes on the current status
         * of the operators.
         */
        class Operator
        {
            friend class FactoryTest;
            friend class impl::Network;
            friend class InputNodeTest;
            friend class NetworkTest;
            friend class OperatorTester;
            friend class OutputNodeTest;
            friend class ThreadImplTest;
            friend class Thread;
            
        public:
            /** The possible states of an operator */
            enum Status
            {
                /** The default status of an operator after instantiation */
                NONE,
                /** The is initialized but not ready to process data */
                INITIALIZED,
                /** The operator is ready to process data */
                ACTIVE,
                /** The operator is actively processing data */
                EXECUTING
            };
            
            /** 
             * Constructs an operator from an operator kernel
             * 
             * \param kernel The operator deletes \c kernel upon its destruction.
             */
            Operator(OperatorKernel* const kernel);
            
            virtual ~Operator();
            
            /** Returns the name of the operator */
            const std::string & name() const { return m_name; }
            
            /** 
             * Sets the name of the operator. The name is for informal
             * use only and does not have any effect on the functionality
             * of the operator.
             */
            void setName(const std::string & name) { m_name = name; }
            
            /** 
             * Returns information about the inputs, outputs and parameters
             * of the operator
             */
            const OperatorInfo* const info() const;
            
            /** Returns the current status of the operator */
            const Status status() const;
            
            /** Sets a parameter \c id to \c value */
            void setParameter(const unsigned int id, const Data& value);
            
            /** Gets the current value of the parameter \c id */
            const Data& getParameter(const unsigned int id) const;
            
            /** 
             * Obtains the current value of the parameter \c id and 
             * attempts to cast it to \c data_t
             * 
             * \throw BadCast If the value can not be casted to \c data_t
             */
            template<typename data_t>
            const data_t& getParameter(unsigned int id) const
            {
                try
                {
                    return dynamic_cast<const data_t &>(getParameter(id));
                }
                catch(std::bad_cast &)
                {
                    throw BadCast();
                }
            }
            
            /**
             * Waits for data at the output ID and returns it. The data is 
             * \em not removed by this function and will still be available
             * and block the output. Use clearOutputData() to remove the output
             * data.
             */
            const DataContainer getOutputData(const unsigned int id) const;
            
            /** 
             * Waits for the input \c to to become empty and then places \c data
             * at the input.
             */
            void setInputData(const unsigned int id, const DataContainer data);
            
            /** Removes any output data from the output \c id */
            void clearOutputData(const unsigned int id);
            
            /** 
             * Initializes the operator if its status is NONE.
             * After a successful call the status is INITIALIZED and can
             * never be set back to NONE.
             * 
             * \throws WrongState If the status is not NONE
             */
            void initialize();
            
        private:
            impl::InputNode* const getInputNode(const unsigned int id) const;
            impl::OutputNode* const getOutputNode(const unsigned int id) const;
            void activate();
            void deactivate();
            
            std::string m_name;
            impl::SynchronizedOperatorKernel* m_kernel;
            std::map<unsigned int, impl::OutputNode*> m_outputs;
            std::map<unsigned int, impl::InputNode*> m_inputs;
        };
    }
}

#endif // STROMX_CORE_OPERATOR_H