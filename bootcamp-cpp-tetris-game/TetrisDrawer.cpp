#include "TetrisDrawer.h"
#include <vector>


TetrisDrawer::TetrisDrawer(sf::RenderWindow & window, Board & board)
{
  this->window = &window;
  this->board = &board;
  blockScaleFactor = 1.0f;
  //backgroundScaleFactor = blockScaleFactor / 2.0f;

  if (!tetrominoTexture.loadFromFile(TEXTURE_DIR)) {
    //error
    std::cout << "Error tetromino";
  }
  tetrominoTexture.setRepeated(true);
  tetrominoSprite.setTexture(tetrominoTexture);
  tetrominoSprite.setScale(sf::Vector2f(blockScaleFactor, blockScaleFactor));

  if (!backgroundTexture.loadFromFile(BACKGROUND_DIR)) {
    //error
    std::cout << "Error background";
  }
  backgroundTexture.setRepeated(true);
  backgroundTexture.setSmooth(true);
  background.setSize(sf::Vector2f(BACKGROUND_WIDTH, BACKGROUND_WIDTH));
  background.setTexture(&backgroundTexture);

}

TetrisDrawer::~TetrisDrawer()
{
}

void TetrisDrawer::draw()
{
  window->clear(sf::Color::Black);
  
  drawBackground();

  drawBoard();
   
  window->display();
}

void TetrisDrawer::drawBackground()
{
  for (float i = 0.f; i < window->getSize().x; i+=BACKGROUND_WIDTH)
  {
    for (float j = 0.f; j < window->getSize().y; j+=BACKGROUND_WIDTH)
    {
      background.setPosition(sf::Vector2f(i, j));
      window->draw(background);
    }
  }
}

void TetrisDrawer::drawBoard()
{
  const std::vector<short> * map = board->getBoard();
  short rows = board->getRows();
  short columns = board->getColumns();
  int position;


  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < columns; j++)
    {
      position = ((columns)*i) + j;
      if ((*map)[position] != board->getPaddingValue()) {
        tetrominoSprite.setTextureRect(sf::IntRect((*map)[position] * TEXTURE_WIDTH, 0, TEXTURE_WIDTH, TEXTURE_WIDTH));
        tetrominoSprite.setPosition(sf::Vector2f(TEXTURE_WIDTH*j*blockScaleFactor, TEXTURE_WIDTH*i*blockScaleFactor));
        window->draw(tetrominoSprite);
      }
    }
  }

}
