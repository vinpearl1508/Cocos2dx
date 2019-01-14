#include "LogoScene.h"
#include "HelloWorldScene.h"
#include "ui/CocosGUI.h"
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
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto logo = Sprite::create("LogoGL.png");
	logo->setPosition(Vec2(screenSize.width / 2 + origin.x, screenSize.height / 2 + origin.y));
	logo->setContentSize(screenSize/5);
	addChild(logo);

	auto scaleTo = ScaleTo::create(2,3,3);
	auto fadeIn = FadeIn::create(2);
	auto spawn = Spawn::create(scaleTo, fadeIn, nullptr);
	logo->runAction(spawn);

	auto loadingBarGB = Sprite::create("loadingbar_bg.png");
	loadingBarGB->setColor(Color3B(0, 0, 0));
	loadingBarGB->setPosition(Vec2(screenSize.width / 2, loadingBarGB->getContentSize().height));
	addChild(loadingBarGB);
	
	static auto loadingbar = ui::LoadingBar::create("loadingbar.png");
	loadingbar->setPercent(0);
	loadingbar->setDirection(ui::LoadingBar::Direction::LEFT);
	loadingbar->setPosition(loadingBarGB->getPosition());
	addChild(loadingbar);
	
	//update Loading Bar
	auto updateLoadingBar = CallFunc::create([]() {
		if (loadingbar->getPercent() < 100)
		{
			loadingbar->setPercent(loadingbar->getPercent() + 1);
		}
	});
	auto sequenceRunUpdateLoadingBar =
		Sequence::createWithTwoActions(updateLoadingBar, DelayTime::create(0.1f));
	auto repeat = Repeat::create(sequenceRunUpdateLoadingBar, 100);
	auto sequence1 = Sequence::create(DelayTime::create(2), repeat, nullptr);
	loadingbar->runAction(sequence1);

	auto gotoNext = CallFunc::create([]() {
		Director::getInstance()->replaceScene(HelloWorld::createScene());
	});
	auto sequence2 = Sequence::create(DelayTime::create(12), gotoNext, nullptr);
	runAction(sequence2);
	return true;
}