#ifndef STREAM_OPERATOR_H
#define STREAM_OPERATOR_H

#include "Parameter.h"
#include "Version.h"

#include <vector>

namespace stream
{
    class Data;
    class DataContainer;
    class DataProvider;
    
    class Operator
    {
    public:
        Operator(const unsigned int id,
                 const std::string & name,
                 const Version & version,
                 const std::vector<Description>& inputs,
                 const std::vector<Description>& outputs,
                 const std::vector<Parameter>& parameters);
        
        const std::string& name() { return m_name; }
        const Version& version() { return m_version; }
        const std::vector<Description>& inputs() { return m_inputs; }
        const std::vector<Description>& outputs() { return m_outputs; }
        const std::vector<Parameter>& parameters() { return m_parameters; }
        
        virtual void setParameter(unsigned int id, const Data& value) = 0;
        virtual void getParameter(unsigned int id, Data& value) = 0;
        
        virtual void execute(DataProvider& provider) = 0;
        virtual void activate(DataProvider& provider) {}
        virtual void deactivate() {}
        
    protected: 
        Description& getParameterDescription(unsigned int id);
        
    private:
        static void validate(const std::vector<Description>& descriptors);
        static void validate(const std::vector<Parameter>& descriptors);
        
        unsigned int m_id;
        std::string m_name;
        Version m_version;
        std::vector<Description> m_inputs;
        std::vector<Description> m_outputs;
        std::vector<Parameter> m_parameters;
        
    };
}

#endif // STREAM_OPERATOR_H