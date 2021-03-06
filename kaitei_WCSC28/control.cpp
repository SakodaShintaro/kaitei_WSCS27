#include"position.hpp"

//Positionクラス内の利きに関する実装がこのファイルにまとめられている

static constexpr int EXTEND = 0, BLOCK = 1;

void Position::putPiece(Piece p, Square sq) {
    //駒を置くことにより長い利きが遮られる
    for (Color c : {BLACK, WHITE}) {
        uint8_t long_control_direction = controls_[c][sq].direction;
        //while (long_control_direction > 0) {
        //    auto index = MSB64(long_control_direction);
        //    long_control_direction &= ~(1 << index);
        //}
        for (auto long_control : LongControlList) {
            if (long_control_direction & long_control) {
                changeLongControl(sq, long_control, c, BLOCK);
            }
        }
    }

    //置いた駒の利きを発生させる
    changeControl(p, sq, 1);
}

void Position::removePiece(Piece p, Square sq) {
    //置かれていた駒の利きを除く
    changeControl(p, sq, -1);

    //駒を取り除くことにより長い利きが通る
    for (Color c : {BLACK, WHITE}) {
        uint8_t long_control_direction = controls_[c][sq].direction;
        for (auto long_control : LongControlList) {
            if (long_control_direction & long_control) {
                changeLongControl(sq, long_control, c, EXTEND);
            }
        }
    }
}

void Position::changeControl(Piece p, Square sq, int diff) {
    Color c = pieceToColor(p);
    if (kind(p) == LANCE && !(p & PROMOTE)) {
        //成ってない香車
        uint8_t dir_bit = (pieceToColor(p) == BLACK ? Con_D : Con_U);
        Dir d = (pieceToColor(p) == BLACK ? U : D);
        for (Square to = sq + d; board_[to] != WALL; to = to + d) {
            if (diff == 1) {
                controls_[c][to].direction |= dir_bit;
                controls_[c][to].number++;
            } else {
                controls_[c][to].direction &= ~dir_bit;
                controls_[c][to].number--;
            }
            if (board_[to] != EMPTY) {
                break;
            }
        }
    } else if (kind(p) == BISHOP) {
        if (p & PROMOTE) {
            //馬なら上下左右に隣接利きを足す
            controls_[c][sq + U].number += diff;
            controls_[c][sq + R].number += diff;
            controls_[c][sq + D].number += diff;
            controls_[c][sq + L].number += diff;
            //あとは角と同じ
        }

        Dir dirs[4] = { RU, RD, LD, LU };
        ControlDir condirs[4] = { Con_LD, Con_LU, Con_RU, Con_RD };
        for (int i = 0; i < 4; i++) {
            for (Square to = sq + dirs[i]; board_[to] != WALL; to = to + dirs[i]) {
                if (diff == 1) {
                    controls_[c][to].direction |= condirs[i];
                    controls_[c][to].number++;
                } else {
                    controls_[c][to].direction &= ~condirs[i];
                    controls_[c][to].number--;
                }
                if (board_[to] != EMPTY) {
                    break;
                }
            }
        }
    } else if (kind(p) == ROOK) {
        if (p & PROMOTE) {
            //竜なら斜め4方向に隣接利きを足す
            controls_[c][sq + RU].number += diff;
            controls_[c][sq + RD].number += diff;
            controls_[c][sq + LD].number += diff;
            controls_[c][sq + LU].number += diff;
            //あとは飛車と同じ
        }

        Dir dirs[4] = { U, R, D, L };
        ControlDir condirs[4] = { Con_D, Con_L, Con_U, Con_R };
        for (int i = 0; i < 4; i++) {
            for (Square to = sq + dirs[i]; board_[to] != WALL; to = to + dirs[i]) {
                if (diff == 1) {
                    controls_[c][to].direction |= condirs[i];
                    controls_[c][to].number++;
                } else {
                    controls_[c][to].direction &= ~condirs[i];
                    controls_[c][to].number--;
                }
                if (board_[to] != EMPTY) {
                    break;
                }
            }
        }
    } else {
        //その他
        controlBB(sq, p, occupied_all_).forEach([&](const Square to) {
            controls_[c][to].number += diff;
        });
    }
}

void Position::changeLongControl(Square sq, ControlDir cd, Color c, int extend_or_block) {
    //sqにあるcd方向の,c側の利きを伸ばす
    //cd方向と逆に盤面をたどっていく
    Dir d = ConDirToOppositeDir[cd];
    if (d == H) {
        return;
    }
    for (Square to = sq + d; board_[to] != WALL; to = to + d) {
        if (extend_or_block == EXTEND) {
            controls_[c][to].direction |= cd;
            controls_[c][to].number++;
        } else {
            controls_[c][to].direction &= ~cd;
            controls_[c][to].number--;
        }
        if (board_[to] != EMPTY) {
            break;
        }
    }
}

void Position::initControl() {
    for (Square sq : SquareList) {
        controls_[BLACK][sq].number = 0;
        controls_[BLACK][sq].direction = 0;
        controls_[WHITE][sq].number = 0;
        controls_[WHITE][sq].direction = 0;
    }
    for (Square sq : SquareList) {
        if (board_[sq] == EMPTY) {
            continue;
        }
        changeControl(board_[sq], sq, 1);
    }
}

void Position::checkControl(){
    Control before[ColorNum][SquareNum];
    for (Square sq : SquareList) {
        before[BLACK][sq] = controls_[BLACK][sq];
        before[WHITE][sq] = controls_[WHITE][sq];
    }

    initControl();
    for (Square sq : SquareList) {
        if (before[BLACK][sq].number != controls_[BLACK][sq].number) {
            print();
            printf("間違った先手の利き\n");
            std::printf("９８７６５４３２１\n");
            std::printf("------------------\n");
            for (int r = Rank1; r <= Rank9; r++) {
                for (int f = File9; f >= File1; f--) {
                    printf("%2d", (int)before[BLACK][FRToSquare[f][r]].number);
                }
                printf("|%d\n", r);
            }
        }
        if (before[BLACK][sq].direction != controls_[BLACK][sq].direction) {
            print();
            assert(false);
        }
        if (before[WHITE][sq].number != controls_[WHITE][sq].number) {
            print();
            printf("間違った後手の利き\n");
            std::printf("９８７６５４３２１\n");
            std::printf("------------------\n");
            for (int r = Rank1; r <= Rank9; r++) {
                for (int f = File9; f >= File1; f--) {
                    printf("%2d", (int)before[WHITE][FRToSquare[f][r]].number);
                }
                printf("|%d\n", r);
            }
            assert(false);
        }
        if (before[WHITE][sq].direction != controls_[WHITE][sq].direction) {
            print();
            assert(false);
        }
    }
}

void Position::printControl() const {
    //利き
    printf("先手の利き\n");
    std::printf("９８７６５４３２１\n");
    std::printf("------------------\n");
    for (int r = Rank1; r <= Rank9; r++) {
        for (int f = File9; f >= File1; f--) {
            printf("%2d", (int)controls_[BLACK][FRToSquare[f][r]].number);
        }
        printf("|%d\n", r);
    }
    printf("後手の利き\n");
    std::printf("９８７６５４３２１\n");
    std::printf("------------------\n");
    for (int r = Rank1; r <= Rank9; r++) {
        for (int f = File9; f >= File1; f--) {
            printf("%2d", (int)controls_[WHITE][FRToSquare[f][r]].number);
        }
        printf("|%d\n", r);
    }
}
