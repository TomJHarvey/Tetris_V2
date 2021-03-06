#include "MainComponent.h"
#include "GuiDimensions.h"
#include "Tetrimino.hpp"

static const int key_press_up = 63232;
static const int key_press_space = 32;

MainComponent::MainComponent()
{
    setSize(gui::window_width, gui::window_height);
    
    m_lines_remaining_label.setText(gui::lines_remaining_text, juce::sendNotification);
    addAndMakeVisible(m_lines_remaining_label);
    
    m_lines_remaining_value.setText(gui::lines_remaining_amount, juce::sendNotification);
    addAndMakeVisible(m_lines_remaining_value);
    
    m_time_label.setText(gui::time_elapsed_text, juce::sendNotification);
    addAndMakeVisible(m_time_label);

    m_time_value.setText(gui::time_elapsed_mins, juce::sendNotification);
    addAndMakeVisible(m_time_value);
    
    m_hold_label.setText(gui::hold_text, juce::sendNotification);
    addAndMakeVisible(m_hold_label);
    
    m_next_label.setText(gui::next_tetrimino_text, juce::sendNotification);
    addAndMakeVisible(m_next_label);
    
    m_tetris_grid.setBounds(gui::side_bar_length,
                            0,
                            gui::scaled_grid_width,
                            gui::scaled_grid_height);
    
    addAndMakeVisible(m_tetris_grid);
    setWantsKeyboardFocus(true);    // Enable use of the keyboard
    addKeyListener(this);
}

bool
MainComponent::keyPressed(const juce::KeyPress &key, juce::Component* originatingComponent)
{
    juce::ignoreUnused(originatingComponent);
    
    int key_code = key.getKeyCode();
    DBG(key_code);
    
    if (key_code == static_cast<int>(Direction::left) ||
        key_code == static_cast<int>(Direction::right) ||
        key_code == static_cast<int>(Direction::down))
    {
        (void)m_tetris_grid.movePiece(static_cast<Direction>(key_code));
    }
    else if (key_code == key_press_up) // create constant, this will also pass in the direction
    {
        m_tetris_grid.rotatePiece();
    }
    else if (key_code == key_press_space)
    {
        bool hard_drop_complete = false;
        while (!hard_drop_complete)
        {
            hard_drop_complete = m_tetris_grid.movePiece(Direction::down);
        }
    }
    return true;
}

void
MainComponent::paint(juce::Graphics& g)
{
    // left side bar
    g.setColour (juce::Colours::purple);
    g.drawRect (0, 0, gui::side_bar_length, getHeight());
    g.fillRect (0, 0, gui::side_bar_length, getHeight());

    // right side bar
    g.setColour (juce::Colours::purple);
    g.drawRect (getWidth() - gui::side_bar_length, 0, gui::side_bar_length, getHeight());
    g.fillRect (getWidth() - gui::side_bar_length, 0, gui::side_bar_length, getHeight());
    
    // hold area
    g.setColour(juce::Colours::black);
    g.drawRect(gui::sidebar_element_offset,
               gui::sidebar_background_square_ypos,
               gui::sidebar_square_length,
               gui::sidebar_square_length);
    
    g.fillRect(gui::sidebar_element_offset,
               gui::sidebar_background_square_ypos,
               gui::sidebar_square_length,
               gui::sidebar_square_length);
    
    // hold label
    m_hold_label.setBounds(gui::sidebar_element_offset,
                           gui::sidebar_top_text_label_height,
                           gui::sidebar_square_length,
                           gui::square_size);
    
    // next tetrimino area
    g.setColour(juce::Colours::black);
    g.drawRect(gui::right_sidebar_xpos,
               gui::sidebar_background_square_ypos,
               gui::sidebar_square_length,
               gui::sidebar_square_length);
    
    g.fillRect(gui::right_sidebar_xpos,
               gui::sidebar_background_square_ypos,
               gui::sidebar_square_length,
               gui::sidebar_square_length);
    
    // next label
    m_next_label.setBounds(gui::right_sidebar_xpos,
                           gui::sidebar_top_text_label_height,
                           gui::sidebar_square_length,
                           gui::square_size);
    
    // time remaining label and value
    m_lines_remaining_label.setBounds(gui::sidebar_element_offset,
                                      gui::sidebar_bottom_text_label_ypos,
                                      gui::sidebar_square_length,
                                      gui::square_size);
    
    m_lines_remaining_value.setBounds(gui::sidebar_element_offset,
                                      gui::sidebar_bottom_value_label_ypos,
                                      gui::sidebar_square_length,
                                      gui::square_size);
    
    // time elapsed label and value
    m_time_label.setBounds(gui::right_sidebar_xpos,
                           gui::sidebar_bottom_text_label_ypos,
                           gui::sidebar_square_length,
                           gui::square_size);
    
    m_time_value.setBounds(gui::right_sidebar_xpos,
                           gui::sidebar_bottom_value_label_ypos,
                           gui::sidebar_square_length,
                           gui::square_size);
}

void
MainComponent::resized()
{
    setSize(gui::window_width, gui::window_height);   // disables resizing
}
