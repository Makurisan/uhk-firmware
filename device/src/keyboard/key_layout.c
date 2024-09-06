#include "key_layout.h"

const uint8_t KeyLayout_Uhk80_to_Uhk60[SLOT_COUNT][MAX_KEY_COUNT_PER_MODULE] = {
    {
        // UHK60 keys
        [10] = 0, // 7
        [11] = 1, // 8
        [12] = 2, // 9
        [13] = 3, // 0
        [14] = 4, // -
        [15] = 5, // =
        [16] = 6, // backspace

        [30] = 14, // y
        [20] = 7, // u
        [21] = 8, // i
        [22] = 9, // o
        [23] = 10, // p
        [24] = 11, // [
        [25] = 12, // ]
        [26] = 13, // |

        [40] = 21, // h
        [31] = 15, // j
        [32] = 16, // k
        [33] = 17, // l
        [34] = 18, // ;
        [35] = 19, // '
        [36] = 20, // enter

        [50] = 22, // n
        [41] = 23, // m
        [43] = 24, // ,
        [44] = 25, // .
        [45] = 26, // /
        [46] = 27, // shift

        [51] = 29, // space
        [42] = 31, // fn
        [54] = 32, // alt
        [55] = 33, // super
        [56] = 34, // ctrl

        [52] = 30, // inner case button

        // new keys

        [0] = 35, // f7
        [1] = 36, // f8
        [2] = 37, // f9
        [3] = 38, // f10
        [4] = 39, // f11
        [5] = 40, // f12
        [6] = 41, // print
        [8] = 42, // del
        [9] = 43, // ins

        [18] = 44, // scrl lck
        [19] = 45, // pause

        [28] = 46, // home
        [29] = 47, // pg up

        [38] = 48, // end
        [39] = 49, // pg down

        [47] = 50, // dbl arrow left
        [48] = 51, // arrow up
        [49] = 52, // dbl arrow right

        [57] = 53, // arrow left
        [58] = 54, // arrow down
        [59] = 55, // arrow right

        [53] = 56, // right case button

        // empty
        [7] = 255,
        [17] = 255,
        [27] = 255,
        [37] = 255,
    },
    {
        // UHK60 keys

        [7] = 0, // tilde
        [8] = 1, // 1
        [9] = 2, // 2
        [10] = 3, // 3
        [11] = 4, // 4
        [12] = 5, // 5
        [13] = 6, // 6


        [14] = 7, // tab
        [15] = 8, // q
        [16] = 9, // w
        [17] = 10, // e
        [18] = 11, // r
        [19] = 13, // t

        [21] = 14, // mouse
        [22] = 15, // a
        [23] = 16, // s
        [24] = 17, // d
        [25] = 18, // f
        [26] = 20, // g

        [28] = 21, // shift
        [29] = 22, // iso key
        [30] = 23, // z
        [31] = 24, // x
        [32] = 25, // c
        [33] = 26, // v
        [34] = 27, // b

        [35] = 28, // ctrl
        [36] = 29, // super
        [37] = 30, // alt
        [40] = 31, // fn
        [41] = 33, // mod

        [39] = 32, // inner case button

        // new keys

        [0] = 34, // esc
        [1] = 35, // f1
        [2] = 36, // f2
        [3] = 37, // f3
        [4] = 38, // f4
        [5] = 39, // f5
        [6] = 40, // f6

        [38] = 41, // left case button

        // unused
        [20] = 255,
        [27] = 255,
        [42] = 255,
        [43] = 255,
        [44] = 255,
        [45] = 255,
        [46] = 255,
        [47] = 255,
        [48] = 255,
        [49] = 255,
        [50] = 255,
        [51] = 255,
        [52] = 255,
        [53] = 255,
        [54] = 255,
        [55] = 255,
        [56] = 255,
        [57] = 255,
        [58] = 255,
        [59] = 255,
    },
    {},
    {},
};
