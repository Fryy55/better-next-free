#pragma once

#include <Geode/modify/SetGroupIDLayer.hpp>


class $modify(HSetGroupIDLayer, SetGroupIDLayer) {
	static void onModify(auto& self);

	$override
	void onNextGroupID1(cocos2d::CCObject* sender);
};