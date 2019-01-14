#include "MainScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* MainScene::createScene()
{
	return MainScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MainScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto background = Sprite::create("annotated_scaled.png");
	background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	background->setContentSize(visibleSize);
	this->addChild(background);

	auto label1 = Label::createWithTTF("Player1  00000", "fonts/Marker Felt.ttf", 14);
	label1->setPosition(Vec2(origin.x + label1->getContentSize().width / 2, origin.y + visibleSize.height - label1->getContentSize().height));
	this->addChild(label1);

	auto label2 = Label::createWithTTF("Player2  00000", "fonts/Marker Felt.ttf", 14);
	label2->setPosition(Vec2(origin.x + visibleSize.width - label2->getContentSize().width / 2, origin.y + visibleSize.height - label2->getContentSize().height));
	this->addChild(label2);

	for (int i = 0; i < 25; i++)
	{
		auto sprite = Sprite::create("ZigzagForest_Square.png");
		sprite->setContentSize(sprite->getContentSize() / 2);
		sprite->setPosition(Vec2(origin.x + i * sprite->getContentSize().width, origin.y + sprite->getContentSize().height / 2));
		this->addChild(sprite);
	}

	for (int i = 0; i < 3; i++)
	{
		auto sprite = Sprite::create("ZigzagGrass_Mud_Round.png");
		sprite->setContentSize(sprite->getContentSize() / 2);
		sprite->setPosition(Vec2(origin.x + visibleSize.width / 6 + i * sprite->getContentSize().width - sprite->getContentSize().width, origin.y + visibleSize.height / 6 * 2 + sprite->getContentSize().height / 2));
		this->addChild(sprite);
	}

	for (int i = 0; i < 3; i++)
	{
		auto sprite = Sprite::create("ZigzagGrass_Mud_Round.png");
		sprite->setContentSize(sprite->getContentSize() / 2);
		sprite->setPosition(Vec2(origin.x + visibleSize.width / 2 + i * sprite->getContentSize().width - sprite->getContentSize().width, origin.y + visibleSize.height / 6 * 2 + 2 * sprite->getContentSize().height));
		this->addChild(sprite);
	}

	for (int i = 0; i < 3; i++)
	{
		auto sprite = Sprite::create("ZigzagGrass_Mud_Round.png");
		sprite->setContentSize(sprite->getContentSize() / 2);
		sprite->setPosition(Vec2(origin.x + visibleSize.width / 6 * 4 + i * sprite->getContentSize().width + sprite->getContentSize().width, origin.y + visibleSize.height / 6 * 2 + sprite->getContentSize().height / 2));
		this->addChild(sprite);
	}

	//auto beeMC = Sprite::create();
	//beeMC->setPosition(origin.x + visibleSize.width / 6 , origin.y + visibleSize.height / 3 * 2);
	//addChild(beeMC);
	//Vector<SpriteFrame*> animFrames;
	///*animFrames.pushBack(SpriteFrame::create("bee1.png", Rect(0, 0, 150, 150)));
	//animFrames.pushBack(SpriteFrame::create("bee2.png", Rect(0, 0, 150, 150)));
	//animFrames.pushBack(SpriteFrame::create("bee3.png", Rect(0, 0, 150, 150)));*/
	//for (int i = 1; i <= 3; i++)
	//{
	//	//std::string std = "bee"+std::to_string(i) + ".png";
	//	animFrames.pushBack(SpriteFrame::create("bee" + std::to_string(i) + ".png", Rect(0, 0, 150, 150)));
	//}
	//auto animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
	//auto animate = Animate::create(animation);
	//beeMC->runAction(RepeatForever::create(animate));

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("walker.plist");
	//sprite
	auto frames = getAnimation("walker (%d).png", 7);
	auto sprite = Sprite::createWithSpriteFrame(frames.front());
	addChild(sprite);
	sprite->setAnchorPoint(Vec2(0,0));
	sprite->setPosition(Vec2(visibleSize.width/10, visibleSize.height/10));
	sprite->setScale(0.15);

	auto animation = Animation::createWithSpriteFrames(frames, 1.0f / 8);
	sprite->runAction(RepeatForever::create(Animate::create(animation)));
	
	auto movement = MoveTo::create(10, Vec2(visibleSize.width / 2, visibleSize.height / 10));
	auto resetPosition = MoveTo::create(0, Vec2(visibleSize.width / 10, visibleSize.height / 10));
	auto sequence = Sequence::create(movement, resetPosition, NULL);
	sprite->runAction(RepeatForever::create(sequence));

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("walkers.plist");
	//sprite
	auto frames1 = getAnimation("walkers (%d).png", 14);
	auto sprite1 = Sprite::createWithSpriteFrame(frames1.front());
	addChild(sprite1);
	sprite1->setAnchorPoint(Vec2(0, 0));
	sprite1->setPosition(Vec2(visibleSize.width / 10 * 9, visibleSize.height / 10));
	sprite1->setScale(0.15);

	auto animation1 = Animation::createWithSpriteFrames(frames1, 1.0f / 8);
	sprite1->runAction(RepeatForever::create(Animate::create(animation1)));

	auto movement1 = MoveTo::create(10, Vec2(visibleSize.width / 2, visibleSize.height / 10));
	auto resetPosition1 = MoveTo::create(0, Vec2(visibleSize.width / 10 * 9, visibleSize.height / 10));
	auto sequence1 = Sequence::create(movement1, resetPosition1, NULL);
	sprite1->runAction(RepeatForever::create(sequence1));

	return true;
}

cocos2d::Vector<cocos2d::SpriteFrame*> MainScene::getAnimation(const char *format, int count)
{
	auto spritecache = SpriteFrameCache::getInstance();
	cocos2d::Vector<cocos2d::SpriteFrame*> animFrames;
	char str[100];
	for (int i = 1; i <= count; i++)
	{
		sprintf(str, format, i);
		animFrames.pushBack(spritecache->getSpriteFrameByName(str));
	}
	return animFrames;
}