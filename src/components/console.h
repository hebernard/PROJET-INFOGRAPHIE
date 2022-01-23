#pragma once
#include "ofxDatGuiComponent.h"
#include "ofxDatGui.h"

class consoleItem : public ofxDatGuiLabel {

    friend class console;

public:

    consoleItem(string label, int index) : ofxDatGuiLabel(label)
    {
        mIndex = index;
    }

    int getIndex()
    {
        return mIndex;
    }

private:

    int mIndex;

};

class console : public ofxDatGuiComponent
{
public:
    console(string name, int nVisible = 6) : ofxDatGuiComponent(name)
    {
        window = new ofxDatGui();
        header = window->addHeader(name, false);
        header->setEnabled(false);
        header->setLabelUpperCase(false);

        clearButton = new ofxDatGuiButton("Clear");
        clearButton->setStripeVisible(false);
        clearButton->setLabelAlignment(ofxDatGuiAlignment::CENTER);
        clearButton->onButtonEvent(this, &console::onClearButtonClicked);

        mAutoHeight = true;
        mNumVisible = nVisible;
        setTheme(ofxDatGuiComponent::getTheme());
        ofAddListener(ofEvents().mouseScrolled, this, &console::onMouseScrolled, OF_EVENT_ORDER_BEFORE_APP);
    }

    ~console()
    {
        mTheme = nullptr;
        window = nullptr;
        header = nullptr;
        clearButton = nullptr;
        ofRemoveListener(ofEvents().mouseScrolled, this, &console::onMouseScrolled, OF_EVENT_ORDER_BEFORE_APP);
    }

    void onClearButtonClicked(ofxDatGuiButtonEvent e)
    {
        clear();
    }

    void log(string label, ofLogLevel logLevel = ofLogLevel::OF_LOG_NOTICE)
    {
        int y = 0;
        if (mItems.size() > 0) y = mItems.back()->getY() + mItems.back()->getHeight() + mSpacing;
        mItems.push_back(new consoleItem(label, mItems.size()));
        mItems.back()->setMask(mRect);
        mItems.back()->setTheme(mTheme);
        mItems.back()->setWidth(mRect.width, 0);
        mItems.back()->setPosition(0, y);
        mItems.back()->setStripeColor(getStripeColor(logLevel));
        if (mAutoHeight) autoSize();

        scrollToBottom();
    }

    ofColor getStripeColor(ofLogLevel logLevel)
    {
        switch (logLevel)
        {
            case OF_LOG_WARNING:
                return ofColor::yellow;
            case OF_LOG_ERROR:
            case OF_LOG_FATAL_ERROR:
                return ofColor::red;
            default:
                return ofColor::white;
        }
    }

    void clear()
    {
        for (auto i : mItems) delete i;
        mItems.clear();
    }

#pragma region mRect
    /*
        temporary getters until mRect is implemented in ofxDatGuiComponent
    */
    int getX()
    {
        return mRect.x;
    }

    int getY()
    {
        return mRect.y;
    }

    int getWidth()
    {
        return mRect.width;
    }

    int getHeight()
    {
        return mRect.height;
    }

    int getNumItems()
    {
        return mItems.size();
    }
#pragma endregion

    void setTheme(const ofxDatGuiTheme* theme)
    {
        mTheme = theme;
        mSpacing = theme->layout.vMargin;
        mBackground = theme->color.guiBackground;
        for (auto i : mItems) i->setTheme(theme);
        setWidth(theme->layout.width, theme->layout.labelWidth);
    }

    void setWidth(int width, float labelWidth = 1)
    {
        mRect.width = width;
        for (auto i : mItems) i->setWidth(mRect.width, labelWidth);
        if (mAutoHeight) autoSize();
    }

    void setHeight(int height)
    {
        mAutoHeight = false;
        mRect.height = height;
        if (mRect.width > 0 && mRect.height > 0) mView.allocate(mRect.width, mRect.height);
    }

    void setPosition(int x, int y)
    {
        window->setPosition(x, y);

        mRect.x = x;
        mRect.y = y + header->getHeight();
        // update each component's mask so mouse events track correctly //
        for (int i = 0; i < mItems.size(); i++) mItems[i]->setMask(mRect);

        clearButton->setPosition(getX(), getY() + getHeight());
    }

    void setItemSpacing(int spacing)
    {
        mSpacing = spacing;
    }

    void setBackgroundColor(ofColor color)
    {
        mBackground = color;
    }

    void setScrollMultiplier(int num)
    {
        scrollMultiplier = num;
    }

    void update()
    {
        for (auto i : mItems) i->update();
        clearButton->update();

        // Anchor bottom-right
        int fullHeight = header->getHeight() + getHeight() + clearButton->getHeight();
        setPosition(ofGetWidth() - getWidth(), ofGetHeight() - fullHeight);
    }

    void draw()
    {
        ofPushStyle();
        ofFill();
        mView.begin();
        ofClear(255, 255, 255, 0);
        ofSetColor(mBackground);
        ofDrawRectRounded(0, 0, mRect.width, mRect.height, 0);
        for (auto i : mItems) i->draw();
        mView.end();
        // draw the fbo of list content //
        ofSetColor(ofColor::white);
        mView.draw(mRect.x, mRect.y);
        clearButton->draw();
        ofPopStyle();
    }

private:

    ofFbo mView;
    ofRectangle mRect;
    ofColor mBackground;
    const ofxDatGuiTheme* mTheme;
    ofxDatGui* window;
    ofxDatGuiHeader* header;
    ofxDatGuiButton* clearButton;

    int mY = 0;
    int mSpacing;
    int mNumVisible;
    bool mAutoHeight;
    int scrollMultiplier = 20;
    vector<consoleItem*> mItems;

    void autoSize()
    {
        mRect.height = ((mTheme->layout.height + mSpacing) * mNumVisible) - mSpacing;
        if (mRect.width > 0 && mRect.height > 0) mView.allocate(mRect.width, mRect.height);
    }

    void onMouseScrolled(ofMouseEventArgs& e)
    {
        if (mItems.size() > 0 && mRect.inside(e.x, e.y) == true) {
            float sy = e.scrollY * scrollMultiplier;
            int btnH = mItems.front()->getHeight() + mSpacing;
            int minY = mRect.height + mSpacing - (mItems.size() * btnH);
            bool allowScroll = false;
            mY = mItems.front()->getY();

            if (sy < 0)
            {
                if (mY > minY)
                {
                    mY += sy;
                    if (mY < minY)
                    {
                        mY = minY;
                    }
                    allowScroll = true;
                }
            }
            else if (sy > 0)
            {
                if (mY < 0) {
                    mY += sy;
                    if (mY > 0)
                    {
                        mY = 0;
                    }
                    allowScroll = true;
                }
            }

            if (allowScroll)
            {
                for (int i = 0; i < mItems.size(); i++)
                {
                    mItems[i]->setPosition(0, mY + (btnH * i));
                }
            }
        }
    }

    void scrollToBottom()
    {
        int btnH = mItems.front()->getHeight() + mSpacing;
        int minY = mRect.height + mSpacing - (mItems.size() * btnH);
        for (int i = 0; i < mItems.size(); i++)
        {
            mItems[i]->setPosition(0, minY + (btnH * i));
        }
    }
};
