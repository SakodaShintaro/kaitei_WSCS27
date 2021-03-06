#pragma once

#include"move.hpp"
#include<vector>

//enum Depth;
class Position;
class History;
extern const int MAX_MOVE_LIST_SIZE;

class MovePicker {
private:
	Move* begin() { return moves_; }
    Move* end() { return end_; }

	const Position& pos_;

	Move killer_moves_[2];
	//Move countermove_;
	Depth depth_;
	Move tt_move_;

	//ProbCut用の指し手生成に用いる、直前の指し手で捕獲された駒の価値
	//int threshold;

	//指し手生成の段階
	int stage_;

	//次に返す手、生成された指し手の末尾、BadCaptureの終端
	//Move *cur_, *end_, *endBadCaptures_;
    Move *cur_, *end_;

    Move *moves_;

    const History& history_;

public:
	//通常探索から呼ばれる際のコンストラクタ
	MovePicker(const Position& pos, const Move ttMove, const Depth depth, const History& history, const Move killers[2]);

    //静止探索から呼ばれる際のコンストラクタ
    MovePicker(const Position& pos, const Move ttMove, const Depth depth, const History& history);

    ~MovePicker() {
        delete[] moves_;
    }
	Move nextMove();
	void generateNextStage();
    void scoreCapture();
    void scoreNonCapture();

    void printAllMoves() {
        for (auto itr = cur_; itr != end_; itr++) {
            itr->printWithScore();
        }
    }
};

extern int PieceToHistory;