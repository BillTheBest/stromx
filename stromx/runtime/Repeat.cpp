/* 
*  Copyright 2015 Matthias Fuchs
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

#include "stromx/runtime/Repeat.h"

#include <boost/assert.hpp>

#include "stromx/runtime/DataProvider.h"
#include "stromx/runtime/Id2DataPair.h"
#include "stromx/runtime/Id2DataComposite.h"
#include "stromx/runtime/Locale.h"
#include "stromx/runtime/NumericParameter.h"
#include "stromx/runtime/OperatorException.h"
#include "stromx/runtime/ReadAccess.h"
#include "stromx/runtime/Variant.h"

namespace 
{
    const static unsigned int INPUT_THREAD = 0;
    const static unsigned int OUTPUT_THREAD = 1;
}

namespace stromx
{
    using namespace runtime;

    namespace runtime
    {
        const std::string Repeat::TYPE("Repeat");
        
        const std::string Repeat::PACKAGE(STROMX_RUNTIME_PACKAGE_NAME);
        const Version Repeat::VERSION(STROMX_RUNTIME_VERSION_MAJOR, STROMX_RUNTIME_VERSION_MINOR, STROMX_RUNTIME_VERSION_PATCH);
        
        Repeat::Repeat()
          : OperatorKernel(TYPE, PACKAGE, VERSION, setupInputs(), setupOutputs()),
            m_currentIteration(0)
        {
        }
        
        void Repeat::activate()
        {
            m_currentIteration = 0;
        }
        
        void Repeat::deactivate()
        {
            m_currentData = DataContainer();
        }
        
        void Repeat::execute(DataProvider& provider)
        {
            if (m_currentData.empty())
            {
                Id2DataPair inputMapper(INPUT);
                Id2DataPair numIterationsMapper(NUM_ITERATIONS);
                provider.receiveInputData(inputMapper && numIterationsMapper);
                m_currentData = inputMapper.data();
                
                ReadAccess access(numIterationsMapper.data());
                
                
                try
                {
                    m_numIterations = toInt(access.get());
                }
                catch (BadCast&)
                {
                    throw InputError(NUM_ITERATIONS, *this, "Number of iterations must be an integer.");
                }
            }
                
            if (m_currentIteration < m_numIterations)
            {
                BOOST_ASSERT(! m_currentData.empty());
                
                Id2DataPair outputMapper(OUTPUT, m_currentData);
                provider.sendOutputData(outputMapper);
                ++m_currentIteration;
            }
            
            if (m_currentIteration >= m_numIterations)
            {
                m_currentData = DataContainer();
                m_currentIteration = 0;
            }
        }
        
        const std::vector<const Input*> Repeat::setupInputs()
        {
            std::vector<const Input*> inputs;
            
            Input* input = new Input(INPUT, Variant::DATA);
            input->setTitle(L_("Input data"));
            input->setOperatorThread(INPUT_THREAD);
            inputs.push_back(input);
            
            Input* numIterations = new Input(NUM_ITERATIONS, Variant::INT);
            numIterations->setTitle(L_("Number of iterations"));
            numIterations->setOperatorThread(INPUT_THREAD);
            inputs.push_back(numIterations);
            
            return inputs;
        }
        
        const std::vector<const Output*> Repeat::setupOutputs()
        {
            std::vector<const Output*> outputs;
            
            Output* output = new Output(OUTPUT, Variant::DATA);
            output->setTitle(L_("Output"));
            output->setOperatorThread(OUTPUT_THREAD);
            outputs.push_back(output);
            
            return outputs;
        }
    } 
}
