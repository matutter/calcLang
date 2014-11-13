#include <iostream>
#include <unistd.h>
#include <termios.h>
#include <cstdio>
#include <vector>
#include <string>

using namespace std;

namespace TermCalc
{
	class Terminal {
		string * buffer;

	public:
		Terminal(string * b)
		{
			this->buffer = b;
		}
		char getch() {
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

	void run( string cmd )
	{
		cout << endl;
		//cout << "cmd: " << cmd << endl;
	}

	void clear()
	{
		cout << "\r";
		for (int i = 0; i < this->buffer->size() + 2; ++i)
			cout << " ";
		cout << "\r";
	}

	void backspace()
	{
		if( this->buffer->size() == 0 ) return;
		this->buffer->resize( this->buffer->size() - 1 );
	}

	int capture()
	{
		//cout << "..." << endl;
		char  c = 0
			, l;
		vector<string> history;
		//history.push_back( string("") );
		//static vector<string>::iterator it = history.begin();


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
					cout << "\rType 'q' again to quit." << endl;
				break;

				case 0x7f:
					clear();
					backspace();
				break;

				default:
					if( l == '[' && c == 'A' )
					{
						clear();
						backspace();
						//if( it != history.end() -1 )
						//	it++;
					}
					else if( l == '[' && c == 'B' )
					{
						clear();
						backspace();
						//if( it != history.begin() )
						//	it--;	
					}
					else if( isprint(c) )
					{
						this->buffer->append<char>(1,c);
					}
			}
			cout << "\r" << *this->buffer << flush;
		} while( c != 'q' || l != 'q' );

		return 0;
	}

};
}
