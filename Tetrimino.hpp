//
//  Tetrimino.hpp
//  TetrisApp
//
//  Created by Tom Harvey on 02/03/2022.
//

#ifndef Tetrimino_hpp
#define Tetrimino_hpp

#include <juce_gui_extra/juce_gui_extra.h>
#include <vector>

using Tiles = std::vector<std::vector<bool>>;

struct Piece
{
    Tiles m_tiles;
    int m_x_pos;
    int m_y_pos;
    juce::Colour colour;
};

enum class PieceType
{
    j,
    l,
    z,
    s,
    t,
    i,
    o,
    invalid = -1
};

class Tetrimino
{
public:
    
    static Piece getPiece(const PieceType& piece_type);
    static Tiles rotatePiece(const Piece& piece); // piece roation pos too?
    // TODO: rotate piece here, then do the kick in tetris grid.

};

#endif /* Tetrimino_hpp */
