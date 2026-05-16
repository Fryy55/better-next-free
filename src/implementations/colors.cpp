#include "LevelEditorLayer.hpp"
#include "CustomizeObjectLayer.hpp"

using namespace geode::prelude;


int HLevelEditorLayer::getNextColorChannel() {
	

	return 55;
}

void HCustomizeObjectLayer::onNextColorChannel(CCObject* sender) {
	auto color = LevelEditorLayer::get()->getNextColorChannel();
	updateSelected(color);
	updateColorSprite();
	updateChannelLabel(color);

	return;
}