#include "stromx/cvcalib3d/Cvcalib3d.h"

#include "stromx/cvcalib3d/FindChessboardCorners.h"
#include <stromx/runtime/Locale.h>
#include <stromx/runtime/Registry.h>

namespace stromx
{
    namespace cvcalib3d
    {
        std::locale locale;
    }
}

void stromxCvcalib3dRegister(stromx::runtime::Registry& registry)
{
    using namespace stromx::cvcalib3d;
    
    locale = stromx::runtime::Locale::generate(STROMX_CVCALIB3D_LOCALE_DIR, STROMX_CVCALIB3D_LOCALE_DOMAIN);
    
    registry.registerOperator(new FindChessboardCorners);
}