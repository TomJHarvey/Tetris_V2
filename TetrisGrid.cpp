//
//  TetrisGrid.cpp
//  TetrisApp
//
//  Created by Tom Harvey on 01/03/2022.
//

#include "TetrisGrid.hpp"
#include "GuiDimensions.h"

static const size_t number_of_kick_tests = 5;

static const std::vector<std::vector<KickDataPosition>> kick_data = {
    {{0,0}, {-1,0}, {-1, 1}, {0, -2}, {-1,-2}},     // KickDirection::start_to_right
    {{0,0}, {1,0}, {1, -1}, {0, 2}, {1, 2}},        // KickDirection::right_to_flipped
    {{0,0}, {1,0}, {1, 1}, {0, -2}, {1, -2}},       // KickDirection::flipped_to_left
    {{0,0}, {-1,0}, {-1, -1}, {0, 2}, {-1, 2}}      // KickDirection::flipped_to_left
};

TetrisGrid::TetrisGrid()
{
    line_counter.resize(gui::grid_height);
    spawnPiece(PieceType::j); // the piece type will be passed in from constructor too
    // make a listener class so that it can call maincomponent to spwan another piece
}

void
TetrisGrid::spawnPiece(const PieceType& piece_type) // pass in piece type
{
    m_current_piece = Tetrimino::getPiece(piece_type);
}

void
TetrisGrid::movePieceWithKeyPress(Direction direction)
{
    bool move_piece = true;
    int x_position = m_current_piece.m_x_pos;
    int y_position = m_current_piece.m_y_pos;
    int direction_multiplier = (direction == Direction::left ? -1 : 1);
    int& position = (direction == Direction::down ? y_position : x_position);
    
    for (const auto& row : m_current_piece.m_tiles)
    {
        for (const auto tile : row)
        {
            if (tile == true)
            {
                // test if hit pieces in grid first
                if (hitFallenPiece(direction, x_position, y_position, direction_multiplier))
                {
                    move_piece = false;
                    break;
                }
                // test if piece will hit sides or bottom of grid
                else if (hitSideLimit(direction, position, direction_multiplier))
                {
                    move_piece = false;
                    break;
                }
            }
            // increment the x position along
            x_position += gui::square_size;
        }
        // reset the x position
        x_position = m_current_piece.m_x_pos;
        
        // increment the y position for the next row
        y_position += gui::square_size;
    }
    
    if (move_piece != false)
    {
        if (direction == Direction::left ||
            direction == Direction::right)
        {
            m_current_piece.m_x_pos =
                m_current_piece.m_x_pos + (direction_multiplier * gui::square_size);
        }
        else if (direction == Direction::down)
        {
            m_current_piece.m_y_pos =
                m_current_piece.m_y_pos + (direction_multiplier * gui::square_size);
        }
        repaint();
    }
    else if (move_piece == false && direction == Direction::down)
    {
        setFallenPiece();
        spawnPiece(PieceType::j);
    }
}

bool
TetrisGrid::hitSideLimit(const Direction& direction,
                         const int& position,
                         const int& direction_multiplier) const
{
    bool result = false;
    if (direction == Direction::left)
    {
        result = (position + (direction_multiplier * (gui::square_size)) < 0);
    }
    else if (direction == Direction::right)
    {
        result = (position + (direction_multiplier * (gui::square_size)) >=
                  gui::scaled_grid_width);
    }
    else if (direction == Direction::down)
    {
        result = (position + (direction_multiplier * (gui::square_size)) >=
                  gui::scaled_grid_height);
    }
    
    return result;
}

bool
TetrisGrid::rotatedOutOfGrid(const int& x, const int& y) const
{
    bool result = false;
    if ( x < 0 || x >= gui::scaled_grid_width)
    {
        result = true;
    }
    if (y >= gui::scaled_grid_height)
    {
        result = true;
    }
    return result;
}

bool
TetrisGrid::hitFallenPiece(const Direction& direction,
                           const int& x_position,
                           const int& y_position,
                           const int& direction_multiplier) const
{
    bool result = false;
    if (direction == Direction::down)
    {
        result = matchCordinates(x_position,
                                 y_position + (direction_multiplier * (gui::square_size)));
    }
    else if (direction == Direction::left ||
             direction == Direction::right)
    {
        result = matchCordinates(x_position + (direction_multiplier * (gui::square_size)),
                                 y_position);
    }
    return result;
}

bool TetrisGrid::matchCordinates(int x_position, int y_position) const
{
    return (std::find_if(m_grid_squares.begin(),
                         m_grid_squares.end(),
            [x_position, y_position](const GridSquare &g) {
            return (g.x_position == x_position) &&
                   (g.y_position == y_position);}) != m_grid_squares.end());
}

