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

#include <stromx/core/XmlWriter.h>
#include <stromx/core/Stream.h>

#include <boost/python.hpp>

using namespace boost::python;
using namespace stromx::core;

namespace
{
    void (XmlWriter::*writeStreamToFileWrap)(const std::string &, const Stream&) const = &XmlWriter::writeStream;
    void (XmlWriter::*writeParametersToFileWrap)(const std::string&, const std::vector<stromx::core::Operator*>&) const = &XmlWriter::writeParameters;
}

void exportXmlWriter()
{    
    class_<XmlWriter>("XmlWriter", init<>())
        .def("writeStream", writeStreamToFileWrap)
        .def("writeParameters", writeParametersToFileWrap)
    ;
}