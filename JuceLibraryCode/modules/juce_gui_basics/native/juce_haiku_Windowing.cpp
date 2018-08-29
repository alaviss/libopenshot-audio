/*
  ==============================================================================

   This file is part of the JUCE library.
   Copyright (c) 2015 - ROLI Ltd.

   Permission is granted to use this software under the terms of either:
   a) the GPL v2 (or any later version)
   b) the Affero GPL v3

   Details of these licenses can be found at: www.gnu.org/licenses

   JUCE is distributed in the hope that it will be useful, but WITHOUT ANY
   WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
   A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

   ------------------------------------------------------------------------------

   To release a closed-source product which uses JUCE, commercial licenses are
   available: visit www.juce.com for more information.

  ==============================================================================
*/



//==============================================================================
static int numAlwaysOnTopPeers = 0;

bool juce_areThereAnyAlwaysOnTopWindows()
{
    return numAlwaysOnTopPeers > 0;
}

//==============================================================================
class HaikuComponentPeer  : public ComponentPeer
{
public:
    HaikuComponentPeer (Component& comp, const int windowStyleFlags)
        : ComponentPeer (comp, windowStyleFlags),
          fullScreen (false), mapped (false),
          depth (0),
          isAlwaysOnTop (comp.isAlwaysOnTop()),
          currentScaleFactor (1.0)
    {
        // it's dangerous to create a window on a thread other than the message thread..
        jassert (MessageManager::getInstance()->currentThreadHasLockedMessageManager());

        if (isAlwaysOnTop)
            ++numAlwaysOnTopPeers;

        
        setTitle (component.getName());
    }

    ~HaikuComponentPeer()
    {
        // it's dangerous to delete a window on a thread other than the message thread..
        jassert (MessageManager::getInstance()->currentThreadHasLockedMessageManager());

        if (isAlwaysOnTop)
            --numAlwaysOnTopPeers;
    }

    //==============================================================================
    void* getNativeHandle() const override
    {
        return (void*) NULL;
    }


    void setVisible (bool shouldBeVisible) override
    {
        // TODO
    }

    void setTitle (const String& title) override
    {
        // TODO
    }

    void setBounds (const Rectangle<int>& newBounds, bool isNowFullScreen) override
    {
        if (fullScreen && ! isNowFullScreen)
        {
        	// TODO
        }

        fullScreen = isNowFullScreen;

        // TODO
    }

    Rectangle<int> getBounds() const override          { return bounds; }

    Point<float> localToGlobal (Point<float> relativePosition) override
    {
        return relativePosition + bounds.getPosition().toFloat();
    }

    Point<float> globalToLocal (Point<float> screenPosition) override
    {
        return screenPosition - bounds.getPosition().toFloat();
    }

    void setAlpha (float /* newAlpha */) override
    {
        //xxx todo!
    }

    StringArray getAvailableRenderingEngines() override
    {
        return StringArray ("Software Renderer");
    }

    void setMinimised (bool shouldBeMinimised) override
    {
        if (shouldBeMinimised)
        {
            // TODO
        }
        else
        {
            setVisible (true);
        }
    }

    bool isMinimised() const override
    {
    	// TODO
        return false;
    }

    void setFullScreen (const bool shouldBeFullScreen) override
    {
        Rectangle<int> r (lastNonFullscreenBounds); // (get a copy of this before de-minimising)

        setMinimised (false);

        if (fullScreen != shouldBeFullScreen)
        {
            // TODO
            component.repaint();
        }
    }

    bool isFullScreen() const override
    {
        return fullScreen;
    }

    bool isFrontWindow() const
    {
    	// TODO
        return false;
    }

    bool contains (Point<int> localPos, bool trueIfInAChildWindow) const override
    {
        // TODO
		return false;
    }

    BorderSize<int> getFrameSize() const override
    {
        return BorderSize<int>();
    }

    bool setAlwaysOnTop (bool /* alwaysOnTop */) override
    {
        return false;
    }

