#include "cube.h"
#include "ents.h"
#include "game.h"
#include "ents.h"
#include "baseentity.h"
#include "coreentity.h"
#include "entityfactory.h"

extern void boxs3D(const vec &o, vec s, int g);
extern void boxs(int orient, vec o, const vec &s);
extern void boxs(int orient, vec o, const vec &s, float size);

namespace entities {
namespace classes {

//
// Spawned set get clear functions.
//
bool CoreEntity::spawned() const {
    return (flags&entities::EntityFlags::EF_SPAWNED) != 0;
}
void CoreEntity::setspawned(bool val) {
    if(val)
        flags |= entities::EntityFlags::EF_SPAWNED;
    else
        flags &= ~entities::EntityFlags::EF_SPAWNED;
}
void CoreEntity::setspawned() {
    flags |= entities::EntityFlags::EF_SPAWNED;
}
void CoreEntity::clearspawned() {
    flags &= ~entities::EntityFlags::EF_SPAWNED;
}

void CoreEntity::setName(const std::string &str) {
    name = str;
}

void CoreEntity::saveToJsonImpl(nlohmann::json& document)
{
	document[classname] = {};
	to_json(document[classname], *this);
}


void CoreEntity::saveToJson(nlohmann::json& document)
{
	document = {
		{"class", currentClassname()},
		{"et_type", et_type},
		{"ent_type", ent_type},
		{"game_type", game_type}
	};
	
	saveToJsonImpl(document);
}

//NOTE: Only CoreEntity needs to implement this
void CoreEntity::fromJsonImpl(const nlohmann::json& document)
{
	document.at(classname).get_to(*this);
}

void CoreEntity::loadFromJson(const nlohmann::json& document) {
	document.at("et_type").get_to(et_type);
	document.at("ent_type").get_to(ent_type);
	document.at("game_type").get_to(game_type);

	fromJsonImpl(document);
}

void CoreEntity::renderForEdit()
{

}

void CoreEntity::renderForEditGui()
{

}

void CoreEntity::renderSelected()
{
	
}


void CoreEntity::renderHighlight(int entselradius, int entorient, float thickness)
{
	gle::colorub(0, 40, 0);
	vec es(entselradius);
    vec eo = o;
    eo.sub(es);
    es.mul(2);
    
	boxs3D(eo, es, 1);

	gle::colorub(200,0,0);
	boxs(entorient, eo, es, thickness);
}

void CoreEntity::renderMoveShadow(int entselradius, int size)
{
	vec es(entselradius);
    vec eo = o;
    eo.sub(es);
    es.mul(2);

	vec a, b;
	gle::colorub(20, 20, 20);
	(a = eo).x = eo.x - fmod(eo.x, size); (b = es).x = a.x + size; boxs3D(a, b, 1);
	(a = eo).y = eo.y - fmod(eo.y, size); (b = es).y = a.x + size; boxs3D(a, b, 1);
	(a = eo).z = eo.z - fmod(eo.z, size); (b = es).z = a.x + size; boxs3D(a, b, 1);
}



void from_json(const nlohmann::json& document,  entities::classes::CoreEntity* entity_ptr)
{
	document.get_to(entity_ptr->name);
}

void to_json(nlohmann::json& document, const entities::classes::CoreEntity* entity_ptr)
{
	if (entity_ptr)
	{
		document = nlohmann::json {entity_ptr->name};
	}
	else
	{
		document = nlohmann::json {nullptr};
	}
}
} // classes
} // entities

ADD_ENTITY_TO_FACTORY(CoreEntity, "core_entity");
