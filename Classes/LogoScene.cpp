#include "LogoScene.h"
#include "HelloWorldScene.h"
USING_NS_CC;
Scene* LogoScene::createScene()
{
	auto scene = Scene::create();
	auto layer = LogoScene::create();
	scene->addChild(layer);
	return scene;
}
bool LogoScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto screenSize = Director::getInstance()->getVisibleSize();
	auto logo = Sprite::create("LogoGL.png");
	logo->setPosition(screenSize.width / 2, screenSize.height / 2);
	logo->setContentSize(screenSize);
	addChild(logo);

	auto gotoNext = CallFunc::create([]() {
		Director::getInstance()->replaceScene(HelloWorld::createScene());
	});
	auto sequence = Sequence::create(DelayTime::create(3), gotoNext,
		nullptr);
	runAction(sequence);

	return true;
}