    void toFront (bool makeActive) override
    {
        if (makeActive)
        {
            setVisible (true);
        }
        // TODO
        handleBroughtToFront();
    }

    void toBehind (ComponentPeer* other) override
    {
        if (HaikuComponentPeer* const otherPeer = dynamic_cast<HaikuComponentPeer*> (other))
        {
            setMinimised (false);
			// TODO
        }
        else
            jassertfalse; // wrong type of window?
    }

    bool isFocused() const override
    {
		return true;
    }

    void grabFocus() override
    {
    }

    void textInputRequired (Point<int>, TextInputTarget&) override {}

	void repaint (const Rectangle<int>& area) override
    {
        // TODO
    }

    void performAnyPendingRepaintsNow() override
    {
        // TODO
    }

    void setIcon (const Image& newIcon) override
    {
    	// TODO
    }
    
    //==============================================================================
    double getCurrentScale() noexcept
    {
        return currentScaleFactor;
    }


    //==============================================================================
    bool dontRepaint;

	static ModifierKeys currentModifiers;
    static bool isActiveApplication;

private:

    Rectangle<int> bounds;
    Image taskbarImage;
    bool fullScreen, mapped;
    int depth;
    BorderSize<int> windowBorder;
    bool isAlwaysOnTop;
    double currentScaleFactor;
    enum { KeyPressEventType = 2 };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HaikuComponentPeer)
};

ModifierKeys HaikuComponentPeer::currentModifiers;
bool HaikuComponentPeer::isActiveApplication = false;

//==============================================================================
JUCE_API bool JUCE_CALLTYPE Process::isForegroundProcess()
{
    return HaikuComponentPeer::isActiveApplication;
}

JUCE_API void JUCE_CALLTYPE Process::makeForegroundProcess() {}
JUCE_API void JUCE_CALLTYPE Process::hide() {}

//==============================================================================
bool KeyPress::isKeyCurrentlyDown (const int keyCode)
{
    // TODO
    return false;
}

void ModifierKeys::updateCurrentModifiers() noexcept
{
    currentModifiers = HaikuComponentPeer::currentModifiers;
}

ModifierKeys ModifierKeys::getCurrentModifiersRealtime() noexcept
{
	// TODO
    return HaikuComponentPeer::currentModifiers;
}


//==============================================================================
void Desktop::setKioskComponent (Component* comp, bool enableOrDisable, bool /* allowMenusAndBars */)
{
    if (enableOrDisable)
        comp->setBounds (getDisplays().getMainDisplay().totalArea);
}

//==============================================================================
ComponentPeer* Component::createNewPeer (int styleFlags, void* nativeWindowToAttachTo)
{
    return new HaikuComponentPeer (*this, styleFlags);
}

//==============================================================================
void Desktop::Displays::findDisplays (float masterScale)
{
}

//==============================================================================
bool MouseInputSource::SourceList::addSource()
{
    if (sources.size() == 0)
    {
        addSource (0, true);
        return true;
    }

    return false;
}

bool Desktop::canUseSemiTransparentWindows() noexcept
{
    return false;
}

Point<float> MouseInputSource::getCurrentRawMousePosition()
{
    // TODO
    return Point<float>();
}

void MouseInputSource::setRawMousePosition (Point<float> newPosition)
{
		// TODO
}

double Desktop::getDefaultMasterScale()
{
    return 1.0;
}

Desktop::DisplayOrientation Desktop::getCurrentOrientation() const
{
    return upright;
}

//==============================================================================
static bool screenSaverAllowed = true;

void Desktop::setScreenSaverEnabled (const bool isEnabled)
{
    if (screenSaverAllowed != isEnabled)
    {
        screenSaverAllowed = isEnabled;

        // TODO
    }
}

bool Desktop::isScreenSaverEnabled()
{
    return screenSaverAllowed;
}

//==============================================================================
void* CustomMouseCursorInfo::create() const
{
    // TODO
    return NULL;
}

void MouseCursor::deleteMouseCursor (void* const cursorHandle, const bool)
{
    if (cursorHandle != nullptr)
    {
    }
}

