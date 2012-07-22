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

#ifndef STROMX_BASE_IMAGEFILTER_H
#define STROMX_BASE_IMAGEFILTER_H

#include "Config.h"
#include <stromx/core/Enum.h>
#include <stromx/core/Image.h>
#include <stromx/core/OperatorKernel.h>
#include <stromx/core/RecycleAccess.h>


struct _IplImage;

namespace cv
{
    class Mat;
}

namespace stromx
{
    namespace base
    {
        /** \brief Abstract base class of image filters. */
        class STROMX_BASE_API ImageFilter : public core::OperatorKernel
        {
        public:
            enum InputId
            {
                SOURCE,
                DESTINATION
            };
            
            enum OutputId
            {
                OUTPUT
            };
            
            enum ParameterId
            {
                IN_PLACE,
		FILTER_PARAMETERS
            };
            
            ImageFilter(const std::string & type);
            
            virtual void setParameter(const unsigned int id, const core::Data& value);
            virtual const core::Data& getParameter(const unsigned int id) const;
            virtual void execute(core::DataProvider& provider);
            virtual void initialize();
            
        protected:
            virtual const std::vector<const core::Parameter*> setupInitParameters() = 0;
            virtual void applyFilter(const cv::Mat & in, cv::Mat & out) = 0;
            
	private:
            const std::vector<const core::Description*> setupInputs();
            const std::vector<const core::Description*> setupOutputs();
            const std::vector<const core::Parameter*> setupParameters();
	    
            static const std::string PACKAGE;
            static const core::Version VERSION;
            
            core::Bool m_inPlace;
        };
    }
}

#endif // STROMX_BASE_IMAGEFILTER_H
