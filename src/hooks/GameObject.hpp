#pragma once

#include <Geode/modify/GameObject.hpp>


class $modify(HGameObject, GameObject) {
	struct Fields {
		bool m_fix = false;
	};

	$override
	void customSetup();
};