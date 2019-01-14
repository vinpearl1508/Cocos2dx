/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "MainScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
	//auto startItem = MenuItemFont::create("Start Game", CC_CALLBACK_1(HelloWorld::menuStartCallBack, this));
	auto startLabel = Label::create("Start Game", "fonts/Marker Felt.ttf", 32);
	startLabel->setColor(Color3B(0, 255, 255));
	auto startItem = MenuItemLabel::create(startLabel, CC_CALLBACK_1(HelloWorld::menuStartCallBack, this));
	startItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + startLabel->getContentSize().height));
	
	auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(startItem, closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

	auto label = Label::createWithTTF("Super Cocos Aliens", "fonts/Marker Felt.ttf", 24);
	if (label == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		// position the label on the center of the screen
		label->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - label->getContentSize().height));

		// add the label as a child to this layer
		this->addChild(label, 1);
	}

	auto label1 = Label::createWithTTF("Player1  00000","fonts/Marker Felt.ttf", 14);
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

	auto sprite = Sprite::create("ZigzagForest_Square.png");
	auto sprite1 = Sprite::create("Blue_Front1.png");
	sprite1->setContentSize(sprite1->getContentSize()/2);
	sprite1->setPosition(Vec2(origin.x + visibleSize.width / 6, origin.y + sprite->getContentSize().height / 2 + sprite1->getContentSize().height / 2));
	this->addChild(sprite1);

	auto sprite2 = Sprite::create("LightBlue_Front1.png");
	sprite2->setContentSize(sprite2->getContentSize() / 2);
	sprite2->setPosition(Vec2(origin.x + visibleSize.width / 6 * 3, origin.y + sprite->getContentSize().height / 2 + sprite2->getContentSize().height / 2));
	this->addChild(sprite2);

	auto sprite3 = Sprite::create("White_Front1.png");
	sprite3->setContentSize(sprite3->getContentSize() / 2);
	sprite3->setPosition(Vec2(origin.x + visibleSize.width / 6 * 5, origin.y + sprite->getContentSize().height / 2 + sprite3->getContentSize().height / 2));
	this->addChild(sprite3);

	for (int i = 0; i < 5; i++)
	{
		auto sprite4 = Sprite::create("ZigzagGrass_Mud_Round.png");
		sprite4->setContentSize(sprite4->getContentSize() / 2);
		sprite4->setPosition(Vec2(origin.x + visibleSize.width / 2 + i * sprite4->getContentSize().width, origin.y + visibleSize.height / 6 * 2 + sprite4->getContentSize().height / 2));
		this->addChild(sprite4);
	}
	
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}

void HelloWorld::menuStartCallBack(Ref* pSender)
{
	auto gotoNext = CallFunc::create([]() {
		Director::getInstance()->replaceScene(MainScene::createScene());
	});
	auto sequence = Sequence::create(gotoNext, nullptr);
	runAction(sequence);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
