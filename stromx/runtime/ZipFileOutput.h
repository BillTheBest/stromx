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

#ifndef STROMX_RUNTIME_ZIPFILEOUTPUT_H
#define STROMX_RUNTIME_ZIPFILEOUTPUT_H

#include <sstream>
#include <vector>
#include "stromx/runtime/Config.h"
#include "stromx/runtime/FileOutput.h"

struct zip;

namespace stromx
{
    namespace runtime
    {
        /** \brief File output which stores the output data in a zip file. */
        class STROMX_RUNTIME_API ZipFileOutput : public FileOutput
        {
        public:
            /**
             * Constructs a file output which stores data in a zip file.
             * 
             * \param archive The path to the zip file.
             * \throws FileAccessFailed If the zip file could not be opened.
             */
            explicit ZipFileOutput(const std::string & archive);
            virtual ~ZipFileOutput();
            
            virtual void initialize(const std::string & filename);
            virtual const std::string & getFilename() const;
            virtual const std::string getText() const;
            
            virtual std::ostream & text();
            virtual std::ostream & openFile(const std::string & ext, const OpenMode mode);
            virtual std::ostream & file();
            virtual void close();
            
        private:
            void dumpFile();
            
            zip* m_archiveHandle;
            bool m_initialized;
            std::string m_archive;
            std::string m_currentBasename;
            std::string m_currentFilename;
            std::ostringstream *m_currentFile;
            std::ostringstream m_currentText;
            std::vector<std::string> m_bufferedFiles;
        };
    }
}

#endif // STROMX_RUNTIME_ZIPFILEOUTPUT_H
