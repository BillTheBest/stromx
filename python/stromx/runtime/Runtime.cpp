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

#include <boost/python.hpp>
#include <stromx/runtime/Runtime.h>
#include <stromx/runtime/Counter.h>
#include <stromx/runtime/Dump.h>
#include <stromx/runtime/PeriodicDelay.h>
#include <stromx/runtime/Queue.h>
#include <stromx/runtime/Trigger.h>
#include <stromx/runtime/Receive.h>
#include <stromx/runtime/Registry.h>
#include <stromx/runtime/Send.h>
#include "ExportOperatorKernel.h"

void exportAbstractFactory();
void exportFactory();
void exportData();
void exportDataContainer();
void exportDataVariant();
void exportDescription();
void exportException();
void exportExceptionObserver();
void exportImage();
void exportConnector();
void exportConnectorObserver();
void exportMatrix();
void exportNone();
void exportOperator();
void exportOperatorException();
void exportOperatorInfo();
void exportOperatorKernel();
void exportParameter();
void exportPrimitive();
void exportReadAccess();
void exportRegistry();
void exportSortInputsAlgorithm();
void exportStream();
void exportString();
void exportThread();
void exportVersion();
void exportWriteAccess();
void exportXmlReader();
void exportXmlWriter();

BOOST_PYTHON_MODULE(libruntime)
{
    using namespace boost::python;
    
    def("register", stromxRuntimeRegister);
    
    exportAbstractFactory();
    exportData();
    exportDataContainer();
    exportDataVariant();
    exportDescription();
    exportException();
    exportExceptionObserver();
    exportMatrix();
    exportImage();
    exportConnector();
    exportConnectorObserver();
    exportNone();
    exportOperator();
    exportOperatorException();
    exportOperatorInfo();
    exportOperatorKernel();
    exportParameter();
    exportPrimitive();
    exportReadAccess();
    exportRegistry();
    exportSortInputsAlgorithm();
    exportFactory();
    exportStream();
    exportString();
    exportThread();
    exportVersion();    
    exportWriteAccess();
    exportXmlReader();
    exportXmlWriter();
    
    stromx::python::exportOperatorKernel<Dump>("Dump");
    stromx::python::exportOperatorKernel<Queue>("Queue");
    stromx::python::exportOperatorKernel<Counter>("Counter");
    stromx::python::exportOperatorKernel<PeriodicDelay>("PeriodicDelay");
    stromx::python::exportOperatorKernel<Receive>("Receive");
    stromx::python::exportOperatorKernel<Send>("Send");
    stromx::python::exportOperatorKernel<Trigger>("Trigger");
}