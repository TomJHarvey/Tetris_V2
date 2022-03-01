//
//  TetrisGrid.hpp
//  TetrisApp
//
//  Created by Tom Harvey on 01/03/2022.
//

#ifndef TetrisGrid_hpp
#define TetrisGrid_hpp

#include <juce_gui_extra/juce_gui_extra.h>


class TetrisGrid : public juce::Component
{
public:
    
    TetrisGrid(int width, int length, int square_size);

    
    void paint (juce::Graphics&) override;
    void resized() override;
    
private:
    int m_width;
    int m_length;
    int m_square_size;
    
};

#endif /* TetrisGrid_hpp */
