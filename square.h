#ifndef SQUARE_H
#define SQUARE_H

class Square
{
private:
    int file;
    int rank;
public:
    Square(int file, int rank);
    Square(const char position[2]);
    bool operator ==(const Square& other) const;
    int getFile() const;
    int getRank() const;
    bool isValid() const;
};
#endif // SQUARE_H
