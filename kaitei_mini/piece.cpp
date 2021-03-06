#include"piece.hpp"

std::unordered_map<int, std::string> PieceToStr = {
    { PAWN,   "歩" },
    { LANCE,  "香" },
    { KNIGHT, "桂" },
    { SILVER, "銀" },
    { GOLD,   "金" },
    { BISHOP, "角" },
    { ROOK,   "飛" },
    { BLACK_PAWN,    "先手歩" },
    { BLACK_LANCE,   "先手香" },
    { BLACK_KNIGHT,  "先手桂" },
    { BLACK_SILVER,  "先手銀" },
    { BLACK_GOLD,    "先手金" },
    { BLACK_BISHOP,  "先手角" },
    { BLACK_ROOK,    "先手飛車" },
    { BLACK_KING,    "先手玉" },
    { BLACK_PAWN_PROMOTE,   "先手と" },
    { BLACK_LANCE_PROMOTE,  "先手成香" },
    { BLACK_KNIGHT_PROMOTE, "先手成桂" },
    { BLACK_SILVER_PROMOTE, "先手成銀" },
    { BLACK_BISHOP_PROMOTE, "先手馬" },
    { BLACK_ROOK_PROMOTE,   "先手竜" },
    { WHITE_PAWN,    "後手歩" },
    { WHITE_LANCE,   "後手香" },
    { WHITE_KNIGHT,  "後手桂" },
    { WHITE_SILVER,  "後手銀" },
    { WHITE_GOLD,    "後手金" },
    { WHITE_BISHOP,  "後手角" },
    { WHITE_ROOK,    "後手飛車" },
    { WHITE_KING,    "後手玉" },
    { WHITE_PAWN_PROMOTE,   "後手と" },
    { WHITE_LANCE_PROMOTE,  "後手成香" },
    { WHITE_KNIGHT_PROMOTE, "後手成桂" },
    { WHITE_SILVER_PROMOTE, "後手成銀" },
    { WHITE_BISHOP_PROMOTE, "後手馬" },
    { WHITE_ROOK_PROMOTE,   "後手竜" },
};

std::unordered_map<int, std::string> PieceToSfenStr = {
    { EMPTY,  "  " },
    { PAWN,   "P" },
    { LANCE,  "L" },
    { KNIGHT, "N" },
    { SILVER, "S" },
    { GOLD,   "G" },
    { BISHOP, "B" },
    { ROOK,   "R" },
    { BLACK_PAWN,    " P" },
    { BLACK_LANCE,   " L" },
    { BLACK_KNIGHT,  " N" },
    { BLACK_SILVER,  " S" },
    { BLACK_GOLD,    " G" },
    { BLACK_BISHOP,  " B" },
    { BLACK_ROOK,    " R" },
    { BLACK_KING,    " K" },
    { BLACK_PAWN_PROMOTE,   "+P" },
    { BLACK_LANCE_PROMOTE,  "+L" },
    { BLACK_KNIGHT_PROMOTE, "+N" },
    { BLACK_SILVER_PROMOTE, "+S" },
    { BLACK_BISHOP_PROMOTE, "+B" },
    { BLACK_ROOK_PROMOTE,   "+R" },
    { WHITE_PAWN,    " p" },
    { WHITE_LANCE,   " l" },
    { WHITE_KNIGHT,  " n" },
    { WHITE_SILVER,  " s" },
    { WHITE_GOLD,    " g" },
    { WHITE_BISHOP,  " b" },
    { WHITE_ROOK,    " r" },
    { WHITE_KING,    " k" },
    { WHITE_PAWN_PROMOTE,   "+p" },
    { WHITE_LANCE_PROMOTE,  "+l" },
    { WHITE_KNIGHT_PROMOTE, "+n" },
    { WHITE_SILVER_PROMOTE, "+s" },
    { WHITE_BISHOP_PROMOTE, "+b" },
    { WHITE_ROOK_PROMOTE,   "+r" }
};