#include "XmlReader.h"

#include "Exception.h"

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>

#include <iostream>

namespace stream
{
    using namespace xercesc;
    
    Stream*const XmlReader::read(const std::string & filename, const OperatorFactory* const factory)
    {        
        try
        {
            XMLPlatformUtils::Initialize();  // Initialize Xerces infrastructure
        }
        catch (const XMLException& toCatch)
        {
            char* message = XMLString::transcode(toCatch.getMessage());
            std::cerr << "Error during initialization! :\n"
                 << message << "\n";
            XMLString::release(&message);
            return 0;
        }
    
        XercesDOMParser* parser = new XercesDOMParser();
        parser->setValidationScheme(XercesDOMParser::Val_Always);
        parser->setDoNamespaces(true);    // optional

        ErrorHandler* errHandler = (ErrorHandler*) new HandlerBase();
        parser->setErrorHandler(errHandler);

        const char* xmlFile = filename.c_str();

        try {
            parser->parse(xmlFile);
        }
        catch (const XMLException& toCatch) {
            char* message = XMLString::transcode(toCatch.getMessage());
            std::cerr << "Exception message is: \n"
                << message << "\n";
            XMLString::release(&message);
            return 0;
        }
        catch (const DOMException& toCatch) {
            char* message = XMLString::transcode(toCatch.msg);
            std::cerr << "Exception message is: \n"
                << message << "\n";
            XMLString::release(&message);
            return 0;
        }
        catch (...) {
            std::cerr << "Unexpected Exception \n" ;
            return 0;
        }

        delete parser;
        delete errHandler;
            
        try
        {
            XMLPlatformUtils::Terminate();  // Terminate after release of memory
        }
        catch(XMLException&)
        {
        }
    }
}
