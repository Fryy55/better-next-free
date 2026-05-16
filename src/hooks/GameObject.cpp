#include "GameObject.hpp"

using namespace geode::prelude;


void HGameObject::customSetup() {
	GameObject::customSetup();

	switch (this->m_objectID) {
		// Keyframe
		case 3032u: [[fallthrough]];
		// Checkpoint
		case 2063u:
			m_fields->m_fix = true;
			break;

		default:
			if (this->m_objectType == GameObjectType::Collectible)
				m_fields->m_fix = true;
			break;
	}

	return;
}