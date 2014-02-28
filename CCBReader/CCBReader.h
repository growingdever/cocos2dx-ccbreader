#ifndef _CCB_CCBREADER_H_
#define _CCB_CCBREADER_H_

#include "cocos2d.h"
#include "ExtensionMacros.h"
#include <string>
#include <vector>
#include "CCBSequence.h"
#include "GUI/CCControlExtension/CCControl.h"


#define CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(T, METHOD) static T * METHOD() { \
    T * ptr = new T(); \
    if(ptr != NULL) { \
        ptr->autorelease(); \
        return ptr; \
    } \
    CC_SAFE_DELETE(ptr); \
    return NULL; \
}

#define CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(T, METHOD) static T * METHOD() { \
    T * ptr = new T(); \
    if(ptr != NULL && ptr->init()) { \
        ptr->autorelease(); \
        return ptr; \
    } \
    CC_SAFE_DELETE(ptr); \
    return NULL; \
}

#define kCCBVersion 6

enum {
    kCCBPropTypePosition = 0,
    kCCBPropTypeSize,
    kCCBPropTypePoint,
    kCCBPropTypePointLock,
    kCCBPropTypeScaleLock,
    kCCBPropTypeDegrees,
    kCCBPropTypeInteger,
    kCCBPropTypeFloat,
    kCCBPropTypeFloatVar,
    kCCBPropTypeCheck,
    kCCBPropTypeSpriteFrame,
    kCCBPropTypeTexture,
    kCCBPropTypeByte,
    kCCBPropTypeColor3,
    kCCBPropTypeColor4FVar,
    kCCBPropTypeFlip,
    kCCBPropTypeBlendmode,
    kCCBPropTypeFntFile,
    kCCBPropTypeText,
    kCCBPropTypeFontTTF,
    kCCBPropTypeIntegerLabeled,
    kCCBPropTypeBlock,
	kCCBPropTypeAnimation,
    kCCBPropTypeCCBFile,
    kCCBPropTypeString,
    kCCBPropTypeBlockCCControl,
    kCCBPropTypeFloatScale,
    kCCBPropTypeFloatXY,
	kCCBPropTypeColor4,
};

enum {
    kCCBFloat0 = 0,
    kCCBFloat1,
    kCCBFloatMinus1,
    kCCBFloat05,
    kCCBFloatInteger,
    kCCBFloatFull
};

enum {
    kCCBPlatformAll = 0,
    kCCBPlatformIOS,
    kCCBPlatformMac
};

enum {
    kCCBTargetTypeNone = 0,
    kCCBTargetTypeDocumentRoot = 1,
    kCCBTargetTypeOwner = 2,
};

enum
{
    kCCBKeyframeEasingInstant,
    
    kCCBKeyframeEasingLinear,
    
    kCCBKeyframeEasingCubicIn,
    kCCBKeyframeEasingCubicOut,
    kCCBKeyframeEasingCubicInOut,
    
    kCCBKeyframeEasingElasticIn,
    kCCBKeyframeEasingElasticOut,
    kCCBKeyframeEasingElasticInOut,
    
    kCCBKeyframeEasingBounceIn,
    kCCBKeyframeEasingBounceOut,
    kCCBKeyframeEasingBounceInOut,
    
    kCCBKeyframeEasingBackIn,
    kCCBKeyframeEasingBackOut,
    kCCBKeyframeEasingBackInOut,
};

enum
{
    CCPositionReferenceCornerBottomLeft,
    CCPositionReferenceCornerTopLeft,
    CCPositionReferenceCornerTopRight,
    CCPositionReferenceCornerBottomRight,
};

enum
{
    kCCBSizeTypeAbsolute,
    kCCBSizeTypePercent,
    kCCBSizeTypeRelativeContainer,
    kCCBSizeTypeHorizontalPercent,
    kCCBSizeTypeVerticalPercent,
    kCCBSizeTypeMultiplyResolution,
};

enum
{
    kCCBScaleTypeAbsolute,
    kCCBScaleTypeMultiplyResolution
};


