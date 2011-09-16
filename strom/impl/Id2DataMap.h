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

#ifndef STROM_IMPL_ID2DATAMAP_H
#define STROM_IMPL_ID2DATAMAP_H


#include "../Description.h"

#include <vector>
#include <map>

namespace strom
{
    class DataContainer;
    
    namespace impl
    {
        class Id2DataMap
        {
        public:
            Id2DataMap();
            Id2DataMap(const std::vector<const Description*> & descriptions);
            
            DataContainer operator[](const unsigned int id) const;
            DataContainer& operator[](const unsigned int id);
            void clear();
            const bool isEmpty() const;
            
        private:
            std::map<unsigned int, DataContainer> m_map;
        };
    }
}

#endif // STROM_IMPL_ID2DATAMAP_H
