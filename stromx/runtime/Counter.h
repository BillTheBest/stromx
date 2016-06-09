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

#ifndef STROMX_RUNTIME_COUNTER_H
#define STROMX_RUNTIME_COUNTER_H

#include "stromx/runtime/Config.h"
#include "stromx/runtime/OperatorKernel.h"
#include "stromx/runtime/Primitive.h"

namespace stromx
{
    namespace runtime
    {
        /** \brief Outputs an increasing integer value. */
        class STROMX_RUNTIME_API Counter : public OperatorKernel
        {
            STROMX_OPERATOR_KERNEL
            
        public:
            enum DataId
            {
                OUTPUT,
                OUTPUT_OFFSET = 0,
                PARAMETER_OFFSET = 1
            };
            
            Counter();
            
            virtual OperatorKernel* clone() const { return new Counter; }
            virtual void setParameter(const unsigned int id, const runtime::Data& value);
            virtual const DataRef getParameter(const unsigned int id) const;
            virtual void execute(runtime::DataProvider& provider);
            virtual void activate();
            
        private:
            static const std::vector<const runtime::Description*> setupInputs();
            static const std::vector<const runtime::Description*> setupOutputs();
            static const std::vector<const runtime::Parameter*> setupParameters();
            
            static const std::string TYPE;
            static const std::string PACKAGE;
            static const runtime::Version VERSION;
            
            unsigned int m_counter;
        };
    }
}

#endif // STROMX_RUNTIME_COUNTER_H
