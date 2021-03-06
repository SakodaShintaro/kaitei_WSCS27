#include"move_picker.hpp"
#include"position.hpp"
#include"history.hpp"
#include<functional>
#include<algorithm>

enum Stage {
    MAIN_SEARCH_START,
	MAIN_SEARCH_CAPTURE,
	MAIN_SEARCH_NON_CAPTURE,
	MAIN_SEARCH_END,

    QSEARCH_START,
    QSEARCH_CAPTURE,
    QSEARCH_END,
};

MovePicker::MovePicker(const Position& pos, const Move ttMove, const Depth depth, const History& history) 
	: pos_(pos), tt_move_(ttMove), depth_(depth), history_(history) {
	stage_ = MAIN_SEARCH_START;
    moves_ = new Move[MAX_MOVE_LIST_SIZE];

    //まずこれら二つは先頭を指す
    cur_ = moves_;
    end_ = moves_;
    if (pos.isKingChecked(pos.color())) {
        //王手がかかっていたら全部生成して最後にNULL_MOVE追加
        pos.generateEvasionMoves(end_);
        *(end_++) = NULL_MOVE;
    }
}

MovePicker::MovePicker(const Position& pos, const Move ttMove, const Depth depth, const History& history, const Square to)
    : pos_(pos), tt_move_(ttMove), depth_(depth), history_(history), to_(to) {
    stage_ = QSEARCH_START;
    moves_ = new Move[MAX_MOVE_LIST_SIZE];

    //まずこれら二つは先頭を指す
    cur_ = moves_;
    end_ = moves_;
    if (pos.isKingChecked(pos.color())) {
        //王手がかかっていたら全部生成して最後にNULL_MOVE追加
        pos.generateEvasionMoves(end_);
        *(end_++) = NULL_MOVE;
    }
}

Move MovePicker::nextMove() {
    //NULL_MOVEが返ったら終わりということ

	while (cur_ == end_) {
		//次のカテゴリの手を生成
		generateNextStage();
	}

    return *(cur_++);
}

void MovePicker::generateNextStage() {
	switch (stage_++) {
        //通常探索から呼ばれるときはここから
    case MAIN_SEARCH_START:
        //tt_moveを設定する
        if (tt_move_ != NULL_MOVE && pos_.isLegalMove(tt_move_)) {
            *(end_++) = tt_move_;
        }
        break;
    case MAIN_SEARCH_CAPTURE:
		pos_.generateCaptureMoves(end_);
        scoreCapture();
	    break;
	case MAIN_SEARCH_NON_CAPTURE:
		pos_.generateNonCaptureMoves(end_);
        scoreNonCapture();
        break;
	case MAIN_SEARCH_END:
        *(end_++) = NULL_MOVE;
        //これでMovePickerからNULL_MOVEが返るようになるので指し手生成が終わる
		break;


        //静止探索から呼ばれるときはここから
    case QSEARCH_START:
        //tt_moveを設定する
        if (tt_move_ != NULL_MOVE && pos_.isLegalMove(tt_move_)) {
            *(end_++) = tt_move_;
        }
        break;
    case QSEARCH_CAPTURE:
        if (depth_ == 0) {
            //深さがちょうど0のときだけ取る手をすべて生成
            pos_.generateCaptureMoves(end_);
        } else {
            //深さが負なら取り返す手だけを生成
            pos_.generateRecaptureMovesTo(to_, end_);
        }
        scoreCapture();
        break;
    case QSEARCH_END:
        *(end_++) = NULL_MOVE;
        //これでMovePickerからNULL_MOVEが返るようになるので指し手生成が終わる
        break;
	}
}

void MovePicker::scoreCapture() {
    for (auto itr = cur_; itr != end_; ++itr) {
        itr->score = static_cast<Score>(kind(itr->capture()));
    }
    std::sort(cur_, end_, std::greater<Move>());
}

void MovePicker::scoreNonCapture() {
    for (auto itr = cur_; itr != end_; ++itr) {
        itr->score = Score(0);
        if (itr->isPromote())
            itr->score += 100;
        itr->score += history_[*itr];
    }
    std::sort(cur_, end_, std::greater<Move>());
}