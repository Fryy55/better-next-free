#include <Geode/Geode.hpp>

#include "GameObject.hpp"

#include <Geode/modify/LevelEditorLayer.hpp>
#include <Geode/modify/SetGroupIDLayer.hpp>

using namespace geode::prelude;


class $modify(LevelEditorLayer) {
	static void onModify(auto& self) {
		if(!self.setHookPriorityPre("LevelEditorLayer::getNextFreeGroupID", Priority::Replace))
			log::warn("Failed to set hook priority for LevelEditorLayer::getNextFreeGroupID");

		return;
	}

	$override
	int getNextFreeGroupID(CCArray* p0) {
		std::array<bool, 10'000> usedGroups;
		#define MARK(group) usedGroups[(group)] = true

		for (auto object : CCArrayExt<GameObject*>(m_objects)) {
			if (!object)
				continue;
			if (object->m_groupCount)
				for (auto group : *object->m_groups)
					MARK(group);

			if (object->m_isTrigger || static_cast<HGameObject*>(object)->m_fields->m_fix) {
				auto trigger = static_cast<EffectGameObject*>(object);

				switch (object->m_objectID) {
					//* Skip standard marks (continue)

					// Stop Trigger
					case 1616u: [[fallthrough]];
					// EditAdvFollow Trigger
					case 3660u:
						MARK(trigger->m_targetControlID ? 0u : trigger->m_targetGroupID);
						continue;

					// Pulse Trigger
					case 1006u:
						MARK(trigger->m_pulseTargetType ? trigger->m_targetGroupID : 0u);
						continue;

					// ReTargetAdvFollow Trigger
					case 3661u:
						MARK(trigger->m_targetControlID ? 0u : trigger->m_targetGroupID);
						MARK(trigger->m_centerGroupID);
						continue;

					// EditArea Triggers
					case 3011u: [[fallthrough]];
					case 3012u: [[fallthrough]];
					case 3013u: [[fallthrough]];
					case 3014u: [[fallthrough]];
					case 3015u:
						MARK(static_cast<EnterEffectObject*>(object)->m_useEffectID ? 0u : trigger->m_targetGroupID);
						continue;

					// AdvRandom Trigger
					case 2068u: [[fallthrough]];
					// Sequence Trigger
					case 3607u:
						for (auto const& chanceObj : static_cast<ChanceTriggerGameObject*>(object)->m_chanceObjects)
							MARK(chanceObj.m_groupID);
						continue;

					// Gradient Trigger
					case 2903u: {
						auto gradientTrigger = static_cast<GradientTriggerObject*>(object);
						MARK(gradientTrigger->m_leftTopLeftID);
						MARK(gradientTrigger->m_upBottomLeftID);
						MARK(gradientTrigger->m_rightTopRightID);
						MARK(gradientTrigger->m_downBottomRightID);
					}
					continue;

					// StopArea Trigger
					case 3024u: [[fallthrough]];
					// ItemEdit Trigger
					case 3619u:
						continue;


					//* Apply standard marks (break)

					// Move Trigger
					case 901u:
						MARK(trigger->m_targetModCenterID);
						break;

					// Rotate Trigger
					case 1346u:
						MARK(trigger->m_rotationTargetID);
						break;

					// KeyframeAnim Trigger
					case 3033u:
						MARK(trigger->m_animationID);
						break;

					// Checkpoint
					case 2063u:
						MARK(static_cast<CheckpointGameObject*>(object)->m_respawnID);
						break;

					default:
						// check for collectibles
						if (object->m_objectType == GameObjectType::Collectible) {
							if (trigger->m_collectibleIsToggleTrigger)
								MARK(trigger->m_targetGroupID);
							continue;
							log::debug("{}", trigger->m_collectibleIsToggleTrigger);
						}

						break;
				}

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
	static void onModify(auto& self) {
		if(Loader::get()->isModLoaded("hjfod.betteredit") && !self.setHookPriorityPre("SetGroupIDLayer::onNextGroupID1", Priority::Stub))
			log::warn("Failed to set hook priority for SetGroupIDLayer::onNextGroupID1");

		return;
	}

	$override
	void onNextGroupID1(CCObject*) {
		m_groupIDValue = LevelEditorLayer::get()->getNextFreeGroupID(nullptr);
		this->updateGroupIDLabel();

		return;
	}
};