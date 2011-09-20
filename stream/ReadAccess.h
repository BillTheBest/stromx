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

#ifndef STREAM_READACCESS_H
#define STREAM_READACCESS_H

#include <tr1/memory>
#include "DataContainer.h"

namespace stream
{
    class Data;
    class DataContainer;
    
    namespace impl
    {
        class ReadAccessImpl;
    }
    
    class ReadAccess
    {
    public:
        ReadAccess(DataContainer data);
        
        const Data & operator()();
        
    private:
        ReadAccess();
        std::tr1::shared_ptr<impl::ReadAccessImpl> m_impl;
    };
}

#endif // STREAM_READACCESS_H
