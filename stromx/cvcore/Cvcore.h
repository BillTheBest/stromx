#ifndef STROMX_CVCORE_CVCORE_H
#define STROMX_CVCORE_CVCORE_H

#include "stromx/cvcore/Config.h"

namespace stromx
{
    namespace runtime
    {
        class Registry;
    }
}

extern "C"
{
    STROMX_CVCORE_API void stromxCvcoreRegister(stromx::runtime::Registry* registry);
}

#endif // STROMX_CVCORE_CVCORE_H
