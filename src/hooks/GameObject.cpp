#include "GameObject.hpp"

using namespace geode::prelude;


void HGameObject::customSetup() {
	GameObject::customSetup();

	switch (this->m_objectID) {
		// Keyframe
		case 3032u: [[fallthrough]];
		// Teleport Orb
		case 3027u: [[fallthrough]];
		// Toggle Orb
		case 1594u: [[fallthrough]];
		// Teleport Portal
		case 2902u: [[fallthrough]];
		// Checkpoint
		case 2063u: [[fallthrough]];
		// Toggle Block
		case 3643u:
			m_fields->m_fix = true;
			break;

		default:
			if (this->m_objectType == GameObjectType::Collectible)
				m_fields->m_fix = true;
			break;
	}

	return;
}