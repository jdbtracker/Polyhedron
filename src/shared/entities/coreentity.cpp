#include "cube.h"
#include "ents.h"
#include "game.h"
#include "ents.h"
#include "baseentity.h"
#include "coreentity.h"
#include "entityfactory.h"

/*
const nlohmann::json json_utils::getSubobject(const nlohmann::json& document, const std::string& key)
{
	if (document.find(key) != document.end()){
		const auto& subObject = document.at(key);
		if (subObject.is_object())
		{
			return subObject;
		}
	}
	
	return NULL;
}



template<>
bool json_utils::tryQueryJsonVar(const nlohmann::json& document, const std::string& key, vec& value)
{
	if (document.find(key) != document.end()) {
		try {
			auto obj = document.at(key);
			
			if (obj.is_object())
			{
				json_utils::tryQueryJsonVar(obj, "x", value.x);
				json_utils::tryQueryJsonVar(obj, "y", value.y);
				json_utils::tryQueryJsonVar(obj, "z", value.z);
			}
			
			return true;
		}
		catch(nlohmann::json::type_error& e) {
            conoutf(CON_ERROR, "nlohmann went nuts again: %s", e.what());
		}
	}
	
	return false;
}

template<>
bool json_utils::tryQueryJsonVar(const nlohmann::json& document, const std::string& key, vec4& value)
{
	if (document.find(key) != document.end()) {
		try {
			auto obj = document.at(key);
			
			if (obj.is_object())
			{
				json_utils::tryQueryJsonVar(obj, "x", value.x);
				json_utils::tryQueryJsonVar(obj, "y", value.y);
				json_utils::tryQueryJsonVar(obj, "z", value.z);
				json_utils::tryQueryJsonVar(obj, "w", value.w);
			}
			
			return true;
		}
		catch(nlohmann::json::type_error& e) {
            conoutf(CON_ERROR, "nlohmann went nuts again: %s", e.what());
		}
	}
	
	return false;
}*/

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


void from_json(const nlohmann::json& document,  entities::classes::CoreEntity* entity_ptr)
{
	document.get_to(entity_ptr->name);
}

void to_json(nlohmann::json& document, const entities::classes::CoreEntity* entity_ptr)
{
	document = nlohmann::json {entity_ptr->name};
}
} // classes
} // entities

ADD_ENTITY_TO_FACTORY(CoreEntity, "core_entity");
