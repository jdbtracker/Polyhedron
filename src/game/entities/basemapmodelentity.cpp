#include "../game.h"
#include "../engine/engine.h"
#include "basemapmodelentity.h"

namespace entities {
namespace classes {

BaseMapModelEntity::BaseMapModelEntity() : BaseEntity() {
    et_type = ET_MAPMODEL;
    ent_type = ENT_INANIMATE;
    game_type = GAMEENTITY;
}

BaseMapModelEntity::~BaseMapModelEntity() {

}

void BaseMapModelEntity::preload() {
}

void BaseMapModelEntity::think() {
}

void BaseMapModelEntity::render() {
}

void BaseMapModelEntity::preloadMapModel(const std::string &filename) {
    // Let's first preload this model.
    preloadmodel(filename.c_str());

    // Now store the map model index.
    model_idx = loadmapmodel(filename.c_str(), this);
}

} // classes
} // entities