void* MouseCursor::createStandardMouseCursor (MouseCursor::StandardCursorType type)
{
    // TODO
    return NULL;
}

void MouseCursor::showInWindow (ComponentPeer* peer) const
{
    if (HaikuComponentPeer* const lp = dynamic_cast<HaikuComponentPeer*> (peer))
    {
    	// TODO
    }
}

void MouseCursor::showInAllWindows() const
{
    for (int i = ComponentPeer::getNumPeers(); --i >= 0;)
        showInWindow (ComponentPeer::getPeer (i));
}

//==============================================================================
Image juce_createIconForFile (const File& /* file */)
{
    return Image::null;
}

//==============================================================================
bool DragAndDropContainer::performExternalDragDropOfFiles (const StringArray& files, const bool canMoveFiles)
{
    if (files.size() == 0)
        return false;

    if (MouseInputSource* draggingSource = Desktop::getInstance().getDraggingMouseSource(0))
        if (Component* sourceComp = draggingSource->getComponentUnderMouse())
            if (HaikuComponentPeer* const lp = dynamic_cast<HaikuComponentPeer*> (sourceComp->getPeer())) {
                // TODO
                return false;
            }

    // This method must be called in response to a component's mouseDown or mouseDrag event!
    jassertfalse;
    return false;
}

bool DragAndDropContainer::performExternalDragDropOfText (const String& text)
{
    if (text.isEmpty())
        return false;

    if (MouseInputSource* draggingSource = Desktop::getInstance().getDraggingMouseSource(0))
        if (Component* sourceComp = draggingSource->getComponentUnderMouse())
            if (HaikuComponentPeer* const lp = dynamic_cast<HaikuComponentPeer*> (sourceComp->getPeer())) {
            	// TODO
                return false; 
            }

    // This method must be called in response to a component's mouseDown or mouseDrag event!
    jassertfalse;
    return false;
}

//==============================================================================
void LookAndFeel::playAlertSound()
{
    std::cout << "\a" << std::flush;
}
//==============================================================================
Rectangle<int> juce_HaikuScaledToPhysicalBounds(ComponentPeer* peer, const Rectangle<int>& bounds)
{
    Rectangle<int> retval = bounds;

    if (HaikuComponentPeer* haikuPeer = dynamic_cast<HaikuComponentPeer*> (peer))
        retval *= haikuPeer->getCurrentScale();

    return retval;
}

void juce_HaikuAddRepaintListener (ComponentPeer* peer, Component* dummy)
{
}

void juce_HaikuRemoveRepaintListener (ComponentPeer* peer, Component* dummy)
{
}

//==============================================================================
#if JUCE_MODAL_LOOPS_PERMITTED
void JUCE_CALLTYPE NativeMessageBox::showMessageBox (AlertWindow::AlertIconType iconType,
                                                     const String& title, const String& message,
                                                     Component* /* associatedComponent */)
{
    AlertWindow::showMessageBox (iconType, title, message);
}
#endif

void JUCE_CALLTYPE NativeMessageBox::showMessageBoxAsync (AlertWindow::AlertIconType iconType,
                                                          const String& title, const String& message,
                                                          Component* associatedComponent,
                                                          ModalComponentManager::Callback* callback)
{
    AlertWindow::showMessageBoxAsync (iconType, title, message, String::empty, associatedComponent, callback);
}

bool JUCE_CALLTYPE NativeMessageBox::showOkCancelBox (AlertWindow::AlertIconType iconType,
                                                      const String& title, const String& message,
                                                      Component* associatedComponent,
                                                      ModalComponentManager::Callback* callback)
{
    return AlertWindow::showOkCancelBox (iconType, title, message, String::empty, String::empty,
                                         associatedComponent, callback);
}

int JUCE_CALLTYPE NativeMessageBox::showYesNoCancelBox (AlertWindow::AlertIconType iconType,
                                                        const String& title, const String& message,
                                                        Component* associatedComponent,
                                                        ModalComponentManager::Callback* callback)
{
    return AlertWindow::showYesNoCancelBox (iconType, title, message,
                                            String::empty, String::empty, String::empty,
                                            associatedComponent, callback);
}

