#ifndef __RESOURCE_POOL
#define __RESOURCE_POOL

#include "App/Utils/PageManager/ResourceManager.h"
#include "lvgl.h"

#define FONT_agencyb_36 ("agencyb_36")
#define FONT_RexBold_28 ("RexBold_28")
#define FONT_RexBold_68 ("RexBold_68")
#define FONT_RexBold_89 ("RexBold_89")
#define FONT_Morganite_36 ("Morganite_36")
#define FONT_Morganite_100 ("Morganite_100")
#define FONT_HandGotn_14 ("HandGotn_14")
#define FONT_HandGotn_20 ("HandGotn_20")
#define FONT_HandGotn_26 ("HandGotn_26")
#define FONT_EuroStar_26 ("EuroStar_26")
#define FONT_EuroStar_60 ("EuroStar_60")

class ResourcePool
{

public:
    ResourceManager Font_;
    ResourceManager Image_;

public:
    void Init();
    lv_font_t* GetFont(const char* name)
    {
        return (lv_font_t*)Font_.GetResource(name);
    }
    const void* GetImage(const char* name)
    {
        return Image_.GetResource(name);
    }
};

extern ResourcePool Resource;

#endif
