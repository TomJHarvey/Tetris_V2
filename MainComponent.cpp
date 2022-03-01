#include "MainComponent.h"

static const int square_size = 33; // determines size of whole window and contents.
static const int grid_width = 10;
static const int grid_height = 20;
static const int scaled_grid_width = grid_width * square_size;
static const int scaled_grid_height = grid_height * square_size;
static const int side_bar_length = 4 * square_size;
static const int pre_grid_bar = 1 * square_size;
static const int window_width = scaled_grid_width + (2 * side_bar_length);
static const int window_height = scaled_grid_height + pre_grid_bar;
static const char* lines_remaining_text = "Lines Remaining";
static const char* lines_remaining_amount = "40";
static const char* time_elapsed_text = "Time elapsed";
static const char* time_elapsed_mins = "00:00:00";
static const char* hold_text = "Hold";
static const char* next_tetrimino_text = "Next";

// used to offset position of elements in sidebar
static const int sidebar_offset = 3;

// the length in squares for elements used in the sidebar
static const int sidebar_length_multiplier = 4;

// the size of a square in the sidebar scaled down
const int sidebar_element_offset = square_size/sidebar_offset;

// the length of a side of a square that will be in the sidebar.
static const int sidebar_square_length =
    (square_size * sidebar_length_multiplier) - 2 * (sidebar_element_offset);

// the starting position of elements in the righthandside bar
const int right_sidebar_xpos =
    window_width - (square_size * sidebar_length_multiplier) + (sidebar_element_offset);

// the y position of the sidebar text values for hold and next
const int sidebar_top_text_label_height = (square_size * 2) + sidebar_element_offset;

// the y position of the sidebar text values for lines remaining and time elapsed
const int sidebar_bottom_text_label_ypos = (square_size * 14) + sidebar_element_offset;

// the y position of the sidebar values for lines remaining and time elapsed
const int sidebar_bottom_value_label_ypos = square_size * 15;

// the length of the background squares for the hold and next tetrimino display
const int sidebar_background_square_ypos = (3 * square_size) + sidebar_element_offset;


MainComponent::MainComponent()
{
    setSize(window_width, window_height);
    
    m_lines_remaining_label.setText(lines_remaining_text, juce::sendNotification);
    addAndMakeVisible(m_lines_remaining_label);
    
    m_lines_remaining_value.setText(lines_remaining_amount, juce::sendNotification);
    addAndMakeVisible(m_lines_remaining_value);
    
    m_time_label.setText(time_elapsed_text, juce::sendNotification);
    addAndMakeVisible(m_time_label);

    m_time_value.setText(time_elapsed_mins, juce::sendNotification);
    addAndMakeVisible(m_time_value);
    
    m_hold_label.setText(hold_text, juce::sendNotification);
    addAndMakeVisible(m_hold_label);
    
    m_next_label.setText(next_tetrimino_text, juce::sendNotification);
    addAndMakeVisible(m_next_label);
}

void MainComponent::paint(juce::Graphics& g)
{
    g.fillAll (juce::Colours::black);
    g.setColour(juce::Colours::grey);
    
    // horizontal grid lines
    for (int vertical_line = 0; vertical_line <= grid_width; vertical_line ++)
    {
        g.drawLine(side_bar_length + (vertical_line * square_size),
                   0,
                   side_bar_length + (vertical_line * square_size),
                   getHeight());
    }
    
    // vertical grid lines
    for (int horizontal_line = 0; horizontal_line <= grid_height; horizontal_line ++)
    {
        g.drawLine(side_bar_length,
                   pre_grid_bar + (horizontal_line * square_size),
                   getWidth() - side_bar_length,
                   pre_grid_bar + (horizontal_line * square_size));
    }

    // pre grid bar
    g.setColour(juce::Colours::slategrey);
    g.drawRect (side_bar_length, 0, scaled_grid_width, square_size);
    g.fillRect (side_bar_length, 0, scaled_grid_width, square_size);

    // left side bar
    g.setColour (juce::Colours::purple);
    g.drawRect (0, 0, side_bar_length, getHeight());
    g.fillRect (0, 0, side_bar_length, getHeight());

    // right side bar
    g.setColour (juce::Colours::purple);
    g.drawRect (getWidth() - side_bar_length, 0, side_bar_length, getHeight());
    g.fillRect (getWidth() - side_bar_length, 0, side_bar_length, getHeight());
    
    // hold area
    g.setColour(juce::Colours::black);
    g.drawRect(sidebar_element_offset,
               sidebar_background_square_ypos,
               sidebar_square_length,
               sidebar_square_length);
    
    g.fillRect(sidebar_element_offset,
               sidebar_background_square_ypos,
               sidebar_square_length,
               sidebar_square_length);
    
    // hold label
    m_hold_label.setBounds(sidebar_element_offset,
                           sidebar_top_text_label_height,
                           sidebar_square_length,
                           square_size);
    
    // next tetrimino area
    g.setColour(juce::Colours::black);
    g.drawRect(right_sidebar_xpos,
               sidebar_background_square_ypos,
               sidebar_square_length,
               sidebar_square_length);
    
    g.fillRect(right_sidebar_xpos,
               sidebar_background_square_ypos,
               sidebar_square_length,
               sidebar_square_length);
    
    // next label
    m_next_label.setBounds(right_sidebar_xpos,
                           sidebar_top_text_label_height,
                           sidebar_square_length,
                           square_size);
    
    // time remaining label and value
    m_lines_remaining_label.setBounds(sidebar_element_offset,
                                      sidebar_bottom_text_label_ypos,
                                      sidebar_square_length,
                                      square_size);
    
    m_lines_remaining_value.setBounds(sidebar_element_offset,
                                      sidebar_bottom_value_label_ypos,
                                      sidebar_square_length,
                                      square_size);
    
    // time elapsed label and value
    m_time_label.setBounds(right_sidebar_xpos,
                           sidebar_bottom_text_label_ypos,
                           sidebar_square_length,
                           square_size);
    
    m_time_value.setBounds(right_sidebar_xpos,
                           sidebar_bottom_value_label_ypos,
                           sidebar_square_length,
                           square_size);
}

void MainComponent::resized()
{
    setSize(window_width, window_height);   // disables resizing
}
