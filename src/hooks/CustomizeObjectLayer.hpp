#pragma once

#include <Geode/modify/CustomizeObjectLayer.hpp>


class $modify(HCustomizeObjectLayer, CustomizeObjectLayer) {
	static void onModify(auto& self);

	$override
	void onNextColorChannel(cocos2d::CCObject* sender);
};