typedef enum
{
	// Content size is set in points (this is the default)
    CCSizeUnitPoints,
    
    // Position is UI points, on iOS this corresponds to the native point system
    CCSizeUnitUIPoints,
    
    // Content size is a normalized value multiplied by the content size of the parent's container
    CCSizeUnitNormalized,
    
    // Content size is the size of the parents container inset by the supplied value
    CCSizeUnitInsetPoints,
    
    // Content size is the size of the parents container inset by the supplied value multiplied by the UIScaleFactor (as defined by CCDirector)
    CCSizeUnitInsetUIPoints,
} CCSizeUnit;


NS_CC_EXT_BEGIN

/**
 * @addtogroup cocosbuilder
 * @{
 * @js NA
 * @lua NA
 */

class CCBFile : public CCNode
{
private:
    CCNode *mCCBFileNode;
    
public:
    CCBFile();
    
    static CCBFile* create();
    
    CCNode* getCCBFileNode();
    void setCCBFileNode(CCNode *pNode); // retain
};

/* Forward declaration. */
class CCNodeLoader;
class CCNodeLoaderLibrary;
class CCNodeLoaderListener;
class CCBMemberVariableAssigner;
class CCBSelectorResolver;
class CCBAnimationManager;
class CCData;
class CCBKeyframe;

/**
 * @brief Parse CCBI file which is generated by CocosBuilder
 */
class CCBReader : public CCObject 
{
private:
    
    CCData *mData;
    unsigned char *mBytes;
    int mCurrentByte;
    int mCurrentBit;
    
    std::vector<std::string> mStringCache;
    std::set<std::string> mLoadedSpriteSheets;
    
    CCObject *mOwner;
    
    CCBAnimationManager *mActionManager; //retain
    CCDictionary* mActionManagers;

    std::set<std::string> *mAnimatedProps;

    CCNodeLoaderLibrary *mCCNodeLoaderLibrary;
    CCNodeLoaderListener *mCCNodeLoaderListener;
    CCBMemberVariableAssigner *mCCBMemberVariableAssigner;
    CCBSelectorResolver *mCCBSelectorResolver;
    
    std::vector<std::string> mOwnerOutletNames;
    CCArray* mOwnerOutletNodes;
    CCArray* mNodesWithAnimationManagers;
    CCArray* mAnimationManagersForNodes;
    
    std::vector<std::string> mOwnerCallbackNames;
    CCArray* mOwnerCallbackNodes;
    CCArray* mOwnerOwnerCallbackControlEvents;
    std::string mCCBRootPath;
    bool hasScriptingOwner;    
    bool init();
public:
    
    bool jsControlled;
    /**
     *  @js NA
     *  @lua NA
     */
    CCBReader(CCNodeLoaderLibrary *pCCNodeLoaderLibrary, CCBMemberVariableAssigner *pCCBMemberVariableAssigner = NULL, CCBSelectorResolver *pCCBSelectorResolver = NULL, CCNodeLoaderListener *pCCNodeLoaderListener = NULL);
    /**
     *  @js NA
     *  @lua NA
     */
    CCBReader(CCBReader *pCCBReader);
    /**
     *  @js NA
     *  @lua NA
     */
    virtual ~CCBReader();
    /**
     *  @js ctor
     */
    CCBReader();


	static CCBReader* create( CCNodeLoaderLibrary *lib );

   
    void setCCBRootPath(const char* pCCBRootPath);
    const std::string& getCCBRootPath() const;
    /**
     *  @js load
     *  @lua NA
     */
    CCNode* readNodeGraphFromFile(const char *pCCBFileName);
    /**
     *  @js load
     *  @lua NA
     */
    CCNode* readNodeGraphFromFile(const char *pCCBFileName, CCObject *pOwner);
    /**
     *  @js load
     *  @lua NA
     */
    CCNode* readNodeGraphFromFile(const char *pCCBFileName, CCObject *pOwner, const CCSize &parentSize);
    /**
     *  @js NA
     *  @lua NA
     */
    CCNode* readNodeGraphFromData(CCData *pData, CCObject *pOwner, const CCSize &parentSize);
    /**
     *  @js loadScene
     *  @lua NA
     */
    CCScene* createSceneWithNodeGraphFromFile(const char *pCCBFileName);
    /**
     *  @js loadScene
     *  @lua NA
     */
    CCScene* createSceneWithNodeGraphFromFile(const char *pCCBFileName, CCObject *pOwner);
    /**
     *  @js loadScene
     *  @lua NA
     */
    CCScene* createSceneWithNodeGraphFromFile(const char *pCCBFileName, CCObject *pOwner, const CCSize &parentSize);
    /**
     *  @js NA
     *  @lua NA
     */
    CCBMemberVariableAssigner* getCCBMemberVariableAssigner();
    /**
     *  @js NA
     *  @lua NA
     */
    CCBSelectorResolver* getCCBSelectorResolver();
    /**
     *  @js getActionManager
     */
    CCBAnimationManager* getAnimationManager();
    /**
     *  @js setActionManager
     */
    void setAnimationManager(CCBAnimationManager *pAnimationManager);
    
