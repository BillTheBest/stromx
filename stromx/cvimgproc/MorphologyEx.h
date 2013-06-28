#ifndef STROMX_CVIMGPROC_MORPHOLOGYEX_H
#define STROMX_CVIMGPROC_MORPHOLOGYEX_H

#include "stromx/cvimgproc/Config.h"
#include <stromx/runtime/Enum.h>
#include <stromx/runtime/EnumParameter.h>
#include <stromx/runtime/NumericParameter.h>
#include <stromx/runtime/OperatorException.h>
#include <stromx/runtime/OperatorKernel.h>
#include <stromx/runtime/Primitive.h>

namespace stromx
{
    namespace cvimgproc
    {
        class STROMX_CVIMGPROC_API MorphologyEx : public runtime::OperatorKernel
        {
        public:
            enum OpId
            {
                MORPH_OPEN,
                MORPH_CLOSE,
                MORPH_GRADIENT,
                MORPH_TOPHAT,
                MORPH_BLACKHAT
            };
            enum ShapeId
            {
                MORPH_RECT,
                MORPH_ELLIPSE,
                MORPH_CROSS
            };
            enum DataFlowId
            {
                MANUAL,
                ALLOCATE,
                IN_PLACE
            };
            enum ConnectorId
            {
                SRC,
                DST
            };
            enum ParameterId
            {
                KSIZEX,
                KSIZEY,
                SHAPE,
                ITERATIONS,
                DATA_FLOW,
                OP
            };
            MorphologyEx();
            virtual OperatorKernel* clone() const { return new MorphologyEx; }
            virtual void setParameter(const unsigned int id, const runtime::Data& value);
            virtual const runtime::DataRef getParameter(const unsigned int id) const;
            void initialize();
            virtual void execute(runtime::DataProvider& provider);
            
        private:
            static const std::string PACKAGE;
            static const runtime::Version VERSION;
            static const std::string TYPE;
            
            const std::vector<const runtime::Parameter*> setupInitParameters();
            const std::vector<const runtime::Parameter*> setupParameters();
            const std::vector<const runtime::Description*> setupInputs();
            const std::vector<const runtime::Description*> setupOutputs();
            
            int convertOp(const runtime::Enum & value);
            int convertShape(const runtime::Enum & value);
            
            runtime::UInt32 m_iterations;
            runtime::UInt32 m_ksizex;
            runtime::UInt32 m_ksizey;
            runtime::Enum m_op;
            runtime::Enum m_shape;
            runtime::Enum m_dataFlow;
            runtime::NumericParameter<runtime::UInt32>* m_iterationsParameter;
            runtime::NumericParameter<runtime::UInt32>* m_ksizexParameter;
            runtime::NumericParameter<runtime::UInt32>* m_ksizeyParameter;
            runtime::EnumParameter* m_opParameter;
            runtime::EnumParameter* m_shapeParameter;
            runtime::EnumParameter* m_dataFlowParameter;
        };
    }
}

#endif // STROMX_CVIMGPROC_MORPHOLOGYEX_H