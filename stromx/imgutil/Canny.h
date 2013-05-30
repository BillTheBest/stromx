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

#ifndef STROMX_IMGUTIL_CANNY_H
#define STROMX_IMGUTIL_CANNY_H

#include "stromx/imgutil/Image.h"
#include "stromx/imgutil/ImageFilter.h"

namespace stromx
{
    namespace imgutil
    {
        /** \brief Applies the %Canny edge detector. */
        class STROMX_IMGUTIL_API Canny : public ImageFilter
        {
        public:
            enum ParameterId
            {
                THRESHOLD_1 = ImageFilter::FILTER_PARAMETERS,
                THRESHOLD_2
            };
            
            Canny();
            
            virtual OperatorKernel* clone() const { return new Canny; }
            virtual void setParameter(const unsigned int id, const runtime::Data& value);
            virtual const runtime::DataRef getParameter(const unsigned int id) const;
            
        protected:
            virtual const std::vector<const runtime::Parameter*> setupParameters();
            virtual void applyFilter(const cv::Mat & in, cv::Mat & out);
            virtual void validateSourceImage(const runtime::Image & source);
            virtual unsigned int computeDestinationSize(const runtime::Image & source);
            
        private:
            static const std::string TYPE;
            
            runtime::Double m_threshold1;
            runtime::Double m_threshold2;
        };
    }
}

#endif // STROMX_IMGUTIL_CANNY_H