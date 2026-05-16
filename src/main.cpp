#include <Geode/Geode.hpp>

#include <Geode/modify/SetGroupIDLayer.hpp>

using namespace geode::prelude;

// this is actually more like src/hooks/SetGroupIDLayer.cpp, but i do some loading time
// stuff here + it's kinda the start of the functionality chain sooo why not main.cpp
class $modify(SetGroupIDLayer) {
	static void onModify(auto& self) {
		/*
			Dear HJ... actually i shall see if it still matters in new BE for v1.1.0
		*/

		auto betterEdit = Loader::get()->getInstalledMod("hjfod.betteredit");
		bool loadBetterEdit = betterEdit && betterEdit->shouldLoad();
		if(loadBetterEdit && !self.setHookPriorityBeforePre("SetGroupIDLayer::onNextGroupID1", "hjfod.betteredit"))
			log::warn("Failed to set hook priority for SetGroupIDLayer::onNextGroupID1");
		log::info(
			"{}Hook priority for SetGroupIDLayer::onNextGroupID1: {}",
			loadBetterEdit ? "BetterEdit detected. " : "",
			self.getHook("SetGroupIDLayer::onNextGroupID1").unwrap()->getPriority()
		);

		return;
	}

	$override
	void onNextGroupID1(CCObject* sender) {
		if (
			auto offsetInput = m_mainLayer
								->getChildByID("next-free-menu")
								->getChildByID("hjfod.betteredit/next-free-offset-input")
		) { // if BE
			auto lel = LevelEditorLayer::get();

			lel->m_levelSettings->m_nextFreeID = numFromString<std::uint16_t>(
				offsetInput->getChildByType<TextInput>(0)->getString()
			).unwrapOr(0u);

			m_groupIDValue = lel->getNextFreeGroupID(gd::unordered_set<int>{});
			this->updateGroupIDLabel();
		} else {
			SetGroupIDLayer::onNextGroupID1(sender);
		}

		return;
	}
};