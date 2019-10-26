#include "playerstart.h"

namespace entities {
namespace classes {

PlayerStart::PlayerStart() {
	et_type = ET_GAMESPECIFIC;
	ent_type = ENT_INANIMATE;
	game_type = PLAYERSTART;
}

void PlayerStart::preload() {

}

void PlayerStart::think() {

}

void PlayerStart::render() {

}

void PlayerStart::reset() {

}

} // classes
} // entities

ADD_ENTITY_TO_FACTORY_SERIALIZED(PlayerStart, "playerstart", BaseEntity);
