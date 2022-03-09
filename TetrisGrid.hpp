//
//  TetrisGrid.hpp
//  TetrisApp
//
//  Created by Tom Harvey on 01/03/2022.
//

#ifndef TetrisGrid_hpp
#define TetrisGrid_hpp

#include <juce_gui_extra/juce_gui_extra.h>

#include "GuiDimensions.h"
#include "Tetrimino.hpp"

enum class Direction
{
    left = 63234,
    right = 63235,
    down = 63233
};

struct GridSquare
{
    int x_position;
    int y_position;
    juce::Colour colour;
};

class TetrisGrid : public juce::Component
                 , private juce::Timer
{
public:
    
    TetrisGrid();
    void spawnPiece();
    bool movePiece(Direction direction);
    void rotatePiece();
    void paint (juce::Graphics&) override;
    void resized() override;
    
private:
    
    bool hitSideLimit(const Direction& direction,
                      const int& position,
                      const int& direction_multiplier) const;
    
    bool hitFallenPiece(const Direction& direction,
                        const int& x_position,
                        const int& y_position,
                        const int& direction_multiplier) const;
    
    bool matchCordinates(int x_position, int y_position) const;
    void setFallenPiece();
    bool rotatedOutOfGrid(const int& x, const int& y) const;
    
private:
    
    void timerCallback() final
    {
        movePiece(Direction::down);
    }
    
    Piece m_current_piece;
    std::vector<GridSquare> m_grid_squares;
    std::vector<int> line_counter;
};

#endif /* TetrisGrid_hpp */
