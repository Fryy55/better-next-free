#pragma once

#include <Geode/modify/LevelEditorLayer.hpp>


class $modify(HLevelEditorLayer, LevelEditorLayer) {
	struct Fields {
		std::uint16_t m_nextFreeOffset = 0u;
	};

	static void onModify(auto& self);

	$override
	int getNextFreeGroupID(gd::unordered_set<int> const& exclude);
};