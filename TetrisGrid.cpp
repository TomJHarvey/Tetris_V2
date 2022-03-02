//
//  TetrisGrid.cpp
//  TetrisApp
//
//  Created by Tom Harvey on 01/03/2022.
//

#include "TetrisGrid.hpp"
#include "GuiDimensions.h"

static int counter = 0;

TetrisGrid::TetrisGrid()
{
    spawnPiece(PieceType::j); // the piece type will be passed in from constructor too
}

void
TetrisGrid::spawnPiece(const PieceType& piece_type) // pass in piece type
{
    m_current_piece = Tetrimino::getPiece(piece_type);
}

void TetrisGrid::paint(juce::Graphics& g)
{
    g.fillAll (juce::Colours::black);
    
    // pre grid bar
    g.setColour(juce::Colours::slategrey);
    g.drawRect (0, 0, gui::scaled_grid_width, gui::square_size);
    g.fillRect (0, 0, gui::scaled_grid_width, gui::square_size);
    
    g.setColour(juce::Colours::grey);
    
    // horizontal grid lines
    for (int vertical_line = 0; vertical_line <= gui::grid_width; vertical_line ++)
    {
        g.drawLine(vertical_line * gui::square_size,
                   gui::square_size,
                   vertical_line * gui::square_size,
                   getHeight());
    }
    
    // vertical grid lines
    for (int horizontal_line = 0; horizontal_line <= gui::grid_height; horizontal_line ++)
    {
        g.drawLine(0,
                   gui::square_size + (horizontal_line * gui::square_size),
                   getWidth(),
                   gui::square_size + (horizontal_line * gui::square_size));
    }
    
    
    
    int x_position = m_current_piece.m_x_pos;
    int y_position = m_current_piece.m_y_pos;
    
    // can i be assured that while its painting the variables stay the same?
    
    // Draw each rectangle of the tetrimino here
    for (const auto& row : m_current_piece.m_tiles)
    {
        for (const auto tile : row)
        {
            if (tile == true)
            {
                g.drawRect (x_position, y_position, gui::square_size, gui::square_size);
                g.fillRect (x_position, y_position, gui::square_size, gui::square_size);
            }
            
            x_position += gui::square_size;
        }
        x_position = m_current_piece.m_x_pos; // this is for the current position not snapping to the top, threading?
        y_position += gui::square_size;
    }
    
    std::cout << counter << std::endl;
    counter++;
}

void TetrisGrid::resized()
{
    //setSize(m_width, m_length);
}
