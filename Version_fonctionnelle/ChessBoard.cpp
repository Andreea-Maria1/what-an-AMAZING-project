/*
* Chess Game.
* \file   ChessBoard.cpp
* \author Andreea Maria Ghioltan et Maria Bourouisa
* \date   20 avril 2023
* Cr�� le 10 avril 2023
*/

#include "ChessBoard.h"

ChessBoard::ChessBoard(QWidget* parent) : QGridLayout(parent)
{
	setSizeConstraint(QLayout::SetMinAndMaxSize);
	initialisation();
	deleteSpacing();
}

ChessBoard::ChessBoard(ChessBoard* chessBoard)
{
	listOfButton_ = chessBoard->getListOfButton();
	listOfPieces_ = chessBoard->getlistOfPieces();
}

void ChessBoard::initialisation()
{
	std::shared_ptr<ChessBoard> chessBoard = std::make_shared<ChessBoard>(this);
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			std::shared_ptr<Button> button = std::make_shared<Button>(i, j, chessBoard);
			button->setStyleSheet("background-color: rgba(100,156,189,1); margin: -10px;");
			button->setBaseColor("blue");

			listOfButton_.push_back(button);
			if (i % 2 == 0)
			{
				if (j % 2 == 0)
				{
					button->setStyleSheet("background-color: rgba(255,250,240,1); margin: -10px;");
					button->setBaseColor("white;");
				}
			}
			else
			{
				if (j % 2 != 0)
				{
					button->setStyleSheet("background-color: rgba(255,250,240,1); margin: -10px;");
					button->setBaseColor("white;");
				}
			}
			addWidget(button.get(), i, j, 1, 1);
		}
	}
}

void ChessBoard::addPieces(std::shared_ptr<Piece> piece)
{
	listOfPieces_.push_back(piece);
	for (std::shared_ptr<Button> button : listOfButton_)
	{
		if (button->getPositionButton().x == piece->getPositionPiece().x && button->getPositionButton().y == piece->getPositionPiece().y)
		{
			button->setPiece(piece);
			isPositionEmpty = false;
		}
	}
}

void ChessBoard::movePiece(Position newPosition, std::shared_ptr<Piece> piece, Button* button)
{
	if (piece->isValidMove(newPosition) && isPositionEmpty)
	{
		piece->getPositionPiece();
		button->setPiece(piece);
		button->setIcon(QIcon(piece->getIcon()));

	}
	else if (piece->isValidMove(newPosition) && !isPositionEmpty)
	{
		piece->getPositionPiece();
		button->setPiece(piece);
		button->setIcon(QIcon(piece->getIcon()));
	}
	else
	{
		clickedPiece_ = nullptr;
	}

	button->setPiece(clickedPiece_);
	button->setIcon(QIcon(clickedPiece_->getIcon()));
	removePiece(clickedButton_);
	clickedPiece_ = nullptr;
}

void ChessBoard::removePiece(Button* button)
{
	button->setIcon(QIcon(""));
	if (button->getBaseColor() == "blue")
	{
		button->setStyleSheet("background-color: rgba(100,156,189,1); margin: -10px;");
	}
	else
	{
		button->setStyleSheet("background-color: rgba(255, 250, 240, 1); margin: -10px;");
	}
	button->setPiece(nullptr);
	button = nullptr;
}

void ChessBoard::deleteSpacing() 
{
	setHorizontalSpacing(0);
	setVerticalSpacing(0);
}

std::vector<std::shared_ptr<Button>> ChessBoard::getListOfButton() const
{
	return listOfButton_;
}

std::vector<std::shared_ptr<Piece>> ChessBoard::getlistOfPieces() const
{
	return listOfPieces_;
}


void ChessBoard::changeColourValidMove(Position newPosition)
{
	for (auto&& button : listOfButton_)
	{
		if (button.get()->getPiece()->isValidMove(newPosition))
		{
			button->setStyleSheet("background-color: rgba(255,255,153,1); margin: -10px;");
		}
	}
}

void ChessBoard::click(Button* button) 
{
	// select piece you want to play
	if (clickedPiece_ == nullptr)
	{
		if (button->getPiece() != nullptr)
		{
			clickedPiece_ = button->getPiece();
			clickedButton_ = button;
			clickedButton_->setStyleSheet("background-color: rgba(102,102,0,1); margin: -10px;");
			//filters //movementManager
			//changeColourValidMove(newPosition);
		}
		// select new position
	}
	else
	{
		movePiece(button->getPositionButton(), clickedPiece_, button);

	}
}