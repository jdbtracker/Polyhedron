#pragma once
#include "animinfo.h"
#include "basephysicalentity.h"

struct occludequery;
struct ragdolldata;

namespace entities
{
    namespace classes {

        class BaseDynamicEntity : public BasePhysicalEntity
        {
            ENTITY_FACTORY_IMPL(BaseDynamicEntity)
        public:
            void stopmoving();
            vec abovehead();
            
            DONTSERIALIZE bool k_left = false;
            DONTSERIALIZE bool k_right = false;
            DONTSERIALIZE bool k_up = false;
            DONTSERIALIZE bool k_down = false;
            DONTSERIALIZE animinterpinfo animinterp[MAXANIMPARTS] { 0 };
            DONTSERIALIZE ragdolldata *ragdoll = nullptr;
            DONTSERIALIZE occludequery *query = nullptr;
            DONTSERIALIZE int lastrendered = -1;
		protected:
        };
    } // classes
} // entities
