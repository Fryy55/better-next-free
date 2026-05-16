#include "LevelEditorLayer.hpp"
#include "SetGroupIDLayer.hpp"
#include "CustomizeObjectLayer.hpp"

using namespace geode::prelude;


void HLevelEditorLayer::onModify(auto& self) {
	// GROUPS
	if(!self.setHookPriorityPre("LevelEditorLayer::getNextFreeGroupID", Priority::Replace))
		log::warn("Failed to set hook priority for LevelEditorLayer::getNextFreeGroupID");
	// COLORS
	if(!self.setHookPriorityPre("LevelEditorLayer::getNextColorChannel", Priority::Replace))
		log::warn("Failed to set hook priority for LevelEditorLayer::getNextColorChannel");

	return;
}

// --------------------------------------------------
/*
	Dear HJLame,

	Not sorry for being the bearer of good news but youre lame af frfr. In fact, lame doesn't
	describe how stupid you truly are. You think of yourself highly bcuz you can type some
	shit up in a .cpp file? Fuck no. You're nothing pal. Not a thing in this world which can
	fix you. I bet your one of those white people who screams "yippee" and claps when the plane
	lands. That is, if you could ride planes. But I know for a fact you couldn't get on
	one -- sending you into the skies would be asking for another boeing plane crash. Not only
	that, but you cannot embody the thing you make. Like Jesus Christ you declothe your Geode
	modding code and can't even do it to yourself? Just do it already, life ain't fair punk.
	The words in the English language cannot cover how much I hate you and your lilypad brain.
	I could call you everything bad in the world but I don't think it'd be enough. In fact, I
	KNOW it wouldn't be enough. When will you realize that you aren't that guy and never will be.
	To show you how unimportant you are, I will write the rest of this message in Turkish (the best
	language ever which all of the greatest humans know). Lanet olsun sana, ne kadar uğraşırsan
	uğraş, asla iyi kod yazamayacaksın, hiç şüphem yok. Bu dünyadan ve Geometry Dash topluluğundan
	defol git! Benim sevgili kayam senden daha iyi bir programcı. İş arkadaşlarından kod çalıp
	kendini iyi bir programcı mı sanıyorsun? Şimdi git ve ne yaptığını bir daha düşün. If you
	understood it, I still hate you, and if you didn't, I hate you even more. I'm not even going
	to read your response because I hate you.

	The truth is HJFat, you've done a lot...
	Of horrible and unspeakable actions.

	I hope you find yourself in bald hell you incompassitated dung beetle,
	Revalutionary

	-----------------------------------------------------------------------
	i was forced to put this here i'm sorry hjfod but pls maybe call the original idk :pray:
*/
static auto betterEditHookPrio = [](auto& self, char const* functionName) {
	static bool init = false;
	static bool loadBetterEdit;

	if (!init) {
		auto betterEdit = Loader::get()->getInstalledMod("hjfod.betteredit");
		loadBetterEdit = betterEdit && betterEdit->shouldLoad();
		
		init = true;
	}

	if (loadBetterEdit && !self.setHookPriorityBeforePre(functionName, "hjfod.betteredit"))
		log::warn("Failed to set hook priority for {}", functionName);

	if (auto hook = self.getHook(functionName); !hook)
		log::error("{} hook not found", functionName);
	else
		log::info(
			"{}Hook priority for {}: {}",
			loadBetterEdit ? "BetterEdit detected. " : "",
			functionName,
			hook.unwrap()->getPriority()
		);
};

// GROUPS
void HSetGroupIDLayer::onModify(auto& self) {
	betterEditHookPrio(self, "SetGroupIDLayer::onNextGroupID1");

	return;
}

// COLORS
void HCustomizeObjectLayer::onModify(auto& self) {
	betterEditHookPrio(self, "CustomizeObjectLayer::onNextColorChannel");

	return;
}