//==============================================================================
const int extendedKeyModifier       = 0x10000;

const int KeyPress::spaceKey        = ' ';
const int KeyPress::returnKey       = 66;
const int KeyPress::escapeKey       = 4;
const int KeyPress::backspaceKey    = 67;
const int KeyPress::leftKey         = extendedKeyModifier + 1;
const int KeyPress::rightKey        = extendedKeyModifier + 2;
const int KeyPress::upKey           = extendedKeyModifier + 3;
const int KeyPress::downKey         = extendedKeyModifier + 4;
const int KeyPress::pageUpKey       = extendedKeyModifier + 5;
const int KeyPress::pageDownKey     = extendedKeyModifier + 6;
const int KeyPress::endKey          = extendedKeyModifier + 7;
const int KeyPress::homeKey         = extendedKeyModifier + 8;
const int KeyPress::deleteKey       = extendedKeyModifier + 9;
const int KeyPress::insertKey       = -1;
const int KeyPress::tabKey          = 61;
const int KeyPress::F1Key           = extendedKeyModifier + 10;
const int KeyPress::F2Key           = extendedKeyModifier + 11;
const int KeyPress::F3Key           = extendedKeyModifier + 12;
const int KeyPress::F4Key           = extendedKeyModifier + 13;
const int KeyPress::F5Key           = extendedKeyModifier + 14;
const int KeyPress::F6Key           = extendedKeyModifier + 16;
const int KeyPress::F7Key           = extendedKeyModifier + 17;
const int KeyPress::F8Key           = extendedKeyModifier + 18;
const int KeyPress::F9Key           = extendedKeyModifier + 19;
const int KeyPress::F10Key          = extendedKeyModifier + 20;
const int KeyPress::F11Key          = extendedKeyModifier + 21;
const int KeyPress::F12Key          = extendedKeyModifier + 22;
const int KeyPress::F13Key          = extendedKeyModifier + 23;
const int KeyPress::F14Key          = extendedKeyModifier + 24;
const int KeyPress::F15Key          = extendedKeyModifier + 25;
const int KeyPress::F16Key          = extendedKeyModifier + 26;
const int KeyPress::numberPad0      = extendedKeyModifier + 27;
const int KeyPress::numberPad1      = extendedKeyModifier + 28;
const int KeyPress::numberPad2      = extendedKeyModifier + 29;
const int KeyPress::numberPad3      = extendedKeyModifier + 30;
const int KeyPress::numberPad4      = extendedKeyModifier + 31;
const int KeyPress::numberPad5      = extendedKeyModifier + 32;
const int KeyPress::numberPad6      = extendedKeyModifier + 33;
const int KeyPress::numberPad7      = extendedKeyModifier + 34;
const int KeyPress::numberPad8      = extendedKeyModifier + 35;
const int KeyPress::numberPad9      = extendedKeyModifier + 36;
const int KeyPress::numberPadAdd            = extendedKeyModifier + 37;
const int KeyPress::numberPadSubtract       = extendedKeyModifier + 38;
const int KeyPress::numberPadMultiply       = extendedKeyModifier + 39;
const int KeyPress::numberPadDivide         = extendedKeyModifier + 40;
const int KeyPress::numberPadSeparator      = extendedKeyModifier + 41;
const int KeyPress::numberPadDecimalPoint   = extendedKeyModifier + 42;
const int KeyPress::numberPadEquals         = extendedKeyModifier + 43;
const int KeyPress::numberPadDelete         = extendedKeyModifier + 44;
const int KeyPress::playKey         = extendedKeyModifier + 45;
const int KeyPress::stopKey         = extendedKeyModifier + 46;
const int KeyPress::fastForwardKey  = extendedKeyModifier + 47;
const int KeyPress::rewindKey       = extendedKeyModifier + 48;
