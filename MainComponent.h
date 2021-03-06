#pragma once

// CMake builds don't use an AppConfig.h, so it's safe to include juce module headers
// directly. If you need to remain compatible with Projucer-generated builds, and
// have called `juce_generate_juce_header(<thisTarget>)` in your CMakeLists.txt,
// you could `#include <JuceHeader.h>` here instead, to make all your module headers visible.
#include <juce_gui_extra/juce_gui_extra.h>

#include "TetrisGrid.hpp"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent   : public juce::Component
                      , public juce::KeyListener
{
public:
    
    MainComponent();
    void paint (juce::Graphics&) override;
    void resized() override;
    bool keyPressed (const juce::KeyPress &key, juce::Component* originatingComponent) override; // compiler warning
    
private:
    
    juce::Label m_lines_remaining_label;
    juce::Label m_lines_remaining_value;
    juce::Label m_time_label;
    juce::Label m_time_value;
    juce::Label m_hold_label;
    juce::Label m_next_label;
    TetrisGrid m_tetris_grid;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
