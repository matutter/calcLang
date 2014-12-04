#ifndef _terminalcalc_hpp
#define _terminalcalc_hpp
#include "definecalc.hpp"
#include <termios.h>        // TCSANOW, ICONAN, ECHO, VTIME, VMIN, TCSADRIAN, ..getattr/setattr
#include <cstdio>			// p error
#include <unistd.h>			// read

namespace TermCalc
{
class Terminal {
	std::string * buffer;
public:
	Terminal(std::string * b)
	{
		this->buffer = b;
	}
	char getch() {
		/* I lost the link for it, i didn't write this function */
		char buf = 0;
		struct termios old = {0};
		if (tcgetattr(0, &old) < 0)
			perror("tcsetattr()");
		old.c_lflag &= ~ICANON;
		old.c_lflag &= ~ECHO;
		old.c_cc[VMIN] = 1;
		old.c_cc[VTIME] = 0;
		if (tcsetattr(0, TCSANOW, &old) < 0)
			perror("tcsetattr ICANON");
		if (read(0, &buf, 1) < 0)
			perror ("read()");
		old.c_lflag |= ICANON;
		old.c_lflag |= ECHO;
		if (tcsetattr(0, TCSADRAIN, &old) < 0)
			perror ("tcsetattr ~ICANON");
		return (buf);
	}
	void clear()
	{
		std::cout << "\r";
		for (int i = 0; i < this->buffer->size() + 2; ++i)
			std::cout << " ";
		std::cout << "\r";
	}
	void backspace()
	{
		if( this->buffer->size() == 0 ) return;
		this->buffer->resize( this->buffer->size() - 1 );
	}
	int capture()
	{
		char  c = 0
			, l;
		do
		{
			l = c;
			c = getch();
			switch( c )
			{
				case '\n':
					return 1;
				break;
				case 'q':
					if( l == 'q' ) continue;
					clear();
					std::cout << "\rType 'q' again to quit." << std::endl;
				break;
				case 0x7f:
					clear();
					backspace();
				break;
				case 'A':
				case 'B':
				case 'C':
				case 'D':
					if( l == '[' ) {
						clear();
						backspace();
						break;
					}
				default:
					if( isprint(c) ) {
						this->buffer->append<char>(1,c);
					}
			}
			std::cout << '\r' << *this->buffer << std::flush;
		} while( c != 'q' || l != 'q' );
		return 0;
	}
};
}
#endif