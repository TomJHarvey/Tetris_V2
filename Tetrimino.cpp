//
//  Tetrimino.cpp
//  TetrisApp
//
//  Created by Tom Harvey on 02/03/2022.
//

#include "Tetrimino.hpp"
#include "GuiDimensions.h"

static const int tetrimino_start_pos_x = gui::square_size * 3;
static const int tetrimino_start_pos_y = gui::square_size * 0;

// TODO: the start positions will vary depending on the pieces.

static const Piece j_piece = {{{false, false, true},
                              {true, true, true},
                              {false, false , false}},
                              tetrimino_start_pos_x,
                              tetrimino_start_pos_y,
                              juce::Colours::orange};

static const Piece l_piece = {{{true, false, false},
                              {true, true, true},
                              {false, false , false}},
                              tetrimino_start_pos_x,
                              tetrimino_start_pos_y,
                              juce::Colours::blue};

static const Piece s_piece = {{{false, true, true},
                              {true, true, false},
                              {false, false , false}},
                              tetrimino_start_pos_x,
                              tetrimino_start_pos_y,
                              juce::Colours::green};

static const Piece z_piece = {{{true, true, false},
                              {false, true, true},
                              {false, false , false}},
                              tetrimino_start_pos_x,
                              tetrimino_start_pos_y,
                              juce::Colours::red};

static const Piece t_piece = {{{false, true, false},
                              {true, true, true},
                              {false, false , false}},
                              tetrimino_start_pos_x,
                              tetrimino_start_pos_y,
                              juce::Colours::pink};

static const Piece i_piece = {{{false, false, false, false},
                              {true, true, true, true},
                              {false, false , false, false},
                              {false, false , false, false}},
                              tetrimino_start_pos_x,
                              tetrimino_start_pos_y,
                              juce::Colours::lightblue};

static const Piece o_piece = {{{false, true, true, false},
                              {false, true, true, false},
                              {false, false , false, false},
                              {false, false , false, false}},
                              tetrimino_start_pos_x,
                              tetrimino_start_pos_y,
                              juce::Colours::yellow};


Piece
Tetrimino::getPiece(const PieceType& piece_type)
{
    Piece piece;
    switch (piece_type)
    {
        case PieceType::j:
            piece = j_piece;
            break;
        case PieceType::l:
            piece = l_piece;
            break;
        case PieceType::s:
            piece = s_piece;
            break;
        case PieceType::z:
            piece = z_piece;
            break;
        case PieceType::t:
            piece = t_piece;
            break;
        case PieceType::i:
            piece = i_piece;
            break;
        case PieceType::o:
            piece = o_piece;
            break;
        case PieceType::invalid:
            break;
    }
    
    return piece;
}


