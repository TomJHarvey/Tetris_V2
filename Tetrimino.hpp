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

enum class KickDirection // When implementing anti clockwise turning this will need to be modified.
{
    start_to_right = 0,
    right_to_flipped,
    flipped_to_left,
    left_to_start,
    full_rotation
};

struct Piece
{
    Tiles m_tiles;
    int m_x_pos;
    int m_y_pos;
    juce::Colour colour;
    KickDirection kick_direction;
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

struct KickDataPosition
{
    int x;
    int y;
};

class Tetrimino
{
public:
    
    static Piece getPiece(const PieceType& piece_type);
    static Tiles rotatePiece(const Piece& piece); // piece roation pos too?
    
    // TODO: rotate piece here, then do the kick in tetris grid.

};

#endif /* Tetrimino_hpp */
