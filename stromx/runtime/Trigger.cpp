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

#include <boost/thread/condition_variable.hpp>
#include <boost/thread/mutex.hpp>
#include "stromx/runtime/DataContainer.h"
#include "stromx/runtime/DataProvider.h"
#include "stromx/runtime/EnumParameter.h"
#include "stromx/runtime/Id2DataPair.h"
#include "stromx/runtime/OperatorException.h"
#include "stromx/runtime/Trigger.h"

namespace stromx
{
    using namespace runtime;

    namespace runtime
    {
        typedef boost::unique_lock<boost::mutex> unique_lock_t;
        
        /** \cond */
        namespace impl
        {
            struct BoostConditionVariable
            {
                boost::condition_variable_any m_cond;
                boost::mutex m_mutex;
            };
        }
        /** \endcond */
        
        const std::string Trigger::TYPE("Trigger");
        
        const std::string Trigger::PACKAGE(STROMX_RUNTIME_PACKAGE_NAME);
        const Version Trigger::VERSION(STROMX_RUNTIME_VERSION_MAJOR, STROMX_RUNTIME_VERSION_MINOR, STROMX_RUNTIME_VERSION_PATCH);
        
        Trigger::Trigger()
          : OperatorKernel(TYPE, PACKAGE, VERSION, setupInputs(), setupOutputs(), setupParameters()),
            m_cond(new impl::BoostConditionVariable),
            m_state(TRIGGER_ACTIVE)
        {
        }
        
        Trigger::~Trigger()
        {
            delete m_cond;
        }

        void Trigger::setParameter(unsigned int id, const Data& value)
        {
            try
            {
                switch(id)
                {
                case TRIGGER:
                {
                    // trigger
                    if(TriggerState(int(m_state)) != ALWAYS_STOP)
                        m_cond->m_cond.notify_all();
                    break;
                }
                case STATE:
                {
                    Enum enumValue = data_cast<Enum>(value);
                    
                    switch(int(enumValue))
                    {
                        case ALWAYS_PASS:
                        case ALWAYS_STOP:
                        case TRIGGER_ACTIVE:
                            break;
                        default:
                            throw WrongParameterValue(*parameters()[id], *this);
                    }
                    
                    m_state = enumValue;
                    
                    // make sure the thread does not stop at the condition variable
                    // if the trigger is deactivated
                    if(m_state == ALWAYS_PASS)
                        m_cond->m_cond.notify_all();
                    break;
                }
                default:
                    throw WrongParameterId(id, *this);
                }
            }
            catch(std::bad_cast&)
            {
                throw WrongParameterType(parameter(id), *this);
            }
        }

        const DataRef Trigger::getParameter(const unsigned int id) const
        {
            switch(id)
            {
            case TRIGGER:
                throw ParameterAccessViolation(parameter(id), *this);
            case STATE:
                return m_state;
            default:
                throw WrongParameterId(id, *this);
            }
        }  
        
        void Trigger::execute(DataProvider& provider)
        {
            Id2DataPair inputDataMapper(INPUT);
            provider.receiveInputData(inputDataMapper);
            
            TriggerState state = TriggerState(int(m_state));
            if(state == TRIGGER_ACTIVE || state == ALWAYS_STOP)
            {
                try
                {
                    // wait for trigger
                    unique_lock_t lock(m_cond->m_mutex);
                    
                    // allow to trigger while waiting
                    provider.unlockParameters();
                    m_cond->m_cond.wait(lock);
                }
                catch(boost::thread_interrupted&)
                {
                    throw Interrupt();
                }
            }
            
            Id2DataPair outputDataMapper(OUTPUT, inputDataMapper.data());
            provider.sendOutputData( outputDataMapper);
        }
        
        const std::vector<const runtime::Description*> Trigger::setupInputs()
        {
            std::vector<const Description*> inputs;
            
            Description* input = new Description(OUTPUT, DataVariant::DATA);
            input->setTitle("Input");
            inputs.push_back(input);
            
            return inputs;
        }
        
        const std::vector<const Description*> Trigger::setupOutputs()
        {
            std::vector<const Description*> outputs;
            
            Description* output = new Description(OUTPUT, DataVariant::DATA);
            output->setTitle("Output");
            outputs.push_back(output);
            
            return outputs;
        }
        
        const std::vector<const Parameter*> Trigger::setupParameters()
        {
            std::vector<const runtime::Parameter*> parameters;
            
            Parameter* trigger = new Parameter(TRIGGER, DataVariant::TRIGGER);
            trigger->setTitle("Trigger");
            trigger->setAccessMode(runtime::Parameter::ACTIVATED_WRITE);
            parameters.push_back(trigger);
            
            EnumParameter* state = new EnumParameter(STATE);
            state->setTitle("State");
            state->setAccessMode(runtime::Parameter::ACTIVATED_WRITE);
            state->add(EnumDescription(Enum(ALWAYS_PASS), "Always off"));
            state->add(EnumDescription(Enum(ALWAYS_STOP), "Always on"));
            state->add(EnumDescription(Enum(TRIGGER_ACTIVE), "Trigger active"));
            parameters.push_back(state);
                                        
            return parameters;
        }
    } 
}