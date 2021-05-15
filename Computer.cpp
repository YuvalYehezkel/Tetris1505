#include "Computer.h"

char Computer::ChooseComputerLevel()
{
	char key_char = 0;
	gotoxy(30, 9);
	cout << "Hi! please enter the level of the computer:" << endl;
	gotoxy(30, 10);
	cout << "for the BEST level press (1)" << endl;
	gotoxy(30, 11);
	cout << "for the GOOD level press (2)" << endl;
	gotoxy(30, 12);
	cout << "for the NOVICE level press (3)" << endl;
	while (1)
	{
		if (_kbhit())
		{
			key_char = _getch();
			return key_char;
		}
	}
}
//void Computer::LessSpaces(general* f)
//{
//
//
//	int counterDeletedLines = 0;
//	int maxHeight = 0; // height of the figure in the row
//	int curHeight = 0;
//	
//	for (int i = 0; i < 4; i++)
//	{
//
//		while (update(GameBoard, f->getSerial(), LEFT));
//
//		while(update(GameBoard, f->getSerial(), DOWN));
//
//		for (int i = ROWS; i > 0; i--)
//		{
//			if (GameBoard.IsFullRow(i, RIGHT_PLAYER))
//			{
//				counterDeletedLines++;
//			}
//
//		}
//		for (int j = 0; j < 4; j++) // we calculate the hight of the figure
//		{
//			curHeight = f->getBodyPos(j).gety();
//			if (j == 0)
//			{
//				curHeight = maxHeight;
//			}
//			if (curHeight < maxHeight)
//			{
//				maxHeight = curHeight; // when the height is smaller the figure is higher
//			}
//		}
//
//		//right
//
//	}

			

	//Point& res ;
	//for (int i = ROWS; i > 0; i--)
	//{
	//	for (int j = COLS + 2; j < 2 * COLS + 3; j++)
	//	{
	//		if (GameBoard.isValidPoint(j, i))
	//		{
	//			for (int count = 0; count < f->getSize(); count++)
	//			{
	//				Point& res = f->getBodyPos(count);// צריכות לממש את הפונקציה שמחזירה את הגוף של הצורה
	//				if ((GameBoard.isValidPoint(res.getX() - 1, res.gety())))
	//				{
	//					f->update(GameBoard, f->getSerial(), LEFT);
	//					break;
	//					//f.updateFigureLeft(GameBoard, f->getSerial());
	//				}
	//				else if (GameBoard.isValidPoint(res.getX() + 1, res.gety()) && GameBoard.isValidPoint(res.getX(), res.gety() + 1))
	//				{
	//					f->update(GameBoard, f->getSerial(), RIGHT);
	//					break;
	//				}
	//				break;
	//				// else if right // else if rotate // else if counterrotate
	//			}
	/*		}
		}
	}*/

void Computer::FindTheBestPlacementOfFigure(general* f)
{

	Figure* temp = new Figure(f->getSerial(), RIGHT_PLAYER, GameBoard);
	
	//Point* FBody = f->getBodyPos();
	bool res;
	int counterDeletedLines1 =0;
	int counterDeletedLines2 = 0;
	int maxHeight1 ; // height of the figure in the row
	int maxHeight2 ;
	int curHeight , BestHeigt;
	int BestRow ; //the placement that delete to most rows
	int BestCol, Col1, Col2;
	BotMovesGrade Pos[SIZE];
	// מערך של 4 שיש בו את המצב של כל צורה ונעשה השמה לעמודה הכי טובה להיות בה של אותו מצב
	// arr[0] = 3 פוזישן במצב 0 בעמודה 

	if (f->getSerial() == BOMB)
	{
		FindTheBestPlacementOfBomb(f);
	}
	else
	{

		for (int i = 0; i < SIZE; i++)
		{

			while (temp->update(GameBoard, temp->getSerial(), LEFT)==true){}
			//temp->print(GameBoard);
			//Sleep(100);
			
			Col1 = LowColOfCurrPlacement(temp);
			while (temp->update(GameBoard, temp->getSerial(), DOWN)==true){}
			//temp->print(GameBoard);


			counterDeletedLines1=BestRow = HowManyDeletedLines(GameBoard); //we calculate how many lines the current figure drops

			maxHeight1=BestHeigt = calculateTheHeightOfCurrPlacement(temp); // the Height of the figure in current placement

			//for (int j = 0; j < SIZE; j++)
			//{
			//	GameBoard.turnToFreePoint(j, i);
			//}
			res=temp->update(GameBoard, temp->getSerial(), RIGHT);

			Col2 = LowColOfCurrPlacement(temp);
			while (temp->update(GameBoard, temp->getSerial(), DOWN)==true){
				//temp->print(GameBoard);
			}

			counterDeletedLines2 = HowManyDeletedLines(GameBoard);
			maxHeight2 = calculateTheHeightOfCurrPlacement(temp);
			BestCol = compareBetween2Placements(BestHeigt, maxHeight2, BestRow, counterDeletedLines2, &BestHeigt, &BestRow, Col1, Col2);

			
			//right
			while (temp->update(GameBoard, temp->getSerial(), RIGHT)==true)
			{
				//temp->print(GameBoard);

				Col2 = LowColOfCurrPlacement(temp);
				while (temp->update(GameBoard, temp->getSerial(), DOWN)==true){
					//temp->print(GameBoard);
				}

				counterDeletedLines2 = HowManyDeletedLines(GameBoard);
				maxHeight2 = calculateTheHeightOfCurrPlacement(temp);
				BestCol = compareBetween2Placements(BestHeigt, maxHeight2, BestRow, counterDeletedLines2, &BestHeigt, &BestRow, BestCol, Col2);
				/*for (int j = 0; j < SIZE; j++)
				{
					GameBoard.turnToFreePoint(j, i);
				}*/
			}
			Pos[i].Setbestcol(BestCol);
			Pos[i].SetDeletedLines(BestRow);
			Pos[i].SetHeight(BestHeigt);

			delete temp;
			Figure* temp = new Figure(f->getSerial(), RIGHT_PLAYER, GameBoard);
			temp->update(GameBoard, temp->getSerial(), CLOCKWISE);

		}
		delete temp;
		int besRotation = compareRotations(Pos, SIZE);
		
		//temp->setBodyPos(FBody);
		//temp->print(GameBoard);
		
		while (f->getRotateNum() != besRotation)
		{
			res=f->update(GameBoard, f->getSerial(), CLOCKWISE);
			f->print(GameBoard);

			
			Sleep(100);
		}
		
		while (LowColOfCurrPlacement(f) < Pos[besRotation].Getbestcol())
		{
			res=f->update(GameBoard, f->getSerial(), RIGHT);
			f->print(GameBoard);
			Sleep(100);
		}
		while (LowColOfCurrPlacement(f) > Pos[besRotation].Getbestcol())
		{
			res=f->update(GameBoard, f->getSerial(), LEFT);
			f->print(GameBoard);
			Sleep(100);

		}
	/*	while (f->update(GameBoard, f->getSerial(), DOWN)) 
		{
			f->print(GameBoard);
			Sleep(100);
		}*/
	}
//	temp->print(GameBoard);
}