    /** Used in CCNodeLoader::parseProperties()
     *  @js NA
     *  @lua NA
     */
    std::set<std::string>* getAnimatedProperties();
    /**
     *  @js NA
     *  @lua NA
     */
    std::set<std::string>& getLoadedSpriteSheet();
    CCObject* getOwner();

    /** Utility methods. 
     *  @js NA
     *  @lua NA
     */
    static std::string lastPathComponent(const char* pString);
    /**
     *  @js NA
     *  @lua NA
     */
    static std::string deletePathExtension(const char* pString);
    /**
     *  @js NA
     *  @lua NA
     */
    static std::string toLowerCase(const char* pCCString);
    /**
     *  @js NA
     *  @lua NA
     */
    static bool endsWith(const char* pString, const char* pEnding);

    /** Parse methods. 
     *  @js NA
     *  @lua NA
     */
    int readInt(bool pSigned);
    /**
     *  @js NA
     *  @lua NA
     */
    unsigned char readByte();
    /**
     *  @js NA
     *  @lua NA
     */
    bool readBool();
    std::string readUTF8();
    /**
     *  @js NA
     *  @lua NA
     */
    float readFloat();
    /**
     *  @js NA
     *  @lua NA
     */
    std::string readCachedString();
    /**
     *  @js NA
     *  @lua NA
     */
    bool isJSControlled();
            
    
    bool readCallbackKeyframesForSeq(CCBSequence* seq);
    bool readSoundKeyframesForSeq(CCBSequence* seq);


    
    CCArray* getOwnerCallbackNames();
    CCArray* getOwnerCallbackNodes();
    CCArray* getOwnerCallbackControlEvents();
    CCArray* getOwnerOutletNames();
    CCArray* getOwnerOutletNodes();
    CCArray* getNodesWithAnimationManagers();
    CCArray* getAnimationManagersForNodes();
    /**
     *  @js NA
     *  @lua NA
     */
    CCDictionary* getAnimationManagers();
    /**
     *  @js NA
     */
    void setAnimationManagers(CCDictionary* x);  // weak reference
    /**
     *  @js NA
     *  @lua NA
     */
    void addOwnerCallbackName(const std::string& name);
    /**
     *  @js NA
     *  @lua NA
     */
    void addOwnerCallbackNode(CCNode *node);
     /**
     *  @js NA
     *  @lua NA
     */
    void addOwnerCallbackControlEvents(CCControlEvent type);
    /**
     *  @js NA
     *  @lua NA
     */
    void addDocumentCallbackName(const std::string& name);
    /**
     *  @js NA
     *  @lua NA
     */
    void addDocumentCallbackNode(CCNode *node);
    /**
     *  @js NA
     *  @lua NA
     */
    void addDocumentCallbackControlEvents(CCControlEvent eventType);
    /**
     *  @js NA
     *  @lua NA
     */
    static float getResolutionScale();
    static void setResolutionScale(float scale);
    /**
     *  @js NA
     *  @lua NA
     */
    CCNode* readFileWithCleanUp(bool bCleanUp, CCDictionary* am);
    
    void addOwnerOutletName(std::string name);
    void addOwnerOutletNode(CCNode *node);

private:
    void cleanUpNodeGraph(CCNode *pNode);
    bool readSequences();
    CCBKeyframe* readKeyframe(int type);
    
    bool readHeader();
    bool readStringCache();
    //void readStringCacheEntry();
    CCNode* readNodeGraph();
    CCNode* readNodeGraph(CCNode * pParent);

    bool getBit();
    void alignBits();

    friend class CCNodeLoader;
};

// end of effects group
/// @}

NS_CC_EXT_END

#endif
