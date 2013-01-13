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

#ifndef STROMX_RUNTIME_ENUM_H
#define STROMX_RUNTIME_ENUM_H

#include "Primitive.h"

namespace stromx
{
    namespace runtime
    {
        /** \brief Value of an enumeration. */
        class STROMX_RUNTIME_API Enum : public UInt32
        {
        public:
            /** Constructs an enumeration value and initializes it to 0. */
            Enum() : UInt32() {}
            
            /** Constructs an enumeration value and initializes it to \c value. */
            Enum(const unsigned int value) : UInt32(value) {}
            
            virtual const DataVariant & variant() const { return DataVariant::ENUM; }
            virtual const std::string & type() const { return TYPE; }
            virtual Data* clone() const { return new Enum(*this); }
            
        private:
            static const std::string TYPE;
        };
    }
}

#endif // STROMX_RUNTIME_ENUM_H
