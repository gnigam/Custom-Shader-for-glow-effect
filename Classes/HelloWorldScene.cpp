#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
 /*   auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    return true;
	*/

	m_eventListenerTouch = EventListenerTouchAllAtOnce::create();
	auto center = Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);

	auto bg = Sprite::create("bg.png");
	bg->setPosition(center);
	auto bgsize = bg->getContentSize();
	float scaleX = visibleSize.width / bgsize.width;
	float scaleY = visibleSize.height / bgsize.height;
	bg->setScaleX(scaleX);
	bg->setScaleY(scaleY);
	addChild(bg);

	auto stable = Sprite::create("stable_bitmap.png");
	stable->setAnchorPoint(ccp(0.5, 0.5));
	stable->setPosition(center);
	addChild(stable);

	Texture2D::TexParams p;
	p.minFilter = GL_LINEAR;
	p.magFilter = GL_LINEAR;
	p.wrapS = GL_REPEAT;
	p.wrapT = GL_REPEAT;

	glActiveTexture(GL_TEXTURE0);

	auto textureCache = Director::getInstance()->getTextureCache();
	auto tex1 = textureCache->addImage("stable_bitmap.png");
	//tex1->setTexParameters(p);

	GLProgram* prog = new GLProgram();
	prog->initWithFilenames("Shader_PositionTexture.vert", "Shader_PositionTexture.frag");

	prog->link();
	prog->use();
	prog->updateUniforms();


	float gtime = Director::getInstance()->getDeltaTime();
	float ctime = Director::getInstance()->getTotalFrames() * Director::getInstance()->getAnimationInterval();

	CCLog("gtime = %f ctime = %f", gtime, ctime);

	ShaderCache::getInstance()->addGLProgram(prog, "Shader_PositionTexture");
	
	stable->setGLProgram(prog);
	
	GLProgramState* state = GLProgramState::getOrCreateWithGLProgram(prog);
	
	state->setUniformFloat("u_gtime", 1.0f);
	state->setUniformFloat("u_ctime",0.5f);
	//state->setUniformFloat("u_color", m_cloudAmount);
	
	prog->release();

	//stable->getTexture()->setTexParameters(p);
	/*
	auto noise = Sprite::create("noise_1024.png");
	noise->setPosition(center);
	noise->getTexture()->setTexParameters(p);
	auto nsize = noise->getContentSize();
	float scaleX1 = visibleSize.width / nsize.width;
	float scaleY1 = visibleSize.height / nsize.height;
	noise->setScaleX(scaleX1);
	noise->setScaleY(scaleY1);
	//addChild(noise);
	*/
	
	/*
	auto textureCache = Director::getInstance()->getTextureCache();
	auto tex1 = textureCache->addImage("noise_512.png");
	tex1->setTexParameters(p);

	auto tex2 = textureCache->addImage("noise_256.png");
	tex2->setTexParameters(p);
	
	GLProgram* prog = new GLProgram();
	prog->initWithFilenames("Shader_PositionTexture.vert", "Shader_PositionTexture.frag");

	prog->link();
	prog->use();
	prog->updateUniforms();

	glActiveTexture(GL_TEXTURE1);
	CHECK_GL_ERROR_DEBUG();
	glBindTexture(GL_TEXTURE_2D, tex1->getName());
	CHECK_GL_ERROR_DEBUG();

	glActiveTexture(GL_TEXTURE2);
	CHECK_GL_ERROR_DEBUG();
	glBindTexture(GL_TEXTURE_2D, tex2->getName());
	CHECK_GL_ERROR_DEBUG();

	glActiveTexture(GL_TEXTURE0);
	
	ShaderCache::getInstance()->addGLProgram(prog, "Shader_PositionTexture");

	

	auto glProgramState = GLProgramState::getOrCreateWithGLProgram(prog);
	
	bg->setGLProgramState(glProgramState);
	
	GLProgram* prog = new GLProgram();
	prog->initWithFilenames("Shader_PositionTexture.vert", "Shader_PositionTexture.frag");

	prog->link();
	prog->use();
	prog->updateUniforms();

	stable->setGLProgram(prog);
	prog->release();
	*/
	return true;

	
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
