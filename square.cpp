#include "square.h"
#include <cctype>

Square::Square(int file, int rank) : file(file), rank(rank){}

Square::Square(const char position[2])
{ // mozliwosc utworzenia pozycji przy pomocy notacji szachowej, np "e4"
    char x = std::tolower(position[0]);
    int file = x - 'a';
    int rank = position[1] - '1';
    this->file = file;
    this->rank = rank;
}

bool Square::operator==(const Square &other) const
{
    return (file == other.file && rank == other.rank);
}

int Square::getFile() const
{
    return file;
}

int Square::getRank() const
{
    return rank;
}

bool Square::isValid() const
{ // sprawdza czy pole nie jest poza szachownicą
    return file >= 0 && file < 8 && rank >= 0 && rank < 8;
}
