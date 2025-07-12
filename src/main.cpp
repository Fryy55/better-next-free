#include <Geode/Geode.hpp>

#include <Geode/modify/LevelEditorLayer.hpp>
#include <Geode/modify/SetGroupIDLayer.hpp>

using namespace geode::prelude;


class $modify(LevelEditorLayer) {
	$override int getNextFreeGroupID(CCArray* p0) {
		std::array<bool, 10'000> usedGroups;
		#define MARK(group) usedGroups[(group)] = true

		for (auto object : CCArrayExt<GameObject*>(m_objects)) {
			if (!object)
				continue;
			if (object->m_groupCount)
				for (auto group : *object->m_groups)
					MARK(group);

			if (object->m_isTrigger) {
				auto trigger = static_cast<EffectGameObject*>(object);

				MARK(trigger->m_targetGroupID);
				MARK(trigger->m_centerGroupID);
			}
		}

		for (std::size_t i = 1; i < 10'000; ++i)
			if (!usedGroups[i])
				return i;

		return 0;
	}
};

class $modify(SetGroupIDLayer) {
	void onNextGroupID1(CCObject*) {
		m_groupIDValue = LevelEditorLayer::get()->getNextFreeGroupID(nullptr);
		this->updateGroupIDLabel();

		return;
	}
};