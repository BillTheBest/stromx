/* 
*  Copyright 2012 Matthias Fuchs
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

#include <stromx/runtime/String.h>

#include <boost/lambda/lambda.hpp>
#include <boost/python.hpp>

using namespace boost::python;
using namespace stromx::runtime;

namespace
{   
    boost::shared_ptr<String> allocateFromString(const std::string & value)
    {
        return boost::shared_ptr<String>(new String(value), boost::lambda::_1);
    }
    
    boost::shared_ptr<String> allocate()
    {
        return boost::shared_ptr<String>(new String(), boost::lambda::_1);
    }
}

void exportString()
{
    class_<String, bases<Data>, boost::shared_ptr<String> >("String", no_init)
        .def("__init__", make_constructor(&allocate))
        .def("__init__", make_constructor(&allocateFromString))
        .def("get", &String::get, return_value_policy<copy_const_reference>())
        .def(self == self)
        .def(self != self)
    ;
}