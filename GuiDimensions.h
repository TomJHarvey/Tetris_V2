//
//  GuiDimensions.h
//  TETRIS_V2
//
//  Created by Tom Harvey on 02/03/2022.
//

#ifndef GuiDimensions_h
#define GuiDimensions_h

namespace gui
{
    static const int square_size = 33; // determines size of whole window and contents.
    static const int grid_width = 10;
    static const int grid_height = 21; // + 1 for pre grid bar.
    static const int scaled_grid_width = grid_width * square_size;
    static const int scaled_grid_height = grid_height * square_size;
    static const int side_bar_length = 4 * square_size;
    static const int pre_grid_bar = 1 * square_size;
    static const int window_width = scaled_grid_width + (2 * side_bar_length);
    static const int window_height = scaled_grid_height;
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
}


#endif /* GuiDimensions_h */
