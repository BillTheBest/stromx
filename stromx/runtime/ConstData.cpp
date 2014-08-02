/* 
*  Copyright 2014 Matthias Fuchs
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

#include "stromx/runtime/ConstData.h"

#include "stromx/runtime/DataContainer.h"
#include "stromx/runtime/DataProvider.h"
#include "stromx/runtime/EnumParameter.h"
#include "stromx/runtime/Id2DataPair.h"
#include "stromx/runtime/OperatorException.h"
#include "stromx/runtime/String.h"
#include "stromx/runtime/TriggerData.h"

namespace stromx
{
    using namespace runtime;

    namespace runtime
    {
        namespace
        {
            DataVariant typeToVariant(const unsigned int type)
            {
                if (type == DataVariant::BOOL.id())
                    return DataVariant::BOOL;
                
                if (type == DataVariant::TRIGGER.id())
                    return DataVariant::TRIGGER;
                
                if (type == DataVariant::INT_32.id())
                    return DataVariant::INT_32;
                
                if (type == DataVariant::UINT_32.id())
                    return DataVariant::UINT_32;
                
                if (type == DataVariant::STRING.id())
                    return DataVariant::STRING;
                
                if (type == DataVariant::FLOAT_32.id())
                    return DataVariant::FLOAT_32;
                    
                throw InternalError("Unhandled data type");
            }
            
            Data* typeToData(const unsigned int type)
            {
                if (type == DataVariant::BOOL.id())
                    return new Bool;
                
                if (type == DataVariant::TRIGGER.id())
                    return new TriggerData;
                
                if (type == DataVariant::INT_32.id())
                    return new Int32;
                
                if (type == DataVariant::UINT_32.id())
                    return new UInt32;
                
                if (type == DataVariant::STRING.id())
                    return new String;
                
                if (type == DataVariant::FLOAT_32.id())
                    return new Float32;
                    
                throw InternalError("Unhandled data type");
            }
        }
        
        const std::string ConstData::TYPE("ConstData");
        const std::string ConstData::PACKAGE(STROMX_RUNTIME_PACKAGE_NAME);
        const Version ConstData::VERSION(0, 1, 0);
        
        ConstData::ConstData()
          : OperatorKernel(TYPE, PACKAGE, VERSION, setupInitParameters()),
            m_type(DataVariant::BOOL.id()),
            m_value(new Bool)
        {
        }
        
        ConstData::~ConstData()
        {
            delete m_value;
        }

        void ConstData::setParameter(unsigned int id, const Data& value)
        {
            try
            {
                switch(id)
                {
                case DATA_TYPE:
                    setDataType(data_cast<Enum>(value));
                    break;
                case VALUE:
                    delete m_value;
                    m_value = value.clone();
                    break;
                default:
                    throw WrongParameterId(id, *this);
                }
            }
            catch(std::bad_cast&)
            {
                throw WrongParameterType(parameter(id), *this);
            }
        }

        const DataRef ConstData::getParameter(const unsigned int id) const
        {
            switch(id)
            {
            case DATA_TYPE:
                return m_type;
            case VALUE:
                if (! m_value)
                    throw InternalError("Value has not been set");
                return *m_value;
            default:
                throw WrongParameterId(id, *this);
            }
        }  
        
        void ConstData::execute(DataProvider& provider)
        {
            if (! m_value)
                throw InternalError("Value has not been set");
            
            DataContainer data(m_value->clone());
            
            Id2DataPair outputDataMapper(OUTPUT, data);
            provider.sendOutputData( outputDataMapper);
        }
        
        void ConstData::initialize()
        {
            OperatorKernel::initialize(setupInputs(), setupOutputs(), setupParameters());
        }
        
        const std::vector<const Description*> ConstData::setupInputs()
        {
            return std::vector<const Description*>();
        }
        
        const std::vector<const Description*> ConstData::setupOutputs()
        {
            std::vector<const Description*> outputs;
            
            Description* output = new Description(OUTPUT, DataVariant::DATA);
            output->setTitle("Output");
            outputs.push_back(output);
            
            return outputs;
        }
        
        const std::vector<const Parameter*> ConstData::setupInitParameters()
        {
            std::vector<const runtime::Parameter*> parameters;
            
            EnumParameter* type = new EnumParameter(DATA_TYPE);
            type->setTitle("Data type");
            type->setAccessMode(runtime::Parameter::NONE_WRITE);
            type->add(EnumDescription(Enum(DataVariant::BOOL.id()), "Bool"));
            type->add(EnumDescription(Enum(DataVariant::TRIGGER.id()), "Trigger"));
            type->add(EnumDescription(Enum(DataVariant::INT_32.id()), "Int32"));
            type->add(EnumDescription(Enum(DataVariant::UINT_32.id()), "UInt32"));
            type->add(EnumDescription(Enum(DataVariant::STRING.id()), "String"));
            type->add(EnumDescription(Enum(DataVariant::FLOAT_32.id()), "Float32"));
            parameters.push_back(type);
                                        
            return parameters;
        }
        
        const std::vector<const Parameter*> ConstData::setupParameters()
        {
            std::vector<const runtime::Parameter*> parameters;
            
            DataVariant variant = typeToVariant(m_type);
            
            Parameter* value = new Parameter(VALUE, variant);
            value->setTitle("Value");
            value->setAccessMode(runtime::Parameter::ACTIVATED_WRITE);
            parameters.push_back(value);
                                        
            return parameters;
        }
        
        void ConstData::setDataType(const Enum& value)
        {
            if (m_type == value)
                return;
            
            // update the type
            m_type = value;
            
            // set the value to a new object of the above type
            delete m_value;
            m_value = 0;
            m_value = typeToData(value);
        }      
    } 
}