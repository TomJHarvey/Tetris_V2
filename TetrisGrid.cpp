//
//  TetrisGrid.cpp
//  TetrisApp
//
//  Created by Tom Harvey on 01/03/2022.
//

#include "TetrisGrid.hpp"


TetrisGrid::TetrisGrid(int width, int length, int square_size)
    : m_width(width)
    , m_length(length)
    , m_square_size(square_size)
{
}


void TetrisGrid::paint(juce::Graphics& g)
{
    g.fillAll (juce::Colours::black);
    g.setColour(juce::Colours::grey);
    // horizontal grid lines
    for (int vertical_line = 0; vertical_line <= m_width; vertical_line ++)
    {
        g.drawLine(vertical_line * m_square_size,
                   0,
                   vertical_line * m_square_size,
                   getHeight());
    }
    
    // vertical grid lines
    for (int horizontal_line = 0; horizontal_line <= m_length; horizontal_line ++)
    {
        g.drawLine(0,
                   horizontal_line * m_square_size,
                   getWidth(),
                   horizontal_line * m_square_size);
    }
}

void TetrisGrid::resized()
{
    //setSize(m_width, m_length);
}