void
TetrisGrid::rotatePiece()
{
    Tiles rotated_tiles = Tetrimino::rotatePiece(m_current_piece);
    
    bool matched_tile = false;
    int kick_offset_x = 0;
    int kick_offset_y = 0;
    std::size_t kick_direction = static_cast<size_t>(m_current_piece.kick_direction);
    for (std::size_t kick_test = 0; kick_test < number_of_kick_tests; kick_test ++)
    {
        int x_position = m_current_piece.m_x_pos;
        int y_position = m_current_piece.m_y_pos;
        matched_tile = false;
        for (const auto& row : rotated_tiles)
        {
            for (const auto tile : row)
            {
                if (tile == true)
                {
                    int kicked_x_position = x_position +
                        (kick_data[kick_direction][kick_test].x * (gui::square_size));
                    int kicked_y_position = y_position +
                        (kick_data[kick_direction][kick_test].y * (gui::square_size));
                    
                    if (matchCordinates(kicked_x_position, kicked_y_position))
                    {
                        matched_tile = true;
                        break;
                    }
                    else if (rotatedOutOfGrid(kicked_x_position, kicked_y_position))
                    {
                        matched_tile = true;
                        break;
                    }
                }
                
                // increment the x position along
                x_position += gui::square_size;
            }
            // reset the x position
            x_position = m_current_piece.m_x_pos;
            
            // increment the y position for the next row
            y_position += gui::square_size;
            
        }
        if (!matched_tile)
        {
                kick_offset_x = kick_data[kick_direction][kick_test].x;
                kick_offset_y = kick_data[kick_direction][kick_test].y;
                break;
        }
    }
    
    if (matched_tile == false)
    {
        m_current_piece.m_x_pos += (kick_offset_x * gui::square_size);
        m_current_piece.m_y_pos += (kick_offset_y * gui::square_size);
        
        // bit messy maybe...
        m_current_piece.kick_direction =
            static_cast<KickDirection>(static_cast<int>(m_current_piece.kick_direction) +  1);
        
        if (m_current_piece.kick_direction == KickDirection::full_rotation)
        {
            m_current_piece.kick_direction = KickDirection::start_to_right;
        }
        
        m_current_piece.m_tiles = rotated_tiles;
        repaint();
    }
}


void
TetrisGrid::setFallenPiece()
{
    // going through the vector happens 3 times, could it functions be passed in as arugments?
    // its used here, paint and movePieceWithKeyPress

    int x_position = m_current_piece.m_x_pos;
    int y_position = m_current_piece.m_y_pos;
    
    for (const auto& row : m_current_piece.m_tiles)
    {
        for (const auto tile : row)
        {
            if (tile == true)
            {
                m_grid_squares.push_back({x_position, y_position, m_current_piece.colour});
                std::size_t line_number = static_cast<std::size_t>(y_position/gui::square_size);
                line_counter[line_number] ++;
                
                if (line_counter[line_number] == (gui::grid_width))
                {
                    // remove all with that y position to clear a line
                    for (int index = 0; index < gui:: grid_width; index++)
                    {
                        int indexed_x_position = index * gui::square_size;
                        m_grid_squares.erase(std::remove_if(m_grid_squares.begin(),
                                                            m_grid_squares.end(),
                           [indexed_x_position, y_position](const GridSquare &g) {
                            return (g.x_position == indexed_x_position) &&
                                   (g.y_position == y_position);}),
                                                            m_grid_squares.end());
                    }
                    
                    // reset the current line counter
                    line_counter[line_number] = 0;
                    
                    // move all blocks above the line down by one line
                    for (auto itr = m_grid_squares.begin(); itr != m_grid_squares.end(); ++itr)
                    {
                        if (itr->y_position < y_position)
                        {
                            itr->y_position += gui::square_size;
                        }
                    }
                    
                    // move the line counter down by one line
                    std::rotate(line_counter.begin(), line_counter.end()-1, line_counter.end());
                }
            }
            
            x_position += gui::square_size;
        }
        
        x_position = m_current_piece.m_x_pos;
        y_position += gui::square_size;
    }
    
    repaint();
}

void
TetrisGrid::paint(juce::Graphics& g)
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
    
    // Draw each rectangle of the current tetrimino here
    g.setColour(m_current_piece.colour);
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
    
    // draw all fallen pieces
    for (const auto& square : m_grid_squares)
    {
        g.setColour(square.colour);
        g.drawRect (square.x_position, square.y_position, gui::square_size, gui::square_size);
        g.fillRect (square.x_position, square.y_position, gui::square_size, gui::square_size);
    }
}

void TetrisGrid::resized()
{
    //setSize(m_width, m_length);
}
