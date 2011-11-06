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

#ifndef STROMX_CORE_DATACONTAINER_H
#define STROMX_CORE_DATACONTAINER_H

#include <tr1/memory>
#include <ostream>

namespace stromx
{
    namespace core
    {
        class Data;
        class DataVariant;
        
        namespace impl
        {
            class ReadAccessImpl;
            class WriteAccessImpl;
            class RecycleAccessImpl;
            class DataContainerImpl;
        }
        
        /** \brief Container which manages the life-cycle of data objects */
        class DataContainer
        {
            friend class impl::WriteAccessImpl;
            friend class impl::ReadAccessImpl;
            friend class impl::RecycleAccessImpl;
            
            friend const bool operator==(const DataContainer & lhs, const DataContainer & rhs); 
            friend const bool operator!=(const DataContainer & lhs, const DataContainer & rhs); 
            friend std::ostream& operator<< (std::ostream& out, const DataContainer & container);
            
        public:
            DataContainer() {}
            explicit DataContainer(core::Data*const data);
            
            const bool empty() const { return m_impl.get() == 0; }
            
        private:
            std::tr1::shared_ptr<impl::DataContainerImpl> m_impl;
        };     
        
        const bool operator==(const DataContainer & lhs, const DataContainer & rhs); 
        const bool operator!=(const DataContainer & lhs, const DataContainer & rhs); 
        std::ostream& operator<< (std::ostream& out, const DataContainer & container);
    }
}

#endif // STROMX_CORE_DATACONTAINER_H