void Computer::FindTheBestPlacementOfBomb(general* f)
{

}
int Computer::compareRotations(BotMovesGrade* position, int size)
{
	int maxHeight=position[0].GetHeight();
	int bestRows= position[0].GetDeletedLines();
	int bestCol = position[0].Getbestcol();
	int bestRotation=0; 

	for (int i = 1; i < size ; i++)
	{
	
		bestRotation=compareBetween2Placements(maxHeight,position[i].GetHeight(), bestRows,position[i].GetDeletedLines(), &maxHeight, &bestRows,bestRotation,i);
	}
	return bestRotation;
}

int Computer::HowManyDeletedLines(Board& board) const//we calculate how many lines the current figure drops
{
	int counterDeletedLines = 0;
	for (int i = ROWS; i > 0; i--)
	{
		if (board.IsFullRow(i, RIGHT_PLAYER))
		{
			counterDeletedLines++;
		}

	}
	return counterDeletedLines;
}

int Computer::calculateTheHeightOfCurrPlacement(general* f) const
{
	Point* body = f->getBodyPos();
	int maxHeight; // height of the figure in the row
	int curHeight;

	for (int j = 0; j < 4; j++) // we calculate the hight of the figure
	{
		curHeight = body[j].gety();
		if (j == 0)
		{
			maxHeight = curHeight;
		}
		if (curHeight < maxHeight)
		{
			maxHeight = curHeight; // when the height is smaller the figure is higher
		}
		
	}
	return maxHeight;
}

int Computer::LowColOfCurrPlacement(general* f)
{
	Point* body = f->getBodyPos();
	int currCol,lowCol;
	for (int i = 0; i < 4; i++)
	{
		currCol=body[i].getX();
		if (i == 0)
		{
			 lowCol= currCol;
		}
		if (currCol < lowCol)
		{
			lowCol = currCol;
		}
	}
	return lowCol; // the col that appear in the most left side
}
int Computer::compareBetween2Placements(int maxHeight1, int maxHeight2, int numDeletedRows1, int numDeletedRows2,int* BestHeight,int* BestRow,int Col1,int Col2)
{
	if (maxHeight1 > maxHeight2)
	{
		*BestHeight = maxHeight1;
	}
	else if(maxHeight1 < maxHeight2)
	{
		*BestHeight = maxHeight2;
	}
	if (numDeletedRows1 > numDeletedRows2)
	{
		*BestRow = numDeletedRows1;
	}
	else if(numDeletedRows1 < numDeletedRows2)
	{
		*BestRow = numDeletedRows2;
	}
	if (*BestRow == numDeletedRows1 && *BestHeight == maxHeight1)
	{
		return Col1;
	}
	else if (*BestRow == numDeletedRows2 && *BestHeight == maxHeight2)
	{
		return Col2;
	}
	else if (*BestRow == numDeletedRows1 && *BestHeight != maxHeight1)
	{
		return Col1;
	}
	else if (*BestRow == numDeletedRows2 && *BestHeight != maxHeight2)
	{
		return Col2;
	}

}
