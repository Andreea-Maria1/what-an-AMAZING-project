/*
* Chess Game.
* \file   Button.h
* \author Andreea Maria Ghioltan et Maria Bourouisa
* \date   20 avril 2023
* Cr�� le 10 avril 2023
*/

#pragma once

#include <iostream>
#include <QPushButton>
#include <Qsize>
#include <memory>
#include "Piece.h"
#include "Position.h"

class Button : public QPushButton {
    Q_OBJECT

public:

    Button(int x, int y, QWidget* parent = nullptr);
    ~Button() = default;
    std::shared_ptr<Piece> getPiece() const;
    void setPiece(std::shared_ptr<Piece> piece);
    Position getPositionButton() const;

public slots:
    void handleClick();

private:
    std::shared_ptr<Piece> pieceOfSquare_ = nullptr;
    Position positionButton_;
};