//
//  TetrisGrid.hpp
//  TetrisApp
//
//  Created by Tom Harvey on 01/03/2022.
//

#ifndef TetrisGrid_hpp
#define TetrisGrid_hpp

#include <juce_gui_extra/juce_gui_extra.h>
#include "Tetrimino.hpp"

class TetrisGrid : public juce::Component
{
public:
    
    TetrisGrid();
    void spawnPiece(const PieceType& piece_type);
    
    void paint (juce::Graphics&) override;
    void resized() override;
    
private:
    Piece m_current_piece;
    
};

#endif /* TetrisGrid_hpp */
