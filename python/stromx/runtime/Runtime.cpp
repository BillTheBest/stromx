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
#include <stromx/runtime/Block.h>
#include <stromx/runtime/Compare.h>
#include <stromx/runtime/ConstData.h>
#include <stromx/runtime/Counter.h>
#include <stromx/runtime/Dump.h>
#include <stromx/runtime/Filter.h>
#include <stromx/runtime/Fork.h>
#include <stromx/runtime/Join.h>
#include <stromx/runtime/Merge.h>
#include <stromx/runtime/PeriodicDelay.h>
#include <stromx/runtime/Push.h>
#include <stromx/runtime/Queue.h>
#include <stromx/runtime/Receive.h>
#include <stromx/runtime/Registry.h>
#include <stromx/runtime/Repeat.h>
#include <stromx/runtime/Send.h>
#include <stromx/runtime/Split.h>
#include "ExportOperatorKernel.h"

void exportAssignThreadsAlgorithm();
void exportAbstractFactory();
void exportFactory();
void exportColor();
void exportData();
void exportDataContainer();
void exportDescription();
void exportDescriptionBase();
void exportException();
void exportExceptionObserver();
void exportFile();
void exportImage();
void exportInputProvider();
void exportConnector();
void exportConnectorObserver();
void exportList();
void exportMatrix();
void exportNone();
void exportOperator();
void exportOperatorInfo();
void exportOperatorKernel();
void exportOutputProvider();
void exportParameter();
void exportPosition();
void exportPrimitive();
void exportReadAccess();
void exportRegistry();
void exportSortInputsAlgorithm();
void exportStream();
void exportString();
void exportThread();
void exportTribool();
void exportTriggerData();
void exportVariant();
void exportVariantHandle();
void exportVariantInterface();
void exportVersion();
void exportVisualizationVariant();
void exportWriteAccess();
void exportXmlReader();
void exportXmlWriter();

BOOST_PYTHON_MODULE(libruntime)
{
    using namespace boost::python;
    
    PyEval_InitThreads();
    
    def("version", version);
    
    exportAssignThreadsAlgorithm();
    exportAbstractFactory();
    exportColor();
    exportData();
    exportDataContainer();
    exportDescriptionBase();
    exportDescription();
    exportException();
    exportExceptionObserver();
    exportFile();
    exportMatrix();
    exportImage();
    exportInputProvider();
    exportConnector();
    exportConnectorObserver();
    exportList();
    exportNone();
    exportOperator();
    exportOperatorInfo();
    exportOperatorKernel();
    exportOutputProvider();
    exportParameter();
    exportPosition();
    exportPrimitive();
    exportReadAccess();
    exportRegistry();
    exportSortInputsAlgorithm();
    exportFactory();
    exportStream();
    exportString();
    exportThread();
    exportTribool();
    exportVariantInterface();
    exportVariantHandle();
    exportTriggerData();
    exportVariant();
    exportVersion();    
    exportVisualizationVariant();
    exportWriteAccess();
    exportXmlReader();
    exportXmlWriter();
    
    stromx::python::exportOperatorKernel<Block>("Block");
    stromx::python::exportOperatorKernel<Compare>("Compare");
    stromx::python::exportOperatorKernel<ConstData>("ConstData");
    stromx::python::exportOperatorKernel<Dump>("Dump");
    stromx::python::exportOperatorKernel<Queue>("Queue");
    stromx::python::exportOperatorKernel<Counter>("Counter");
    stromx::python::exportOperatorKernel<Filter>("Filter");
    stromx::python::exportOperatorKernel<Fork>("Fork");
    stromx::python::exportOperatorKernel<Join>("Join");
    stromx::python::exportOperatorKernel<Merge>("Merge");
    stromx::python::exportOperatorKernel<PeriodicDelay>("PeriodicDelay");
    stromx::python::exportOperatorKernel<Push>("Push");
    stromx::python::exportOperatorKernel<Receive>("Receive");
    stromx::python::exportOperatorKernel<Repeat>("Repeat");
    stromx::python::exportOperatorKernel<Send>("Send");
    stromx::python::exportOperatorKernel<Split>("Split");
}