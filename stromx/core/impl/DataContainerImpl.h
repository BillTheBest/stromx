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

#ifndef STROMX_CORE_IMPL_DATACONTAINERIMPL_H
#define STROMX_CORE_IMPL_DATACONTAINERIMPL_H

#include <boost/thread/condition_variable.hpp>
#include <boost/thread/mutex.hpp>
#include "../Config.h"

namespace stromx
{
    namespace core
    {
        class Data;
        class Recycler;
        
        namespace impl
        {
            class DataContainerImpl
            {
            public:
                DataContainerImpl(Data* data);
                ~DataContainerImpl();
                
                void getReadAccess(const bool waitWithTimeout, const unsigned int timeout);
                void returnReadAccess();
                
                void getWriteAccess(const bool waitWithTimeout, const unsigned int timeout);
                void returnWriteAccess();
                
                void getRecycleAccess(Recycler* const recycler);
                void returnRecycleAccess();
                
                Data* data() const { return m_data; }
                
            private:
                typedef boost::lock_guard<boost::mutex> lock_t;
                typedef boost::unique_lock<boost::mutex> unique_lock_t;
                
                boost::mutex m_mutex;
                boost::condition_variable_any m_cond;
                
                void recycle();
                
                unsigned int m_readAccessCounter;
                bool m_writeAccess;
                Recycler* m_recycleAccess;
                Data* m_data;
            };
        }
    }
}

#endif // STROMX_CORE_IMPL_DATACONTAINERIMPL_H
